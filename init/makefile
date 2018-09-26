textaddr = 0xb000
kernel.bin: head.o main.o
	ld -s -o kernel.bin main.o head.o  -Ttext $(textaddr) -e start

main.o: main.c
	gcc -c main.c -o main.o

head.o: head.asm
	nasm -f elf  head.asm -o head.o

clean:
	rm main.o head.o kernel.bin

