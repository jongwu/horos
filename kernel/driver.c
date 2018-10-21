#include "lib.h"
#include "driver.h"
#include "global.h"
extern char key[60];
void keyboard(int k)
{
	if(k==57)
	{
		disp_str(" ");
		return;
	}
	if (k>53)return;
	if (k==14)
	{	
		disp_pos-=2;
		disp_str(" ");
		disp_pos-=2;
		return;
	}
key[2]='1';
key[3]='2';
key[4]='3';
key[5]='4';
key[6]='5';
key[7]='6';
key[8]='7';
key[9]='8';
key[10]='9';
key[11]='0';
key[12]='-';
key[13]='=';
key[14]=' ';
key[15]=' ';
key[16]='q';
key[17]='w';
key[18]='e';
key[19]='r';
key[20]='t';
key[21]='y';
key[22]='u';
key[23]='i';
key[24]='o';
key[25]='p';
key[26]='[';
key[27]=']';
key[28]='\n';
key[29]=' ';
key[30]='a';
key[31]='s';
key[32]='d';
key[33]='f';
key[34]='g';
key[35]='h';
key[36]='j';
key[37]='k';
key[38]='l';
key[39]=';';
key[40]='\'';
key[42]=' ';
key[43]='\\';
key[44]='z';
key[45]='x';
key[46]='c';
key[47]='v';
key[48]='b';
key[49]='n';
key[50]='m';
key[51]=',';
key[52]='.';
key[53]='/';
	char *p="a";
	*p=key[k];
	disp_str(p);
}
