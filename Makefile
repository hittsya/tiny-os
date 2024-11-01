CXX=i386-elf-g++
CC=i386-elf-gcc
LD=i386-elf-ld
AS=nasm
QEMU=qemu-system-i386

CFLAGS = -g -m32 -nostdlib -nostdinc -fno-builtin -fno-stack-protector -nostartfiles -nodefaultlibs \
	 -Wall -Wextra -Werror -ffreestanding -fno-stack-protector -z execstack -m32 -no-pie -fno-pic \
	 -I. -Ikernel
LDFLAGS = -melf_i386

C_SOURCES = $(wildcard kernel/*.c kernel/drivers/*.c kernel/libc/*.c kernel/arch/x86/*.c)
HEADERS = $(wildcard kernel/*.h kernel/drivers/*.h kernel/libc/*.h kernel/arch/x86/*.h)
OBJ = ${C_SOURCES:.c=.o kernel/arch/x86/int.o}

all: os-image.bin

os-image.bin: boot/x86/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/x86/kmain.o ${OBJ}
	@echo "LD 	$<"
	@$(LD) ${LD_FLAGS} -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/x86/kernel.o ${OBJ}
	@echo "LD 	$<"
	@$(LD) -o $@ -Ttext 0x1000 $^ 

run:
	@$(QEMU) -fda os-image.bin

%.o: %.c ${HEADERS} 
	@echo "CC	$<"
	@$(CC) ${CFLAGS} -ffreestanding -c $< -o $@

%.o: %.asm
	@echo "AS	$<"
	@$(AS) $< -f elf -o $@

%.bin: %.asm
	@echo "AS	$<" 
	@$(AS) $< -f bin -o $@

clean:
	@- rm -rf *.bin *.dis *.o os-image.bin *.elf
	@- rm -rf kernel/*.o boot/*.bin kernel/drivers/*.o boot/*.o kernel/libc/*.o kernel/arch/x86/*.o
