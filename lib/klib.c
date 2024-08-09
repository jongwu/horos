
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
void poweroff(void);
void help(void);
extern void pprint(char,int);
void snow(char*);
void sleep(int t);
void help(void);
void regist_cmd(char *name, void *func);
void time(void);
void poweroff(void);
void clear(void);
void echo(char *buf);
PUBLIC char * itoa(char * str, int num);
void init_disp_pos(void);
char * itoa1(char * str, int num);
extern int disp_pos;
#define BCD_TO_DEC(val) \
(((val) & 15)  + ((val) >> 4) * 10)

struct time_val{
	int sec;
	int min;
	int hour;
	int day;
	int mon;
	int year;
};

/*======================================================================*
                               itoa
 *======================================================================*/
char * itoa1(char * str, int num)
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
void init_disp_pos(void)
{
	disp_pos=0;
}

PUBLIC char * itoa(char * str, int num)
{
        char *  p = str;
        char    ch;
        int     i;
        bool  flag = FALSE;

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
	char output;
	itoa1(&output, input);
	disp_str(&output); 
}

void echo(char *buf)
{
	disp_str(buf);
}

void clear(void)
{
	init_disp_pos();
	int i = 2000;
	while(i--)disp_str(" ");
	init_disp_pos();
	disp_str("$ ");
	
}

void poweroff(void)
{
	disp_str("\nI will sleep and never wake up\nsee you next time \n");
	__asm__ ("cli");
	__asm__ ("hlt");
}

void time(void)
{
	struct time_val t;
	t.sec = CMOS_READ(0);
	t.min = CMOS_READ(2);
	t.hour = CMOS_READ(4);
	t.day = CMOS_READ(7);
	t.mon = CMOS_READ(8);
	t.year = CMOS_READ(9);

	t.sec = BCD_TO_DEC(t.sec);
	t.min = BCD_TO_DEC(t.min);
	t.hour = BCD_TO_DEC(t.hour);
	t.day = BCD_TO_DEC(t.day);
	t.mon = BCD_TO_DEC(t.mon);
	t.year = BCD_TO_DEC(t.year);
	t.year += 2000;
	t.hour += 8;
	t.hour %= 24;

	disp_int(t.year);
	disp_str("/");
	disp_int(t.mon);
	disp_str("/");
	disp_int(t.day);
	disp_str("  ");
	disp_int(t.hour);
	disp_str(":");
	disp_int(t.min);
	disp_str(":");
	disp_int(t.sec);

}

void cmd_table_init(void)
{
	CMD_NUM = 0;
	regist_cmd("echo", echo);
	regist_cmd("clear", clear);
	regist_cmd("poweroff", poweroff);
	regist_cmd("time", time);
	regist_cmd("snow", snow);
	regist_cmd("help", help);
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

void regist_cmd(char *name, void *func)
{
       if(name == NULL || func == NULL)
               return;

       cmd_fun_table[CMD_NUM] = func;
       cmd_table[CMD_NUM] = name;
       CMD_NUM++;
}

int leng(char *msg)
{
        int len = 0;
        while(msg[len]){
		len++;
        }
        return len;
}

void help(void)
{
	for(int i = 0; i < CMD_NUM; i++)
	{
		disp_str(cmd_table[i]);
		disp_str(", ");
	}
}

void sleep(int t)
{
       while(t--)
       {
               int i = 1000000;
               while(i--);
       }
}

void snow(char *p)
{
       int i = 1000, k = 2, ka[100];
       char ch = *p;
       while(i--)
       {
               k = (k + 3) * 2;
               k %= 4000;
		ka[(i+1)%10] = k;
               pprint(ch, ka[(i+1)%10]);
               sleep(18);
               pprint(' ', ka[(i)%10]);
       }       
	while(i<10)
	{
		pprint(' ', ka[i++]);
	}
}

