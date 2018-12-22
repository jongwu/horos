#ifndef __PAGE__
#define __PAGE__
#include "global.h"

static inline void init_pde();
static void init_pte();
static inline void open_paging();
void start_paging();
void* get_free_page();
void memset(char*, int, int);

















#endif
