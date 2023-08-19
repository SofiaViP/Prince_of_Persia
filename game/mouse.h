#ifndef _MOUSE_H
#define _MOUSE_H

#include <stdint.h>
#include <stdio.h>

#include <utils.h>
#include <video_gr.h>
#include <macros.h>
#include <pixmaps/objects.h>
#include <target.h>
#include <state.h>

/** @defgroup mouse mouse
 * @{
 *
 * Mouse
 */

/**
 * @brief Subscribes and enables mouse interrupts
 * 
 * @param bit_no - address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return 0 upon success and 1 otherwise
 */
int (mouse_subscribe_int)(uint8_t* bit_no);

/**
 * @brief Unsubscribes mouse interrupts
 * 
 * @return 0 upon success and 1 otherwise
 */
int (mouse_unsubscribe_int)();

/**
* @brief Enables stream mode data reporting
* 
* Enables stream mode data reporting, by sending the respective command to the mouse
*
* @return 0 upon success and 1 otherwise
*/
int (mouse_enable_data_report)();

/**
* @brief Disables stream mode data reporting
* 
* Disables stream mode data reporting, by sending the respective command to the mouse
*
* @return 0 upon success and 1 otherwise
*/
int (mouse_disable_data_report)();

/**
 * @brief Mouse interrupt handler
 * 
 * Parses data, after receiving a full packet
 */
void (mouse_ih)();

/**
* @brief Parses packet bytes
* 
* Parses each byte of a packet and saves it in the struct
*
* @param byte_num - current byte number
* @param pp - struct packet, to save packet data
* @return 0 upon success and 1 otherwise
*/
int (parse_packet)(uint8_t byte_num, struct packet* pp);

/**
* @brief Parses mouse movements
* 
* Parses mouse movements related to the Fight Screen 
*
* @param pp - struct packet, where the packet data is saved
* @return 0 upon success and 1 otherwise
*/
int (parse_movement)(struct packet pp);

/**
 * @brief Switches mouse state
 * 
 * Switches mouse state, depending on the mouse movement
 *
 * @return 0 upon success and 1 otherwise
 */
int (change_mouse_state)();

/**
 * @brief Checks if object is inside circle
 * 
 * @param x - the horizontal coordenate of the object
 * @param y - the vertical coordenate of the object
 * @param center_x - the horizontal coordenate of the center of the circle
 * @param center_y - the vertical coordenate of the center of the circle
 * @param radius - the radius of the circle
 * @return 0 if it is not inside the circle and 1 otherwise
 */
bool (is_inside_target)(uint8_t x, uint8_t y, uint8_t center_x, uint8_t center_y, uint8_t radius);

/**
 * @brief Loads cursor xpm
 * 
 * @return 0 upon success and 1 otherwise
 */
int (load_cursor)();

/**
 * @brief Erases cursor
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_cursor)();

/**
 * @brief Draws cursor
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_cursor)();

int (draw_cursor_above)(); // TO BE CHANGED

/**
 * @}
 */

#endif //_MOUSE_H
