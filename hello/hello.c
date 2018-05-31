#include <ncurses.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  
  initscr();
  noecho();
  curs_set(FALSE);

  while(1) {
    clear();

    mvprintw(rand()%40,rand()%100,"Hello, world!");

    refresh();

    usleep(100000);
  }

  endwin();

  return 0;
}
