#include <time.h>
#include "windows.h"

typedef struct _clock {
	WIN *pwin;
	time_t last_time;
}CLOCK;

CLOCK console_clock;

void clock_init(WIN *pwin);
void clock_update();
