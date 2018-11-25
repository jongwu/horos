#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
#include "page.h"
void dispA();
void dispB();

struct task *task_list[20];
u32 task_number=0, task_max=0;
void thread_function(thread_func function, void *arg)
{
        function(arg);
}

void scheduler()
{
	struct task *cur,*next;
	if(task_max < 2)
		return;
	if(task_number < task_max)
	{
		cur = task_list[task_number % task_max];
		next = task_list[(task_number + 1) % task_max];
		task_number++;
		task_number %= task_max;
		cur->status = READY;
		switch_to(cur, next);
	}
	
}	

void init_thread(struct task *thread, int proi)
{
	disp_str("go into init_thread\n");
	memset(thread, 0, 4096);
	thread->status = RUNNING;
	thread->thread_stack = thread + PAGE_SIZE;
}

void thread_create(struct task *thread, thread_func function, void *arg)
{
	disp_str("go into thread_creat\n");
	thread->thread_stack -= sizeof(thread);
	thread->thread_stack->eip = thread_function;
	thread->thread_stack->func = function;
	thread->thread_stack->func_arg = arg;
	thread->thread_stack->ebp = 0;
	thread->thread_stack->ebx = 0;
	thread->thread_stack->ebi = 0;
	thread->thread_stack->esi = 0;
}

void thread_start(thread_func function, void *arg)
{
	disp_str("go into thread_start\n");
	struct task *thread = get_free_page();
	disp_int((int)thread);
	disp_str("\n");
	init_thread(thread, 0);
	thread_create(thread, function, arg);
	task_list[task_max++] = thread; 
}

