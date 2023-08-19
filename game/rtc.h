#ifndef _RTC_H
#define _RTC_H

#include <stdbool.h>
#include <stdint.h>
#include <pixmaps/numbers.h>
#include <video_gr.h>
#include <macros.h>
#include <state.h>

/** @defgroup rtc rtc
 * @{
 *
 * RTC
 */

/**
 * @brief Reads RTC register 
 * 
 * @param reg - Register to read
 * @param data - Pointer to save read information
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_read_reg(uint32_t reg, uint8_t * data);

/**
 * @brief Writes data to RTC register
 * 
 * @param reg - Register to write to
 * @param data - Data to write
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_write_reg(uint32_t reg, uint8_t data);

/**
 * @brief Waits for RTC to stop updating
 * 
 */
void wait_valid_rtc();

/**
 * @brief Reads RTC Date and Time
 * 
 * @param reg - Register to read
 * @param data - Pointer to save read information
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int read_rtc_dt(uint32_t reg, uint8_t * data);

/**
 * @brief 
 * 
 * @param bcd - Value in BCD format
 * @return uint8_t variable in decimal format
 */
uint8_t bcd_to_decimal(uint8_t bcd); 

/**
 * @brief Disables RTC updates
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int disable();

/**
 * @brief Enables RTC updates
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int enable();

/**
 * @brief Updates local time data Structure  with current RTC info
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_update();

/**
 * @brief Sets RTC interrupts
 * 
 * @param on - detetermins weather to activate or de-activate
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_set_interrupts(bool on);

/**
 * @brief Function that handles RTC interrupts.
 * 
 */
void rtc_ih(void);

/**
 * @brief Subscribes to RTC interrupts
 * 
 * @param bit_no - represents mask to use
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_subscribe_int(uint8_t *bit_no);

/**
 * @brief Unsubscribes to RTC interrupts
 * 
 * @return Returns 0 upon sucess and 1 in case of failure 
 */
int rtc_unsubscribe_int();

/**
 * @brief Sets individual interrupt
 * 
 * @param reg - represents interrupt
 * @param on - detetermins weather to activate or de-activate
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int rtc_set_int(uint32_t reg, bool on);

/**
 * @brief Increases timer structure if variable activateTimer is true
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (increase_timer)();


/**
 * @brief Draws Timer
 * 
 * @param points - 1 -> draws colon between minutes and seconds | 0 -> draws only the numbers 
 * @return Returns 0 upon sucess and 1 in case of failure
 */

int (draw_timer)(bool points);

/**
 * @brief Prints Time and Date
 * 
 */
void print_rtc_struct();

/**
 * @brief 
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int load_number_sprites();

/**
 * @brief Erases the timer
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (erase_timer)();

/**
 * @brief Get the Current Date Time object
 * 
 * @return Returns Current Date-Time
 */
date_time_t getCurrentDateTime();

/**
 * @brief Get the Timer object
 * 
 * @return Returns the game timer
 */
game_timer_t getTimer();

/**
 * @brief reset the Timer object
 */
void reset_time();

/**
 * @}
 */

#endif //_RTC_H
