#ifndef _THIEF_H
#define _THIEF_H

#include <stdbool.h>
#include <stdint.h>

#include <pixmaps/thiefSprites.h>
#include <video_gr.h>
#include <macros.h>
#include <map.h>

/** @defgroup thief thief
 * @{
 *
 * Thief
 */

/**
 * @brief Loads thief's xpm's
 * 
 * @return 0 upon success and 1 otherwise 
 */
int (load_thief_sprites)();

/**
 * @brief Gets thief's position
 * 
 * @return thief's position
 */
position_t (get_thief_position)();

/**
 * @brief Gets thief state
 * 
 * @return thief's state
 */
state_t (get_thief_state)();

/**
 * @brief Sets the thief's state to a given state
 * 
 * @param state_t - new state for the thief
 * 
 * @return
 */
int (set_thief_state)(state_t);

/**
 * @brief Gets the thief's sprite index in the xpm array
 * 
 * @return thief sprite index
 */
int (get_thief_sprite)();

/**
 * @brief Gets the thief's number of remaining hearts
 * 
 * @return thief's hearts
 */
uint8_t (get_thief_hearts)();

/**
 * @brief Erases the thief 
 * 
 * @return 0 upon success and 1 otherwise 
 */
int (erase_thief)();

/**
 * @brief Draws the thief
 * 
 * @return 0 upon success and 1 otherwise 
 */
int (draw_thief)();

/**
 * @brief Erases the thief's hearts
 * 
 * @return 0 upon success and 1 otherwise 
 */
int(erase_thief_hearts)();

/**
 * @brief Draws the thief's hearts
 * 
 * @return 0 upon success and 1 otherwise 
 */
int (draw_thief_hearts)();

/**
 * @brief Decreases the thief's remaining hearts by 1
 * 
 * @return 0 upon success and 1 otherwise 
 */
int (thief_decrease_hearts)();

/**
 * @brief Resets the thief's attributes
 * 
 */
void (reset_thief)();

/**
 * @}
 */

#endif //_THIEF_H
