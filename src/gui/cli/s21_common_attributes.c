#include "s21_desktop_start.h"

void init_color_text() {
  init_pair(1, COLOR_RED, COLOR_BLACK);
  init_pair(2, COLOR_WHITE, COLOR_BLACK);
}
void free_field(int **field, int length) {
  for (int i = 0; i < length; ++i) {
    free(field[i]);
  }
  free(field);
}
void init_figures() { FIGURE_INIT(); }