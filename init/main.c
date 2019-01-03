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
void dispA();
void dispB();
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
//	disp_int(CMOS_READ(0));
//	thread_start(dispA, NULL); 
//	thread_start(dispB, NULL);
	sti();
//	time();
	do_shell();
/*	char *str="Hello, my friend. This is horos.\n";
	disp_str(str);
	wait();
	str = "I am a small operating system in developing.\n";
	disp_str(str);
	wait();
	str = "Jianyong Wu create me since July 1, 2018.\n";
	disp_str(str);
	wait();
	str = "If you are inteasted in me please clone me from https://github.com/jianyongwu/horos and develop me.\n";
	disp_str(str);
	wait();
	str = "Thank you\n";
	disp_str(str);
	wait();
	str="now,keyboard is enabled, so you can type words\n";
	disp_str("\n");
	disp_str(str);      */
//	int_n();
    while(1);
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

void wait()
{
	int i=0x7fffff;
	while(i--);
}


void dispA()
{
		int y=1000;
		while(1){
			int x=0x100000;
			while(x--);
			disp_str("~ ");
		}
}

void dispB()
{
	int y=1000;
	while(1){
		int x=0x100000;
		while(x--);
		disp_str("! ");
	}
}
