#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>

#include <kernel/libc/memory.h>
#include <kernel/kdefines.h>

static int kvga_make_curoff(int col, int row)
{
    return 2 * (row * VGA_MAX_COLS + col);
}

static int kvga_curoff_row(int off)
{
    return off / (2 * VGA_MAX_COLS);
}

static int kvga_curoff_col(int off)
{
    return (off - (kvga_curoff_row(off) * 2 * VGA_MAX_COLS)) / 2;
}

void kvga_set_curoff(int off)
{
    off /= 2;
    port_write_byte(VGA_REG_SCRN_CNTL, 14);
    port_write_byte(VGA_REG_SCRN_DATA, (u8)(off >> 8));
    port_write_byte(VGA_REG_SCRN_CNTL, 15);
    port_write_byte(VGA_REG_SCRN_DATA, (u8)(off & 0xff));
}

int kvga_get_curoff()
{
    port_write_byte(VGA_REG_SCRN_CNTL, 14);
    int offset = port_read_byte(VGA_REG_SCRN_DATA) << 8;

    port_write_byte(VGA_REG_SCRN_CNTL, 15);
    offset += port_read_byte(VGA_REG_SCRN_DATA);

    return offset * 2;
}

int kvga_putchar(char c, int col, int row, char attr)
{
    u8 *vidmem = (u8 *) VGA_VIDMEM;
    if (!attr) attr = VGA_WHITE_ON_BLACK;

    if (col >= VGA_MAX_COLS || row >= VGA_MAX_ROWS) {
        vidmem[2 * (VGA_MAX_COLS)*(VGA_MAX_ROWS) - 2] = 'X';
        vidmem[2 * (VGA_MAX_COLS)*(VGA_MAX_ROWS) - 1] = VGA_RED_ON_WHITE;
        return kvga_make_curoff(col, row);
    }

    int offset;
    if (col >= 0 && row >= 0) offset = kvga_make_curoff(col, row);
    else offset = kvga_get_curoff();

    if (c == '\n') {
        row    = kvga_curoff_row(offset);
        offset = kvga_make_curoff(0, row+1);
    } else {
        vidmem[offset]   =  c;
        vidmem[offset+1] =  attr;
        offset           += 2;
    }

    if (offset >= VGA_MAX_ROWS * VGA_MAX_COLS * 2) {
        for (int i = 1; i < VGA_MAX_ROWS; i++) {
            memcpy((s8 *)(kvga_make_curoff(0, i)   + VGA_VIDMEM),
                   (s8 *)(kvga_make_curoff(0, i-1) + VGA_VIDMEM),
                   VGA_MAX_COLS * 2);
        }

        char *last_line = (s8 *)(kvga_make_curoff(0, VGA_MAX_ROWS-1) + VGA_VIDMEM);
        for (int i = 0; i < VGA_MAX_COLS * 2; i++) {
            last_line[i] = 0;
        }

        offset -= 2 * VGA_MAX_COLS;
    }

    kvga_set_curoff(offset);
    return offset;
}

void kvga_putstr(char *message, int col, int row)
{
    int off;
    if (col >= 0 && row >= 0)
        off = kvga_make_curoff(col, row);
    else {
        off = kvga_get_curoff();
        row = kvga_curoff_row(off);
        col = kvga_curoff_col(off);
    }

    int i = 0;
    while (message[i] != 0) {
        off = kvga_putchar(message[i++], col, row, VGA_WHITE_ON_BLACK);
        col = kvga_curoff_col(off);
        row = kvga_curoff_row(off);
    }
}

void kvga_print_c(const char *message)
{
    kvga_putstr_c(message, -1, -1);
}

void kvga_print(char *message)
{
    kvga_putstr_c(message, -1, -1);
}

void kvga_putstr_c(const char *message, int col, int row)
{
    kvga_putstr((char *)message, col, row);
}

void kvga_clear()
{
    int scrn_sz = VGA_MAX_ROWS * VGA_MAX_COLS;
    char *vidmem = (char *)VGA_VIDMEM;

    for (int i = 0; i < scrn_sz; ++i) {
        vidmem[i*2+0] = ' ';
        vidmem[i*2+1] = VGA_WHITE_ON_BLACK;
    }

    kvga_set_curoff(kvga_make_curoff(0, 0));
}

void kvga_print_bkscp()
{
    int offset = kvga_get_curoff()-2;
    int row    = kvga_curoff_row(offset);
    int col    = kvga_curoff_col(offset);

    kvga_putchar(' ' /* 0x08 */, col, row, VGA_WHITE_ON_BLACK);
    kvga_set_curoff(kvga_get_curoff()-1);
}
