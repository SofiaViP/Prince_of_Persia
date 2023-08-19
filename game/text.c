#include <lcom/lcf.h>
#include <text.h>

static xpm_image_t sprites[5];

int (load_text)(){
  xpm_row_t* xpms[5] = {princeMenu, instructions, scoreboard, scoreboardYourScore, scoreboardEnter};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 5; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}

int (erase_main_menu)(){
  return erase_xpm(sprites[0], 25, 175, 1);
}

int (draw_main_menu)(){
  return draw_xpm(sprites[0], 25, 175, 1);
}

int (erase_instructions)(){
  return erase_xpm(sprites[1],0, 0, 1);
}

int (draw_instructions)(){
  return draw_xpm(sprites[1], 0, 0, 1);
}

int (erase_scoreboard)(){
  if(erase_xpm(sprites[2], 216, 0, 1)) return 1;
  if(erase_xpm(sprites[3], 110, 140, 1)) return 1;
  if(erase_xpm(sprites[4], 200, get_v_res()- 80, 1)) return 1;
  if(erase_score()) return 1;
  return 0;
}

int (draw_scoreboard)(){
  if(draw_xpm(sprites[2], 216, 0, 1)) return 1;
  if(draw_xpm(sprites[3], 110, 140, 1)) return 1;
  if(draw_xpm(sprites[4], 200, get_v_res()- 80, 1)) return 1;
  if(draw_score()) return 1;
  return 0;
  return erase_xpm(sprites[2], 216, 0, 1);
}
