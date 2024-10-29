#ifndef _VGA_H_
#define _VGA_H_

#define VGA_VIDMEM   0xb8000
#define VGA_MAX_ROWS 25
#define VGA_MAX_COLS 80

#define VGA_WHITE_ON_BLACK 0x0f
#define VGA_RED_ON_WHITE   0xf4

#define VGA_REG_SCRN_CNTL 0x3d4
#define VGA_REG_SCRN_DATA 0x3d5

/* @brief Set the VGA cursor offset
 *
 * @param off cursor offset
 */
void kvga_set_curoff(int off);

/* @brief Get the current VGA cursor offset
 *
 * @returns current cursor offset
 */
int kvga_get_curoff();

/* @brief Clear the screen
 */
void kvga_clear();

/* @brief Print character at the specific position with
 * specific attribute.
 *
 * @param c Character
 * @param col Column address
 * @param row Row address
 * @param row Attr attribute
 *
 * @returns resulting cursor offset
 */
int kvga_putchar(char c, int col, int row, char attr);

/* @brief Print the string
 */
void kvga_putstr(char *message, int col, int row);

/* @brief Print the string, accepts constant character array
 */
void kvga_putstr_c(const char *message, int col, int row);

#endif /* _VGA_H_ */
