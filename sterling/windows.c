#include "windows.h"

void win_init_params(WIN *pwin, WIN *pprevwin) {

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
    	pwin->pnext = 0;
	pwin->pwindow = 0;
	if(pprevwin) {
		pprevwin->pnext = pwin;
	}
}

void win_draw_borders(WIN *pwin, bool bclear) {
	int i, j;
	int x, y, w, h;

	getbegyx(pwin->pwindow, y, x);
	getmaxyx(pwin->pwindow, h, w);

	

	if(bclear == 0) {
		wborder(pwin->pwindow, '|', '|', '-', '-', '+', '+', '+', '+');
	}
	else {
		for(j = y; j <= y + h; ++j)
			for(i = x; i <= x + w; ++i)
				mvaddch(j, i, ' ');
	}
	wrefresh(pwin->pwindow);
}
