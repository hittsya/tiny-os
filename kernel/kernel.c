#include "drivers/port.h"
#include "drivers/vga.h"

#include "arch/x86/isr.h"
#include "arch/x86/idt.h"

#include "util.h"

void kmain() {
    kvga_clear();

    kisr_install();
    __asm__ __volatile__("int $2");
    __asm__ __volatile__("int $3");
}
