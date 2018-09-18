set -e
make -C boot/
make -C init/
dd if=boot/boot.bin of=c.img bs=512 count=1 conv=notrunc
dd if=boot/setup.bin of=c.img seek=1 conv=notrunc
dd if=init/head.bin of=c.img seek=9 conv=notrunc
qemu-system-x86_64 c.img -m 1024
bochs -f bochsrc.bxrc
