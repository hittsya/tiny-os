#ifndef _VGA_H_
#define _VGA_H_

#define VGA_VIDMEM   0xb8000
#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80

#define VGA_WHITE_ON_BLACK 0x0f
#define VGA_RED_ON_WHITE   0xf4

#define VGA_REG_SCRN_CNTL 0x3d4
#define VGA_REG_SCRN_DATA 0x3d5

void kvga_clear();
//void kvga_putstr(char *message, int col, int row);
//void kvga_print(char *message);

#endif /* _VGA_H_ */
