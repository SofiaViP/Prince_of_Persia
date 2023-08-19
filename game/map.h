#ifndef _MAP_H
#define _MAP_H

#include <stdbool.h>
#include <stdint.h>
#include <macros.h>
#include <video_gr.h>
#include <state.h>
#include <pixmaps/backgrounds.h>
#include <pixmaps/objects.h>

/** @defgroup map map
 * @{
 *
 * Map
 */

/**
 * @brief Loads block xpms to the sprites array
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_map)();

/**
 * @brief Erases the current map
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_map)();

/**
 * @brief Draws the current map
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_map)();

/**
 * @brief Gets the current map
 * 
 * @param size - number of blocks of the current map
 * @return array of blocks which belong to the current map
 */
position_t* (get_map)(int *size);

/**
 * @brief Sets Prince starting position, given the current map
 * 
 * @param pos - Prince position to be modified
 */
void (set_start_pos)(position_t* pos);

/**
 * @brief Draws spikes on the current map
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_spikes)();

/**
 * @brief Erases spikes on the current map
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_spikes)();

/**
 * @brief Gets the spikes position on the current map
 * 
 * @return spikes position on the current map
 */
position_t (get_spikes)();

/**
 * @}
 */

#endif //_MAP_H
