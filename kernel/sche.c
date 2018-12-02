#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
#include "page.h"
void dispA();
void dispB();
static void init_task();
struct task *task_list[20];
int task_number=10, task_max;
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
	thread->t_stack = (void *)(thread + PAGE_SIZE);
}

void thread_create(struct task *thread, thread_func function, void *arg)
{
	disp_str("go into thread_creat\n");
	disp_str("go into thread_creat\n");
	int tm = sizeof(struct thread_stack);
	disp_int(tm);
	disp_str("\n");
	void *tmp = thread->t_stack;
/*	thread->t_stack -= sizeof(struct thread_stack);
	thread->t_stack->eip = thread_function;
	thread->t_stack->func = function;
	thread->t_stack->func_arg = arg;
	thread->t_stack->ebp = 0;
	thread->t_stack->ebx = 0;
	thread->t_stack->ebi = 0;
	thread->t_stack->esi = 0;
*/
}

void thread_start(thread_func function, void *arg)
{
	disp_int(task_number);
	init_task();
	disp_str("go into thread_start\n");
	struct task *thread = get_free_page();
	struct task tmp = *thread;
	thread->proi = 0;
	thread->status = RUNNING;
	
	disp_int((int)thread);
	disp_str("\n");
	init_thread(thread, 0);
	thread_create(thread, function, arg);
	disp_str("aaaaaaaaaaa\n");
	task_list[task_max++] = thread; 
/*	task_list[0]= thread;
	disp_int(task_max);
		disp_str("\n");
	disp_int(task_number);
*/
}

static void init_task()
{
	disp_str("go into init task\n");
	int i=0;
	i=0;
	disp_str("i=");
	disp_int(i);
	disp_str("\n");
	if(i==0)
	{
		disp_str("go into set task number\n");
		task_number = 0;
		task_max = 0;
		disp_int(task_number);
		disp_str("\n");
	}
	i++;
}
