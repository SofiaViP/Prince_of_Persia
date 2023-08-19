#include <lcom/lcf.h>
#include "rtc.h"
#include "utils.h"

uint8_t hour, minute, second, day, month, year;
int rtc_hook_id = 5;
int seconds = 0;
static date_time_t dateTime;
static game_timer_t timer = {0, 0};
static xpm_image_t numbers[11];

int rtc_read_reg(uint32_t reg, uint8_t * data){
    if(sys_outb(RTC_ADDR_REG, reg)) return 1;
    if(utils_sys_inb(RTC_DATA_REG, data)) return 1;
    return 0;
}

int rtc_write_reg(uint32_t reg, uint8_t data){
    if(sys_outb(RTC_ADDR_REG, reg)) return 1;
    if(sys_outb(RTC_DATA_REG, data)) return 1;
    return 0;
}

int read_rtc_dt(uint32_t reg, uint8_t * data){
    wait_valid_rtc();
    if(rtc_read_reg(reg, data)) return 1;
    return 0;
}

void wait_valid_rtc() {
    uint8_t data;
    do {
        rtc_read_reg(REGISTER_A, &data);
    } while ( data & UIP);
}

int disable(){
    uint8_t data;
    if(rtc_read_reg(REGISTER_B, &data)) return 1;
    data = data | SET;
    if(rtc_write_reg(RTC_DATA_REG, data)) return 1;
    return 0;
}

int enable(){
    uint8_t data;
    if(rtc_read_reg(REGISTER_B, &data)) return 1;
    data = data & ~(SET);
    if(rtc_write_reg(RTC_DATA_REG, data)) return 1;
    return 0;
}

uint8_t bcd_to_decimal(uint8_t bcd) {
    return ((bcd & 0xF0) >> 4) * 10 + (bcd & 0x0F);
}

int rtc_update(){
    if(disable()) return 1;
    if(read_rtc_dt(RTC_HOUR_REG, &hour) || read_rtc_dt(RTC_MINUTE_REG, &minute) || read_rtc_dt(RTC_SECOND_REG, &second) || read_rtc_dt(RTC_DAY_REG, &day) || read_rtc_dt(RTC_MONTH_REG, &month)|| read_rtc_dt(RTC_YEAR_REG, &year)) return 1;
    if(enable()) return 1;
    dateTime.second = bcd_to_decimal(second);
    dateTime.minute = bcd_to_decimal(minute);
    dateTime.hour = bcd_to_decimal(hour);
    dateTime.day = bcd_to_decimal(day);
    dateTime.month = bcd_to_decimal(month);
    dateTime.year = bcd_to_decimal(year);
    return 0;
}

void print_rtc_struct(){
    printf("%d/%d/%d", dateTime.year, dateTime.month, dateTime.day);
    if(dateTime.hour < 10)
        printf(" 0%d", dateTime.hour);
    else printf(" %d", dateTime.hour);
    if(dateTime.minute < 10)
        printf(":0%d", dateTime.minute);
    
    else printf(":%d", dateTime.minute);
    if(dateTime.second < 10){
        printf(":0%d", dateTime.second);
    }
    else printf(":%d", dateTime.second);
}

int rtc_subscribe_int(uint8_t *bit_no){
    *bit_no = rtc_hook_id;
     return sys_irqsetpolicy(RTC_IRQ,  IRQ_REENABLE | IRQ_EXCLUSIVE, &rtc_hook_id);
}

int rtc_unsubscribe_int() {
    return sys_irqrmpolicy(&rtc_hook_id);
}

int rtc_set_interrupts(bool on){
    //SET UPDATE
    if(rtc_set_int(AIE, false)) return 1;
    if(rtc_set_int(PIE, false)) return 1;
    if(rtc_set_int(UIE, on)) return 1;
    return 0;
}

int rtc_set_int(uint32_t reg, bool on){
    uint8_t data;
    if(rtc_read_reg(REGISTER_B, &data)) return 1;
    data = on ? (reg | data) : (data & (~reg));
    if(rtc_write_reg(REGISTER_B, data)) return 1;
    return 0;
}

int (increase_timer)(){
    if (erase_timer()) return 1;
    if(timer.minutes == 99 && timer.seconds ==59) {
        reset_game();
        return 0;
    }
    if (timer.seconds == 59){
        timer.minutes++;
        timer.seconds = 0;
    }
    else timer.seconds++;
    if (draw_timer(1)) return 1;
    return 0;
}

void rtc_ih(void) {
    uint8_t regA;
    sys_outb(RTC_ADDR_REG, REGISTER_C);
    utils_sys_inb(RTC_DATA_REG, &regA);
    if(regA & UF){
        rtc_update();
        switch (get_mode()){
            case GAME_1: case GAME_2: case GAME_3: case FIGHT:
                increase_timer();
                break;
            default:
                break;
        }
    }
}

int (load_number_sprites)(){
  xpm_row_t* xpms[11] = {zero, one, two, three, four, five, six, seven, eight, nine, points};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 11; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    numbers[i] = img;
  }
  return 0;
}

int (erase_timer)(){
    if (vg_draw_rectangle(get_h_res() - numbers[0].width*4 - numbers[10].width - 10, 0, numbers[0].width*4 + numbers[10].width + 10, numbers[0].height + 10, 0x000000)) return 1;

    if (erase_xpm(numbers[timer.minutes / 10], get_h_res() - numbers[0].width*4 - numbers[10].width - 5, 5, 1)) return 1;
    if (erase_xpm(numbers[timer.minutes % 10], get_h_res() - numbers[0].width*3 - numbers[10].width - 5, 5, 1)) return 1;

    if (erase_xpm(numbers[timer.seconds / 10], get_h_res() - numbers[0].width*2 - 5, 5, 1)) return 1;
    if (erase_xpm(numbers[timer.seconds % 10], get_h_res() - numbers[0].width - 5, 5, 1)) return 1;
    return 0;
}

int (draw_timer)(bool points){
    if (points){
        if (vg_draw_rectangle(get_h_res() - numbers[0].width*4 - numbers[10].width - 10, 0, numbers[0].width*4 + numbers[10].width + 10, numbers[0].height + 10, 0x000000)) return 1;
    }
    
    if (draw_xpm(numbers[timer.minutes / 10], get_h_res() - numbers[0].width*4 - numbers[10].width - 5, 5, 1)) return 1;
    if (draw_xpm(numbers[timer.minutes % 10], get_h_res() - numbers[0].width*3 - numbers[10].width - 5, 5, 1)) return 1;

    if (points){
        if (draw_xpm(numbers[10], get_h_res() - numbers[0].width*2 - numbers[10].width - 5, 15, 1)) return 1;
    }

    if (draw_xpm(numbers[timer.seconds / 10], get_h_res() - numbers[0].width*2 - 5, 5, 1)) return 1;
    if (draw_xpm(numbers[timer.seconds % 10], get_h_res() - numbers[0].width - 5, 5, 1)) return 1;
    return 0;
}

date_time_t getCurrentDateTime(){
    return dateTime;
}

game_timer_t getTimer(){
    return timer;
}

void reset_time(){
    timer.minutes = 0;
    timer.seconds = 0;
}
