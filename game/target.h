#ifndef _TARGET_H
#define _TARGET_H

#include <stdbool.h>
#include <stdint.h>

#include <macros.h>
#include <video_gr.h>
#include <pixmaps/objects.h>
#include <prince.h>

/** @defgroup target target
 * @{
 *
 * Target
 */

/**
 * @brief Loads target xpm
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_target_sprites)();

/**
 * @brief Gets target position
 * 
 * @return target position
 */
position_t (get_target_pos)();

/**
 * @brief Gets target color
 * 
 * @return target color
 */
bool (get_target_color)();

/**
 * @brief Erases target
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_target)();

/**
 * @brief Draws target
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_target)();

/**
 * @brief Randomizes target position and color and resets size
 * 
 * @return 0 upon success and 1 otherwise
 */
int (randomize_target)();

/**
 * @brief Decreases target size
 * 
 * @return 0 upon success and 1 otherwise
 */
int (decrease_target)();

/**
 * @}
 */

#endif //_TARGET_H
