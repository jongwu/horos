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

struct task task_list[20];
u32 task_number=0, task_max=0;

void scheduler()
{
	struct task cur, next;
	if(task_max < 1)
		return;
	if(task_number < task_max)
	{
		cur = task_list[task_number % task_max];
		next = task_list[(task_number + 1) % task_max];
		task_number++;
//		switch_to(cur, next);
	}
	
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
