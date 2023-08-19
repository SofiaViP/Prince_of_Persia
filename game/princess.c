#include <lcom/lcf.h>
#include <princess.h>

static xpm_image_t sprites[2];
static position_t princess_pos = {650, 361, 33, 82};
static state_t princess_state = L_STAND;

int (load_princess_sprites)(){
  xpm_row_t* xpms[2] = {princess, hug};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 2; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}

int (get_princess_sprite)(){
  switch (princess_state){
  case L_STAND:
    return 0;
  case L_JUMP:
    return 1;
  default:
    return -1;
  }
}

position_t (get_princess_position)(){
  return princess_pos;
}

int (set_princess_state)(state_t new_state){
    princess_state = new_state;
    return 0;
}

int (erase_princess)(){
    return erase_xpm(sprites[get_princess_sprite()], princess_pos.x -  (princess_pos.width/2), princess_pos.y - (princess_pos.height/2), 1);
}

int (draw_princess)(){
    return draw_xpm(sprites[get_princess_sprite()], princess_pos.x -  (princess_pos.width/2), princess_pos.y - (princess_pos.height/2), 1);
}

void (reset_princess)(){
  princess_state = L_STAND;
}
