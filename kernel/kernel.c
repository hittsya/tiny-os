#include "drivers/port.h"
#include "drivers/vga.h"

void main() {
    port_write_byte(0x3d4, 14);

    int position = port_read_byte(0x3d5);
    position = position << 8;
    int offset_from_vga = position * 2;

    kvga_clear();
    char *vga = (char *)0xb8000;
    vga[offset_from_vga] = 't';
    vga[offset_from_vga+1] = 0x0f;
}
