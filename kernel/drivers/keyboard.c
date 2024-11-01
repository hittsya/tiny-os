#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>

#include <kernel/arch/x86/isr.h>
#include <kernel/libc/string.h>
#include <kernel/libc/memory.h>

#include <kernel/kernel.h>

static char key_buffer[256];

#if 0
static const char *SCANCODE_NAMES[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
        "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
#endif

static const char SCANCODE_ASCII[] = { '?', '?', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

static void kbd_cb(struct kisr_registers regs)
{
    (void)regs;
    u8 scancode = port_read_byte(0x60);

    if (scancode > KSCANCODE_MAX)
        return;

    /**/   if (scancode == KSCANCODE_BACKSPACE) {
        if (key_buffer[0] != '\0') {
            backspace(key_buffer);
            kvga_print_bkscp();
        }
    } else if (scancode == KSCANCODE_ENTER) {
        kvga_print("\n");
        handle_usr_input(key_buffer);
        key_buffer[0] = '\0';
    } else {
        char letter = SCANCODE_ASCII[(int)scancode];
        char str[2] = {letter, '\0'};
        append(key_buffer, letter);
        kvga_print(str);
    }
}

void kirq_kbd_init()
{
    kisr_reg_irq_hndlr(IRQ1, kbd_cb);
}
