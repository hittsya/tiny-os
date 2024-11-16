#include <kernel/drivers/keyboard.h>
#include <kernel/drivers/port.h>
#include <kernel/drivers/vga.h>

#include <kernel/arch/x86/isr.h>
#include <kernel/libc/string.h>
#include <kernel/libc/memory.h>

#include <kernel/kernel.h>

static char key_buffer[256];
static int  key_buffer_shift_dirty = 0;
#if 0
static const char *UPPERCASE_NAMES[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
        "7", "8", "9", "0", "-", "=", "Backspace", "Tab", "Q", "W", "E",
        "R", "T", "Y", "U", "I", "O", "P", "[", "]", "Enter", "Lctrl",
        "A", "S", "D", "F", "G", "H", "J", "K", "L", ";", "'", "`",
        "LShift", "\\", "Z", "X", "C", "V", "B", "N", "M", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar"};
#endif

static const char UPPERCASE_ASCII[] = { '?', '?', '1', '2', '3', '4', '5', '6',
        '7', '8', '9', '0', '-', '=', '?', '?', 'Q', 'W', 'E', 'R', 'T', 'Y',
        'U', 'I', 'O', 'P', '[', ']', '?', '?', 'A', 'S', 'D', 'F', 'G',
        'H', 'J', 'K', 'L', ';', '\'', '`', '?', '\\', 'Z', 'X', 'C', 'V',
        'B', 'N', 'M', ',', '.', '/', '?', '?', '?', ' '};

#if 0
static const char *LOWERCASE_NAMES[] = { "ERROR", "Esc", "1", "2", "3", "4", "5", "6",
    	"7", "8", "9", "0", "-", "=", "Backspace", "Tab", "q", "w", "e",
        "r", "t", "y", "u", "i", "o", "p", "[", "]", "Enter", "Lctrl",
        "a", "s", "d", "f", "g", "h", "j", "k", "l", ";", "'", "`",
        "LShift", "\\", "z", "x", "c", "v", "b", "n", "m", ",", ".",
        "/", "RShift", "Keypad *", "LAlt", "Spacebar", "CapsLock"};
#endif

static const char LOWERCASE_ASCII[] = { '?', '?', '1', '2', '3', '4', '5', '6',
    	'7', '8', '9', '0', '-', '=', '?', '?', 'q', 'w', 'e', 'r', 't', 'y',
        'u', 'i', 'o', 'p', '[', ']', '?', '?', 'a', 's', 'd', 'f', 'g',
        'h', 'j', 'k', 'l', ';', '\'', '`', '?', '\\', 'z', 'x', 'c', 'v',
        'b', 'n', 'm', ',', '.', '/', '?', '?', '?', ' ', '?'};

static inline int kbd_buffer_not_empty()
{
	return key_buffer[0] != '\0';
}

static void kbd_parse_defsc(u8 scancode)
{
  char letter;

  if (key_buffer_shift_dirty)
  	 letter = UPPERCASE_ASCII[(int)scancode];
  else
     letter = LOWERCASE_ASCII[(int)scancode];

  char str[2] = {letter, '\0'};
  append(key_buffer, letter);
  kvga_print(str);
}

static void kbd_cb(struct kisr_registers regs)
{
    (void)regs;

    u8 scancode = port_read_byte(0x60);
    if (scancode > KSCANCODE_MAX) return;

	switch (scancode) {
	  case KSCANCODE_BACKSPACE:
	    if (kbd_buffer_not_empty()) {
	        backspace(key_buffer);
	        kvga_print_bkscp();
	        return;
	    }
	    break;
      case KSCANCODE_LSHIFT1:
      case KSCANCODE_LSHIFT2:
        key_buffer_shift_dirty = 1;
        break;
      case KSCANCODE_LSHIFT_REL1:
      case KSCANCODE_LSHIFT_REL2:
        key_buffer_shift_dirty = 0;
        break;
	  case KSCANCODE_ENTER:
		kvga_print("\n");
	    handle_usr_input(key_buffer);
	    key_buffer[0] = '\0';
	    break;
	  default:
	    kbd_parse_defsc(scancode);
	    break;
	}
}

void kirq_kbd_init()
{
    kisr_reg_irq_hndlr(IRQ1, kbd_cb);
}
