#include "clock.h"

void clock_init(WIN *pwin) {
	console_clock.pwin = pwin;
}

void clock_update() {
	time_t current_time;
    	char* c_time_string;
	WINDOW* pwin = console_clock.pwin->pwindow;

	init_pair(1, COLOR_RED, COLOR_BLACK);

    	current_time = time(NULL);

    	c_time_string = ctime(&current_time);

	wattron(pwin, COLOR_PAIR(1));

	int err = mvwprintw(pwin, 1, 1, "%s", c_time_string);

	if(err==ERR)
		mvprintw(1,1,"Error rendering time");

	wrefresh(pwin);

	wattroff(pwin, COLOR_PAIR(1));
}
