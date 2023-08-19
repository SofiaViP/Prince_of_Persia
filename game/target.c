#include <lcom/lcf.h>
#include <target.h>

static xpm_image_t sprites[10];
static position_t target_pos = {0, 0, 80, 80};
static bool color; //1 -> red | 2-> blue
static int size = 4;


int (load_target_sprites)(){
  xpm_row_t* xpms[10] = {red_1, red_2, red_3, red_4, red_5, blue_1, blue_2, blue_3, blue_4, blue_5};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 10; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}

position_t (get_target_pos)(){
  return target_pos;
}

bool (get_target_color)(){
  return color;
}

int (erase_target)(){
  return erase_xpm(sprites[(5 * color) + size], target_pos.x -  (target_pos.width/2), target_pos.y - (target_pos.height/2), 0);
}

int (draw_target)(){
  swap_buffers(1);
  return draw_xpm(sprites[(5 * color) + size], target_pos.x -  (target_pos.width/2), target_pos.y - (target_pos.height/2), 0);
  return 0;
}

int (decrease_target)(){
  erase_target();
  if(size>0){
    size--;
    xpm_image_t target=sprites[(5 * color) + size];
    target_pos.height= target.height;
    target_pos.width= target.width;
  } 
  else{
    if(get_target_color()){
      prince_decrease_hearts();
      set_thief_state(L_FIGHT);
    }
    randomize_target();
  }
  return 0;
}


int (randomize_target)(){
  size = 4;
  xpm_image_t target=sprites[(5 * color) + size];
  target_pos.height= target.height;
  target_pos.width= target.width;
  target_pos.x = (rand() % (get_h_res() - 160)) + 80;
  target_pos.y = (rand() % (get_v_res() - 160)) + 80;
  color = rand() % 2;
  set_frame_count(0);
  return 0;
}
