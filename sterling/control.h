#include <string.h>
#include <time.h>
#include <stdlib.h>
#include "windows.h"

typedef struct _control {
	WIN *pwin;
}CONTROL;

CONTROL control;

void control_init(WIN *pwin);
void control_render(double delta);
void control_update();
void contorl_parse_input();
bool control_handle_input(int c);
