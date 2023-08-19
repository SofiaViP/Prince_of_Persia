#include <lcom/lcf.h>
#include <kbd.h>

int hook_id = KBD_IRQ, i = 0;
uint8_t scancode;
uint8_t a[2] = {0};

int (kbd_subscribe_int)(uint8_t* bit_no){
    *bit_no = hook_id;
    return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &hook_id);
}

int (kbd_unsubscribe_int)(){
    return sys_irqrmpolicy(&hook_id);
}

void (kbc_ih)(){
    if (read_outbuff(&scancode)) return;
    a[i] = scancode;
    if (i == 0 && scancode == FIRST_BYTE) i = 1;
    else i = 0;
    switch (get_mode()){
    case MAIN_MENU:
        if (scancode == ENTER_BREAK) {
            set_mode(INSTRUCTIONS);
            }
        break;
    case GAME_1:
        if (scancode != FIRST_BYTE)
            change_prince_state(scancode);
        break;
    case GAME_2:
        if (scancode != FIRST_BYTE)
            change_prince_state(scancode);
        break;
    case GAME_3:
        if (scancode != FIRST_BYTE)
            change_prince_state(scancode);
        if ((get_thief_position().x-get_prince_position().x)<200 && get_thief_state()!=DEAD){
            set_mode(FIGHT);
        }
        if ((get_princess_position().x-get_prince_position().x<70)){
            erase_prince();
            set_frame_count(0);
            set_mode(HUG);
        }
        break;
    case SCOREBOARD:
        if(scancode == ENTER_BREAK){
            reset_game();
        }
        break;
    default:
        break;
    }
}

int (kbc_enable_int)(){
    uint8_t cmd;
    if (issue_command(KBC_CMD_REG, READ_CMD_BYTE)) return 1;
    if (read_outbuff(&cmd)) return 1;
    cmd |= BIT(0);
    if (issue_command(KBC_CMD_REG, WRITE_CMD_BYTE)) return 1;
    if (issue_command(KBC_OUT_BUF, cmd)) return 1;
    return 0;
}

uint8_t* (get_scancode)(){
    return &scancode;
}
