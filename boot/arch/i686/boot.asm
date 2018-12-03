         ;filename: boot.asm
         ;descriptor: using as bootloader, setup GDT, loader setup.asm and kernel
         ;build time: 2018-9-15          

	org 0x7c00
	setup_base_address	equ	0x000009000 
	head_segment_address	equ	0x000000af6
	setup_sector	        equ	1
	head_sector	        equ	9
         
	mov ax, 0x7c00      
	mov ss,ax
        mov sp,0
	;get memory size from BIOS int 15
	mov eax, 0
	mov ds, eax
	jmp get_mem_size


;loader will load setup.asm and kernel code to corresponding memory
loader:                                  
         mov eax,0x000                    ;set ds
         mov ds,eax
      
         mov eax,0x7c0                     ;set ss 
         mov ss,eax
         xor esp,esp                        ;set esp to 0
         
         ;load setup code from sector 1 to 4 in hard disk
         mov edi,setup_base_address 	    ;set destination buffer address
         mov eax,setup_sector
         mov ebx,edi
	 mov ecx, 4
                        
setup:   call read_hard_disk_0               
	 inc eax
	 loop setup

	;load head code from 9 to 100 in hard disk
	 mov edi, 0
	 mov eax, head_sector
	 mov ebx, edi
	 mov ebp, head_segment_address
	 mov ds, ebp
	 mov ecx, 100
read_head:
	 call read_hard_disk_0
	 inc eax
	 loop read_head
	 mov ebp, 0
	 mov ds, ebp
	;jmp to setup code
	 jmp  0x00:setup_base_address
	


 

;-------------------------------------------------------------------------------
read_hard_disk_0:                        ;read hard disk
                                         ;EAX=sector
                                         ;DS:EBX=destination memory address
                                         ;return EBX=EBX+512 
         push eax 
         push ecx
         push edx
      
         push eax
         
         mov dx,0x1f2
         mov al,1
         out dx,al                       ;sectors amount number

         inc dx                          ;0x1f3
         pop eax
         out dx,al                       ;LBA address 7~0

         inc dx                          ;0x1f4
         mov cl,8
         shr eax,cl
         out dx,al                       ;LBA address 15~8

         inc dx                          ;0x1f5
         shr eax,cl
         out dx,al                       ;LBA address 23~16

         inc dx                          ;0x1f6
         shr eax,cl
         or al,0xe0                      ;LBA address 27~24
         out dx,al

         inc dx                          ;0x1f7
         mov al,0x20                     ;read
         out dx,al

  .waits:
         in al,dx
         and al,0x88
         cmp al,0x08
         jnz .waits                      ;ready to read

         mov ecx,256                     ;totall number of read
         mov dx,0x1f0
  .readw:
         in ax,dx
         mov [ebx],ax
         add ebx,2
         loop .readw

         pop edx
         pop ecx
         pop eax
 
         ret

;-------------------------------------------------------------------------------
	;GDTR  initial
         pgdt             dw 0
                          dd 0x00007e00      ;GDT base address

;-------------------------------------------------------------------------------
	;get memory size from BIOS int 15
	mem_size_para_address equ 0x00006000
get_mem_size:
        mcr_number dd 0
        mov ebx, 0
        mov eax, 0x08
        mov es, eax
        mov di, mem_size_para_address
.loop   mov eax, 0x0e820
        mov ecx, 20
        mov edx, 0x0534d4150
        int 15h
        jc $
        add di, 20
        inc dword [mcr_number+0x7c00]
        cmp ebx, 0
        jne .loop
	jmp loader

;-------------------------------------------------------------------------------                             
         times 510-($-$$) db 0
                          db 0x55,0xaa
