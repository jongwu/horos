#include "type.h"
#include "lib.h"
#include "global.h"
#include "idt.h"
extern void print(char *msg, int len);
int leng(char *msg);
void init_disp_pos();
int main()
{
	init_idt();
	set_idtr();
	init_disp_pos();
	clear_disp();
        char *str="Hello, my friend. This is horos. I am a small operating system in developing. Jianyong Wu create me since July 1, 2018. If you are inteasted in me please clone me from https://github.com/jianyongwu/horos and develop me. Thank you\n";
	disp_str(str);
	str="now, I just begin to boot kernel, but this kernel is nothing else beside print some words\n";
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
        disp_int(irq);
        disp_str("\n");
}

void disp_int(int input)
{
	disp_str("spurious_irq called\n");
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
