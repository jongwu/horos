extern void print(char *msg, int len);
int leng(char *msg);
int main()
{
        char *str="                                              					                                                                                                                                                                                                                                                                                                                                                                                                                                                                   ";
        int len=leng(str);
        print(str,len);
        str="Hello, my friend. This is horos. I am a small operating system in developing. Jianyong Wu create me since July 1, 2018. If you are inteasted in me please clone me from https://github.com/jianyongwu/horos and develop me. Thank you";
        len=leng(str);
        print(str,len);
        print(str,len);
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

