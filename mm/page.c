#include "page.h"
int *pde = 0, *pte = 0;
static inline void init_pde()
{
	pde=(void *)0;
	*pde = 0x1003;

}

static void init_pte()
{
	int i=-1;
	pte = (void *)0x1000;
	while(i++ < 1024)
	{
		*(pte + i) = 0x003 + i * 0x1000;
	}

}

static inline void open_paging()
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
	open_paging();
}
