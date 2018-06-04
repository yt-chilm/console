#include <ncurses.h>
#include <unistd.h>

#include "math_3d.h"
#include "engine.h"

MESH* pcube = 0;
WINDOW *pwindow = 0;

void init_objects(void) {
	pcube = engine_new_mesh("Cube", 8);
	pcube->pvertices[0] = vec3(-1, 1, 1);
	pcube->pvertices[1] = vec3(1, 1, 1);
	pcube->pvertices[2] = vec3(-1, -1, 1);
	pcube->pvertices[3] = vec3(-1, -1, -1);
	pcube->pvertices[4] = vec3(-1, 1, -1);
	pcube->pvertices[5] = vec3(1, 1, -1);
	pcube->pvertices[6] = vec3(1, -1, 1);
	pcube->pvertices[7] = vec3(1, -1, -1);
}

void init_engine(void) {

}

void init_display(void) {
	pwindow = initscr();
  	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	nodelay(pwin, TRUE);
	noecho();

  	curs_set(0);

  	start_color();
/*
	init_color(0, 700, 0, 0);
	init_color(1, 700, 0, 0);
	init_color(2, 700, 0, 0);
	init_color(3, 700, 0, 0);
	init_color(4, 700, 0, 0);
	init_color(5, 700, 0, 0);
	init_color(6, 700, 0, 0);
	init_color(7, 700, 0, 0);
*/
	init_pair(COL_CUBE, 1, 0);

}

int main(int argc, char *argv[]) {

	init_display();

	init_engine();

	init_objects();

  	while(1) {
    		clear();

    		refresh();

    		usleep(166666);
  	}

  	endwin();

  	return 0;
}
