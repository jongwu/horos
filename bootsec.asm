;%define bootsec 0x7c0
org 0x7c00

_start:
	mov ax, bootsec
	mov ds, ax

	in al, 0x92
	or al, 2
	out 0x92, al


protect_mode:
	cli
	lgdt [gdtr]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp
	ret

gdtr:
	dw 
	dq gdt32

gdt32:
	; code segment
	dw 0xffff ; limit
	dw 0x00; base
	db 0x0; base
	dw 0xcf9a ; flag
	db 0x0 ; base
	
	; data segment
	dw 0xffff ; limit
	dw 0x00   ; base
	db 0x0    ; base
	dw 0xcf92 ; flag
	db 0x0    ; base

%define mod32_segment_cs 0
%define mod32_segment_ds 8

