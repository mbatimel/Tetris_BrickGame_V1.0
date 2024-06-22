#include "s21_actions_bricks.h"

figure I = {0};
figure O = {0};
figure J = {0};
figure L = {0};
figure S = {0};
figure Z = {0};
figure T = {0};

__attribute__((constructor)) static void init_figures() { FIGURE_INIT(); }

void copy_figure(int** dest, int src[4][4]) {
  for (int i = 0; i < 4; ++i) {
    for (int j = 0; j < 4; ++j) {
      dest[i][j] = src[i][j];
    }
  }
}
void free_fields(int** field, int length) {
  if (field == NULL) return;  // Проверка на NULL

  for (int i = 0; i < length; ++i) {
    if (field[i] != NULL) {
      free(field[i]);
    }
  }
  free(field);
}
void free_figure(int** fig) {
  if (fig == NULL) return;  // Проверка на NULL

  for (int i = 0; i < 4; ++i) {
    if (fig[i] != NULL) {
      free(fig[i]);
    }
  }
  free(fig);
}

figure* get_random_figure() {
  switch (rand() % 7) {
    case 0:
      return &I;
    case 1:
      return &O;
    case 2:
      return &J;
    case 3:
      return &L;
    case 4:
      return &S;
    case 5:
      return &Z;
    case 6:
      return &T;
    default:
      return &I;
  }
}
int** allocate_field(int width, int length) {
  int** field = (int**)calloc(length, sizeof(int*));
  if (field == NULL) {
    return NULL;  // Проверка на ошибку выделения памяти
  }
  for (int i = 0; i < length; ++i) {
    field[i] = (int*)calloc(width, sizeof(int));
    if (field[i] == NULL) {
      for (int j = 0; j < i; ++j) {
        free(field[j]);
      }
      free(field);
      return NULL;  // Проверка на ошибку выделения памяти
    }
  }
  return field;
}

int** allocate_figure() {
  int** figure = (int**)malloc(4 * sizeof(int*));
  if (figure == NULL) {
    return NULL;  // Проверка на ошибку выделения памяти
  }
  for (int i = 0; i < 4; ++i) {
    figure[i] = (int*)malloc(4 * sizeof(int));
    if (figure[i] == NULL) {
      for (int j = 0; j < i; ++j) {
        free(figure[j]);
      }
      free(figure);
      return NULL;  // Проверка на ошибку выделения памяти
    }
  }
  return figure;
}
int* getInstance_ch() {
  static int ch;
  return &ch;
}
int get_user_input() {
  int ch = getch();
  return ch;
}
void save_high_score(int high_score) {
  char buffer[256] = {'\0'};
  sprintf(buffer, "%d", high_score);
  const char* filename = "brick_game/tetris/high_score.txt";
  FILE* fp = fopen(filename, "w");
  if (fp) fputs(buffer, fp);
  fclose(fp);
}