#include <lcom/lcf.h>
#include <map.h>

static xpm_image_t sprites[11];


static position_t map1[] = {
    {100, 400, 200, 400},
    {400, 400, 200, 400},
    {650, 500, 300, 200},
    {250, 573, 100, 54}
};

static position_t map2[] = {
    {150, 164, 300, 54},
    {600, 348, 400, 54},
    {400, 573, 800, 54},
    {700, 192, 200, 257}
};

static position_t map3[] = {
    {400,100,800,200},
    {400,500,800,200}
};

static position_t spikes_pos[] = {
    {249, 540, 48, 56},
    {349, 540, 48, 40}
};

static int map1_size = 4, map2_size = 4, map3_size = 2;

int (load_map)(){
  xpm_row_t* xpms[11] = {block_1, block_2, block_3, block_4, block_5, block_6, block_7, block_8, block_9, block_10, spikes};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 11; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    sprites[i] = img;
  }
  return 0;
}



int (erase_map)(){
    switch (get_mode()){
        case GAME_1:
            for (int i = 0; i < map1_size; i++){
                if (erase_xpm(sprites[i], map1[i].x - map1[i].width/2, map1[i].y - map1[i].height/2, 1)) return 1;
            }
            return 0;
         case GAME_2:
            for (int i = 0; i < map2_size; i++){
                if (erase_xpm(sprites[i + 4], map2[i].x - map2[i].width/2, map2[i].y - map2[i].height/2, 1)) return 1;
            }
            return 0;
        case GAME_3: case FIGHT: case HUG:
            for (int i = 0; i < map3_size; i++){
                if (erase_xpm(sprites[i + 8], map3[i].x - map3[i].width/2, map3[i].y - map3[i].height/2, 1)) return 1;
            }
            return 0;
        default:
            return 1;
        }
}

int (draw_map)(){
    switch (get_mode()){
        case GAME_1:
            for (int i = 0; i < map1_size; i++){
                if (draw_xpm(sprites[i], map1[i].x - map1[i].width/2, map1[i].y - map1[i].height/2, 1)) return 1;
            }
            if(draw_xpm(sprites[10], 225, 512, 1))return 1;
            return 0;
        case GAME_2:
            for (int i = 0; i < map2_size; i++){
                if (draw_xpm(sprites[i + 4], map2[i].x - map2[i].width/2, map2[i].y - map2[i].height/2, 1)) return 1;
            }
            return draw_xpm(sprites[10], 325, 512, 1); 
            return 0;
        case GAME_3: case FIGHT: case HUG:
            for (int i = 0; i < map3_size; i++){
                if (draw_xpm(sprites[i + 8], map3[i].x - map3[i].width/2, map3[i].y - map3[i].height/2, 1)) return 1;
            }
            return 0;
        default:
            return 1;
        }
}

position_t* (get_map)(int *size){
    switch (get_mode()){
    case GAME_1:
        *size = map1_size;
        return map1;
    case GAME_2:
        *size = map2_size;
        return map2;
    case GAME_3: case FIGHT: case HUG:
        *size = map3_size;
        return map3;
    default:
        break;
    }
    return 0;
}

void (set_start_pos)(position_t* pos){
    switch (get_mode()){
    case GAME_1:
        pos->x = 20;
        pos->y = 150; 
        break;
    case GAME_2:
        pos->x = 20;
        pos->y = 100; 
        break;
    case GAME_3:
        pos->x = 20;
        pos->y = 350; 
    default:
        break;
    }
}

/*int (draw_spikes)(){
    switch (get_mode()){
    case GAME_1:
        return draw_xpm(sprites[10], 225, 512, 1);
    case GAME_2:
        return draw_xpm(sprites[10], 325, 512, 1); 
    default:
        return 0;
    }
}*/

int (erase_spikes)(){
    switch (get_mode()){
    case GAME_1:
        return erase_xpm(sprites[10], 225, 512, 1);
    case GAME_2:
        return erase_xpm(sprites[10], 325, 512, 1); 
    default:
        return 0;
    }
}

position_t (get_spikes)(){
    
    switch (get_mode()){
        case GAME_1:
            return spikes_pos[0];
        case GAME_2:
            return spikes_pos[1]; 
        default:{
            position_t default_pos;
            default_pos.x = 1;
            default_pos.y = 1;
            default_pos.width = 1;
            default_pos.height = 1;
            return default_pos;
        }
    }
}
