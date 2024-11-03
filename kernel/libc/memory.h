#ifndef _MEMORY_H_
#define _MEMORY_H_

#include <kernel/kdefines.h>

void memcpy(char *source, char *dest, int nbytes);
void memset(u8 *dest, u8 val, u32 len);

u32 kmalloc(u32 size, int align, u32 *phys_addr);

#endif /* _MEMORY_H_ */