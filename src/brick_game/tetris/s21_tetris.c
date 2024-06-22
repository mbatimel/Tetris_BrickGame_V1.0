#include "s21_tetris.h"

void get_Current_high_score(GameInfo_t* h_score) {
  const char* filename = "brick_game/tetris/high_score.txt";
  FILE* fp = fopen(filename, "r+");

  if (fp) {
    char buffer[256] = {'\0'};
    if (fgets(buffer, sizeof(buffer), fp) != NULL) {
      sscanf(buffer, "%d", &h_score->high_score);
    }
    fclose(fp);
  } else {
    h_score->high_score = 0;
  }
}

void updateCurrentState(GameInfo_t* status) {
  updateLevelandSpeed(status);
  int ch = get_user_input();
  int* p_ch = getInstance_ch();
  *p_ch = ch;

  if (status->action != Terminate) {
    switch (ch) {
      case 'Q':
      case 'q':
        status->action = Terminate;
        break;
      case KEY_UP:
        status->action = Up;
        break;
      case KEY_LEFT:
        status->action = Left;
        break;
      case KEY_RIGHT:
        status->action = Right;
        break;
      case KEY_DOWN:
        status->action = Down;
        break;
      case ' ':
        status->action = Action;
        break;
      case 'P':
      case 'p':
        status->action = Pause;
        *p_ch = 0;
        break;
      default:
        status->action = Action;
        break;
    }
  }
}

void userInput(GameInfo_t* status) {
  switch (status->action) {
    case Terminate:
      status->action = Terminate;
      break;
    case Up:
      rotateFigureClockwise(status);
      status->action = Action;
      break;
    case Left:
      moveFigureLeft(status);
      status->action = Action;
      break;
    case Right:
      moveFigureRight(status);
      status->action = Action;
      break;
    case Down:

      dropFigure(status);
      status->action = Action;
      break;
    case Action:
      moveFigureDown(status);
      break;
    case Start:
      init_first_figure(status);
      generate_next_figure(status);
      status->action = Action;
      break;
    case Pause:
      break;
    default:
      break;
  }
}

void init_first_figure(GameInfo_t* status) {
  figure* random_figure = get_random_figure();

  status->current_figure = allocate_figure();
  status->figure_position_x = (FIELD_WIDTH - 4) / 2;
  status->figure_position_y = 0;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      status->current_figure[i][j] = random_figure->fig[i][j];
    }
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }
}

void generate_next_figure(GameInfo_t* status) {
  if (status->next != NULL) {
    free_figure(status->next);
  }
  status->next = allocate_figure();
  copy_figure(status->next, get_random_figure()->fig);
}

void terminatePushButton(GameInfo_t* status) {
  free_fields(status->field, FIELD_LENGTH);
  free_figure(status->next);
  free_figure(status->current_figure);
  status->score = 0;
  if (status->score > status->high_score) {
    status->high_score = status->score;
  }
  save_high_score(status->high_score);
  status->level = 0;
  status->speed = 1;
  status->action = Terminate;
}

void moveFigureLeft(GameInfo_t* status) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        if (status->figure_position_x + j - 1 <= 0) {
          return;
        }
      }
    }
  }

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 0;
      }
    }
  }

  status->figure_position_x--;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }
}
void moveFigureRight(GameInfo_t* status) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        if (status->figure_position_x + j + 1 >= 9) {
          return;
        }
      }
    }
  }
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 0;
      }
    }
  }

  status->figure_position_x++;

  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }
}
#include <stdbool.h>

bool canMoveDown(GameInfo_t* status) {
  int res = 1;
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        int newX = status->figure_position_x + j;
        int newY = status->figure_position_y + i;

        if (newY >= 18) {
          res = 0;
        } else if (status->field[newY + 1][newX] == 1) {
          int temp_res = 0;
          for (int k = 0; k < 4; ++k) {
            for (int l = 0; l < 4; ++l) {
              if (status->current_figure[k][l] == 1) {
                int tempX = status->figure_position_x + l;
                int tempY = status->figure_position_y + k;

                if (tempY == newY + 1 && tempX == newX) {
                  temp_res++;
                }
              }
            }
          }
          if (!temp_res) {
            res = 0;
          }
        }
      }
    }
  }
  return res;
}

void moveFigureDown(GameInfo_t* status) {
  // Проверка возможности перемещения фигуры вниз
  if (!canMoveDown(status)) {
    switch_to_next_figure(status);
    return;
  }

  // Удаляем старую позицию фигуры
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 0;
      }
    }
  }

  // Перемещаем фигуру вниз
  status->figure_position_y++;

  // Обновление новой позиции фигуры на поле
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }
}

void rotateFigureClockwise(GameInfo_t* status) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      if (status->current_figure[i][j] == 1) {
        if (status->figure_position_x + j + 1 >= 9 ||
            status->figure_position_y + i + 1 >= 19 ||
            status->figure_position_y + i - 1 <= 0 ||
            status->figure_position_x + j - 1 <= 0) {
          return;
        }
      }
    }
  }
  int size = 4;
  int new_figure[4][4] = {0};

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      new_figure[j][size - 1 - i] = status->current_figure[i][j];
    }
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 0;
      }
    }
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      status->current_figure[i][j] = new_figure[i][j];
    }
  }

  for (int i = 0; i < size; ++i) {
    for (int j = 0; j < size; ++j) {
      if (status->current_figure[i][j] == 1) {
        status->field[status->figure_position_y + i]
                     [status->figure_position_x + j] = 1;
      }
    }
  }
}