all: boot.bin setup.bin
	
boot.bin: boot.asm
	nasm boot.asm -o boot.bin

setup.bin: setup.asm
	nasm setup.asm -o setup.bin

clean:
	rm boot.bin setup.bin
