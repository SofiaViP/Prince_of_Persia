#ifndef _PRINCE_H
#define _PRINCE_H

#include <stdbool.h>
#include <stdint.h>

#include <pixmaps/princeSprites.h>
#include <video_gr.h>
#include <macros.h>
#include <map.h>
#include <timer.h>

/** @defgroup prince prince
 * @{
 *
 * Prince
 */

/**
 * @brief Loads the prince xpms to the sprites array
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_prince_sprites)();

/**
 * @brief Gets the prince state
 * 
 * @return Prince state
 */
state_t (get_prince_state)();

/**
 * @brief Gets the prince position
 * 
 * @return Prince position
 */
position_t (get_prince_position)();

/**
 * @brief Sets the prince position
 * 
 * @param x - The X-coordinate of the prince
 * @param y - The Y-coordinate of the prince
 * 
 */
void (set_prince_position)(int x, int y);

/**
 * @brief Gets the sprite corresponding to the current state
 * 
 * @return index of the sprite
 */
int (get_sprite)();

/**
 * @brief Erases the Prince
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_prince)();

/**
 * @brief Draws the Prince
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_prince)();

/**
 * @brief Changes the Prince position
 * 
 * @param delta_x - Delta in the X direction
 * @param delta_y - Delta in the Y direction
 * 
 * @return 0 upon success and 1 otherwise
 */
int (change_prince)(int8_t delta_x, int8_t delta_y);

/**
 * @brief Change the Prince state
 *
 * Changes the Prince state according to the scancode received from the keyboard
 * 
 * @param scancode - keyboard scancode
 * 
 * @return 0 upon success and 1 otherwise
 */
int (change_prince_state)(uint8_t scancode);

/**
 * @brief Set the Price state
 * 
 * @param state_t - new state to be set 
 * 
 * @return 0 upon success and 1 otherwise
 */
int (set_prince_state)(state_t);

/**
 * @brief Checks the collisions between two elements
 * 
 * @param position_t - Prince position
 * @param position_t - block/spikes position
 * @return colision data
 */
collision_data_t (check_collision)(position_t pos1, position_t pos2);

/**
 * @brief Fullfill the action according to the Prince state
 * 
 * @return 0 upon success and 1 otherwise
 */
int (prince_action)();

/**
 * @brief Draws the Prince hearts
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_prince_hearts)();

/**
 * @brief Erases the Prince hearts
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_prince_hearts)();

/**
 * @brief Descrease Prince hearts by one
 * 
 * @return 0 upon success and 1 otherwise
 */
int (prince_decrease_hearts)();

/**
 * @brief Get number of Prince hearts
 * 
 * @return nummber of the prince hearts
 */
uint8_t (get_prince_hearts)();

/**
 * @brief Resets the prince attributes
 */
void (reset_prince)();

/**
 * @}
 */

#endif //_PRINCE_H
