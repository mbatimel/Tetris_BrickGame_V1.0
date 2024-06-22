#include "gui/cli/s21_desktop_start.h"

int main() {
  initscr();
  cbreak();
  start_color();
  init_color_text();
  keypad(stdscr, TRUE);
  nodelay(stdscr, TRUE);
  noecho();
  init_figures();
  start_window();
  endwin();
  return 0;
}