#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
void dispA();
void dispB();
struct task {
	unsigned int cs;
	unsigned int eip;
};
int current = 0;
	struct task ptask[2]={{0x10, dispA},{0x10, dispB}};
void scheduler()
{
	disp_str("S");
	ptask[0].cs=0x10;
	ptask[0].eip=dispA-0xb000;
	ptask[1].cs=0x10;
	ptask[1].eip=dispB-0xb000;
	unsigned int ip = ptask[(++current)%2].eip;
	
//	disp_int(ptask[0].eip);
	__asm__ __volatile__ ("call %0":: "r"(ip)); 

}	

void dispA()
{
//	while(1)
	{
		int x=0x100000;
		while(x--);
		disp_str("process A is running");
	}
}

void dispB()
{
//	while(1)
	{
		int x=0x100000;
		while(x--);
		disp_str("process B is running");
	}
}
