#ifndef _TIMER_H
#define _TIMER_H

#include <stdbool.h>
#include <stdint.h>

#include <pixmaps/numbers.h>
#include <video_gr.h>
#include <macros.h>
#include <state.h>
#include <mouse.h>
#include <prince.h>
#include <thief.h>

/** @defgroup timer0 timer0
 * @{
 *
 * Timer 0
 */

/**
 * @brief Timer 0 interrupt handler
 * 
 * Increments counter
 * Re-draw all xpm's
 * Swaps buffers via double-buffering  
 */
void (timer_int_handler)();

/**
 * @brief Subscribes and enables Timer 0 interrupts
 * 
 * @param bit_no - address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return 0 upon success and 1 otherwise
 */
int (timer_subscribe_int)(uint8_t* bit_no);

/**
 * @brief Unsubscribes Timer 0 interrupts
 * 
 * @return 0 upon success and 1 otherwise
 */
int (timer_unsubscribe_int)();

/**
 * @brief Gets frame count
 * 
 * @return frame_count
 */
int (get_frame_count)();

/**
* @brief Sets new frame count
*
* @param new_frame_count - new frame count to be set
*/
void (set_frame_count)(int new_frame_count);

/**
 * @}
 */

#endif //_TIMER_H
