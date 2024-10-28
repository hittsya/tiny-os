#include "port.h"
#include "vga.h"

static int kvga_make_curoff(int col, int row)
{
    return 2*(row * VGA_MAX_COLS + col);
}

static void kvga_set_curoff(int off)
{
    off /= 2;
    port_write_byte(VGA_REG_SCRN_CNTL, 14);
    port_write_byte(VGA_REG_SCRN_DATA, (unsigned char)(off >> 8));
    port_write_byte(VGA_REG_SCRN_CNTL, 15);
    port_write_byte(VGA_REG_SCRN_DATA, (unsigned char)(off & 0xff));
}

void kvga_clear()
{
    int scrn_sz = VGA_MAX_ROWS * VGA_MAX_COLS;
    char *vidmem= (char *)VGA_VIDMEM;

    for (int i = 0; i < scrn_sz; ++i) {
        vidmem[i*2+0] = ' ';
        vidmem[i*2+1] = VGA_WHITE_ON_BLACK;
    }

    kvga_set_curoff(kvga_make_curoff(0, 0));
}
