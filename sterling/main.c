
#include <stdlib.h>
#include <stdio.h>
#include <panel.h>
#include "windows.h"
#include "clock.h"

#define WINCOUNT 2
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
		if(pwin->bdirty==1) {
			win_draw_borders(pwin, 0);
			pwin->bdirty=0;
		}
		pwin=pwin->pnext;
	}
}

void main_create_windows() {
	pwindows[0] = malloc(sizeof(WIN));
	win_init_params(pwindows[0], NULL);
	pwindows[0]->pwindow = newwin(3, (COLS/2)-1, 0, 0);
	clock_init(pwindows[0]);

	pwindows[1] = malloc(sizeof(WIN));
	win_init_params(pwindows[1], pwindows[0]);
	pwindows[1]->pwindow = newwin(15, (COLS/2)-1, 6, 0);
}

void main_destroy_windows() {
	for(int c=0; c<WINCOUNT; c++) {
		free(pwindows[c]);
	}
}

