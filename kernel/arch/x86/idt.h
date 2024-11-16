/* idt.h - kernel interrupt descriptor table
 */
#ifndef _IDT_H_
#define _IDT_H_

#include <kernel/kdefines.h>

#define KERN_IDT_CS      0x08
#define KERN_IDT_ENTRIES 256

/* IDT single entry
 */

#if KARCH_X86_32
struct PACKED kidt_entry {
    u16 low_offset;  /* Lower 16 bits of handler function address */
    u16 selector;    /* Kernel segment selector */
    u8  always0;
    u8  flags;
    u16 high_offset; /* Higher 16 bits of handler function address */
};
#endif


#if KARCH_X86_64
struct PACKED kidt_entry {
 u16 low_offset;  /* Lower 16 bits of handler function address */
 u16 selector;    /* Kernel segment selector */
 u8  ist;
 u8  flags;
 u16 mid_offset; /* Higher 16 bits of handler function address */
 u32 high_offset;
 u32 reserved;
};
#endif

/* @brief A pointer to the array of interrupt handlers.
 */
struct PACKED kidt_register{
    u16    limit;
    kptr_t base;
};

/* @brief Add entry to the IDT
 */
void kidt_addentry(int n, kptr_t handler);

/* @brief Load added IDT entries
 */
void kidt_ldentries();

#endif /* _IDT_H_ */
