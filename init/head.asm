bits 32
head_base_addr equ 0xa000
head_segment equ 0x30

start:
	call setup_idt
	call write_idt
	lidt [idtr+head_base_addr]
	int 0
	jmp $

setup_idt:
	mov edi, isr
	mov eax, 0x8e00
	mov edx, 0x00300000
	mov dx,  di
	mov ecx, 255
	mov ebx, idt+head_base_addr
	ret

write_idt:
	mov dword [ebx], edx
	mov dword [ebx+4], eax
	add ebx, 8
	loop write_idt
	mov dword [ebx], edx
	mov dword [ebx+4], eax
	ret
	
	
idt:
	times 4*512-1 dd 0

idtr:
	dw 15
	dd idt+head_base_addr

isr:
	mov eax, 0x20
	mov gs, eax
	mov ecx, 400
	mov ebx, 400
s:
	mov byte [gs:ebx], '+'
	add ebx, 2
	loop s
	jmp $
