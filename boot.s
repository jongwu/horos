;reference from a book, you can complie it using nasm, 
;and write it into a hard disk uding dd. x86 machine 
;can boot from this hard disk.

org 0x7c00 
section start
mov ax, cs
mov ds, ax
mov ax, 0x7c0
mov ds, ax
mov bx, 512
call hdd
call s
;call s
jmp $
hdd: mov dx, 0x1f2
     mov al, 0x01
     out dx,al
     mov dx, 0x1f3
     mov al, 0x02
     out dx, al
     inc dx
     mov al, 0x00
     out dx, al
     inc dx
     out dx, al
     inc dx
     mov al, 0xe0
     out dx, al
     mov dx, 0x1f7
     mov al, 0x20
     out dx, al
	 mov dx,0x1f7
	call .waits
	call .readw 
     ret
.waits: in al,dx 
	and al,0x88 
	cmp al,0x08 
	jnz .waits
	mov cx, 256
	mov dx, 0x1f0
	ret
.readw:
	in ax, dx
	mov [bx], ax
	add bx,2
	loop .readw
	ret
hd: mov dx, 0x0080
    mov cx, 0x0002
    mov ax, 0x201
    mov bx, 0x200
    int 0x13
    ret
s:	mov ax, BootMessage
	mov bp, ax
	mov cx, 16
	mov ax, 01301h
	mov bx, 000ch
	mov dl, 0
	int 10h
	ret
times 510-($-$$) db 0
db 0x55 
db 0xaa
;section DispStr

BootMessage: db "hello world"

times 512 db 0

