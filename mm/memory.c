#include "page.h"

/* we use at most 16M memeory */
unsigned char page_map[4096];

/*
 * assume we have 16M memory
 * the contain of the set represents reference times
 */
void init_mem(void)
{
	/* kernel reserved memory lower than 4M */
	for(int i = 0; i < 1024; i++)
	{
		page_map[i] = 100;
	}

	/* user can use memory higher than 4M */
	for(int i = 1024; i < 4096; i++)
	{
		page_map[i] = 0;
	}
}

void *get_free_page(void)
{
	for (int i = 1024; i < 4096; i++)
	{
		if(page_map[i] == 0)
		{
			page_map[i] = 1;
			i *= 4096;
			return (void *)i;
		}
	}

	return NULL;
}

void free_page(unsigned int addr)
{
	if((addr/=4096) < 4096)
	page_map[addr]=0;
}

void memset(char *p, int n, int num)
{
	if(num < 0) return;
	while(num--)
	{
		*p++ = n;
	}
}
