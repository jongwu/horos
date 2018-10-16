#include "idt.h"
void set_idt_gate(int n, unsigned int addr)
{
	unsigned int val_low, val_high, tmp;
	val_low = 0x300000;
	addr -= 0xb000;
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
	set_idt_gate(0, &divide_error);
	set_idt_gate(1, &single_step_exception);
	set_idt_gate(2, &nmi);
	set_idt_gate(3, &breakpoint_exception);
	set_idt_gate(4, &overflow);
	set_idt_gate(5, &bounds_check);
	set_idt_gate(6, &inval_opcode);
	set_idt_gate(7, &copr_not_available);
	set_idt_gate(8, &double_fault);
	set_idt_gate(9, &copr_seg_overrun);
	set_idt_gate(10, &inval_tss);
	set_idt_gate(11, &segment_not_present);
	set_idt_gate(12, &stack_exception);
	set_idt_gate(13, &general_protection);
	set_idt_gate(14, &page_fault);
	set_idt_gate(15, &copr_error);
	set_idt_gate(16, &hwint00);
	set_idt_gate(17, &hwint01);
	set_idt_gate(18, &hwint02);
	set_idt_gate(19, &hwint03);
	set_idt_gate(20, &hwint04);
	set_idt_gate(21, &hwint05);
	set_idt_gate(22, &hwint06);
	set_idt_gate(23, &hwint07);
	set_idt_gate(24, &hwint08);
	set_idt_gate(25, &hwint09);
	set_idt_gate(26, &hwint10);
	set_idt_gate(27, &hwint11);
	set_idt_gate(28, &hwint12);
	set_idt_gate(29, &hwint13);
	set_idt_gate(30, &hwint14);
	set_idt_gate(31, &hwint15);
}
