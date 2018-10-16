         ;filename: boot.asm
         ;descriptor: using as bootloader, setup GDT, loader setup.asm and kernel
         ;build time: 2018-9-15          
         
	 setup_base_address	equ	0x00009000 
	 head_base_address	equ	0x0000a000
	 setup_sector		equ	1
	 head_sector		equ	9
         
         mov ax,cs      
         mov ss,ax
         mov sp,0x7c00
;	 call Init8259A
         ; setup GDT
	 ; comput gdt segment address 
         mov eax,[cs:pgdt+setup_base_address+0x02]      ;GDT address
         xor edx,edx
         mov ebx,16
         div ebx                             

         mov ds,eax                         ;DS point to the gdt address
         mov ebx,edx                        ;ebx is start offset 

         ;skip #0 descriptor
         ;build #1 descriptor,this is data descriptor,cover 0~4GB linear address
         mov dword [ebx+0x08],0x0000ffff    ;base address is 0，segment limit is 0xFFFFF
         mov dword [ebx+0x0c],0x00cf9200    ;D bit is 1, granularity is 4KB

         ;build code segment descriptor in protect mode
         mov dword [ebx+0x10],0x7c0001ff    ;base address is 0x00007c00，segment limit is 0x1FF 
         mov dword [ebx+0x14],0x00409800    ;granularity is 1B

         ;stack descriptor                  ;base address is 0x00007C00，segment limit is 0xFFFFE 
         mov dword [ebx+0x18],0x7c00fffe    ;granularity is 4KB 
         mov dword [ebx+0x1c],0x00cf9600
         
         ;display descriptor   
         mov dword [ebx+0x20],0x80007fff    ;base address is 0x000B8000，segment limit is 0x07FFF 
         mov dword [ebx+0x24],0x0040920b    ;granularity is 1B

	;setup code descriptor
	 mov dword [ebx+0x28], 0x90000800   ;base addrass is 0x9000, limit is 2kB
	 mov dword [ebx+0x2c], 0x00409800   ;code segment 

	;head code descriptor
	 mov dword [ebx+0x30], 0xb000ffff   ;base address is 1M, limit is 128KB
	 mov dword [ebx+0x34], 0x004f9800   ;code segment
         
         ;set descriptor limit in gdtr
         mov word [cs: pgdt+setup_base_address],55      ;descriptor limit   

 	;load GDTR
         lgdt [cs: pgdt+setup_base_address]

	;open a20
         in al,0x92                          
         or al,0000_0010B
         out 0x92,al                        

	;close peripheral interrupt
         cli                                

	;open protect mode
         mov eax,cr0
         or eax,1
         mov cr0,eax                        
      
        ;jump to protect mode
	mov eax, 0x08
	mov ds, eax
	mov eax, 0x18
	mov ss, eax
	mov sp, 0
	mov eax, 0x20
	mov gs, eax
         jmp dword 0x0030:0x170

         [bits 32]			    ;32 bit code
	
	;GDTR  initial
         pgdt             dw 0
                          dd 0x00007e00      ;GDT base address
; Init8259A ---------------------------------------------------------------------------------------------
Init8259A:
        mov     al, 011h
        out     020h, al        ; 主8259, ICW1.

        out     0A0h, al        ; 从8259, ICW1.

        mov     al, 020h        ; IRQ0 对应中断向量 0x20
        out     021h, al        ; 主8259, ICW2.

        mov     al, 028h        ; IRQ8 对应中断向量 0x28
        out     0A1h, al        ; 从8259, ICW2.

        mov     al, 004h        ; IR2 对应从8259
        out     021h, al        ; 主8259, ICW3.

        mov     al, 002h        ; 对应主8259的 IR2
        out     0A1h, al        ; 从8259, ICW3.

        mov     al, 001h
        out     021h, al        ; 主8259, ICW4.

        out     0A1h, al        ; 从8259, ICW4.

        mov     al, 11111111b   ; 仅仅开启定时器中断
        ;mov    al, 11111111b   ; 屏蔽主8259所有中断
        out     021h, al        ; 主8259, OCW1.

        mov     al, 11111111b   ; 屏蔽从8259所有中断
        out     0A1h, al        ; 从8259, OCW1.

        ret
;-----------------------------------------------------------------------------------------------------------
