set -e

#build all
make

#install bootloader and kernel into hard disk
dd if=boot/boot.bin of=c.img bs=512 count=1 conv=notrunc
dd if=boot/setup.bin of=c.img seek=1 conv=notrunc
dd if=kernel.bin of=c.img seek=9 conv=notrunc

#run kernel in qemu and bochs
qemu-system-x86_64 c.img -m 1G
#bochs -f bochsrc.bxrc
