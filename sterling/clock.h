#include <time.h>
#include <string.h>
#include "windows.h"

typedef struct _clock {
	WIN *pwin;
	time_t last_time;
	bool bshowunix;
	char str_displaytime[32];
	char str_realdate[64];
}CLOCK;

CLOCK console_clock;

void clock_init(WIN *pwin);
void clock_render(double delta);
void clock_update();
bool clock_handle_input(int c);
