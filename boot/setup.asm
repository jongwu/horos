bits 32

setup:
	mov eax, 0x20
	mov gs, eax
	mov ebx, 0
	mov ecx, 200
s:	mov byte [gs:ebx], '='
	add ebx, 2
	loop s
	jmp 0x30:0x00
