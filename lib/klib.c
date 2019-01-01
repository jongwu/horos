
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            klib.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/

#include "type.h"
#include "const.h"
#include "protect.h"
#include "proto.h"
#include "global.h"
#include "lib.h"
extern void (*cmd_fun_table[10])(void *arg);
extern void print(char *msg, int len);
void poweroff();
void help();
/*======================================================================*
                               itoa
 *======================================================================*/
char * itoa1(char * str, int num)/* 数字前面的 0 不被显示出来, 比如 0000B800 被显示成 B800 */
{
        char *  p = str;
        int     i=0;
        int     a[10];
        int x=num;
//	*p++='0';
        while(x/=10)i++;
       for(int j=i; j>=0; j--)
        {
                a[j]=num%10;
                num/=10;
        }

        for(int j=0;j<=i;j++)
        {
                *p = a[j]+'0';
                p++;
        }
        *p=0;
        return str;
}


/*======================================================================*
                               disp_int
 *======================================================================*/
/*PUBLIC void disp_int(int input)
{
	char output[160];
	itoa(output, input);
	disp_str(output);
}*/
void init_disp_pos()
{
	disp_pos=0;
}

PUBLIC char * itoa(char * str, int num)/* 数字前面的 0 不被显示出来, 比如 0000B800 被显示成 B800 */
{
        char *  p = str;
        char    ch;
        int     i;
        t_bool  flag = FALSE;

        *p++ = '0';
        *p++ = 'x';

        if(num == 0){
                *p++ = '0';
        }
        else{
                for(i=28;i>=0;i-=4){
                        ch = (num >> i) & 0xF;
                        if(flag || (ch > 0)){
                                flag = TRUE;
                                ch += '0';
                                if(ch > '9'){
                                        ch += 7;
                                }
                                *p++ = ch;
                        }
                }
        }

        *p = 0;

        return str;
}
void disp_int(int input)
{
	char* output;
	itoa1(output, input);
	disp_str(output); 
}

void echo(char *buf)
{
	disp_str(buf);
}

void clear()
{
	init_disp_pos();
	int i = 2000;
	while(i--)disp_str(" ");
}

void poweroff()
{
	disp_str("poweroff has not been implimented yet, if you know how to do it, show me your code or just do it");
}

void cmd_table_init()
{
	CMD_NUM = 4;
	cmd_fun_table[0] = echo;
	cmd_fun_table[1] = clear;
	cmd_fun_table[2] = poweroff;
	cmd_fun_table[3] = help;
	cmd_table[0]="echo";
	cmd_table[1]="clear";
	cmd_table[2]="poweroff";
	cmd_table[3]="help";
	for(int i = 0; i < 20; i++)
	{
		kd_buf[i] = '\0';
	}
	p_kd_buf = 0;
}

int str_equal(char *p1, char *p2)
{
	while(*p1)
	{
		if(*p1++ != *p2++) return 0;
	}
	if(*p2)	return 0;
	return 1;
}

int leng(char *msg)
{
        int len = 0;
        while(msg[len]){
		len++;
        }
        return len;
}

void help()
{
	for(int i = 0; i < CMD_NUM; i++)
	{
		disp_str(cmd_table[i]);
		disp_str(", ");
	}
}
