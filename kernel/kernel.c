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
    kvga_clear();
    irq_irs_install();

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
