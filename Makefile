#CXX=i386-elf-g++
#CC=i386-elf-gcc
#LD=i386-elf-ld

CXX=x86_64-elf-g++
CC=x86_64-elf-gcc
LD=x86_64-elf-ld
AS=nasm

QEMU=qemu-system-i386
QEMU_GRUB=qemu-system-x86_64

CFLAGS = -g -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
	 -Wall -Wextra -Werror -ffreestanding -z execstack -no-pie -fno-pic -Wno-int-to-pointer-cast \
	 -Wno-pointer-to-int-cast \
	 -I. -Ikernel
#LDFLAGS = -melf_i386

CFLAGS += -DKARCH_X86_64=1
#CFLAGS += -DKARCH_X86_32=1

C_SOURCES = $(wildcard kernel/*.c kernel/drivers/*.c kernel/libc/*.c kernel/arch/x86/*.c)
HEADERS = $(wildcard kernel/*.h kernel/drivers/*.h kernel/libc/*.h kernel/arch/x86/*.h)

OBJ = ${C_SOURCES:.c=.o kernel/arch/x86/int.o}
OBJ_GRUB = ${C_SOURCES:.c=.o kernel/boot/x86_64/main64.o kernel/boot/x86_64/main.o kernel/boot/x86_64/header.o kernel/arch/x86/int.o}

TARGET ?= grub # grub|custom

all: kernel.iso

kernel.iso: kernel-grub.bin
	cp kernel-grub.bin bootloader/grub/boot/
	mv kernel-grub.bin build/
	grub-mkrescue /usr/lib/grub/i386-pc -o build/kernel.iso bootloader/grub/

os-image.bin: bootloader/custom/x86/boot.bin kernel.bin
	cat $^ > os-image.bin
	mv kernel.bin build/
	mv os-image.bin build/

kernel.bin: bootloader/custom/x86/kmain.o ${OBJ}
	@echo "LD 	$<"
	@(LD) ${LD_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel-grub.bin: ${OBJ_GRUB}
	@echo "LD 	$<"
	@$(LD) -n -o $@ -T bootloader/grub/linker.ld $^

run:
	@echo "## Running sumulation (QEMU-custom) ## "
	$(QEMU) -fda build/os-image.bin

run-grub:
	@echo "## Running sumulation (QEMU-grub) ## "
	$(QEMU_GRUB) -cdrom build/kernel.iso -d int -no-reboot

%.o: %.c ${HEADERS} 
	@echo "CC	$<"
	@$(CC) ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	@echo "AS	$<"
	@$(AS) $< -f elf64 -o $@

%.bin: %.asm
	@echo "AS	$<" 
	@$(AS) $< -f bin -o $@

clean:
	@- rm -rf *.bin *.dis *.o os-image.bin *.elf
	@- rm -rf kernel/*.o ssbl/*.bin kernel/drivers/*.o ssbl/*.o kernel/libc/*.o kernel/arch/x86/*.o kernel/boot/x86_64/*.o
	@- rm -rf bootloader/grub/*.bin
