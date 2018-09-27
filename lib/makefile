klib.o: klib.asm
	nasm -m elf klib.asm -o klib.o

klibc.o: klib.c
	gcc -c klib.c -o klibc.o
