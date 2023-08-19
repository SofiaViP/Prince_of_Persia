#include <lcom/lcf.h>
#include <prince.h>

static xpm_image_t sprites[18];
static position_t prince_pos = {20, 150, 20, 80};
static state_t prince_state = R_FALL;
static uint8_t hearts = 5;
static int y_speed = 0;
static int jump_frame = 0;

int (load_prince_sprites)(){
  xpm_row_t* xpms[18] = {heart, l_stand, l_half_run, l_run, l_start_jump, l_jump, l_end_jump, l_fall, r_stand, r_half_run, r_run, r_start_jump, r_jump, r_end_jump, r_fall, r_stand_fight, r_fight, spikes_dead};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 18; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}

position_t (get_prince_position)(){
  return prince_pos;
}

void (set_prince_position)(int x, int y){
  prince_pos.x = x;
  prince_pos.y = y;
}

state_t (get_prince_state)(){
  return prince_state;
}

uint8_t (get_prince_hearts)(){
  return hearts;
}

int (get_sprite)(){
  switch (prince_state){
  case L_STAND:
    return 1;
  case L_RUN:
    return (get_frame_count() / 4) % 2 == 0 ? 2 : 3; // Alternating between sprites every 4 frames
    //return 3;
  case L_JUMP:
    if(get_frame_count() - jump_frame < 4){
      return 4;
    }
    else if(get_frame_count() - jump_frame < 12){
      return 5;
    }
    else if(get_frame_count() - jump_frame < 16){
      return 6;
    }
  case L_FALL:
    return 7;
  case R_STAND:
    return 8;
  case R_RUN:
    return (get_frame_count() / 4) % 2 == 0 ? 9 : 10; // Alternating between sprites every 4 frames
    //return 10;
  case R_JUMP:
    if(get_frame_count() - jump_frame < 6){
      return 11;
    }
    else if(get_frame_count() - jump_frame < 18){
      return 12;
    }
    else if(get_frame_count() - jump_frame < 24){
      return 13;
    }
  case R_FALL:
    return 14;
  case R_STAND_FIGHT:
    return 15;
  case R_FIGHT:
    return 16;
  case DEAD: 
    return 17;
  default:
    return -1;
  }
}

int (erase_prince)(){
  if (prince_state != CHANGE) return erase_xpm(sprites[get_sprite()], prince_pos.x - (prince_pos.width/2), prince_pos.y - (prince_pos.height/2), 1);
  return 0;
}

int (set_prince_state)(state_t ps){
  erase_prince();
  switch (ps){
    case R_STAND_FIGHT:
      prince_pos.y=399-prince_pos.height/2+6;
      prince_pos.x=300;
      break;
    case R_FIGHT:
      prince_pos.y=399-prince_pos.height/2+20;
      prince_pos.x=325;
      break;
    case R_STAND:
      prince_pos.y=399-prince_pos.height/2;
      break;
    default:
      break;
  }
  prince_state=ps;
  return 0;    
}

int (draw_prince)(){
  draw_xpm(sprites[get_sprite()], prince_pos.x - (prince_pos.width/2), prince_pos.y - (prince_pos.height/2), 1);
  return 0;
}


int (change_prince)(int8_t delta_x, int8_t delta_y){
  xpm_image_t sprite = sprites[get_sprite()];
  position_t next_pos = {prince_pos.x + delta_x, prince_pos.y + delta_y, (prince_state == R_RUN || prince_state == L_RUN)? 62 : sprite.width, prince_pos.height};
  
  position_t spikes = get_spikes();
  collision_data_t col_spikes = check_collision(next_pos, spikes);
  if(col_spikes.collision){
    prince_state = DEAD;
    sprite = sprites[get_sprite()];
    erase_spikes();
    prince_pos.x = spikes.x - 12;
    prince_pos.y = spikes.y + 12;
    prince_pos.width = sprite.width;
    prince_pos.width = sprite.width;

    hearts = 0;
    erase_prince_hearts();

    set_frame_count(0);
    return 0;
  }

  int map_size;
  position_t* map = get_map(&map_size);
    
  for(int i = 0; i < map_size; i++){
      collision_data_t col = check_collision(next_pos, map[i]);
      if (col.collision){
        draw_map();
        erase_prince_hearts();
        draw_prince_hearts();
        if(prince_state == R_FALL || prince_state == L_FALL){
          prince_pos.y = next_pos.y + col.y_offset;
        }
        else{
          prince_pos.x = next_pos.x + col.x_offset;
        }
        switch(prince_state){
          case R_FALL:
            prince_pos.x += 10;
            prince_state = R_STAND;
            break;
          case R_RUN: 
            prince_state = R_STAND;
            break;
           case L_FALL:
            prince_pos.x -= 10;
          case L_RUN:
            prince_state = L_STAND;
            break;
          case R_JUMP:
            prince_pos.x -= 10;
            prince_state = R_FALL;
            break;
          case L_JUMP:
            prince_pos.x += 10;
            prince_state = L_FALL;
            break;
          default:
            break;
        }
        if(y_speed > 30){ 
          prince_decrease_hearts();
        }
        y_speed = 0;
        return 0;
      }
  }

  if (next_pos.x < next_pos.width/2.0){
    prince_state = L_STAND;
    return 0;
  }

  prince_pos = next_pos;
  if (prince_pos.x >= ((int)get_h_res() + prince_pos.width/2)){
    prince_state = CHANGE;
    return 0;
  }

  if(prince_state != R_FALL && prince_state != L_FALL && prince_state != R_JUMP && prince_state != L_JUMP){
    position_t fall_pos = {(delta_x > 0)? prince_pos.x : prince_pos.x - 20, prince_pos.y + 15, 20, prince_pos.height};
    for(int i = 0; i < map_size; i++){
        collision_data_t col = check_collision(fall_pos, map[i]);
        if (col.collision){
          return 0;
        }
    }
    if(prince_state == R_RUN || prince_state == R_STAND){
      erase_prince();
      prince_pos.x += 15;
      prince_state = R_FALL;
    }
    else{
      erase_prince();
      prince_pos.x -= 25;
      prince_state = L_FALL;
    }
  }

  return 0;
}

collision_data_t (check_collision)(position_t pos1, position_t pos2) {
    collision_data_t collision_data;
    
    // Calculate the boundaries of each rectangle
    int pos1_left = pos1.x - pos1.width / 2;
    int pos1_right = pos1.x + pos1.width / 2;
    int pos1_top = pos1.y - pos1.height / 2;
    int pos1_bottom = pos1.y + pos1.height / 2;

    int pos2_left = pos2.x - pos2.width / 2;
    int pos2_right = pos2.x + pos2.width / 2;
    int pos2_top = pos2.y - pos2.height / 2;
    int pos2_bottom = pos2.y + pos2.height / 2;

    // Check for collision
    bool collision = !(pos1_right <= pos2_left || pos1_left >= pos2_right ||
                       pos1_bottom <= pos2_top || pos1_top >= pos2_bottom);
    
    collision_data.collision = collision;

    if (collision) {
        // Calculate the distance needed to move in the x and y directions
        int x_offset = 0;
        int y_offset = 0;

        if (pos1_right >= pos2_left && pos1_left <= pos2_right) {
            // Collision in the x direction
            if (pos1.x < pos2.x) {
                // Move position 1 to the left
                x_offset = pos2_left - pos1_right;
            } else {
                // Move position 1 to the right
                x_offset = pos2_right - pos1_left;
            }
        }

        if (pos1_bottom >= pos2_top && pos1_top <= pos2_bottom) {
            // Collision in the y direction
            if (pos1.y < pos2.y) {
                // Move position 1 upwards
                y_offset = pos2_top - pos1_bottom;
            } else {
                // Move position 1 downwards
                y_offset = pos2_bottom - pos1_top;
            }
        }
        
        // Adjust offsets if there is only a touch but no overlap
        if (x_offset == 0) {
            if (pos1_right == pos2_left)
                x_offset = -1; // Adjusting x_offset to indicate touch but no overlap
            else if (pos1_left == pos2_right)
                x_offset = 1; // Adjusting x_offset to indicate touch but no overlap
        }

        if (y_offset == 0) {
            if (pos1_bottom == pos2_top)
                y_offset = -1; // Adjusting y_offset to indicate touch but no overlap
            else if (pos1_top == pos2_bottom)
                y_offset = 1; // Adjusting y_offset to indicate touch but no overlap
        }
        
        collision_data.x_offset = x_offset;
        collision_data.y_offset = y_offset;
    } else {
        collision_data.x_offset = 0;
        collision_data.y_offset = 0;
    }

    return collision_data;
}

int (change_prince_state)(uint8_t scancode){ //controller
  switch (prince_state){
    //RIGHT
    case R_STAND:
      if(scancode == RIGHT_MAKE){
        erase_prince();
        prince_state = R_RUN;
      }
      else if (scancode == LEFT_MAKE){
        erase_prince();
        prince_state = L_RUN;
      } 
      break;
    case R_RUN:
      if(scancode == RIGHT_BREAK){
        erase_prince();
        prince_state = R_STAND;
      } 
      else if(scancode == UP_MAKE){
        erase_prince();
        prince_pos.y -= 30;
        jump_frame = get_frame_count();
        prince_state = R_JUMP;
      }
      break;
    case R_FALL: case R_JUMP:
      break;
    //LEFT
    case L_STAND:
      if(scancode == LEFT_MAKE){
        erase_prince();
        prince_state = L_RUN;
      }
      else if (scancode == RIGHT_MAKE){
        erase_prince();
        prince_state = R_RUN;
      } 
      break;
    case L_RUN:
      if(scancode == LEFT_BREAK){
        erase_prince();
        prince_state = L_STAND;
      }
      else if(scancode == UP_MAKE){
        erase_prince();
        prince_pos.y -= 30;
        jump_frame = get_frame_count();
        prince_state = L_JUMP;
      }
      break;
    case L_FALL:case L_JUMP:
      break;
  
    default:
      return 1;
  }
  return 0;
}

int (prince_action)(){
  switch(prince_state){
    case R_STAND:  //não altera o model só fica parado
      break;
    case R_RUN:
      change_prince(8, 0);
      break;
    case R_FALL:
      y_speed += 2;
      change_prince(2, y_speed);
      break;
    case R_JUMP:
      if(get_frame_count() - jump_frame < 4){
        change_prince(8, -4);
      }
      else if(get_frame_count() - jump_frame < 8){
       change_prince(8, -2);
      }
      else if(get_frame_count() - jump_frame < 12){
        change_prince(8, 2);
      }
      else if(get_frame_count() - jump_frame < 16){
        change_prince(8, 4);
      }
      else{
        prince_state = R_FALL;
      }
      break;
    
    //LEFT
    case L_STAND: //não altera o model só fica parado
      break;
    case L_RUN:
      change_prince(-8, 0);
      break;
    case L_FALL: 
      y_speed += 2;
      change_prince(-2, y_speed);
      break;

    case L_JUMP:
      if(get_frame_count() - jump_frame < 4){
        change_prince(-8, -4);
      }
      else if(get_frame_count() - jump_frame < 8){
       change_prince(-8, -2);
      }
      else if(get_frame_count() - jump_frame < 12){
        change_prince(-8, 2);
      }
      else if(get_frame_count() - jump_frame < 16){
        change_prince(-8, 4);
      }
      else{
        prince_state = L_FALL;
      }

      break;

    case CHANGE:
      switch (get_mode()){
        case GAME_1: set_mode(GAME_2);
        break;
        case GAME_2: set_mode(GAME_3);
        break;
        default:
        break;
      }
      set_start_pos(&prince_pos);
      prince_state = R_FALL;
      break;

    case DEAD:
    if(get_frame_count() == 60){
      reset_game();
      return 1;
    }

    default:
      return 0;
  } 
  return 0;
}

int (draw_prince_hearts)(){
  xpm_image_t heart = sprites[0];
  for (uint8_t h = 0; h < hearts; h++){
    if (draw_xpm(heart, 5 + (heart.width + 5) * h, get_v_res() - heart.height - 5, 1)) return 1;
  }
  return 0;
}

int (erase_prince_hearts)(){
  xpm_image_t heart = sprites[0];
  for (uint8_t h = 0; h < 5; h++){
    if (erase_xpm(heart, 5 + (heart.width + 5) * h, get_v_res() - heart.height - 5, 1)) return 1;
  }
  return 0;
}

int (prince_decrease_hearts)(){
  if(hearts>0){
    erase_prince_hearts();
    hearts--;
    draw_prince_hearts();
  }
  return hearts;
}

void (reset_prince)(){
  prince_pos.x = 20; 
  prince_pos.y = 150;
  prince_pos.width = 20;
  prince_pos.height = 80;
  prince_state = R_FALL;
  y_speed = 0;
  hearts = 5;
}
