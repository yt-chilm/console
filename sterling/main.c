#include <stdlib.h>
#include <stdio.h>
#include <panel.h>
#include <time.h>
#include <sys/times.h>
#include <sys/types.h>
#include <unistd.h>

#include "windows.h"
#include "clock.h"

#define WINCOUNT 5
#define SYSCOUNT 1

WIN *pwindows[WINCOUNT];
PANEL *ppanels[WINCOUNT];

void main_update_windows(float interpol);
void main_create_windows();
void main_destroy_windows();

long GetTickCount()
{
    	struct tms tm;
    	return times(&tm);
}

int main(int argc, char *argv[]) {

	const int TICKS_PER_SECOND = 25;
	const int SKIP_TICKS = 1000 / TICKS_PER_SECOND;
	const int MAX_FRAMESKIP = 5;

	long next_system_tick = GetTickCount();
    	int loops;
    	float interpolation;

    	bool system_is_running = true;

	void (*update_ptr_arr[])() = {clock_update};

	initscr();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	main_create_windows();

	while(system_is_running) {

        	loops = 0;
        	while(GetTickCount() > next_system_tick && loops < MAX_FRAMESKIP) {
            		for(int c=0; c<SYSCOUNT; c++) {
				(*update_ptr_arr[c])();
			}

            		next_system_tick += SKIP_TICKS;
            		loops++;
        	}

        	interpolation = (GetTickCount() + SKIP_TICKS - next_system_tick) / (float)SKIP_TICKS;
        	main_update_windows(interpolation);
		refresh();
    	}

	main_destroy_windows();
	endwin();

	return 0;
}

void main_update_windows(float interpol) {
	WIN *pwin = pwindows[0];
	while(pwin) {
	//	if(pwin->bdirty==1) {
			win_draw_borders(pwin, 0);
			pwin->bdirty=0;
	//	}
		pwin=pwin->pnext;
	}
}

void main_create_windows() {
	int x=0, y=0;
	pwindows[0] = malloc(sizeof(WIN));
	win_init_params(pwindows[0], NULL, "Time & Date", "1");
	pwindows[0]->pwindow = newwin(3, (COLS/2)-1, y, x);
	clock_init(pwindows[0]);

	y+=3;

	pwindows[1] = malloc(sizeof(WIN));
	win_init_params(pwindows[1], pwindows[0], "$$$", "2");
	pwindows[1]->pwindow = newwin(LINES-3, (COLS/2)-1, y, x);

	x+=(COLS/2);
	y=0;

	pwindows[2] = malloc(sizeof(WIN));
	win_init_params(pwindows[2], pwindows[1], "£££", "3");
	pwindows[2]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);

	y+=(LINES/3);

	pwindows[3] = malloc(sizeof(WIN));
	win_init_params(pwindows[3], pwindows[2], "^^^", "4");
	pwindows[3]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);

	y+=(LINES/3);

	pwindows[4] = malloc(sizeof(WIN));
	win_init_params(pwindows[4], pwindows[3], "&&&", "5");
	pwindows[4]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);
}

void main_destroy_windows() {
	for(int c=0; c<WINCOUNT; c++) {
		free(pwindows[c]);
	}
}

