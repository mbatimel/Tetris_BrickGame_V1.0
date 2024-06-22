#include "s21_tetris.h"
void dropFigure(GameInfo_t* status) {
  while (canMoveDown(status)) {
    moveFigureDown(status);
  }
  switch_to_next_figure(status);
}
void check_and_remove_lines(GameInfo_t* status) {
  int count = 0;
  int check = 1;
  for (int i = FIELD_LENGTH - 2; i >= 1; i--) {
    for (int j = 1; j < FIELD_WIDTH - 1; j++) {
      if (status->field[i][j] != 1) {
        check = 0;
      }
    }

    if (check) {
      // Удаление заполненной строки
      for (int k = i; k > 0; k--) {
        for (int j = 0; j < FIELD_WIDTH - 1; j++) {
          status->field[k][j] = status->field[k - 1][j];
        }
      }
      count++;
    }
  }

  // Обновление счета
  switch (count) {
    case 1:
      status->score += 100;
      break;
    case 2:
      status->score += 300;
      break;
    case 3:
      status->score += 700;
      break;
    case 4:
      status->score += 1500;
      break;
    default:
      break;
  }
}

bool canPlaceFigure(GameInfo_t* status) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        int newY = status->figure_position_y + i;
        int newX = status->figure_position_x + j;
        if (newY >= FIELD_LENGTH || newX >= FIELD_WIDTH || newX < 0 ||
            status->field[newY][newX] == 1) {
          return false;
        }
      }
    }
  }
  return true;
}
void switch_to_next_figure(GameInfo_t* status) {
  check_and_remove_lines(status);
  // Устанавливаем текущую фигуру на поле
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }

  free_figure(status->current_figure);

  status->current_figure = status->next;
  status->next = NULL;
  status->figure_position_x = (FIELD_WIDTH - 4) / 2;
  status->figure_position_y = 0;
  generate_next_figure(status);

  if (!canPlaceFigure(status)) {
    status->action = Terminate;
  }
}

void updateLevelandSpeed(GameInfo_t* status) {
  switch (status->score) {
    case 0:
      status->level = 0;
      status->speed = 1200;
      break;
    case 100:
      status->level = 2;
      status->speed = status->level * 500;
      break;
    case 200:
      status->level = 3;
      status->speed = status->level * 300;
      break;
    case 300:
      status->level = 4;
      status->speed = status->level * 200;
      break;
    case 400:
      status->level = 5;
      status->speed = status->level * 100;
      break;
    case 500:
      status->level = 6;
      status->speed = status->level * 50;
      break;
    case 600:
      status->level = 7;
      status->speed = status->level * 40;
      break;
    case 700:
      status->level = 8;
      status->speed = status->level * 30;
      break;
    case 800:
      status->level = 9;
      status->speed = status->level * 20;
      break;
    case 900:
      status->level = 10;
      status->speed = status->level * 10;
      break;
    case 1000:
      status->level = 11;
      status->speed = status->level * 10;
      break;
    default:
      status->level = 12;
      status->speed = 10;
      break;
  }
}
