bits 32
global switch_to
global ret_from_intr
global fun

switch_to:
	push esi
	push edi
	push ebx
	push ebp

	mov eax, [esp + 20]
	mov [eax], esp

	mov eax, [esp + 24]
	mov esp, [eax]
;	mov esp, 0x101fdc

	pop ebp
	pop ebx
	pop edi
	pop esi
	ret

ret_from_intr:
	sti
;	push 0x0
;	push 0x10
;	mov eax, esp
;	add eax, 8
;	push dword [eax]
;	mov byte [gs:20], '+'
	ret
;	iret
;	jmp $

fun:
	mov ecx, 10
	mov ebx, 0
.1
	mov byte [gs:30+ebx], '*'
	add ebx, 2
	loop .1
	jmp $
