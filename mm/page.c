#include "page.h"
static inline void init_pde()
{
	int *pde=0, i=0;
	*pde = 0x1113;
	while(i++ < 1023)
	{
		*(pde + i) = 0x10000;
	}

}

static void init_pte()
{
	int *pte = 0x1000;
	int i=-1;
	while(i++ < 256)
	{
		*(pte + i) = 0x113 + i * 0x1000;
	}

}

void open_paging()
{
	__asm__ __volatile__ ("movl %0, %%cr3":: "r"(0));
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
