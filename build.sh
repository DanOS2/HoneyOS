echo "Build HoneyOS"

# компиляция библиотек
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/terminal/tty.c -o bin/tty.o
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/drivers/ports.c -o bin/ports.o
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/drivers/keyboard.c -o bin/keyboard.o


i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/start.s -o bin/start.o
i686-elf-gcc -O2 -std=gnu99 -Wall -Wextra -ffreestanding -g -c src/kernel.c -o bin/kernel.o
i686-elf-gcc -ffreestanding -nostdlib -g -T src/linker.ld bin/start.o bin/keyboard.o bin/ports.o bin/tty.o bin/kernel.o -o bin/kernel.elf -lgcc


if [ ! -f "/build" ]; then
	mkdir build
fi
if [ ! -f "/build/boot" ]; then
	mkdir build/boot
fi
if [ ! -f "/build/boot/grub" ]; then
	mkdir build/boot/grub
fi
echo "Create iso"
cp bin/kernel.elf build/boot/kernel.elf
cp src/grub.cfg build/boot/grub/grub.cfg
grub-mkrescue -o HoneyOS.iso build/