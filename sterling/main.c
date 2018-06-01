#include <stdlib.h>
#include <stdio.h>
#include <panel.h>
#include "windows.h"
#include "clock.h"

#define WINCOUNT 5
#define SYSCOUNT 1

WIN *pwindows[WINCOUNT];
PANEL *ppanels[WINCOUNT];

void main_update_windows();
void main_create_windows();
void main_destroy_windows();

int main(int argc, char *argv[]) {

	void (*update_ptr_arr[])() = {clock_update};

	initscr();
	raw();
	cbreak();
	keypad(stdscr, TRUE);
	noecho();

	start_color();

	init_pair(1, COLOR_RED, COLOR_BLACK);
	init_pair(2, COLOR_GREEN, COLOR_BLACK);
	init_pair(3, COLOR_BLUE, COLOR_BLACK);
	init_pair(4, COLOR_CYAN, COLOR_BLACK);

	main_create_windows();

	while(1) {
		for(int c=0; c<SYSCOUNT; c++) {
			(*update_ptr_arr[c])();
		}

		main_update_windows();
		refresh();
		usleep(100000);
	}

	main_destroy_windows();
	endwin();

	return 0;
}

void main_update_windows() {
	WIN *pwin = pwindows[0];
	while(pwin) {
	//	if(pwin->bdirty==1) {
			wattron(pwin->pwindow, COLOR_PAIR(3));
			win_draw_borders(pwin, 0);
			wattroff(pwin->pwindow, COLOR_PAIR(3));
			pwin->bdirty=0;
	//	}
		pwin=pwin->pnext;
	}
}

void main_create_windows() {
	int x=0, y=0;
	pwindows[0] = malloc(sizeof(WIN));
	win_init_params(pwindows[0], NULL);
	pwindows[0]->pwindow = newwin(3, (COLS/2)-1, y, x);
	clock_init(pwindows[0]);

	y+=3;

	pwindows[1] = malloc(sizeof(WIN));
	win_init_params(pwindows[1], pwindows[0]);
	pwindows[1]->pwindow = newwin(LINES-3, (COLS/2)-1, y, x);

	x+=(COLS/2);
	y=0;

	pwindows[2] = malloc(sizeof(WIN));
	win_init_params(pwindows[2], pwindows[1]);
	pwindows[2]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);

	y+=(LINES/3);

	pwindows[3] = malloc(sizeof(WIN));
	win_init_params(pwindows[3], pwindows[2]);
	pwindows[3]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);

	y+=(LINES/3);

	pwindows[4] = malloc(sizeof(WIN));
	win_init_params(pwindows[4], pwindows[3]);
	pwindows[4]->pwindow = newwin((LINES/3), (COLS/2)-1, y, x);
}

void main_destroy_windows() {
	for(int c=0; c<WINCOUNT; c++) {
		free(pwindows[c]);
	}
}

