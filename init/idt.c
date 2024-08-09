#include "idt.h"
#include "type.h"
#include "lib.h"

unsigned int idt[512];
void set_idt_gate(int n, unsigned int addr)
{
	unsigned int val_low, val_high, tmp;
	val_low = 0x300000;

	/* 0xb000 is head segment phyical address */
//	addr -= 0xb000;

	tmp = 0x0000ffff & addr;
	val_low |= tmp;
	idt[n*2] = val_low;
	val_high = 0x8e00;
	tmp = 0xffff0000 & addr;
	val_high |= tmp;
	idt[2*n +1] = val_high;
}

void init_idt()
{
	set_idt_gate(0, (u32)&divide_error);
	set_idt_gate(1, (u32)&single_step_exception);
	set_idt_gate(2, (u32)&nmi);
	set_idt_gate(3, (u32)&breakpoint_exception);
	set_idt_gate(4, (u32)&overflow);
	set_idt_gate(5, (u32)&bounds_check);
	set_idt_gate(6, (u32)&inval_opcode);
	set_idt_gate(7, (u32)&copr_not_available);
	set_idt_gate(8, (u32)&double_fault);
	set_idt_gate(9, (u32)&copr_seg_overrun);
	set_idt_gate(10, (u32)&inval_tss);
	set_idt_gate(11, (u32)&segment_not_present);
	set_idt_gate(12, (u32)&stack_exception);
	set_idt_gate(13, (u32)&general_protection);
	set_idt_gate(14, (u32)&page_fault);
	set_idt_gate(16, (u32)&copr_error);
	set_idt_gate(32, (u32)&hwint00);
	set_idt_gate(33, (u32)&hwint01);
	set_idt_gate(34, (u32)&hwint02);
	set_idt_gate(35, (u32)&hwint03);
	set_idt_gate(36, (u32)&hwint04);
	set_idt_gate(37, (u32)&hwint05);
	set_idt_gate(38, (u32)&hwint06);
	set_idt_gate(39, (u32)&hwint07);
	set_idt_gate(40, (u32)&hwint08);
	set_idt_gate(41, (u32)&hwint09);
	set_idt_gate(42, (u32)&hwint10);
	set_idt_gate(43, (u32)&hwint11);
	set_idt_gate(44, (u32)&hwint12);
	set_idt_gate(45, (u32)&hwint13);
	set_idt_gate(46, (u32)&hwint14);
	set_idt_gate(47, (u32)&hwint15);
	set_idt_gate(0x80, (u32)&syscall_handler);
}

void exception_handler(int vec_no, int err_code, int eip, int cs, int eflags)
{
//        int i;
//        int text_color = 0x74;
	(void)err_code;
	(void)eip;
	(void)cs;
	(void)eflags;
	char *p0="#DE Divide Error";
	char *p1="#DB RESERVED";
        char *p2="NMI Interrupt";
        char *p3="#BP Breakpoint";
        char *p4="#OF Overflow";
        char *p5="#BR BOUND Range Exceeded";
        char *p6="#UD Invalid Opcode (Undefined Opcode)";
        char *p7="#NM Device Not Available (No Math Coprocessor)";
        char *p8="#DF Double Fault";
        char *p9="Coprocessor Segment Overrun (reserved)";
        char *p10="#TS Invalid TSS";
        char *p11="#NP Segment Not Present";
        char *p12="#SS Stack-Segment Fault";
        char *p13="#GP General Protection";
        char *p14="#PF Page Fault";
        char *p15="¡ª  (Intel reserved. Do not use.)";
        char *p16="#MF x87 FPU Floating-Point Error (Math Fault)";
        char *p17="#AC Alignment Check";
        char *p18="#MC Machine Check";
        char *p19="#XF SIMD Floating-Point Exception";
//	char *p[20]={p0,p1};                               
//	disp_str(p[vec_no]);

	disp_int(vec_no);
	disp_str("\n");
	char* error_msg[20]={p0,p1,p2,p3,p4,p5,p6,p7,p8,p9,p10,p11,p12,p13,p14,p15,p16,p17,p18,p19};
	disp_str(error_msg[vec_no]);
}
