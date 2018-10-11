ENTRYPOINT = start
ENTRYOFFSET = 0xb000
ASM = nasm
ASMOFLAG = -I include -o
ASMFLAG = -f elf -I include -o
CC = gcc
CFLAG = -I include -c  -o
#CFLAG = -I include -c -fno-builtin -fno-stack-protector -o
LD = ld
LDFLAG =  -Ttext $(ENTRYOFFSET) -e $(ENTRYPOINT) 
OBJ = lib/klib.o lib/klibc.o init/head.o init/main.o init/idt.o
KERNEL = kernel.bin
INCLUDE = include/const.h include/global.h include/lib.h include/type.h include/protect.h include/proto.h include/string.h
all: boot/boot.bin boot/setup.bin $(KERNEL)
clean:
	rm -r $(KERNEL)

lib/klib.o: lib/klib.asm $(INCLUDE)
	$(ASM) $(ASMFLAG) $@ $<

lib/klibc.o: lib/klib.c $(INCLUDE)
	$(CC) $(CFLAG) $@ $<

boot/boot.bin: boot/boot.asm $(INCLUDE)
	$(ASM) $(ASMOFLAG) $@ $<

boot/setup.bin: boot/setup.asm $(INCLUDE)
	$(ASM) $(ASMOFLAG) $@ $<

init/head.o: init/head.asm $(INCLUDE)
	$(ASM) $(ASMFLAG) $@ $<

init/main.o: init/main.c $(INCLUDE)
	$(CC) $(CFLAG) $@ $<

init/idt.o: init/idt.c
	$(CC) $(CFLAG) $@ $<

$(KERNEL): $(OBJ)
	$(LD) $(LDFLAG) -o $@ $(OBJ)
