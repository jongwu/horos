org 0x7c00
%define bootsec 0x7c0
%define mod32_segment_cs 0
%define mod32_segment_ds 8
%define kernel_offset 0x7e00

_start:
	mov ax, bootsec
	mov ds, ax

	in al, 0x92
	or al, 2
	out 0x92, al
	jmp protect_mode

protect_mode:
	cli
	lgdt [gdtr]
	mov eax, cr0
	or eax, 1
	mov cr0, eax
	jmp	mod32_segment_cs:kernel_offset
	ret

gdtr:
	dw gdtrend - gdt32 -1
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

gdtrend db '0'

call load_kernel

load_kernel:
	mov ax, mod32_segment_ds
	mov es, ax
	mov bx, 0x7e00
	mov ah, 2
	mov al, 1
	mov ch, 2
	mov cl, 2
	mov dh, 0
	mov dl, 0x80
	int 0x13
	ret

times  (510-($-$$)) db 0
dw 0xaa55
kernel:
	call printstr
	jmp $

printstr:
	mov ax, message
	mov bp, ax
	mov cx, len
	mov ax, 01301h
	mov bx, 000ch
	mov dl, 0
	int 10h
	ret

message: db "jump into kernel"
msgend db 0
len equ msgend-message
