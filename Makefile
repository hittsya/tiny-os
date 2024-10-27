CXX=i386-elf-g++
CC=i386-elf-gcc
LD=i386-elf-ld
AS=nasm
QEMU=qemu-system-i386

C_SOURCES = $(wildcard kernel/*.c drivers/*.c)
HEADERS = $(wildcard kernel/*.h drivers/*.h)
OBJ = ${C_SOURCES:.c=.o}

os-image.bin: boot/x86/boot.bin kernel.bin
	cat $^ > os-image.bin

kernel.bin: boot/x86/kmain.o ${OBJ}
	@echo "LD 	$<"
	@$(LD) -o $@ -Ttext 0x1000 $^ --oformat binary

kernel.elf: boot/x86/kernel.o ${OBJ}
	@echo "LD 	$<"
	@$(LD) -o $@ -Ttext 0x1000 $^ 

run: os-image.bin
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
	@- rm -rf kernel/*.o boot/*.bin drivers/*.o boot/*.o
