
#ifndef S21_ACTIONS_BTICKS_H
#define S21_ACTIONS_BTICKS_H
#include <curses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "s21_bricks.h"

figure* get_random_figure();
void free_figure(int** fig);
int** allocate_figure();
void copy_figure(int** dest, int src[4][4]);
int** allocate_field(int width, int length);
void free_fields(int** field, int length);
int get_user_input();
int* getInstance_ch();
void save_high_score(int high_score);
#endif  // end of  S21_ACTIONS_BTICKS_H