ENTRYPOINT = start
ENTRYOFFSET = 0xc000
ARCH = $(shell uname -m)
ASM = nasm
ASMOFLAG = -I include -o
ASMFLAG = -f elf32 -I include -o
CC = gcc
CFLAG = -m32 -Wall -nostdinc -fno-stack-protector -fno-omit-frame-pointer -fno-tree-sra -Wextra -mno-red-zone -fno-reorder-blocks -fno-asynchronous-unwind-tables  -I include -c -fno-builtin -Wstrict-prototypes -Wmissing-prototypes -o
#CFLAG = -m32 -I include -c -o
LD = gcc
LDFLAG = -nostdinc -nostdlib -Wl,--no-dynamic-linker -Wl,--omagic -Wl,--build-id=none -Wl,--gc-sections -Ttext $(ENTRYOFFSET) -e $(ENTRYPOINT) -Wl,-m,elf_i386
OBJ = init/head.o init/main.o init/idt.o kernel/sche.o kernel/switch.o kernel/driver.o mm/page.o mm/memory.o lib/klib.o lib/klibc.o shell/shell.o
KERNEL = kernel.bin
INCLUDE = include/const.h include/global.h include/lib.h include/type.h include/protect.h include/proto.h  include/sche.h include/driver.h include/page.h

all: boot/boot.bin boot/setup.bin $(KERNEL)
clean:
	rm -f $(KERNEL) */*.o boot/*.bin c.img

lib/klib.o: lib/klib.asm $(INCLUDE)
	$(ASM) $(ASMFLAG) $@ $<

lib/klibc.o: lib/klib.c $(INCLUDE)
	$(CC) $(CFLAG) $@ $<

boot/boot.bin: boot/arch/$(ARCH)/boot.asm $(INCLUDE)
	$(ASM) $(ASMOFLAG) $@ $<

boot/setup.bin: boot/setup.asm $(INCLUDE)
	$(ASM) $(ASMOFLAG) $@ $<

init/head.o: init/head.asm $(INCLUDE)
	$(ASM) $(ASMFLAG) $@ $<

init/main.o: init/main.c $(INCLUDE)
	$(CC) $(CFLAG) $@ $<

init/idt.o: init/idt.c
	$(CC) $(CFLAG) $@ $<

kernel/sche.o:	kernel/sche.c 
	$(CC) $(CFLAG) $@ $<

kernel/driver.o: kernel/driver.c
	$(CC) $(CFLAG) $@ $<

kernel/switch.o: kernel/switch.asm
	$(ASM) $(ASMFLAG) $@ $<

mm/page.o: mm/page.c
	$(CC) $(CFLAG) $@ $<

mm/memory.o: mm/memory.c
	$(CC) $(CFLAG) $@ $<

shell/shell.o: shell/shell.c
	$(CC) $(CFLAG) $@ $<

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAG)  -o $@ $(OBJ) 
