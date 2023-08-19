#include <lcom/lcf.h>
#include <state.h>

static game_mode_t mode = MAIN_MENU;

void (set_mode)(game_mode_t new_mode){
  switch (mode){
  case MAIN_MENU:
    erase_main_menu();
    erase_cursor();
    break;
  case INSTRUCTIONS:
    erase_instructions();
    erase_cursor();
    break;
  case GAME_1: case GAME_2:
    erase_map();
    erase_spikes();
    erase_prince();
    erase_timer();
    erase_cursor();
    break;
  case GAME_3:
    erase_map();
    erase_prince();
    erase_thief();
    erase_princess();
    erase_timer();
    erase_cursor();
    break;
  case FIGHT:
    erase_map();
    erase_prince();
    erase_prince_hearts();
    erase_thief();
    erase_princess();
    erase_thief_hearts();
    erase_timer();
    erase_cursor();
    break;
  case HUG:
    erase_map();
    erase_princess();
    erase_cursor();
    break;
  case SCOREBOARD:
    erase_scoreboard();
    break;
  default:
    break;
  }

  mode = new_mode;

  switch (new_mode){
  case MAIN_MENU:
    draw_main_menu();
    draw_cursor();
    break;
  case INSTRUCTIONS:
    draw_instructions();
    draw_cursor();
    break;
  case GAME_1: case GAME_2:
    draw_map();
    draw_timer(1);
    erase_prince_hearts();
    draw_prince_hearts();
    draw_prince();
    draw_cursor();
    break;
  case GAME_3:
    draw_map();
    draw_timer(1);
    erase_prince_hearts();
    draw_prince_hearts();
    draw_prince();
    draw_princess();
    draw_thief();
    draw_cursor();
    break;
  case FIGHT:
    set_prince_state(R_STAND_FIGHT);
    draw_map();
    draw_timer(1);
    erase_prince_hearts();
    draw_prince_hearts();
    draw_thief_hearts();
    draw_prince();
    draw_princess();
    draw_thief();
    draw_cursor();
    break;
  case HUG:
    set_princess_state(L_JUMP);
    draw_map();
    draw_princess();
    draw_cursor();
    break;
  case SCOREBOARD:
    setUpScoreboard(getTimer(),get_prince_hearts(),getCurrentDateTime());
    draw_scoreboard();
    draw_cursor();
    break;
  default:
    break;
  }
}

game_mode_t (get_mode)(){
  return mode;
}

void reset_game(){
  set_mode(MAIN_MENU);
  reset_prince();
  reset_thief();
  reset_time();
  reset_princess();
}
