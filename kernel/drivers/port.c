#include "port.h"

unsigned char port_read_byte(unsigned short port)
{
    unsigned char res;
    __asm__("in %%dx, %%al" : "=a" (res) : "d" (port));
    return res;
}

void port_write_byte(unsigned short port, unsigned char data)
{
    __asm__("out %%al, %%dx" : : "a" (data), "d" (port));
}

unsigned short port_read_word(unsigned short port)
{
    unsigned short res;
    __asm__("in %%dx, %%ax" : "=a" (res) : "d" (port));
    return res;
}

void port_write_word(unsigned short port, unsigned short data)
{
    __asm__("out %%ax, %%dx" : : "a" (data), "d" (port));
}
