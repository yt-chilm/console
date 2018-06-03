#include "control.h"

#define PROMPT "#:"

int cursor_x, cursor_y;
bool bcursor_on;
double delta_diff;
time_t last_time;
char input[256];
int inputlen;

void control_init(WIN *pwin) {
	pwin->handle_input = &control_handle_input;
	pwin->renderer = &control_render;
	control.pwin = pwin;
	cursor_y = 1;
	cursor_x = (int)strlen((char*)PROMPT)+1;
	bcursor_on = true;
	delta_diff = 0;
	last_time = time(NULL);
	inputlen=0;
}

void control_render(double delta) {

	WINDOW* pwin = control.pwin->pwindow;

	wclear(pwin);

	init_pair(3, COLOR_WHITE, COLOR_BLACK);

	wattron(pwin, COLOR_PAIR(3));

	mvwprintw(pwin, 1, 1, PROMPT);

	mvwprintw(pwin, cursor_y, cursor_x, "%s", input);

	if(bcursor_on)
		mvwprintw(pwin, cursor_y, cursor_x+(strlen(input)), "_");

	wattroff(pwin, COLOR_PAIR(3));

	//wrefresh(pwin);
}

void control_update() {

	time_t current;

	current = time(NULL);

	if(difftime(current, last_time)<1.0)
		return;

	bcursor_on=!bcursor_on;
	delta_diff=0;
	control.pwin->bdirty = 1;

	last_time=current;
}

void control_parse_input() {

	if(strstr(input, "exit")!=NULL) {
		exit(0);
	}
}

bool control_handle_input(int c) {
	switch(c) {
		case 10: // enter
			control_parse_input();
			memset(&input, 0, sizeof(char)*256);
			input[0] = '\0';
			inputlen=0;
		break;
		case KEY_BACKSPACE:
			input[--inputlen]='\0';
			return true;
		break;
		default:
			input[inputlen++]=c;
		break;
	}
	return false;
}
