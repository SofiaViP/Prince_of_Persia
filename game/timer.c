#include <lcom/lcf.h>
#include <timer.h>

int timer_hook_id = TIMER_IRQ;
uint8_t timer_count = 0;
static int frame_count = 0;

int (timer_subscribe_int)(uint8_t* bit_no){
    *bit_no = timer_hook_id;
    return sys_irqsetpolicy(TIMER_IRQ, IRQ_REENABLE, &timer_hook_id);
}

int (timer_unsubscribe_int)(){
    return sys_irqrmpolicy(&timer_hook_id);
}

void (timer_int_handler)(){
    timer_count++;

    switch (get_mode()){
    case MAIN_MENU:
        timer_count = 0;
        if(timer_count%(sys_hz()/30) == 0){
            draw_cursor();
        }
        break;
    case INSTRUCTIONS:
        if(timer_count%(sys_hz()/30) == 0){
            draw_cursor();
        }
        if (timer_count % (sys_hz() * 3) == 0){
            set_mode(GAME_1);
            timer_count = 0;
        }
        break;
    case GAME_1: case GAME_2: case GAME_3:
        if (timer_count % sys_hz() == 0){
            timer_count = 0;
        }
        if(timer_count%(sys_hz()/30) == 0){
            erase_prince();
            frame_count++;
            if(prince_action() == 0){
                draw_prince();
                draw_cursor();
            }
        }
        break;
    case FIGHT:
        if (timer_count % sys_hz() == 0){
            decrease_target();
            timer_count = 0;
        }
        if(timer_count%(sys_hz()/30) == 0){
            frame_count++;
            draw_prince();
            draw_thief();
            draw_target();
            draw_cursor_above();
            if(get_prince_hearts()==0){
                reset_game();
            }
        }
        if(frame_count==7){
            if(get_prince_state()!=R_STAND_FIGHT) set_prince_state(R_STAND_FIGHT);
            if(get_thief_state()!=L_STAND_FIGHT) set_thief_state(L_STAND_FIGHT);
        }
        if(frame_count==14){
            if(get_thief_hearts()==0){
                set_thief_state(DEAD);
                set_prince_state(R_STAND);
                set_mode(GAME_3);
            }
        }
        break;
    case HUG:
        if(timer_count%(sys_hz()/30) == 0){
            frame_count++;
            draw_cursor();
            }
        if (frame_count == 90){
            set_mode(SCOREBOARD);
        }
        break;
    case SCOREBOARD:
        if(timer_count%(sys_hz()/30) == 0){
            
        }
        break;
    default:
        break;
    }
    swap_buffers(0);
}

int (get_frame_count)(){
    return frame_count;
}

void (set_frame_count)(int new_frame_count){
    frame_count = new_frame_count;
}
