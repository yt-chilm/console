#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  
  initscr();
  noecho();
  curs_set(FALSE);

  start_color();

  while(1) {
    clear();

    if(can_change_color()) {
      init_color(COLOR_RED, rand()%1000, rand()%1000, rand()%1000);
    }

    init_pair(1, COLOR_RED, COLOR_BLACK);

    attrset(COLOR_PAIR(1));

    mvprintw(rand()%40,rand()%100,"Hello, world!");

    refresh();

    usleep(250000);
  }

  endwin();

  return 0;
}
