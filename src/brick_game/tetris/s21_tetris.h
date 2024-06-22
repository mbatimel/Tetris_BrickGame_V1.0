#ifndef S21_TETRIS_H
#define S21_TETRIS_H
#include <curses.h>
#include <stdbool.h>
#include <string.h>

#include "s21_actions_bricks.h"
#include "s21_bricks.h"

#define FIELD_WIDTH 10
#define FIELD_LENGTH 20
typedef enum {
  Start,
  Pause,
  Terminate,
  Left,
  Right,
  Up,
  Down,
  Action
} UserAction_t;

typedef struct {
  int** field;
  int** next;
  int** current_figure;
  int score;
  int high_score;
  int level;
  int speed;
  int figure_position_x;
  int figure_position_y;
  UserAction_t action;
} GameInfo_t;

void userInput(GameInfo_t* status);
void updateCurrentState(GameInfo_t* status);

void init_first_figure(GameInfo_t* status);
void generate_next_figure(GameInfo_t* status);
void get_Current_high_score(GameInfo_t* h_score);
void terminatePushButton(GameInfo_t* status);

void moveFigureLeft(GameInfo_t* status);
void moveFigureRight(GameInfo_t* status);
void moveFigureDown(GameInfo_t* status);
void rotateFigureClockwise(GameInfo_t* status);
void switch_to_next_figure(GameInfo_t* status);
void updateLevelandSpeed(GameInfo_t* status);
bool canMoveDown(GameInfo_t* status);

void dropFigure(GameInfo_t* status);
bool canPlaceFigure(GameInfo_t* status);
void check_and_remove_lines(GameInfo_t* status);
#endif  // end of S21_TETRIS_H