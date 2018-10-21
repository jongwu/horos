#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
void scheduler()
{
	int tmp=disp_pos;
	heartbeat++;
	disp_int(heartbeat);
	disp_pos=tmp;
}	
