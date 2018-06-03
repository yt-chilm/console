#include "clock.h"

void clock_init(WIN *pwin) {
	pwin->handle_input = &clock_handle_input;
	pwin->renderer = &clock_render;
	console_clock.pwin = pwin;
}

void clock_render(double delta) {

	int x, y;

	WINDOW* pwin = console_clock.pwin->pwindow;

	init_pair(1, COLOR_GREEN, COLOR_BLACK);

	wattron(pwin, COLOR_PAIR(1));

	mvwprintw(pwin, 1, 2, "%s", console_clock.str_displaytime);

	getmaxyx(pwin, y, x);

	int len = strlen(console_clock.str_realdate);
	mvwprintw(pwin, 1, x-len-1, "%s", console_clock.str_realdate);

	//wrefresh(pwin);

	wattroff(pwin, COLOR_PAIR(1));
}

void clock_update() {
	time_t current_time;
	struct tm *loc_time;
    	char* c_time_string;
	double diff_t;

    	current_time = time(NULL);

	diff_t = difftime(current_time, console_clock.last_time);

	if(diff_t < 1.0)
		return;

	loc_time = localtime(&current_time);

    	c_time_string = asctime(loc_time);

	if(console_clock.bshowunix)
		sprintf(console_clock.str_displaytime, "%u", (unsigned)current_time);
	else
		strftime(console_clock.str_displaytime, 32, "%H:%M:%S\n", loc_time);

	strftime(console_clock.str_realdate, 64, "Today is %A, %b %d\n", loc_time);

	console_clock.last_time = current_time;

	console_clock.pwin->bdirty = 1;
}

bool clock_handle_input(int c) {
	switch(c) {
		case 't':
		case 'T':
			console_clock.bshowunix=!console_clock.bshowunix;
		break;
		default:
		break;
	}
	return false;
}
