#include "s21_desktop_start.h"
void start_game() {
  srand(time(NULL));
  UserAction_t ua_t;
  ua_t = Start;
  GameInfo_t statusgame = {NULL, NULL, NULL, 0, 0, 1, 1000, 0, 0, ua_t};
  statusgame.field = allocate_field(FIELD_WIDTH, FIELD_LENGTH);
  userInput(&statusgame);
  draw_figure_in_center(&statusgame);

  while (statusgame.action != Terminate) {
    updateCurrentState(&statusgame);

    if (statusgame.action != Pause) {
      userInput(&statusgame);
      if (statusgame.action == Action) {
        moveFigureDown(&statusgame);  // Автоматическое опускание фигуры
      }
    }
    erase();
    init_side_panel(&statusgame);
    print_field(&statusgame);
    refresh();
    napms(statusgame.speed);
  }

  terminatePushButton(&statusgame);
  erase();
  refresh();
}

void init_side_panel(GameInfo_t *status) {
  get_Current_high_score(status);
  int side_panel_x = FIELD_WIDTH + 6;
  mvprintw(0, side_panel_x, "Side Panel");
  mvprintw(2, side_panel_x, "Level: %d", status->level);
  mvprintw(3, side_panel_x, "Score: %d", status->score);
  mvprintw(4, side_panel_x, "Speed: %d", status->speed / 100);
  mvprintw(5, side_panel_x, "High Score: %d", status->high_score);
  mvprintw(6, side_panel_x, "Next");
  print_next_figure(side_panel_x, status);
  refresh();
}

void init_play_ground() {
  for (int y = 0; y < FIELD_LENGTH; y++) {
    for (int x = 0; x < FIELD_WIDTH; x++) {
      if (y == FIELD_LENGTH - 1 || y == 0) {
        mvprintw(y, x, "*");
      } else if (x == FIELD_WIDTH - 1 || x == 0) {
        mvprintw(y, x, "*");
      }
    }
  }
}

void print_next_figure(int side_panel_x, GameInfo_t *status) {
  if (status->next == NULL) return;  // Проверка на NULL

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->next[i][j] == 1) {
        mvprintw(7 + i, side_panel_x + j, ".");
      } else {
        mvprintw(7 + i, side_panel_x + j, " ");
      }
    }
  }
}

void draw_figure_in_center(GameInfo_t *status) {
  if (status->current_figure == NULL) return;  // Проверка на NULL

  int center_x = FIELD_WIDTH / 2 - 2;
  int center_y = 0;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j]) {
        status->field[center_y + i][center_x + j] =
            status->current_figure[i][j];
      }
    }
  }
}

void print_field(GameInfo_t *status) {
  for (int i = 0; i < FIELD_LENGTH; ++i) {
    for (int j = 0; j < FIELD_WIDTH; ++j) {
      if (status->field[i][j] == 1) {
        mvprintw(i, j, ".");
      } else if (i == 0 || i == FIELD_LENGTH - 1 || j == 0 ||
                 j == FIELD_WIDTH - 1) {
        mvprintw(i, j, "*");
      } else {
        mvprintw(i, j, " ");
      }
    }
  }
}
