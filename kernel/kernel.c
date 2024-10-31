#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>
#include <kernel/drivers/keyboard.h>

#include <kernel/arch/x86/isr.h>
#include <kernel/arch/x86/idt.h>
#include <kernel/arch/x86/timer.h>

#include <kernel/util.h>

void kmain() {
    kvga_clear();

    kisr_install();
    __asm__ __volatile__("sti");
    //kirq_timer_init(50);
    kirq_kbd_init();
}
