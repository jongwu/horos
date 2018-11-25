#ifndef HS_SCHE
#define HS_SCHE
#include "global.h"

#define PAGE_SIZE 1024

long long heartbeat;
typedef void thread_func(void*);

struct thread_stack{
        u32 ebp;
        u32 ebx;
        u32 ebi;
        u32 esi;
        void (*eip)(thread_func* func, void* func_arg);
        thread_func *func;
        void *func_arg;
};

enum task_status {
        RUNNING,
        READY,
        BLOCKED,
        WAITING,
        DIED
};

struct task {
        struct thread_stack *thread_stack;
        enum task_status status;
        u32 prio;
        u32 ticks;
        u32* pde;
        u32 magic;
};

void scheduler();
void thread_create(struct task *thread, thread_func function, void *arg);
void thread_start(thread_func function, void *arg);
void init_thread(struct task *thread, int proi);











#endif
