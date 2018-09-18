bits 32
start:
	idt_start equ 0x00a000
	mov ebx, 0x00a000
	push ebx
        mov eax, 0x00008e00
        mov edi, 0x00280000
        mov di, isr
        mov [ebx+_idt], edi
        mov [ebx+_idt+4], eax
        add ebx, 8
        mov [ebx+_idt], edi
        mov [ebx+_idt+4], eax
	pop ebx
	lidt [ebx+idt_descr]
	int 0
	jmp $


idt_descr:
	dw 79  	    ;limit len
	dd idt_start+_idt     ;idt address

_idt:			  ;gate desbrib base address
	 dd 0    ;gate describ table	
	dd 0
	dd 0
	dd 0


isr:
;	jmp $
	push eax
	push gs
	push ebx
	push ecx

	mov eax,  0x20
	mov gs, eax
	mov ebx, 0
	mov ecx, 1500
        mov byte [gs:bx], ' '
        inc ebx
        inc ebx
        mov byte [gs:ebx], 'h'
        add ebx, 2
        mov byte [gs:ebx], 'e'
        add ebx, 2
        mov byte [gs:ebx], 'l'
        add ebx, 2
        mov byte [gs:ebx], 'l'
        add ebx, 2
        mov byte [gs:ebx], 'o'
        add ebx, 2
        mov byte [gs:ebx], ','
        add ebx, 2
        mov byte [gs:ebx], 'k'
        add ebx, 2
        mov byte [gs:ebx], 'e'
        add ebx, 2
        mov byte [gs:ebx], 'r'
        add ebx, 2
        mov byte [gs:ebx], 'n'
        add ebx, 2
        mov byte [gs:ebx], 'e'
        add ebx, 2
        mov byte [gs:ebx], 'l'
        add ebx, 2

	pop ecx
	pop ebx
	pop gs
	pop eax

	ret

