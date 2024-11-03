#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>
#include <kernel/drivers/keyboard.h>

#include <kernel/arch/x86/isr.h>
#include <kernel/arch/x86/idt.h>
#include <kernel/arch/x86/timer.h>

#include <kernel/libc/memory.h>
#include <kernel/libc/string.h>

#include <kernel/kernel.h>

typedef struct SMAP_entry {
	u32 BaseL; // base address uint64_t
	u32 BaseH;
	u32 LengthL; // length uint64_t
	u32 LengthH;
	u32 Type; // entry Type
	u32 ACPI; // extended
} __attribute__((packed)) SMAP_entry_t;


void kmain()
{
    irq_irs_install();
    //kvga_clear();

    kvga_print_c("## Tiny-OS V0.1 ## ");
    kvga_print_c("\n> ");
}

void handle_usr_input(char *ch)
{
    if (strcmp(ch, "HALT") == 0)
    {
        kvga_print_c("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(ch, "PANIC") == 0)
    {
        kvga_print_c("Requested kernel panic\n");
		kpanic("Test");
    }

    kvga_print_c("You said: ");
    kvga_print(ch);
    kvga_print_c("\n> ");
}

void irq_irs_install()
{
    __asm__ __volatile__("sti");
    kisr_install();
    kirq_kbd_init();
}

void kpanic(const char *msg)
{
  kvga_print_c ("*** Kernel panic: ");
  kvga_print_c (msg);
  kvga_print_c (" ***\n");;
  asm volatile("hlt");
}