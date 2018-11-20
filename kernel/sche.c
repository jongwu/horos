#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
void dispA();
void dispB();
struct thread_stack{
	u32 ebp;
	u32 ebx;
	u32 ebi;
	u32 esi;
	void (*eip)(thread_func* func, void* func_arg);
};

enum task_status {
	RUNNING,
	READY,
	BLOCKED,
	WAITING,
	DIED
};
	
struct task {
	void *thread_stack;
	enum task_status status;
	u32 prio;
	u32 ticks;
	u32* pde;
	u32 magic;
};

void scheduler()
{

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
