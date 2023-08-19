#ifndef _VIDEO_GR_H
#define _VIDEO_GR_H

#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <macros.h>

/** @defgroup video_gr video_gr
 * @{
 *
 * Video Card
 */

/**
 * @brief Get the horizontal resolution of the screen
 * 
 * @return The horizontal resolution of the screen
 */
unsigned (get_h_res)();

/**
 * @brief Get the vertical resolution of the screen
 * 
 * @return The vertical resolution of the screen
 */
unsigned (get_v_res)();

/**
 * @brief Draw a pixel at the specified coordinates with the given color.
 * 
 * @param x - the x-coordinate of the pixel
 * @param y - the y-coordinate of the pixel
 * @param color - the color of the pixel
 * @param buffer - boolean value indicating whether to draw on the
 * first or second buffer
 * 
 * @return 0 upon success and 1 otherwise
 */
int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color, bool buffer);

/**
 * @brief Draw an XPM image on the screen at the specified coordinates
 * 
 * @param img - the XPM image to draw
 * @param x - the x-coordinate of the top-left corner of the image
 * @param y - the y-coordinate of the top-left corner of the image.
 * @param buffer - boolean value indicating whether to draw on the
 * first or second buffer
 * 
 * @return 0 upon success and 1 otherwise
 */
int (draw_xpm)(xpm_image_t img, uint16_t x, uint16_t y, bool buffer);

/**
 * @brief
 * 
 * @param img - the XPM image to draw
 * @param x - the x-coordinate of the top-left corner of the image
 * @param y - the y-coordinate of the top-left corner of the image.
 * @param buffer - boolean value indicating whether to draw on the
 * first or second buffer
 * 
 * @return 0 upon success and 1 otherwise
 */
int (erase_xpm)(xpm_image_t img, uint16_t x, uint16_t y, bool buffer);

/**
 * @brief Swap the buffers, effectively updating the screen with the
 * contents of the double buffer
 * 
 * @param buffer - boolean value indicating whether to draw on the
 * first or second buffer
 */
void (swap_buffers)(bool buffer);

/**
 * @}
 */

 #endif //_VIDEO_GR_H
