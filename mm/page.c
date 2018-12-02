#include "page.h"
int *pde = 0, *pte = 0;
#define START_PAGING_ADDR (236 * 1024 * 1024)
static inline void init_pde()
{
	pde=(void *)(START_PAGING_ADDR);
	int i = -1;
	while(i++ < 1024)
		*(pde + i) = 0x003 + i * 0x1000 + START_PAGING_ADDR + 0x1000;

}

static void init_pte()
{
	int i=-1, j = -1;
	pte = (void *)(START_PAGING_ADDR +0x1000);
	while(j++ < 1024)
	{
		while(i++ < 1024)
		{
			*(pte + j*1024 + i) = 0x003 + j * 0x1000 * 0x1000 + i * 0x1000;
		}
	}
}

static inline void open_paging()
{
	__asm__ __volatile__ ("movl %0, %%cr3":: "r"(START_PAGING_ADDR));
	__asm__ __volatile__ ("movl %%cr0, %%eax" :: );
	__asm__ __volatile__ ("or %0, %%eax" ::"i"(0x80000000));
	__asm__ __volatile__ ("movl %%eax, %%cr0" ::);
}

void start_paging()
{
	init_pde();
	init_pte();
//	open_paging();
}
