#include <lcom/lcf.h>
#include <stdint.h>
#include <stdio.h>
#include <macros.h>
#include <timer.h>
#include <kbd.h>
#include <mouse.h>
#include <video_gr.h>
#include <text.h>
#include <map.h>
#include <prince.h>
#include <princess.h>
#include <rtc.h>

int (proj_main_loop)(int argc, char *argv[]){
  int ipc_status, r;
  uint8_t rtc_bit_no, timer_bit_no, kbd_bit_no, mouse_bit_no;
  message msg;
  
  if (vg_init(DIRECT_MODE) == NULL) return 1;

  if (rtc_set_interrupts(true)) return 1;

  if (timer_subscribe_int(&timer_bit_no)) return 1;
  if (kbd_subscribe_int(&kbd_bit_no)) return 1;
  if (rtc_subscribe_int(&rtc_bit_no)) return 1;
  if (mouse_enable_data_report()) return 1;
  if (mouse_subscribe_int(&mouse_bit_no)) return 1;

  if (load_text()) return 1;
  if (load_cursor()) return 1;
  if (load_map()) return 1;
  if (load_number_sprites()) return 1;
  if (load_prince_sprites()) return 1;
  if (load_princess_sprites()) return 1;
  if (load_thief_sprites()) return 1;
  if (load_target_sprites()) return 1;
  if (load_scoreboard_numbers_sprites()) return 1;
  if (loadHighScores()) return 1;
  

  if (draw_main_menu()) return 1;
  if (draw_cursor()) return 1;

  randomize_target();

  while(*get_scancode() != ESC_BREAK) {
    if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) { 
        printf("driver_receive failed with: %d", r);
        continue;
    }
    if (is_ipc_notify(ipc_status)) {
        switch (_ENDPOINT_P(msg.m_source)) {
            case HARDWARE:
                if (msg.m_notify.interrupts & BIT(timer_bit_no)){
                  timer_int_handler();
                }
                if (msg.m_notify.interrupts & BIT(kbd_bit_no)) {
                  kbc_ih();
                }
                if (msg.m_notify.interrupts & BIT(rtc_bit_no)) {
                  rtc_ih();
                }
                if (msg.m_notify.interrupts & BIT(mouse_bit_no)){
                  mouse_ih();
                }
                break;
            default:
                break;
        }
    }
 }
  if (saveHighScores()) return 1;
  if (kbd_unsubscribe_int()) return 1;
  if (timer_unsubscribe_int()) return 1;
  if (mouse_unsubscribe_int()) return 1;
  if (mouse_disable_data_report()) return 1;
  if(rtc_set_interrupts(false)) return 1;
  if(rtc_unsubscribe_int()) return 1;
  return vg_exit();
}

int main(int argc, char *argv[]) {
  lcf_set_language("EN-US");

  lcf_trace_calls("/home/lcom/labs/proj/src/trace.txt");
  lcf_log_output("/home/lcom/labs/proj/src/output.txt");

  if (lcf_start(argc, argv)) return 1;
  
  lcf_cleanup();

  return 0;
}
