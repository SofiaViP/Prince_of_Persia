#include <lcom/lcf.h>
#include <thief.h>

static xpm_image_t sprites[3];
static position_t thief_pos = {500, 361, 58, 78};
static state_t thief_state = L_STAND_FIGHT;
static uint8_t hearts = 5;


int (load_thief_sprites)(){
  xpm_row_t* xpms[3] = {thief_heart, l_stand_fight, l_fight};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 3; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}

position_t (get_thief_position)(){
  return thief_pos;
}

state_t (get_thief_state)(){
  return thief_state;
}

int set_thief_state(state_t ts){
  erase_thief();
  switch (ts){
    case L_STAND_FIGHT:
      thief_pos.y=399-thief_pos.height/2+1;
      thief_pos.x=500;
      break;
    case L_FIGHT:
      thief_pos.y=399-thief_pos.height/2+15;
      thief_pos.x=440;
      break;
    default:
      break;
  }
  thief_state=ts;
  return 0;  
}

int (get_thief_sprite)(){
  switch (thief_state){
  case L_STAND_FIGHT:
    return 1;
  case L_FIGHT:
    return 2;
  default:
    return -1;
  }
}

uint8_t (get_thief_hearts)(){
  return hearts;
}

int (erase_thief)(){
  return erase_xpm(sprites[get_thief_sprite()], thief_pos.x -  (thief_pos.width/2), thief_pos.y - (thief_pos.height/2), 1);
}

int (draw_thief)(){
  if(thief_state!=DEAD){
    draw_xpm(sprites[get_thief_sprite()], thief_pos.x -  (thief_pos.width/2), thief_pos.y - (thief_pos.height/2), 1);
  }
  return 0;    
}

int (draw_thief_hearts)(){
  xpm_image_t heart = sprites[0];
  for (uint8_t h = 0; h < hearts; h++){
    if (draw_xpm(heart, get_h_res() - 5 - (heart.width + 5) * (h + 1), get_v_res() - heart.height - 5, 1)) return 1;
  }
  return 0;
}

int (erase_thief_hearts)(){
  xpm_image_t heart = sprites[0];
  for (uint8_t h = 0; h < 5; h++){
    if (erase_xpm(heart, get_h_res() - 5 - (heart.width + 5) * (h + 1), get_v_res() - heart.height - 5, 1)) return 1;
  }
  return 0;
}

int (thief_decrease_hearts)(){
  if(hearts>0){
  erase_thief_hearts();
  hearts--;
  draw_thief_hearts();    
  }
  return hearts;
}

void reset_thief(){
  thief_state = L_STAND_FIGHT;
  hearts = 5;
}
