#include "isr.h"
#include "idt.h"
#include "../../drivers/vga.h"
#include "../../util.h"

static char *ISR_EX_2_STR[] = {
    "Division By Zero",
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",

    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",

    "Coprocessor Fault",
    "Alignment Check",
    "Machine Check",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",

    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
};

void kisr_install() {
    kidt_addentry(0,  (u32)isr0);
    kidt_addentry(1,  (u32)isr1);
    kidt_addentry(2,  (u32)isr2);
    kidt_addentry(3,  (u32)isr3);
    kidt_addentry(4,  (u32)isr4);
    kidt_addentry(5,  (u32)isr5);
    kidt_addentry(6,  (u32)isr6);
    kidt_addentry(7,  (u32)isr7);
    kidt_addentry(8,  (u32)isr8);
    kidt_addentry(9,  (u32)isr9);
    kidt_addentry(10, (u32)isr10);
    kidt_addentry(11, (u32)isr11);
    kidt_addentry(12, (u32)isr12);
    kidt_addentry(13, (u32)isr13);
    kidt_addentry(14, (u32)isr14);
    kidt_addentry(15, (u32)isr15);
    kidt_addentry(16, (u32)isr16);
    kidt_addentry(17, (u32)isr17);
    kidt_addentry(18, (u32)isr18);
    kidt_addentry(19, (u32)isr19);
    kidt_addentry(20, (u32)isr20);
    kidt_addentry(21, (u32)isr21);
    kidt_addentry(22, (u32)isr22);
    kidt_addentry(23, (u32)isr23);
    kidt_addentry(24, (u32)isr24);
    kidt_addentry(25, (u32)isr25);
    kidt_addentry(26, (u32)isr26);
    kidt_addentry(27, (u32)isr27);
    kidt_addentry(28, (u32)isr28);
    kidt_addentry(29, (u32)isr29);
    kidt_addentry(30, (u32)isr30);
    kidt_addentry(31, (u32)isr31);

    kidt_ldentries();
}

void kisr_handler(struct kisr_registers r) {
    kvga_print_c("received interrupt: ");
    char s[3];
    itoa(r.int_no, s);
    kvga_print(s);
    kvga_print_c("\n");
    kvga_print(ISR_EX_2_STR[r.int_no]);
    kvga_print_c("\n");
}
