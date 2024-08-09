#ifndef _IDT_SET_
#define _IDT_SET_
void  divide_error(void);
void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags);
void  single_step_exception(void);
void  nmi(void);
void  breakpoint_exception(void);
void  overflow(void);
void  bounds_check(void);
void  inval_opcode(void);
void  copr_not_available(void);
void  double_fault(void);
void  copr_seg_overrun(void);
void  inval_tss(void);
void  segment_not_present(void);
void  stack_exception(void);
void  general_protection(void);
void  page_fault(void);
void  copr_error(void);
void  hwint00(void);
void  hwint01(void);
void  hwint02(void);
void  hwint03(void);
void  hwint04(void);
void  hwint05(void);
void  hwint06(void);
void  hwint07(void);
void  hwint08(void);
void  hwint09(void);
void  hwint10(void);
void  hwint11(void);
void  hwint12(void);
void  hwint13(void);
void  hwint14(void);
void  hwint15(void);
void  syscall_handler(void);
void set_idt_gate(int , unsigned int);
void init_idt(void);
void int_n(void);
void set_idtr(void);
void sti(void);













#endif
