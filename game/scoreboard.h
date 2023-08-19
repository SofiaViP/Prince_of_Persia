#ifndef _SCOREBOARD_H
#define _SCOREBOARD_H

#include <pixmaps/numbers.h>
#include <video_gr.h>
#include <macros.h>
#include <stdbool.h>
#include <stdint.h>

/** @defgroup scoreboard scoreboard
 * @{
 *
 * Scoreboard
 */

/**
 * @brief Determines Scores new Position in Leaderboard
 * 
 * @param score Score to compare with current Leaderboard
 * @return Returns score position as an int or -1 in case it's not a highscore
 */
int (highScorePosition)(int score);

/**
 * @brief Loads High Scores saved in file scoreboard.txt
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (loadHighScores)();

/**
 * @brief Saves High Scores to the file scoreboard.txt
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (saveHighScores)();

/**
 * @brief Saves player score and adds to Leaderboard in case it's a top score
 * 
 * @param dateTime Time stamp of when the game ended
 * @param score Player Score
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (newScore)(date_time_t dateTime, int score);

/**
 * @brief Draws the player current Score and Leaderboard
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (draw_score)();

/**
 * @brief Erases the Leaderboard and player score
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (erase_score)();

/**
 * @brief Loads Numbers and Symbol Sprites from numbers.h
 * 
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (load_scoreboard_numbers_sprites)();

/**
 * @brief Set the Up Scoreboard object
 * 
 * @param t In game timer used to calculate score
 * @param lives Remaining lives used in score calculation
 * @param dt Timestamp of when the game was comleted
 * @return Returns 0 upon sucess and 1 in case of failure
 */
int (setUpScoreboard)(game_timer_t t, int lives, date_time_t dt);

/**
 * @brief Calculates Score for Game
 * 
 * @param seconds Time taken to complete level in seconds.
 * @param lives Remaining lives
 * @return Final score
 */
int (calculateScore)(int seconds, int lives);

/**
 * @}
 */

#endif //_SCOREBOARD_H
