#include "lib.h"
int cmd_open;
void *cmd_arg_table[10];
void do_shell()
{
	disp_str("welcome to horos shell\n");
	disp_str("command list:  ");
	for(int i = 0; i < CMD_NUM; i++)
	{
		disp_str(cmd_table[i]);
		disp_str(", ");
	}
	cmd_open = 1;
	int k = 0;
	disp_str(kd_buf);
	disp_str("\n$ ");
	while(1)
	{
		if(p_kd_buf < 1)continue;
		if(kd_buf[p_kd_buf - 1] == '\n')
		{
			if(p_kd_buf <= 1)
			{
				disp_str("$ ");
				p_kd_buf = 0;
				kd_buf[0] = '\0';
				continue;
			}	
			char *arg, *cmd;
			int i;
			k = 0;
			kd_buf[p_kd_buf - 1] = '\0';
			parse_cmd(kd_buf, cmd, arg);
			for(i =0 ; i<CMD_NUM; i++)
			{
				if(str_equal(cmd_table[i], cmd))
				{
					thread_function(cmd_fun_table[i], arg);
					if(!str_equal(cmd_table[i],"clear"))
						disp_str("\n$ ");
					p_kd_buf = 0;
					break;
				}
			}
			p_kd_buf = 0;
			if(i < CMD_NUM)continue;
			shell_disp(cmd);
			disp_str(": command not found \n$ ");
		}
	}
}

int parse_cmd(char *buf, char *cmd, char *arg)
{
	int i = 0;
	while(i < p_kd_buf && buf[i] && buf[i] != ' ')
	{
		*(cmd +i) = *(buf + i);
		i++;
	}
	*(cmd +i) = '\0';
	if(buf[i] != ' '){
//	disp_int(p_kd_buf);
	return 0;}
	int j = 0;
	i++;
	while(i < p_kd_buf)
	{
		*(arg + j) = buf[i];
		i++; j++;
	}
	return 1;
}

void shell_disp(char *str)
{
	disp_str(str);
}
