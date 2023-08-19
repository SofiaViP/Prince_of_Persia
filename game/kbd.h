#ifndef _KBD_H
#define _KBD_H

#include <stdbool.h>
#include <stdint.h>
#include <macros.h>
#include <utils.h>
#include <state.h>

/** @defgroup kbd kbd
 * @{
 *
 * Keyboard
 */

/**
 * @brief Subscribes and enables keyboard interrupts
 * 
 * @param bit_no - address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return 0 upon success and 1 otherwise
 */
int (kbd_subscribe_int)(uint8_t* bit_no);

/**
 * @brief Unsubscribes keyboard interrupts
 * 
 * @return 0 upon success and 1 otherwise
 */
int (kbd_unsubscribe_int)();

/**
 * @brief Keyboard interrupt handler
 * 
 * Processes received scancode
 */
void (kbc_ih)();

/**
 * @brief Gets current scancode
 * 
 * @return reference to the current scancode
 */
uint8_t* (get_scancode)();

/**
 * @}
 */

#endif //_KBD_H
