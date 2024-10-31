#include <kernel/drivers/port.h>

u8 port_read_byte(u16 port)
{
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void port_write_byte(u16 port, u8 data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

u16 port_read_word(u16 port)
{
    unsigned short res;
    __asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
    return res;
}

void port_write_word(u16 port, u16 data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
