#include "s21_desktop_start.h"

void start_window() {
  curs_set(0);

  int click_button = 0;
  while (click_button != 'q') {
    attron(A_BOLD);
    attron(COLOR_PAIR(1));
    mvprintw(FIELD_WIDTH / 2, FIELD_LENGTH / 2, INTRO_MESSAGE);
    attroff(COLOR_PAIR(1));
    attroff(A_BOLD);
    click_button = getch();
    switch (click_button) {
      case '\n':
        erase();
        start_game();
        break;
    }
  }
}
