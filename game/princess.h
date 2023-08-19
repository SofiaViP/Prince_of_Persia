#ifndef _PRINCESS_H
#define _PRINCESS_H

#include <stdbool.h>
#include <stdint.h>

#include <pixmaps/princessSprites.h>
#include <video_gr.h>
#include <macros.h>
#include <timer.h>

/** @defgroup princess princess
 * @{
 *
 * Princess
 */

/**
 * @brief Loads the princess xpms to the sprites array
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_princess_sprites)();

/**
 * @brief Gets the princess sprite index in the xpm array
 * 
 * @return thief sprite index
 */
int (get_princess_sprite)();

/**
 * @brief Gets the princess position
 * 
 * @return princess position
 */
position_t (get_princess_position)();


/**
 * @brief Sets princess new state
 * 
 * @param new_state - princess state to be switched to
 * @return 0 upon success and 1 otherwise
 */
int (set_princess_state)(state_t new_state);

/**
 * @brief Erases the princess
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_princess)();

/**
 * @brief Draws the princess
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_princess)();

/**
 * @brief Resets princess to initial state
*/
void (reset_princess)();

/**
 * @}
 */

#endif //_PRINCESS_H
