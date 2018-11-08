#ifndef HS_LIB
#define HS_LIB

#include "type.h"
static void disp_str(char *);
static void out_byte(t_port port, t_8 value);
static t_8      in_byte(t_port port);
static void     disp_color_str(char * info, int color);
static void     init_prot();
extern void	spurious_irq(int);
extern void disp_int(int);
static void	disp_char();
static void init_disp_pos();





#endif
