nasm bootsec.asm -o boot.bin
dd if=boot.bin of=boot.img bs=1024 count=1
qemu-system-x86_64 boot.img -m 1024
