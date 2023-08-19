#include <lcom/lcf.h>
#include <utils.h>

int (utils_get_MSB)(uint16_t value, uint8_t* msb){
    if (msb == NULL) return 1;
    *msb = (uint8_t)(value >> 8);
    return 0;
}

int (utils_get_LSB)(uint16_t value, uint8_t* lsb){
    if (lsb == NULL) return 1;
    *lsb = (uint8_t)value;
    return 0;
}

int (utils_sys_inb)(int port, uint8_t* value){
    if (value == NULL) return 1;
    uint32_t val32;
    if (sys_inb(port, &val32)) return 1;
    *value = (uint8_t)val32;
    return 0;
}

int (read_outbuff)(uint8_t* data){
    uint8_t status;
    while( 1 ) {
        if (utils_sys_inb(KBC_ST_REG, &status)) return 1;
        if( status & KBC_OBF ) {
            if (utils_sys_inb(KBC_OUT_BUF, data)) return 1;
            if ( (status & (KBC_ERROR)) == 0 )
                return 0;
            else
                return 1;
        }
        tickdelay(micros_to_ticks(DELAY_US));
    }
}

int (issue_command)(uint8_t reg, uint8_t cmd){
    uint8_t status;
    while( 1 ) {
        if (utils_sys_inb(KBC_ST_REG, &status)) return 1;
    if( (status & KBC_IBF) == 0 ) {
        return (sys_outb(reg, cmd));
    }
    tickdelay(micros_to_ticks(DELAY_US));
}
}
