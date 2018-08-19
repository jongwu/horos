         ;代码清单13-2
         ;文件名：c13_core.asm
         ;文件说明：保护模式微型核心程序 
         ;创建日期：2011-10-26 12:11

         ;以下常量定义部分。内核的大部分内容都应当固定 
         core_code_seg_sel     equ  0x08    ;内核代码段选择子
         core_data_seg_sel     equ  0x30    ;内核数据段选择子 
         sys_routine_seg_sel   equ  0x28    ;系统公共例程代码段的选择子 
         video_ram_seg_sel     equ  0x20    ;视频显示缓冲区的段选择子
         core_stack_seg_sel    equ  0x18    ;内核堆栈段选择子
         mem_0_4_gb_seg_sel    equ  0x08    ;整个0-4GB内存的段的选择子
;	entry equ 0x40004

;-------------------------------------------------------------------------------
         ;以下是系统核心的头部，用于加载核心程序 


;         core_entry       dd entry          ;核心代码段入口点#10
;                          dw core_code_seg_sel
;	core_entry      dd entry
	entry dd 0x40004
start:

         ;以下在屏幕上显示"Protect mode OK." 
	mov eax, video_ram_seg_sel
	mov gs, eax
         mov byte [gs:0x00],'P'
         mov byte [gs:0x02],'r'
         mov byte [gs:0x04],'o'
         mov byte [gs:0x06],'t'
         mov byte [0x000B8008],'e'
         mov byte [0x000B800a],'c'
         mov byte [0x000B800c],'t'
         mov byte [0x000B800e],' '
         mov byte [0x000B8010],'m'
         mov byte [0x000B8012],'o'
         mov byte [0x000B8014],'d'
         mov byte [0x000B8016],'e'
         mov byte [0x000B8018],' '
         mov byte [0x000B801a],'O'
         mov byte [0x000B801c],'K'
	jmp edi
