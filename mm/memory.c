#include "page.h"

/* we use at most 16M memeory */
unsigned char page_map[4096];

/*
 * assume we have 16M memory
 * the contain of the set represents reference times
 */
void init_mem()
{
	/* kernel reserved memory lower than 1M */
	for(int i = 0; i < 256; i++)
	{
		page_map[i] = 100;
	}

	/* user can use memory higher than 1M */
	for(int i = 256; i < 4096; i++)
	{
		page_map[i] = 0;
	}
}

unsigned int get_free_page()
{
	for (int i = 256; i < 4096; i++)
	{
		if(page_map[i] == 0)
		{
			page_map[i] = 1;
			return 4096*i;
		}
	}
}

void free_page(unsigned int addr)
{
	if(addr/=4096 < 4096)
	mem_map[addr]=0;
}

