#ifndef HS_LIB
#define HS_LIB

#include "type.h"
#include "lib.h"

extern void disp_str(char *);
extern void out_byte(t_port port, u8 value);
extern u8      in_byte(t_port port);
extern void     disp_color_str(char * info, int color);
extern void     init_prot(void);
extern void	spurious_irq(int);
void disp_int(int);
extern void	disp_char(void);
extern void init_disp_pos(void);
extern void  do_shell(void);
extern int cmd_open;
extern int CMD_NUM;
extern char *cmd_table[10];
void cmd_table_init(void);
extern void (*cmd_fun_table[10])(void *);
extern char kd_buf[20];
extern int p_kd_buf;
extern int str_equal(char *, char *);
extern int leng(char *msg);
void clear_disp(void);
//#define inb_p(port) ({ 
//unsigned char _v; 
//__asm__ volatile ( "inb %%dx,%%al": "=a" (_v): "d" (port)); 
//_v; 
//})

#define inb_p(port) ({ \
unsigned char _v; \
__asm__ volatile ( "inb %%dx,%%al\n" \
"\tjmp 1f\n" \
"1:\tjmp 1f\n" \
"1:": "=a" (_v): "d" (port)); \
_v; \
})




#define outb_p(value,port) \
__asm__ ( "outb %%al,%%dx\n" \
"\tjmp 1f\n" \
"1:\tjmp 1f\n" \
"1:":: "a" (value), "d" (port))





//#define outb_p(value, port) 
//__asm__ ("outb %%al, %%dx" :: "a"(value), "d"(port))

#define CMOS_READ(addr) ({ \
outb_p (0x80 | addr, 0x70); \
  inb_p (0x71); \
})



#endif
