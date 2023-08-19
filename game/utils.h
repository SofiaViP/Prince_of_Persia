#ifndef _UTILS_H
#define _UTILS_H

#include <stdbool.h>
#include <stdint.h>
#include <macros.h>

/** @defgroup utils utils
 * @{
 *
 * Utils
 */

/**
 * @brief Invokes sys_inb() system call but reads the value into a uint8_t variable.
 *
 * @param port the input port that is to be read
 * @param value address of 8-bit variable to be update with the value read
 * @return Return 0 upon success and non-zero otherwise
 */
int (utils_sys_inb)(int port, uint8_t* value);

/**
 * @brief Reads return value/data from the KBC
 * 
 * Leaves the loop only upon some input from the output buffer 
 * 
 * @param data - data read from the output buffer 
 * @return 0 upon success and 1 otherwise
 */
int (read_outbuff)(uint8_t* data);

/**
 * @brief Issues command
 * 
 * @param reg - register to whom the command will be issued
 * @param cmd - command to be issued
 * @return 0 upon success and 1 otherwise
 */
int (issue_command)(uint8_t reg, uint8_t cmd);

/**
 * @}
 */

#endif //_UTILS_H
