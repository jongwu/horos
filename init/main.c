#include "type.h"
#include "lib.h"
#include "global.h"
#include "idt.h"
#include "page.h"
extern void print(char *msg, int len);
int leng(char *msg);
void wait();
void disp_int(int input);
int main()
{
	init_idt();
	set_idtr();
	init_disp_pos();
	start_paging();
	open_paging();
	clear_disp();
	char x=57;
/*	for(int i=0;i<10;i++)
	{
		char tmp=x-i;
		disp_char(tmp);
		wait();
	}*/
	sti();
	char *str="Hello, my friend. This is horos.\n";
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
	disp_str(str);      
//	int_n();
    while(1);
    return 0;
}

int leng(char *msg)
{
        int len=0;
        while(msg[len]){
                len++;
        }
        return len;
}

void spurious_irq(int irq)
{
	clear_disp();
	disp_str("spurious_irq called\n");
        disp_int(irq);
        disp_str("\n");
}

void disp_int(int input)
{
        char* output;
        itoa(output, input);
        disp_str(output); 
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
