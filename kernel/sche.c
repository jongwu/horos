#include "sche.h"
#include "lib.h"
#include "type.h"
#include "global.h"
#include "page.h"
void dispA();
void dispB();
static void init_task();
void ret_from_intr();
struct task *task_list[20], *current;
int task_number, task_max;
void fun();
void thread_function(thread_func function, void *arg)
{
        function(arg);
}

struct task* running_task()
{
	u32 esp;
	__asm__ ("movl %%esp, %0":"=g"(esp));
	return (struct task *) (esp & 0xfffff000);
}

void scheduler()
{
	struct task *cur=current, *next;
	if(task_max < 2)
		return;
	if(task_number < task_max)
	{
		disp_str("* ");
		next = task_list[(task_number) % task_max];
		current = next;
		task_number++;
		task_number %= task_max;
		cur->status = READY;
		next->status = RUNNING;
		switch_to(cur, next);
	}
}	

void init_thread(struct task *thread, int proi)
{
	disp_str("go into init_thread\n");
	memset(thread, 0, 4096);
	int tmp = (int)thread + PAGE_SIZE;
	thread->t_stack = (void *)tmp;
}

void thread_create(struct task *thread, thread_func function, void *arg)
{
	disp_str("go into thread_creat\n");
	int tmp = (int)thread->t_stack - sizeof(struct thread_stack);
	thread->t_stack = (void*)tmp;
	disp_int(thread->t_stack);
	disp_str("\n");
	thread->t_stack->ret = ret_from_intr;
	thread->t_stack->eip = thread_function;
//	thread->t_stack->eip = fun;
	thread->t_stack->func = function;
	thread->t_stack->func_arg = arg;
	thread->t_stack->unused = '&';
	thread->t_stack->ebp = 'a';
	thread->t_stack->ebx = 'b';
	thread->t_stack->ebi = 'c';
	thread->t_stack->esi = 'd';

}

void thread_start(thread_func function, void *arg)
{
	disp_str("go into thread_start\n");
	int *p = get_free_page();
	struct task *thread = get_free_page();
	
	thread->proi = 0;
	thread->status = RUNNING;
	
	init_thread(thread, 0);
	thread_create(thread, function, arg);
	task_list[task_max++] = thread; 

}

void init_global()
{
	task_number = 0;
	task_max = 0;
}

