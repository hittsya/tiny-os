#include <kernel/libc/memory.h>

static u32 place_ptr = 0x10000;

void memcpy(char *source, char *dest, int nbytes)
{
    for (int i = 0; i < nbytes; i++) {
        *(dest + i) = *(source + i);
    }
}

void memset(u8 *dest, u8 val, u32 len)
{
    u8 *temp = (u8 *)dest;
    for ( ; len != 0; len--)
      *temp++ = val;
}

u32 kmalloc(u32 size, int align, u32 *phys_addr) {
    if (align == 1 && (place_ptr & 0xFFFFF000)) {
        place_ptr &= 0xFFFFF000;
        place_ptr += 0x1000;
    }

    if (phys_addr)
      *phys_addr = place_ptr;

    u32 ret = place_ptr;
    place_ptr += size;
    return ret;
}