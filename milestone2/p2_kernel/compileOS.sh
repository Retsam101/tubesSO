dd if=bootload of=floppya.img bs=512 count=1 conv=notrunc
bcc -ansi -c -o p2_kernel.o p2_kernel.c
as86 kernel.asm -o kernel_asm.o
ld86 -o p2_kernel -d p2_kernel.o kernel_asm.o
dd if=p2_kernel of=floppya.img bs=512 conv=notrunc seek=3
dd if=message.txt of=floppya.img bs=512 count=1 seek=30 conv=notrunc
bochs -f opsys.bxrc
