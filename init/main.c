#include "type.h"
#include "lib.h"
#include "global.h"
extern void print(char *msg, int len);
int leng(char *msg);

int main()
{
        char *str="                                              					                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ";
        int len=leng(str);
        print(str,len);
        str="Hello, my friend. This is horos. I am a small operating system in developing. Jianyong Wu create me since July 1, 2018. If you are inteasted in me please clone me from https://github.com/jianyongwu/horos and develop me. Thank you\n";
        len=leng(str);
//        print(str,len);
//        print(str,len);
	disp_str(str);
	str="now, I just begin to boot kernel, but this kernel is nothing else beside print some words\n";
	disp_str("\n");
	disp_str(str);
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

