#include <lcom/lcf.h>
#include <video_gr.h>

static uint8_t *video_mem;		/* Process (virtual) address to which VRAM is mapped */
static uint8_t *first_buffer;	
static uint8_t *second_buffer;	

static unsigned h_res;	        /* Horizontal resolution in pixels */
static unsigned v_res;	        /* Vertical resolution in pixels */
static unsigned bits_per_pixel;
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel */
static unsigned int vram_base;
static unsigned int vram_size;

static bool indexed_mode;

static uint8_t RedMaskSize, RedPos;
static uint8_t GreenMaskSize, GreenPos;
static uint8_t BlueMaskSize, BluePos;

unsigned (get_h_res)(){
  return h_res;
}

unsigned (get_v_res)(){
  return v_res;
}

void *(vg_init)(uint16_t mode){
  vbe_mode_info_t vmi_p;
  if (vbe_get_mode_info(mode, &vmi_p)) return NULL;

  indexed_mode = (mode == INDEXED_MODE);

  RedMaskSize = vmi_p.RedMaskSize;
  GreenMaskSize = vmi_p.GreenMaskSize;
  BlueMaskSize = vmi_p.BlueMaskSize;

  RedPos = vmi_p.RedFieldPosition;
  GreenPos = vmi_p.GreenFieldPosition;
  BluePos = vmi_p.BlueFieldPosition;

  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bits_per_pixel = vmi_p.BitsPerPixel;

  struct minix_mem_range mr;
  bytes_per_pixel = ceil(bits_per_pixel / 8.0);
  vram_base = vmi_p.PhysBasePtr;
  vram_size = h_res * v_res * bytes_per_pixel;
  int r;				    

/* Allow memory mapping */

  mr.mr_base = (phys_bytes)vram_base;	
  mr.mr_limit = mr.mr_base + vram_size;  

  if( OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr))){
    panic("sys_privctl (ADD_MEM) failed: %d\n", r);
    return NULL;
  }

/* Map memory */

  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  first_buffer = (uint8_t*) malloc (vram_size);
  second_buffer = (uint8_t*) malloc (vram_size);

  if(video_mem == MAP_FAILED){
    panic("couldn't map video memory");
    return NULL;
  }

  reg86_t r86;
  memset(&r86, 0, sizeof(r86));
  r86.ah = AH_REG;
  r86.al = AL_SET_VBE_MODE;
  r86.bx = BIT(14)|mode;
  r86.intno = 0x10;

  if( sys_int86(&r86) != OK ) {
    printf("set_vbe_mode: sys_int86() failed \n");
    return NULL;
  }

  return video_mem;
}

// buffer = 0 -> second_buffer | buffer = 1 -> first_buffer
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color, bool buffer){
  if(x > get_h_res() || y > get_v_res()) return 0;
  if (buffer){
    void* pos1 = (first_buffer + (y*h_res + x)*bytes_per_pixel);
    if (memcpy(pos1, &color, bytes_per_pixel) == NULL) return 1;
  }
  else {
    void* pos2 = (second_buffer + (y*h_res + x)*bytes_per_pixel);
    if (memcpy(pos2, &color, bytes_per_pixel) == NULL) return 1;
  }
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color){
  for (unsigned i = 0; i < len; i++){
    if (vg_draw_pixel(x + i, y, color, 1)) return 1;
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color){
  for (unsigned i = 0; i < height; i++){
    if(vg_draw_hline(x, y + i, width, color)) return 1;
  }
  return 0;
}

int (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y, bool buffer){
    if (x > h_res || y > v_res || x < 0 || y < 0) return 1;

    uint32_t color = 0;
    uint16_t width = ((x + img.width) > h_res)? h_res - x : img.width;
    uint16_t height = ((y + img.height) > v_res)? v_res - y : img.height;
    
    for (uint16_t row = 0; row < height; row++){
        for (uint16_t col = 0; col < width; col++){

            uint8_t* color_address = img.bytes + (img.width * row + col) * bytes_per_pixel;
            memcpy(&color, color_address, bytes_per_pixel);
            
            if (color == xpm_transparency_color(img.type)) continue;

            if (vg_draw_pixel(col+x, row+y, color, buffer)) return 1;
        }
    }
    return 0;
}

int (erase_xpm)(xpm_image_t img, uint16_t x, uint16_t y, bool buffer){
    uint32_t transparency = TRANSPARENCY_COLOR_8_8_8_8;
    uint32_t color = 0;
    for (uint16_t row = 0; row < img.height; row++){
        for (uint16_t col = 0; col < img.width; col++){

            uint8_t* color_address = img.bytes + (img.width * row + col) * bytes_per_pixel;
            memcpy(&color, color_address, bytes_per_pixel);

            if (color == xpm_transparency_color(img.type)) continue;

            if (vg_draw_pixel(col+x, row+y, transparency, buffer)) return 1;
        }
    }
    return 0;
}

void (swap_buffers)(bool buffer){
  if (buffer) memcpy(second_buffer, first_buffer, vram_size);
  else memcpy(video_mem, second_buffer, vram_size);
}

