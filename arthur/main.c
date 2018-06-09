#define MATH_3D_IMPLEMENTATION
 
#include <ncurses.h>
#include <unistd.h>
#include <time.h>
#include <sys/times.h>

#include "math_3d.h"
#include "engine.h"

MESH* pcube = 0;
WINDOW *pwindow = 0;
CAMERA *pcamera = 0;
BUFFER *pbackbuffer = 0;

long GetTickCount()
{
    	struct tms tm;
    	return times(&tm);
}


void init_objects(void) {
	pcube = engine_new_mesh("Cube", 8);
/*
	pcube->pvertices[0] = vec3(-1, 1, 1);
	pcube->pvertices[1] = vec3(1, 1, 1);
	pcube->pvertices[2] = vec3(-1, -1, 1);
	pcube->pvertices[3] = vec3(-1, -1, -1);
	pcube->pvertices[4] = vec3(-1, 1, -1);
	pcube->pvertices[5] = vec3(1, 1, -1);
	pcube->pvertices[6] = vec3(1, -1, 1);
	pcube->pvertices[7] = vec3(1, -1, -1);
*/
	pcube->position = vec3(0, 0, -30);
	pcube->rotation = vec3(0, 0, 0);
}

void init_engine(void) {
	int x, y;
	getmaxyx(pwindow, y, x);
	pbackbuffer = engine_init_backbuffer(x, y);
	pcamera = engine_new_camera();

	//pcamera->position(0, 0, 10);
	//pcamera->target(0, 0, 0);
}

void init_display(void) {
	pwindow = initscr();
  	noecho();
	cbreak();
	keypad(stdscr, TRUE);
	//nodelay(pwindow, TRUE);

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
	init_pair(2, 2, 0);
	init_pair(3, 3, 0);
	init_pair(4, 4, 0);

}

int main(int argc, char *argv[]) {

	init_display();

	init_engine();

	init_objects();

	long previous = GetTickCount();
	long ctr = 0;
	bool brunning = true;
  	while(brunning) {
    		wclear(pwindow);

		engine_clear_backbuffer(pbackbuffer);

		engine_draw(pcamera, pcube, pbackbuffer);

		engine_render(pwindow, pbackbuffer);

		long current = GetTickCount();

		long fps = 1000.0 / (current - previous);

		char text[64];
		sprintf(text, "FPS:%u, time:%u", fps, current);
		mvwprintw(pwindow, 1, 1, text);

    		wrefresh(pwindow);

		//pcube->rotation = vec3(pcube->rotation.x+(0.01f*(current-previous)), pcube->rotation.y+(0.01f*(current-previous)), pcube->rotation.z);
		pcube->rotation = vec3(pcube->rotation.x, pcube->rotation.y+(0.01f), pcube->rotation.z);

		previous = current;

    		usleep(1000000.0/10.0);
  	}

	engine_kill_camera(pcamera);

	engine_kill_backbuffer(pbackbuffer);

  	endwin();

  	return 0;
}
