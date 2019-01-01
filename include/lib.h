#ifndef HS_LIB
#define HS_LIB

#include "type.h"
extern void disp_str(char *);
extern void out_byte(t_port port, t_8 value);
extern t_8      in_byte(t_port port);
extern void     disp_color_str(char * info, int color);
extern void     init_prot();
extern void	spurious_irq(int);
extern void disp_int(int);
extern void	disp_char();
extern void init_disp_pos();
extern void  do_shell();
extern int cmd_open;
extern int CMD_NUM;
extern char *cmd_table[10];
extern void *cmd_arg_table[10];
extern void (*cmd_fun_table[10])(void *);
extern char kd_buf[20];
extern int p_kd_buf;
extern int str_equal(char *, char *);
extern int leng(char *msg);
#endif
