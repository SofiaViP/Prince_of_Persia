#ifndef _TEXT_H
#define _TEXT_H

#include <stdbool.h>
#include <stdint.h>

#include <macros.h>
#include <video_gr.h>
#include <pixmaps/backgrounds.h>
#include <scoreboard.h>

/** @defgroup text text
 * @{
 *
 * Text
 */

/**
 * @brief Loads text xpm images
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_text)();

/**
 * @brief Erases main menu
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_main_menu)();

/**
 * @brief Draws main menu
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_main_menu)();

/**
 * @brief Erases instructions
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_instructions)();

/**
 * @brief Draws instructions
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_instructions)();

/**
 * @brief Erases scoreboard
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_scoreboard)();

/**
 * @brief Draws scoreboard
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_scoreboard)();

/**
 * @}
 */

#endif //_TEXT_H
