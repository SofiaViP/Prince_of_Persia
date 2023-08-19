#ifndef _STATE_H
#define _STATE_H

#include <stdbool.h>
#include <stdint.h>

#include <macros.h>
#include <timer.h>
#include <prince.h>
#include <princess.h>
#include <map.h>
#include <text.h>
#include <target.h>
#include <rtc.h>
#include <thief.h>

/** @defgroup state state
 * @{
 *
 * Game State
 */

/**
 * @brief Switches game mode
 * 
 * @param new_mode - game mode to switch to
 */
void (set_mode)(game_mode_t new_mode);

/**
 * @brief Gets the current game mode 
 * 
 * @return current game mode
 */
game_mode_t (get_mode)();

/**
 * @brief Resets game to its inital state
 * 
 */
void (reset_game)();

/**
 * @}
 */

#endif //_STATE_H
