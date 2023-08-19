#include <lcom/lcf.h>
#include <mouse.h>

int mouse_hook_id = MOUSE_IRQ;
static uint8_t curr_byte, byte_num;
// uint8_t status;

movement_t move = MOUSE_OTHER;
mouse_state_t state = INIT;
//static int8_t x = 0, y = 0;

struct packet pp;
static xpm_image_t cursor_xpm;
static position_t cursor_pos = {400, 300, 11, 16};


int (mouse_subscribe_int)(uint8_t* bit_no){
    *bit_no = mouse_hook_id;
    return sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int (mouse_unsubscribe_int)(){
    return sys_irqrmpolicy(&mouse_hook_id);
}

int (mouse_enable_data_report)(){
    uint8_t result;
    while (1){
        if (issue_command(KBC_ST_REG, MOUSE_CMD_BYTE)) return 1;
        if (issue_command(WRITE_CMD_BYTE, ENABLE_CMD)) return 1;
        if (utils_sys_inb(KBC_OUT_BUF, &result)) return 1;
        if (result == MOUSE_ACK) return 0;
        if (result == MOUSE_NACK || result == MOUSE_ERROR) return 1;
    }
}

int (mouse_disable_data_report)(){
    uint8_t result;
    while (1){
        if (issue_command(KBC_ST_REG, MOUSE_CMD_BYTE)) return 1;
        if (issue_command(WRITE_CMD_BYTE, DISABLE_CMD)) return 1;
        if (utils_sys_inb(KBC_OUT_BUF, &result)) return 1;
        if (result == MOUSE_ACK) return 0;
        if (result == MOUSE_NACK || result == MOUSE_ERROR) return 1;
    }
}

void (mouse_ih)(){
    if (read_outbuff(&curr_byte)) return;
   
    if (parse_packet(byte_num, &pp)) return;

    if (byte_num == 2){
        byte_num = 0;

        if (pp.delta_x != 0 || pp.delta_y != 0){

            cursor_pos.x += pp.delta_x;
            cursor_pos.y -= pp.delta_y;

            if (cursor_pos.x > (int)(get_h_res()-11)) cursor_pos.x = (int)(get_h_res()-11);
            if (cursor_pos.x < 0) cursor_pos.x = 0;
            if (cursor_pos.y > (int)(get_v_res()-16)) cursor_pos.y = (int)(get_v_res()-16);
            if (cursor_pos.y < 0) cursor_pos.y = 0;
        }

        if(get_mode()==FIGHT){
            parse_movement(pp);
            change_mouse_state(move);

            if(state==HIT && !(get_target_color())){
                set_prince_state(R_FIGHT);
                if(thief_decrease_hearts()){
                    randomize_target();
                }else set_frame_count(0);

                state=INIT;
                
            }
            else if(state==MISS && get_target_color()){
                set_thief_state(L_FIGHT);
                if(prince_decrease_hearts()){
                    randomize_target();
                } else set_frame_count(0);
                state=INIT;
            } 
            else if(state==HIT || state==MISS){
                randomize_target();
                state=INIT;
            }
        }

    }
    else byte_num++;
}

int (parse_packet)(uint8_t byte_num, struct packet* pp){
    if (byte_num == 0){
        if (curr_byte & BIT(3)){
            pp->bytes[byte_num] = curr_byte;
            pp->y_ov = curr_byte & BIT(7);
            pp->x_ov = curr_byte & BIT(6);
            pp->delta_y = (curr_byte & BIT(5)) ? 0xFF00 : 0x0000;
            pp->delta_x = (curr_byte & BIT(4)) ? 0xFF00 : 0x0000;
            pp->mb = curr_byte & BIT(2);
            pp->rb = curr_byte & BIT(1);
            pp->lb = curr_byte & BIT(0);
            return 0;
        }
    }
    else if (byte_num == 1){
        pp->bytes[byte_num] = curr_byte;
        pp->delta_x |= curr_byte;
        return 0;
    }
    else if (byte_num == 2){
        pp->bytes[byte_num] = curr_byte;
        pp->delta_y |= curr_byte;
        return 0;
    }
    return 1;
}

int (parse_movement)(struct packet pp) {
    position_t pos= get_target_pos();

    if (pp.lb && !pp.mb && !pp.rb) {
        if (!(get_target_color()) && is_inside_target(cursor_pos.x, cursor_pos.y, pos.x, pos.y, pos.height/2)) {
            move=CORRECT_CLICK;
        }
        else{
            move=WRONG_CLICK;
        }
    }

    else if(!pp.lb && !pp.mb && pp.rb){
        if (get_target_color() && is_inside_target(cursor_pos.x, cursor_pos.y, pos.x, pos.y, pos.height/2)) {
            move=CORRECT_CLICK;
        }
        else {
            move=WRONG_CLICK;
        }
    }

    else if(pp.lb && pp.mb) move=WRONG_CLICK;

    else if(!pp.lb && !pp.mb && !pp.rb){
        if(is_inside_target(cursor_pos.x, cursor_pos.y, pos.x, pos.y, pos.height/2)){
            move=CORRECT_NO_CLICK;
        }
        else move= WRONG_NO_CLICK;
    }

    else {
        move = MOUSE_OTHER;
    }

    return 0;
}

bool (is_inside_target)(uint8_t x, uint8_t y, uint8_t center_x, uint8_t center_y, uint8_t radius) {
    int dx = x - center_x;
    int dy = y - center_y;
    int distance_squared = dx * dx + dy * dy;
    int radius_squared = radius * radius;

    return distance_squared <= radius_squared;
}



int (change_mouse_state)(){
    switch (state){
    case INIT:
        if (move == CORRECT_CLICK) state = GOOD_CLICK;
        else if (move == WRONG_CLICK) state = BAD_CLICK;
        break;
    case GOOD_CLICK:
        if (move == CORRECT_CLICK) break;
        else if (move == CORRECT_NO_CLICK) state = HIT;
        else state = INIT;
        break;
    case BAD_CLICK:
        if (move == WRONG_CLICK) break;
        state = MISS;
        break;
    case MISS:
        state= INIT;
        break;
    case HIT:
        state= INIT;
        break;
    default:
        return 1;
    }
    return 0;
}

int (load_cursor)(){
    uint8_t* sprite;
    sprite = xpm_load(cursor, XPM_8_8_8, &cursor_xpm);
    if (sprite == NULL) return 1; 
    return 0;
}

int (erase_cursor)(){
    if (erase_xpm(cursor_xpm, cursor_pos.x, cursor_pos.y, 0)) return 1;
    return 0;
}

int (draw_cursor)(){
    swap_buffers(1);
    if (draw_xpm(cursor_xpm, cursor_pos.x, cursor_pos.y, 0)) return 1;
    return 0;
}


int (draw_cursor_above)(){
    if (draw_xpm(cursor_xpm, cursor_pos.x, cursor_pos.y, 0)) return 1;
    return 0;
}

