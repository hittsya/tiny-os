#include <kernel/arch/x86/idt.h>
#include <kernel/drivers/vga.h>

static struct kidt_entry idt[KERN_IDT_ENTRIES];

void kidt_addentry(int n, kptr_t handler)
{
#if KARCH_X86_64
    idt[n].low_offset  = L16(handler);
    idt[n].selector    = KERN_IDT_CS;
    idt[n].ist         = 0;
    idt[n].reserved    = 0;
    idt[n].flags       = 0b1110 | ((0 & 0b11) << 5) |(1 << 7);
    idt[n].mid_offset  = H16(handler);
    idt[n].high_offset = handler >> 32;
#endif

#if KARCH_X86_32
    idt[n].low_offset  = L16(handler);
    idt[n].selector    = KERN_IDT_CS;
    idt[n].always0     = 0;
    idt[n].flags       = 0x8E;
    idt[n].high_offset = H16(handler);
#endif
}

void kidt_ldentries()
{
    struct kidt_register idt_reg;

#if KARCH_X86_64
    idt_reg.base = (u64) &idt;
    idt_reg.limit = 0xFFF;
#endif

#if KARCH_X86_32
    idt_reg.base = (u32) &idt;
    idt_reg.limit = KERN_IDT_ENTRIES * sizeof(struct kidt_entry) - 1;
#endif

#if KARCH_X86_64
    __asm__ __volatile__("lidt (%0)" :: "r" (&idt_reg));
#endif

#if KARCH_X86_32
    __asm__ __volatile__("lidtl (%0)" :: "r" (&idt_reg));
#endif
}
