         ;filename: boot.asm
         ;descriptor: using as bootloader, setup GDT, loader setup.asm and kernel
         ;build time: 2018-9-15          
         
	 setup_base_address equ  0x00009000 
	 head_base_address equ 0x00000a000
	 setup_sector equ 1
	 head_sector equ 9
         
         mov ax,cs      
         mov ss,ax
         mov sp,0x7c00
      
         ; setup GDT
	 ; comput gdt segment address 
         mov eax,[cs:pgdt+0x7c00+0x02]      ;GDT address
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
	 mov dword [ebx+0x30], 0xa000f000   ;base address is 1M, limit is 128KB
	 mov dword [ebx+0x34], 0x00409800   ;code segment
         
         ;set descriptor limit in gdtr
         mov word [cs: pgdt+0x7c00],55      ;descriptor limit   

 	;load GDTR
         lgdt [cs: pgdt+0x7c00]

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
         jmp dword 0x0010:loader             

         [bits 32]			    ;32 bit code

;loader will load setup.asm and kernel code to corresponding memory
 loader:                                  
         mov eax,0x0008                     ;set ds
         mov ds,eax
      
         mov eax,0x0018                     ;set ss 
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
	 mov edi, head_base_address
	 mov eax, head_sector
	 mov ebx, edi
	 mov ecx, 92
read_head:
	 call read_hard_disk_0
	 inc eax
	 loop read_head
	;jmp to setup code
	 jmp 0x28:0x000
	


 

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
         times 510-($-$$) db 0
                          db 0x55,0xaa
