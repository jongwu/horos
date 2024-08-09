#ifndef __PAGE__
#define __PAGE__
#include "global.h"

void start_paging(void);
void* get_free_page(void);
void free_page(unsigned int addr);
void init_mem(void);
void memset(char*, int, int);
void init_pte(void);

extern int *pde;
extern int *pte;
#define START_PAGING_ADDR (236 * 1024 * 1024)
static inline void init_pde(void)
{
	pde=(void *)(START_PAGING_ADDR);
	int i = -1;
	while(++i < 1024)
		*(pde + i) = 0x003 + i * 0x1000 + START_PAGING_ADDR + 0x1000;

}

static inline void open_paging(void)
{
	__asm__ __volatile__ ("movl %0, %%cr3":: "r"(START_PAGING_ADDR));
	__asm__ __volatile__ ("movl %%cr0, %%eax" :: );
	__asm__ __volatile__ ("or %0, %%eax" ::"i"(0x80000000));
	__asm__ __volatile__ ("movl %%eax, %%cr0" ::);
}
















#endif
