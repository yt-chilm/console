#ifndef _WINDOWS_H_
#define _WINDOWS_H_

#include <panel.h>
#include <stdbool.h>

typedef struct _win WIN;

typedef struct _win_borders {
	char ls, rs, ts, bs, tl, tr, bl, br; 
}WIN_BORDER;

typedef struct _win_color {
	int red;
	int green;
	int blue;
}WIN_COLOR;

typedef struct _win {
	int x, y;
	int w, h;
	WIN_BORDER border;
	WIN_COLOR color_text;
	WIN_COLOR color_bk;
	bool bdirty;
	WINDOW *pwindow;
	WIN *pnext;
}WIN;

void win_init_params(WIN *pwin, WIN *pprevwin);
void win_draw_borders(WIN *pwin, bool bclear);

#endif
