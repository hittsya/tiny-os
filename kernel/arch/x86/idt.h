/* idt.h - kernel interrupt descriptor table
 */
#ifndef _IDT_H_
#define _IDT_H_

#include "../../kdefines.h"

#define KERN_IDT_CS      0x08
#define KERN_IDT_ENTRIES 256

/* IDT single entry
 */
struct PACKED kidt_entry {
    u16 low_offset;  /* Lower 16 bits of handler function address */
    u16 selector;    /* Kernel segment selector */
    u8  always0;
    u8  flags;
    u16 high_offset; /* Higher 16 bits of handler function address */
};

/* @brief A pointer to the array of interrupt handlers.
 */
struct PACKED kidt_register{
    u16 limit;
    u32 base;
};

/* @brief Add entry to the IDT
 */
void kidt_addentry(int n, u32 handler);

/* @brief Load added IDT entries
 */
void kidt_ldentries();

#endif /* _IDT_H_ */
