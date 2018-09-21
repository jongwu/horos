bits 32
head_base_addr equ 0xb000
head_segment equ 0x30
pde_base_addr equ 0x0000
pte_base_addr equ 0x1000
global print
global start
extern main
start:
	call setup_idt
	call write_idt
	lidt [idtr+head_base_addr]
	call setup_pde
	call start_paging
;	int 200
	jmp main

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
	times 512 dd 0

idtr:
	dw 512*4-1
	dd idt+head_base_addr

setup_pde:
	mov eax, pte_base_addr
	add eax, 0x113
	mov ecx, 4
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
	mov ecx, 1023
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

start_paging:
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
	mov byte [gs:ebx], '='
	add ebx, 2
	loop s
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
	
