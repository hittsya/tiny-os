#include "isr.h"
#include "idt.h"
#include "../../drivers/vga.h"
#include "../../drivers/port.h"
#include "../../util.h"

static kisr_t IRQ_HANDLERS[256];

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

    // Remap the PIC
    port_write_byte(0x20, 0x11);
    port_write_byte(0xA0, 0x11);
    port_write_byte(0x21, 0x20);
    port_write_byte(0xA1, 0x28);
    port_write_byte(0x21, 0x04);
    port_write_byte(0xA1, 0x02);
    port_write_byte(0x21, 0x01);
    port_write_byte(0xA1, 0x01);
    port_write_byte(0x21, 0x0);
    port_write_byte(0xA1, 0x0);

    // Install the IRQs
    kidt_addentry(32, (u32)irq0);
    kidt_addentry(33, (u32)irq1);
    kidt_addentry(34, (u32)irq2);
    kidt_addentry(35, (u32)irq3);
    kidt_addentry(36, (u32)irq4);
    kidt_addentry(37, (u32)irq5);
    kidt_addentry(38, (u32)irq6);
    kidt_addentry(39, (u32)irq7);
    kidt_addentry(40, (u32)irq8);
    kidt_addentry(41, (u32)irq9);
    kidt_addentry(42, (u32)irq10);
    kidt_addentry(43, (u32)irq11);
    kidt_addentry(44, (u32)irq12);
    kidt_addentry(45, (u32)irq13);
    kidt_addentry(46, (u32)irq14);
    kidt_addentry(47, (u32)irq15);
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

void kirq_handler(struct kisr_registers r)
{
    if (r.int_no >= 40)
        port_write_byte(0xA0, 0x20);
    port_write_byte(0x20, 0x20);

    if (IRQ_HANDLERS[r.int_no] != 0) {
        kisr_t handler = IRQ_HANDLERS[r.int_no];
        handler(r);
    }
}

void kisr_reg_irq_hndlr(u8 n, kisr_t handler)
{
    IRQ_HANDLERS[n] = handler;
}
