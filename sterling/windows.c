#include "windows.h"

void win_init_params(WIN *pwin, WIN *pprevwin, char *pname, char *pkey) {

	pwin->border.ls = '|';
    	pwin->border.rs = '|';
    	pwin->border.ts = '-';
    	pwin->border.bs = '-';
    	pwin->border.tr = '+';
    	pwin->border.tl = '+';
    	pwin->border.br = '+';
    	pwin->border.bl = '+';

    	pwin->color_text.red = rand()%1000;
    	pwin->color_text.green = rand()%1000;
    	pwin->color_text.blue = rand()%1000;
    	pwin->color_bk.red = 0;
    	pwin->color_bk.green = 0;
    	pwin->color_bk.blue = 0;
	pwin->bdirty = 1;

	pwin->ptitle = pname;
	pwin->pkey = pkey;

    	pwin->pnext = 0;
	pwin->pwindow = 0;
	if(pprevwin) {
		pprevwin->pnext = pwin;
	}
}

void win_draw_borders(WIN *pwin, bool bclear) {
	int i, j;
	int x, y, w, h;
	short int or, og, ob;

	getbegyx(pwin->pwindow, y, x);
	getmaxyx(pwin->pwindow, h, w);

	color_content(COLOR_RED, &or, &og, &ob);

	init_color(COLOR_RED, pwin->color_text.red, pwin->color_text.green, pwin->color_text.blue);

	init_pair(9, COLOR_RED, COLOR_BLACK);

	wattron(pwin->pwindow, COLOR_PAIR(9));

	if(bclear == 0) {
		wborder(pwin->pwindow, pwin->border.ls, pwin->border.rs, 
					pwin->border.ts, pwin->border.bs, 
					'+', '+', '+', '+');
	}
	else {
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	}

	init_pair(8, COLOR_WHITE, COLOR_BLACK);

	wattron(pwin->pwindow, COLOR_PAIR(8));

	mvwprintw(pwin->pwindow, 0, 2, " %s ", pwin->ptitle);

	mvwprintw(pwin->pwindow, 0, w-5, "[%s]", pwin->pkey);

	wattroff(pwin->pwindow, COLOR_PAIR(8));
	wattroff(pwin->pwindow, COLOR_PAIR(9));

	wrefresh(pwin->pwindow);

	init_color(COLOR_RED, or, og, ob);
}
