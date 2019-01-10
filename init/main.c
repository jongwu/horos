#include "type.h"
#include "lib.h"
#include "global.h"
#include "idt.h"
#include "page.h"
#include "sche.h"
extern void print(char *msg, int len);
extern struct task* task_list[20];
void wait();
void disp_int(int input);
extern int task_number;
extern int task_max;
void time();
int main()
{
	clear_disp();
	init_idt();
	set_idtr();
	init_disp_pos();
	init_mem();
	start_paging();
	init_global(); 
	cmd_table_init();
	sti();
	do_shell();
	return 0;
}

void spurious_irq(int irq)
{
	clear_disp();
	disp_str("spurious_irq called\n");
        disp_int(irq);
        disp_str("\n");
}

void clear_disp()
{
        char *str="                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                    ";
        int len=leng(str);
        print(str,len);
}
