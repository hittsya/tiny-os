#include <kernel/arch/x86/idt.h>
#include <kernel/drivers/vga.h>

static struct kidt_entry    idt[KERN_IDT_ENTRIES];
static struct kidt_register idt_reg;

void kidt_addentry(int n, u32 handler)
{
    idt[n].low_offset  = L16(handler);
    idt[n].selector    = KERN_IDT_CS;
    idt[n].always0     = 0;
    idt[n].flags       = 0x8E;
    idt[n].high_offset = H16(handler);
}

void kidt_ldentries()
{
    idt_reg.base = (u32) &idt;
    idt_reg.limit = KERN_IDT_ENTRIES * sizeof(struct kidt_entry) - 1;
    __asm__ __volatile__("lidtl (%0)" : : "r" (&idt_reg));
}
