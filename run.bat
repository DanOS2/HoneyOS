@echo off
qemu-system-i386 -m 32 -cdrom HoneyOS.iso -monitor stdio -serial file:Qemu_log.txt -no-reboot 