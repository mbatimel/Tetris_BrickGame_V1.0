#ifndef S21_DESKTOP_START_H
#define S21_DESKTOP_START_H
#include <ncurses.h>
#include <stdio.h>
#include <time.h>

#include "../../brick_game/tetris/s21_tetris.h"

#define INTRO_MESSAGE "--Press ENTER to start!--"

#define FIELD_WIDTH 10
#define FIELD_LENGTH 20
#define PLAY_GROUND int play_ground[FIELD_WIDTH][FIELD_LENGTH]

void start_window();
void init_color_text();
void init_play_ground();
void start_game();
void init_side_panel(GameInfo_t *status);

void print_next_figure(int side_panel_x, GameInfo_t *status);
void draw_figure_in_center(GameInfo_t *status);
void free_field(int **field, int length);
void print_field(GameInfo_t *status);

void init_figures();
#endif  // end of S21_DESKTOP_START_H