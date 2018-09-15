bits 32
head:
	mov eax, 0x20
	mov gs, eax
	mov ecx, 400
	mov ebx, 400
s:
	mov byte [gs:ebx], '+'
	add ebx, 2
	loop s
	jmp $
