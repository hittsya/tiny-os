#include <kernel/arch/x86/idt.h>
#include <kernel/arch/x86/isr.h>

#include <kernel/drivers/vga.h>
#include <kernel/drivers/port.h>

#include <kernel/libc/string.h>
#include <kernel/kdefines.h>

static kisr_t IRQ_HANDLERS[256];

static const char *ISR_EX_2_STR[] = {
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
    kidt_addentry(0,  (kptr_t)isr0);
    kidt_addentry(1,  (kptr_t)isr1);
    kidt_addentry(2,  (kptr_t)isr2);
    kidt_addentry(3,  (kptr_t)isr3);
    kidt_addentry(4,  (kptr_t)isr4);
    kidt_addentry(5,  (kptr_t)isr5);
    kidt_addentry(6,  (kptr_t)isr6);
    kidt_addentry(7,  (kptr_t)isr7);
    kidt_addentry(8,  (kptr_t)isr8);
    kidt_addentry(9,  (kptr_t)isr9);
    kidt_addentry(10, (kptr_t)isr10);
    kidt_addentry(11, (kptr_t)isr11);
    kidt_addentry(12, (kptr_t)isr12);
    kidt_addentry(13, (kptr_t)isr13);
    kidt_addentry(14, (kptr_t)isr14);
    kidt_addentry(15, (kptr_t)isr15);
    kidt_addentry(16, (kptr_t)isr16);
    kidt_addentry(17, (kptr_t)isr17);
    kidt_addentry(18, (kptr_t)isr18);
    kidt_addentry(19, (kptr_t)isr19);
    kidt_addentry(20, (kptr_t)isr20);
    kidt_addentry(21, (kptr_t)isr21);
    kidt_addentry(22, (kptr_t)isr22);
    kidt_addentry(23, (kptr_t)isr23);
    kidt_addentry(24, (kptr_t)isr24);
    kidt_addentry(25, (kptr_t)isr25);
    kidt_addentry(26, (kptr_t)isr26);
    kidt_addentry(27, (kptr_t)isr27);
    kidt_addentry(28, (kptr_t)isr28);
    kidt_addentry(29, (kptr_t)isr29);
    kidt_addentry(30, (kptr_t)isr30);
    kidt_addentry(31, (kptr_t)isr31);

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
    kidt_addentry(32, (kptr_t)irq0);
    kidt_addentry(33, (kptr_t)irq1);
    kidt_addentry(34, (kptr_t)irq2);
    kidt_addentry(35, (kptr_t)irq3);
    kidt_addentry(36, (kptr_t)irq4);
    kidt_addentry(37, (kptr_t)irq5);
    kidt_addentry(38, (kptr_t)irq6);
    kidt_addentry(39, (kptr_t)irq7);
    kidt_addentry(40, (kptr_t)irq8);
    kidt_addentry(41, (kptr_t)irq9);
    kidt_addentry(42, (kptr_t)irq10);
    kidt_addentry(43, (kptr_t)irq11);
    kidt_addentry(44, (kptr_t)irq12);
    kidt_addentry(45, (kptr_t)irq13);
    kidt_addentry(46, (kptr_t)irq14);
    kidt_addentry(47, (kptr_t)irq15);
    kidt_ldentries();
}

void kisr_handler(struct kisr_registers r) {
    kvga_print_c("received interrupt: ");
    char s[3];
    itoa(r.int_no, s);
    kvga_print(s);
    kvga_print_c("\n");
    kvga_print((char *)ISR_EX_2_STR[r.int_no]);
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
