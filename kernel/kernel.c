#include "drivers/port.h"
#include "drivers/vga.h"
#include "drivers/keyboard.h"

#include "arch/x86/isr.h"
#include "arch/x86/idt.h"
#include "arch/x86/timer.h"

#include "util.h"

void kmain() {
    kvga_clear();

    kisr_install();
    __asm__ __volatile__("sti");
    //kirq_timer_init(50);
    kbd_init();
}
