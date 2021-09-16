@echo off
echo **********************************************************************************************
echo *                                        Build HoneyOS                                       *
echo **********************************************************************************************

i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/library/tty.c -o bin/tty.o
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/library/ports.c -o bin/ports.o


i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/start.s -o bin/start.o
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/kernel.c -o bin/kernel.o
i686-elf-gcc -ffreestanding -nostdlib -g -T src/linker.ld bin/start.o bin/ports.o bin/tty.o bin/kernel.o -o bin/kernel.elf -lgcc

If Not Exist "build\*.*" mkdir build
cd build
If Not Exist "boot\*.*" mkdir boot
cd boot
If Not Exist "grub\*.*" mkdir grub
cd ..
cd ..
echo Create iso
cp bin/kernel.elf build/boot/kernel.elf
cp src/grub.cfg build/boot/grub/grub.cfg
ubuntu run grub-mkrescue -o HoneyOS.iso build/

pause
