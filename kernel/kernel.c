#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>
#include <kernel/drivers/keyboard.h>

#include <kernel/arch/x86/isr.h>
#include <kernel/arch/x86/idt.h>
#include <kernel/arch/x86/timer.h>

#include <kernel/libc/memory.h>
#include <kernel/libc/string.h>
#include <kernel/kernel.h>

void kmain()
{
    irq_irs_install();
    //kvga_clear();
    kvga_print_c("## Tiny-OS V0.1 ## ");
    kvga_print_c("\n> ");
}

void handle_usr_input(char *ch)
{
    if (strcmp(ch, "halt") == 0)
    {
        kvga_print_c("Stopping the CPU. Bye!\n");
        asm volatile("hlt");
    }

    if (strcmp(ch, "panic") == 0)
    {
        kvga_print_c("Requested kernel panic\n");
		kpanic("Test");
    }

    kvga_print_c("\n> ");
}

void irq_irs_install()
{
    __asm__ __volatile__("sti");
    kisr_install();
    //kirq_kbd_init();
}

void kpanic(const char *msg)
{
  kvga_print_c ("*** Kernel panic: ");
  kvga_print_c (msg);
  kvga_print_c (" ***\n");;
  asm volatile("hlt");
}