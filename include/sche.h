#ifndef HS_SCHE
#define HS_SCHE

long long heartbeat;
void scheduler();
typedef void thread_func(void*);
void thread_create(struct task_struct* pthread, thread_func func, void *arg);
void init_thread(struct task_struct* pthread, int prio);
struct task_struct* thread_start(thread_func func, void *arg);











#endif
