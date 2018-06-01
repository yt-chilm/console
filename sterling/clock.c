#include "clock.h"

void clock_init(WIN *pwin) {
	console_clock.pwin = pwin;
}

void clock_update() {
	time_t current_time;
	struct tm *loc_time;
    	char* c_time_string;
	char buf[256];
	int x, y;
	WINDOW* pwin = console_clock.pwin->pwindow;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);

    	current_time = time(NULL);

	loc_time = localtime(&current_time);

    	c_time_string = asctime(loc_time);

	strftime(buf, 256, "%H:%M:%S\n", loc_time);

	wattron(pwin, COLOR_PAIR(1));

	mvwprintw(pwin, 1, 2, "%s", buf);

	int len = strftime (buf, 256, "Today is %A, %b %d\n", loc_time);

	getmaxyx(pwin, y, x);

	mvwprintw(pwin, 1, x-len-1, "%s", buf);

	wrefresh(pwin);

	wattroff(pwin, COLOR_PAIR(1));
}
