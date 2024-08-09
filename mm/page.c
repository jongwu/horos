#include "page.h"
int *pde = 0, *pte = 0;

void start_paging(void)
{
	init_pde();
	init_pte();
	open_paging();
}


void init_pte(void)
{
	int i=-1, j = -1;
	pte = (void *)(START_PAGING_ADDR +0x1000);
	while(++j < 1024)
	{
		i = -1;
		while(++i < 1024)
		{
			*(pte + j*1024 + i) = 0x003 + j * 0x1000 * 0x1000 + i * 0x1000;
		}
	}
}

