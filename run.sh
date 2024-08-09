set -e

#build all
#[ -f kernel.bin ] || docker run -t --rm -v $PWD:/root/horos ubuntu:18.04 bash -c "apt update; apt install -y build-essential nasm; cd /root/horos; make"

[ -f kernel.bin ] || make

#install bootloader and kernel into hard disk
dd if=/dev/zero of=c.img bs=1M count=10
dd if=boot/boot.bin of=c.img bs=512 count=1 conv=notrunc
dd if=boot/setup.bin of=c.img seek=1 conv=notrunc
dd if=kernel.bin of=c.img seek=9 conv=notrunc

#run kernel in qemu and bochs
apt install -y qemu-system-i386
qemu-system-i386 c.img -m 1G
#bochs -f bochsrc.bxrc
