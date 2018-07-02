;reference from a book, you can complie it using nasm, 
;and write it into a hard disk uding dd. x86 machine 
;can boot from this hard disk.

org 07c00h

mov ax, cs
mov ds, ax
mov es, ax
call DispStr
mov ax, 0xb800
mov es, ax
mov si, data
mov di, 2000
mov cx, 14
rep movsb
jmp $
DispStr:
	mov ax, BootMessage
	mov bp, ax
	mov cx, 16
	mov ax, 01301h
	mov bx, 000ch
	mov dl, 0
	int 10h
	ret

BootMessage: db "hello world"
times 510-($-$$) db 0
db 0x55 
db 0xaa


