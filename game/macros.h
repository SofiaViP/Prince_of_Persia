#ifndef _LCOM_MACROS_H_
#define _LCOM_MACROS_H_


/** @defgroup macros macros
 * @{
 *
 * Constants for programming the devices
 */

/* Timer Macros */

#define TIMER_IRQ 0x00 /**< @brief IRQ line for the timer interrupts*/

/* Mouse Macros */

#define MOUSE_IRQ 0x0C /**< @brief IRQ line for the mouse interrupts*/

#define MOUSE_CMD_BYTE 0xD4 /**< @brief Command byte for the KBC to forward its argument to the mouse without any interpretation*/

#define ENABLE_CMD 0xF4 /**< @brief Mouse's enable data reporting command*/
#define DISABLE_CMD 0xF5 /**< @brief Mouse's disable data reporting command*/

#define MOUSE_ACK 0xFA /**< @brief Mouse's OK aknowledgement byte*/
#define MOUSE_NACK 0xFE /**< @brief Mouse's invalide byte aknowledgement byte*/
#define MOUSE_ERROR 0xFC /**< @brief Mouse's ERROR aknowledgement byte*/

typedef enum {INIT, CLICK, GOOD_CLICK, BAD_CLICK, MISS, HIT} mouse_state_t; /**< @brief States of the mouse's click*/
typedef enum {CORRECT_CLICK, WRONG_CLICK, CORRECT_NO_CLICK, WRONG_NO_CLICK, MOUSE_OTHER} movement_t; /**< @brief Movements of the mouse*/

/* Keyboard Macros */
#define DELAY_US 20000

#define KBD_IRQ 0x01 /**< @brief IRQ line for keyboard interrupts*/

#define KBC_OUT_BUF 0x60 /**< @brief KBC output buffer address*/
#define KBC_ST_REG  0x64 /**< @brief KBC status register address*/
#define KBC_CMD_REG 0x64 /**< @brief KBC command register address*/

#define KBC_ERROR (BIT(7)|BIT(6)) /**< @brief KBC status: error*/
#define KBC_IBF BIT(1) /**< @brief KBC status: input buffer full*/
#define KBC_OBF BIT(0) /**< @brief KBC status: output buffer full (data available for reading)*/

#define FIRST_BYTE 0xE0 /**< @brief Keyboard first byte*/

#define ENTER_BREAK 0x9C /**< @brief ENTER key break code*/
#define RIGHT_MAKE 0x4D /**< @brief ARROW RIGHT key make code*/
#define RIGHT_BREAK 0xCD /**< @brief ARROW RIGHT key break code*/
#define LEFT_MAKE 0x4B /**< @brief ARROW LEFT key make code*/
#define LEFT_BREAK 0xCB /**< @brief ARROW LEFT key break code*/
#define UP_MAKE 0x48 /**< @brief ARROW UP key make code*/
#define UP_BREAK 0xC8 /**< @brief ARROW UP key break code*/
#define ESC_MAKE 0x01 /**< @brief ESCAPE key make code*/
#define ESC_BREAK 0x81 /**< @brief ESCAPE key break code*/

#define READ_CMD_BYTE 0x20 /**< @brief KBC Read command byte*/
#define WRITE_CMD_BYTE 0x60 /**< @brief KBC Write command byte*/

/* Video Graphics Macros */
#define AH_REG 0x4F /**< @brief AH register address*/
#define AH_SUCCESS 0x00 /**< @brief AH success*/

#define AL_SET_VBE_MODE 0x02 /**< @brief Lower bits of the command that sets the VBE to Graphic Mode */

#define INDEXED_MODE 0x105 /**< @brief Indexed mode code*/
#define DIRECT_MODE 0x115 /**< @brief Direct color mode code*/


/* RTC Macros */

#define RTC_IRQ 0x08 /**< @brief IRQ line for the RTC interrupts*/
#define RTC_ADDR_REG 0x70 
#define RTC_DATA_REG 0x71
#define RTC_SECOND_REG 0x00
#define RTC_MINUTE_REG 0x02
#define RTC_HOUR_REG 0x04
#define RTC_DAY_REG 0x07
#define RTC_MONTH_REG 0x08
#define RTC_YEAR_REG 0x09
#define RTC_BINARY 0x11
#define REGISTER_A 0x0A
#define REGISTER_B 0x0B
#define REGISTER_C 0x0C
#define RS_HALF_SECOND 0x0F

/* Resgister A */
#define UIP BIT(7)
/* Register B */
#define UIE BIT(4)
#define AIE BIT(5)
#define PIE BIT(6)
#define SET BIT(7)
/* Register C */
#define UF BIT(4)
#define AF BIT(5)
#define PF BIT(6)


typedef struct {
    int day;
    int month;
    int year;
    int second;
    int minute;
    int hour;
} date_time_t; /**< @brief Struct for the date time*/

/* Prince */

typedef enum {L_STAND, L_RUN, L_JUMP, L_FALL, L_STAND_FIGHT, L_FIGHT, R_STAND, R_RUN, R_JUMP, R_FALL, R_STAND_FIGHT, R_FIGHT, CHANGE, DEAD} state_t; /**< @brief States for the game's characters*/

/* Model */

typedef enum {MAIN_MENU, INSTRUCTIONS, GAME_1, GAME_2, GAME_3, FIGHT, HUG, SCOREBOARD} game_mode_t; /**< @brief Game's states including menus and levels*/

typedef struct {
    int x;
    int y;
    int width;
    int height;
} position_t; /**< @brief Struct for the position of the game's elements*/

typedef struct {
    uint8_t minutes;
    uint8_t seconds; 
} game_timer_t; /**< @brief Struct for the game's timer*/

typedef struct {
    int x;
    int y;
    int radius;
    bool color;
} circle_t; /**< @brief Struct for circles used in the game's FIGHT mode*/

typedef struct {
    position_t** map;
    int size;
} map_t; /**< @brief Struct for the game's maps used to build each level*/

/* Highscore  */

typedef struct {
    date_time_t datetime;
    int score;
} high_score_t ; /**< @brief Struct for the game's scoring system which includes, date, time and score*/

typedef struct {
    bool collision;
    int x_offset;
    int y_offset;
} collision_data_t; /**< @brief Struct for collision analysis*/

#endif /* _LCOM_MACROS_H */
