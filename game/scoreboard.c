#include <lcom/lcf.h>
#include "scoreboard.h"

high_score_t highscores[5];
static xpm_image_t numbers_score[14];
int sbn = -1;
int yourScore;

int highScorePosition(int score){
    for (int i = 0; i < 5; i++){
        if(highscores[i].score < score){
            return i;
        }
    }
    return -1;
}

int (load_scoreboard_numbers_sprites)(){
  xpm_row_t* xpms[14] = {zeroS, oneS, twoS, threeS, fourS, fiveS, sixS, sevenS, eightS, nineS, points, slash, point, star};
  xpm_image_t img;
  uint8_t* sprite;

  for (uint8_t i = 0; i < 14; i++){
    sprite = xpm_load(xpms[i], XPM_8_8_8, &img);
    if (sprite == NULL) return 1; 
    numbers_score[i] = img;
  }
  return 0;
}

int (newScore)(date_time_t dateTime, int score){
    yourScore = score;
    sbn = highScorePosition(score);
    if(sbn == -1) return 1;
    int pos = sbn;
    high_score_t oldHighScores[5];
    memcpy(oldHighScores, highscores, sizeof(oldHighScores));
    high_score_t newHighScore = {dateTime, score};
    highscores[pos] = newHighScore;
    pos++;
    while(pos < 5){
        highscores[pos] = oldHighScores[pos-1];
        pos++;
    }
    return 0;
}

int (loadHighScores)(){
    FILE *f = fopen("/home/lcom/labs/g4/proj/src/scoreboard.txt", "r");
    if (f == NULL) { printf("File Path Wrong\n");return 1;};
    for (int i = 0; i < 5; i++) {
        high_score_t highscore;
        date_time_t dateTime;
        int score = 0;
        fscanf(f, "%d/%d/%d %d:%d:%d - %d\n", &dateTime.day, &dateTime.month, &dateTime.year, &dateTime.hour, &dateTime.minute, &dateTime.second, &score);
        highscore.datetime = dateTime;
        highscore.score = score;
        highscores[i] = highscore;
    }
    fclose(f);
    return 0;
}

int saveHighScores() {
    FILE *f = fopen("/home/lcom/labs/g4/proj/src/scoreboard.txt", "w");
    if (f == NULL) return 1;
    for (int i = 0; i < 5; i++) {
        high_score_t ds = highscores[i];
        fprintf(f, "%d/%d/%d %d:%d:%d - %d\n", ds.datetime.day, ds.datetime.month, ds.datetime.year, ds.datetime.hour, ds.datetime.minute, ds.datetime.second, ds.score);
    }
    fclose(f);
    return 0;
}

int (erase_score)(){
    int yoffset = 200;
    int date_offset = get_h_res() - numbers_score[2].width*6 - numbers_score[10].width*2 - 160;
    int score_offset = date_offset - numbers_score[0].width*6 - numbers_score[11].width*2 -30;
    
    if(erase_xpm(numbers_score[yourScore / 10], get_h_res()/2 - numbers_score[0].width*2, 150, 1)) return 1;
    if(erase_xpm(numbers_score[yourScore % 10], get_h_res()/2 - numbers_score[0].width, 150, 1)) return 1;
    
    for(int i = 0; i < 5; i++){
        
        yoffset = yoffset + 50;
        high_score_t ds = highscores[i];
        //Draw Number
        if(erase_xpm(numbers_score[i+1], score_offset - numbers_score[0].width*3 - numbers_score[12].width*0.5 - 30, yoffset, 1)) return 1;
        if(erase_xpm(numbers_score[12], score_offset - numbers_score[0].width*2 - numbers_score[12].width*1 - 30, yoffset, 1)) return 1;

        //Draw Score
        if(erase_xpm(numbers_score[ds.score / 10], score_offset - numbers_score[0].width*2, yoffset, 1)) return 1;
        if(erase_xpm(numbers_score[ds.score % 10], score_offset - numbers_score[0].width, yoffset, 1)) return 1;

        //Draw Date
        if (erase_xpm(numbers_score[ds.datetime.day / 10], date_offset - numbers_score[0].width*6 - numbers_score[11].width*2, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.day % 10], date_offset - numbers_score[0].width*5 - numbers_score[11].width*2, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[11], date_offset - numbers_score[0].width*4 - numbers_score[11].width*2, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[ds.datetime.month / 10], date_offset - numbers_score[0].width*4 - numbers_score[11].width, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.month % 10], date_offset - numbers_score[0].width*3 - numbers_score[11].width, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[11], date_offset - numbers_score[0].width*2 - numbers_score[11].width, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[ds.datetime.year / 10], date_offset - numbers_score[0].width*2, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.year % 10], date_offset - numbers_score[0].width, yoffset, 1)) return 1;
        
        //Draw Time
        if (erase_xpm(numbers_score[ds.datetime.hour / 10], get_h_res() - numbers_score[0].width*6 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.hour % 10], get_h_res() - numbers_score[0].width*5 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[10], get_h_res() - numbers_score[0].width*4 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[ds.datetime.minute / 10], get_h_res() - numbers_score[0].width*4 - numbers_score[10].width - 130, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.minute % 10], get_h_res() - numbers_score[0].width*3 - numbers_score[10].width - 130, yoffset, 1)) return 1;

        
        if (erase_xpm(numbers_score[10], get_h_res() - numbers_score[0].width*2 - numbers_score[10].width - 130, yoffset, 1)) return 1;

        if (erase_xpm(numbers_score[ds.datetime.second / 10], get_h_res() - numbers_score[0].width*2 - 130, yoffset, 1)) return 1;
        if (erase_xpm(numbers_score[ds.datetime.second % 10], get_h_res() - numbers_score[0].width - 130, yoffset, 1)) return 1;

        if(sbn == i){
            if(erase_xpm(numbers_score[13], get_h_res() - numbers_score[13].width -80, yoffset-10, 1)) return 1;
        }
    }
    sbn = -1;
    return 0;
}

int (draw_score)(){
    int yoffset = 200;
    int date_offset = get_h_res() - numbers_score[2].width*6 - numbers_score[10].width*2 - 160;
    int score_offset = date_offset - numbers_score[0].width*6 - numbers_score[11].width*2 -30;
    
    if(draw_xpm(numbers_score[yourScore / 10], get_h_res()/2 - numbers_score[0].width*2, 150, 1)) return 1;
    if(draw_xpm(numbers_score[yourScore % 10], get_h_res()/2 - numbers_score[0].width, 150, 1)) return 1;
    
    for(int i = 0; i < 5; i++){
        
        yoffset = yoffset + 50;
        high_score_t ds = highscores[i];
        //Draw Number
        if(draw_xpm(numbers_score[i+1], score_offset - numbers_score[0].width*3 - numbers_score[12].width*0.5 - 30, yoffset, 1)) return 1;
        if(draw_xpm(numbers_score[12], score_offset - numbers_score[0].width*2 - numbers_score[12].width*1 - 30, yoffset, 1)) return 1;

        //Draw Score
        if(draw_xpm(numbers_score[ds.score / 10], score_offset - numbers_score[0].width*2, yoffset, 1)) return 1;
        if(draw_xpm(numbers_score[ds.score % 10], score_offset - numbers_score[0].width, yoffset, 1)) return 1;

        //Draw Date
        if (draw_xpm(numbers_score[ds.datetime.day / 10], date_offset - numbers_score[0].width*6 - numbers_score[11].width*2, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.day % 10], date_offset - numbers_score[0].width*5 - numbers_score[11].width*2, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[11], date_offset - numbers_score[0].width*4 - numbers_score[11].width*2, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[ds.datetime.month / 10], date_offset - numbers_score[0].width*4 - numbers_score[11].width, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.month % 10], date_offset - numbers_score[0].width*3 - numbers_score[11].width, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[11], date_offset - numbers_score[0].width*2 - numbers_score[11].width, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[ds.datetime.year / 10], date_offset - numbers_score[0].width*2, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.year % 10], date_offset - numbers_score[0].width, yoffset, 1)) return 1;
        
        //Draw Time
        if (draw_xpm(numbers_score[ds.datetime.hour / 10], get_h_res() - numbers_score[0].width*6 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.hour % 10], get_h_res() - numbers_score[0].width*5 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[10], get_h_res() - numbers_score[0].width*4 - numbers_score[10].width*2 - 130, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[ds.datetime.minute / 10], get_h_res() - numbers_score[0].width*4 - numbers_score[10].width - 130, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.minute % 10], get_h_res() - numbers_score[0].width*3 - numbers_score[10].width - 130, yoffset, 1)) return 1;
        
        if (draw_xpm(numbers_score[10], get_h_res() - numbers_score[0].width*2 - numbers_score[10].width - 130, yoffset, 1)) return 1;

        if (draw_xpm(numbers_score[ds.datetime.second / 10], get_h_res() - numbers_score[0].width*2 - 130, yoffset, 1)) return 1;
        if (draw_xpm(numbers_score[ds.datetime.second % 10], get_h_res() - numbers_score[0].width - 130, yoffset, 1)) return 1;

        if(sbn == i){
            if(draw_xpm(numbers_score[13], get_h_res() - numbers_score[13].width - 80, yoffset -10, 1)) return 1;
        }
    }
    return 0;
}

int (setUpScoreboard)(game_timer_t t, int lives, date_time_t dt){
    return newScore(dt, calculateScore((t.minutes*60 + t.seconds), lives));
}

int (calculateScore)(int seconds, int lives) {
    int maxScore = 100;
    int minScore = 10;
    int maxSeconds = 20;
    int minSeconds = 300;
    int maxLives = 5;
    int minLives = 1;

    // Calculate time score
    double timeFactor = 1.0 - ((double)(seconds - maxSeconds) / (double)(minSeconds - maxSeconds));
    int timeScore = (int)(timeFactor * (maxScore - minScore)) + minScore;

    // Calculate lives score
    double livesFactor = (double)(lives - minLives) / (double)(maxLives - minLives);
    int livesScore = (int)(livesFactor * (maxScore - minScore)) + minScore;

    // Calculate total score by averaging timeScore and livesScore
    int totalScore = (timeScore + livesScore) / 2;

    return totalScore;
}
