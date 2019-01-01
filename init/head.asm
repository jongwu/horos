bits 32
head_base_addr equ 0xb000
head_segment equ 0x30
pde_base_addr equ 0x0000
pte_base_addr equ 0x1000
global print
global start
extern start_paging
extern main
extern current
extern spurious_irq
extern disp_int
extern scheduler
extern keyboard
extern exception_handler
global  syscall_handler
global  divide_error
global  single_step_exception
global  nmi
global  breakpoint_exception
global  overflow
global  bounds_check
global  inval_opcode
global  copr_not_available
global  double_fault
global  copr_seg_overrun
global  inval_tss
global  segment_not_present
global  stack_exception
global  general_protection
global  page_fault
global  copr_error
global  hwint00
global  hwint01
global  hwint02
global  hwint03
global  hwint04
global  hwint05
global  hwint06
global  hwint07
global  hwint08
global  hwint09
global  hwint10
global  hwint11
global  hwint12
global  hwint13
global  hwint14
global  hwint15
extern idt
global set_idtr
global int_n
global sti
start:
;	mov ebx, idt
;	call init_idt
;	lidt [idtr]
;	call setup_pde
;	call start_paging
;	sti
;	call start_paging
	sub esp, 4096
	mov [current], esp
	jmp main
	jmp $

setup_idt:
	mov eax, 0x8e00
	mov edx, 0x00300000
;	mov edi, isr-head_base_addr
	mov dx,  di
;	mov ecx, 255
	ret

write_idt:
	mov dword [ebx], edx
	mov dword [ebx+4], eax
	add ebx, 8
;	loop write_idt
	ret
	
;idt:
;	times 512 dd 0

idtr:
	dw 512*4-1
	dd idt
set_idtr:
	lidt [idtr]
	ret

int_n:
	int 32
	ret
;we just set 1M page memory for kernel
setup_pde:
	mov eax, pte_base_addr
	add eax, 0x113
	mov ecx, 1
	mov edx, 0
.l1	mov [pde_base_addr+edx], eax
	call setup_pte
	add eax, 4*1024
	add edx, 4
	loop .l1
	ret

setup_pte:
	push eax
	push ecx
	push edx
	push edi
	mov eax, 0
	add eax, 0x113
	mov ecx, 255
	mov ebx, 0
.l2	mov edi, edx
	shl edi, 10
	mov [pte_base_addr+ebx+edi], eax
	add eax, 4*1024
	add ebx, 4
	loop .l2
	pop edi
	pop edx
	pop ecx
	pop eax
	ret

;start_paging:
	push eax
	push ebx
	mov eax, pde_base_addr
	mov cr3, eax
	mov eax, cr0
	mov ebx, 1
	shl ebx, 31
	or  eax, ebx
	mov cr0, eax
	pop ebx
	pop eax
	ret

isr:
	mov eax, 0x20
	mov gs, eax
	mov ecx, 400
	mov ebx, 0
s:
	mov byte [gs:ebx], '-'
	add ebx, 2
	loop s
	jmp $

isr_:
	mov eax, 0x20
	mov gs, eax
	mov ecx, 400
	mov ebx, 0
s1:
	mov byte [gs:ebx], '+'
	add ebx, 2
	loop s1
	jmp $

print:
	mov eax, 0x20
        mov gs, eax
        mov esi, 0
        mov edi, 0
        mov ebx, ebp
        mov ecx, [esp + 8]
        mov edi, [esp + 4]
        jmp l1
l1:
        mov eax, [edi]
        mov byte [gs:esi], al
        add esi, 2
        inc edi
        loop l1
	ret


init_idt:
	mov edi, divide_error-head_base_addr
	call setup_idt
	call write_idt
	
	mov edi, single_step_exception-head_base_addr
	call setup_idt
	call write_idt

	mov edi, nmi-head_base_addr
	call setup_idt
	call write_idt

	mov edi, breakpoint_exception-head_base_addr
	call setup_idt
	call write_idt

	mov edi, overflow-head_base_addr
	call setup_idt
	call write_idt
	
	mov edi, bounds_check-head_base_addr
	call setup_idt
	call write_idt

	mov edi, inval_opcode-head_base_addr
	call setup_idt
	call write_idt

	mov edi, copr_seg_overrun-head_base_addr
	call setup_idt
	call write_idt

	mov edi, inval_tss-head_base_addr
	call setup_idt
	call write_idt

	mov edi, double_fault-head_base_addr
	call setup_idt
	call write_idt

	mov edi, segment_not_present-head_base_addr
	call setup_idt
	call write_idt

	mov edi, stack_exception-head_base_addr
	call setup_idt
	call write_idt

	mov edi, general_protection-head_base_addr
	call setup_idt
	call write_idt

	mov edi, page_fault-head_base_addr
	call setup_idt
	call write_idt

	mov edi, copr_error-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint00-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint01-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint02-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint03-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint04-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint05-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint06-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint07-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint08-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint09-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint10-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint11-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint12-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint13-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint14-head_base_addr
	call setup_idt
	call write_idt

	mov edi, hwint15-head_base_addr
	call setup_idt
	call write_idt
	ret


%macro	hwint_master	1
	push	%1
	call	spurious_irq
	mov al, 0x20
	out 0x20, al
	call wait_
	add esp, 4
	iret
%endmacro

eoi_8259_master:
	push eax
	mov al, 0x20
	out 0x20, al
	pop eax
	ret

ALIGN	16
hwint00:		; Interrupt routine for irq 0 (the clock).
	call eoi_8259_master
	call scheduler	
	iret

ALIGN	16
hwint01:		; Interrupt routine for irq 1 (keyboard)
	push eax
	xor eax, eax
	in  al, 0x60
	push eax
;	call disp_int
	call keyboard
	and al, 0x7f	
	out 0x61, al
	call eoi_8259_master
	pop eax
	pop eax
	iret

ALIGN	16
hwint02:		; Interrupt routine for irq 2 (cascade!)
	hwint_master	2

ALIGN	16
hwint03:		; Interrupt routine for irq 3 (second serial)
	hwint_master	3

ALIGN	16
hwint04:		; Interrupt routine for irq 4 (first serial)
	hwint_master	4

ALIGN	16
hwint05:		; Interrupt routine for irq 5 (XT winchester)
	hwint_master	5

ALIGN	16
hwint06:		; Interrupt routine for irq 6 (floppy)
	hwint_master	6

ALIGN	16
hwint07:		; Interrupt routine for irq 7 (printer)
	hwint_master	7
; ---------------------------------
%macro	hwint_slave	1
	push	%1
	call	spurious_irq
;	jmp isr_
	add	esp, 4
	mov al, 0x20
	out 0xa0, al
;	jmp $
;	jmp isr
	ret
%endmacro
; ---------------------------------

ALIGN	16
hwint08:		; Interrupt routine for irq 8 (realtime clock).
	hwint_slave	8

ALIGN	16
hwint09:		; Interrupt routine for irq 9 (irq 2 redirected)
	hwint_slave	9

ALIGN	16
hwint10:		; Interrupt routine for irq 10
	hwint_slave	10

ALIGN	16
hwint11:		; Interrupt routine for irq 11
	hwint_slave	11

ALIGN	16
hwint12:		; Interrupt routine for irq 12
	hwint_slave	12

ALIGN	16
hwint13:		; Interrupt routine for irq 13 (FPU exception)
	hwint_slave	13

ALIGN	16
hwint14:		; Interrupt routine for irq 14 (AT winchester)
	hwint_slave	14

ALIGN	16
hwint15:		; Interrupt routine for irq 15
	hwint_slave	15


divide_error:
	push	0xFFFFFFFF	; no err code
	push	0		; vector_no	= 0
	jmp	exception
single_step_exception:
	push	0xFFFFFFFF	; no err code
	push	1		; vector_no	= 1
	jmp	exception
nmi:
	push	0xFFFFFFFF	; no err code
	push	2		; vector_no	= 2
	jmp	exception
breakpoint_exception:
	push	0xFFFFFFFF	; no err code
	push	3		; vector_no	= 3
	jmp	exception
overflow:
	push	0xFFFFFFFF	; no err code
	push	4		; vector_no	= 4
	jmp	exception
bounds_check:
	push	0xFFFFFFFF	; no err code
	push	5		; vector_no	= 5
	jmp	exception
inval_opcode:
	push	0xFFFFFFFF	; no err code
	push	6		; vector_no	= 6
	jmp	exception
copr_not_available:
	push	0xFFFFFFFF	; no err code
	push	7		; vector_no	= 7
	jmp	exception
double_fault:
	push	8		; vector_no	= 8
	jmp	exception
copr_seg_overrun:
	push	0xFFFFFFFF	; no err code
	push	9		; vector_no	= 9
	jmp	exception
inval_tss:
	push	10		; vector_no	= A
	jmp	exception
segment_not_present:
	push	11		; vector_no	= B
	jmp	exception
stack_exception:
	push	12		; vector_no	= C
	jmp	exception
general_protection:
	push	13		; vector_no	= D
	jmp	exception

page_fault:
	push	14		; vector_no	= E
	jmp	exception
;	add esp, 8
;	iret
	

copr_error:
	push	0xFFFFFFFF	; no err code
	push	16		; vector_no	= 10h
	jmp	exception

exception:
	call	exception_handler
	hlt

syscall_handler:
	iret

;exception_handler:
;	push ebp
;	push eax
;	mov ebp, esp
;	mov eax, [ebp + 12]
;	add eax, 65
;	mov byte [gs:0], al
;	pop eax
;	pop ebp
;	ret

sti:
	sti
	ret

wait_:
	push ecx
	push eax
	mov ecx, 10000000
.s2
	inc eax
	loop .s2
	pop eax
	pop ecx
	ret

waitl:
	push ecx
	mov ecx, 100000000
.s3
	call wait_
	loop .s3
	pop ecx
	ret


