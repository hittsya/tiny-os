#include "keyboard.h"

#include "keyboard.h"
#include "port.h"
#include "vga.h"

#include "../arch/x86/isr.h"
#include "../util.h"


static void kbd_scan_decode(u8 scancode) {
    switch (scancode) {
    case 0x0:
        kvga_print("ERROR");
        break;
    case 0x1:
        kvga_print("ESC");
        break;
    case 0x2:
        kvga_print("1");
        break;
    case 0x3:
        kvga_print("2");
        break;
    case 0x4:
        kvga_print("3");
        break;
    case 0x5:
        kvga_print("4");
        break;
    case 0x6:
        kvga_print("5");
        break;
    case 0x7:
        kvga_print("6");
        break;
    case 0x8:
        kvga_print("7");
        break;
    case 0x9:
        kvga_print("8");
        break;
    case 0x0A:
        kvga_print("9");
        break;
    case 0x0B:
        kvga_print("0");
        break;
    case 0x0C:
        kvga_print("-");
        break;
    case 0x0D:
        kvga_print("+");
        break;
    case 0x0E:
        kvga_print("Backspace");
        break;
    case 0x0F:
        kvga_print("Tab");
        break;
    case 0x10:
        kvga_print("Q");
        break;
    case 0x11:
        kvga_print("W");
        break;
    case 0x12:
        kvga_print("E");
        break;
    case 0x13:
        kvga_print("R");
        break;
    case 0x14:
        kvga_print("T");
        break;
    case 0x15:
        kvga_print("Y");
        break;
    case 0x16:
        kvga_print("U");
        break;
    case 0x17:
        kvga_print("I");
        break;
    case 0x18:
        kvga_print("O");
        break;
    case 0x19:
        kvga_print("P");
        break;
    case 0x1A:
        kvga_print("[");
        break;
    case 0x1B:
        kvga_print("]");
        break;
    case 0x1C:
        kvga_print("ENTER");
        break;
    case 0x1D:
        kvga_print("LCtrl");
        break;
    case 0x1E:
        kvga_print("A");
        break;
    case 0x1F:
        kvga_print("S");
        break;
    case 0x20:
        kvga_print("D");
        break;
    case 0x21:
        kvga_print("F");
        break;
    case 0x22:
        kvga_print("G");
        break;
    case 0x23:
        kvga_print("H");
        break;
    case 0x24:
        kvga_print("J");
        break;
    case 0x25:
        kvga_print("K");
        break;
    case 0x26:
        kvga_print("L");
        break;
    case 0x27:
        kvga_print(";");
        break;
    case 0x28:
        kvga_print("'");
        break;
    case 0x29:
        kvga_print("`");
        break;
    case 0x2A:
        kvga_print("LShift");
        break;
    case 0x2B:
        kvga_print("\\");
        break;
    case 0x2C:
        kvga_print("Z");
        break;
    case 0x2D:
        kvga_print("X");
        break;
    case 0x2E:
        kvga_print("C");
        break;
    case 0x2F:
        kvga_print("V");
        break;
    case 0x30:
        kvga_print("B");
        break;
    case 0x31:
        kvga_print("N");
        break;
    case 0x32:
        kvga_print("M");
        break;
    case 0x33:
        kvga_print(",");
        break;
    case 0x34:
        kvga_print(".");
        break;
    case 0x35:
        kvga_print("/");
        break;
    case 0x36:
        kvga_print("Rshift");
        break;
    case 0x37:
        kvga_print("Keypad *");
        break;
    case 0x38:
        kvga_print("LAlt");
        break;
    case 0x39:
        kvga_print("Spc");
        break;
    default:
        if (scancode <= 0x7f) {
            kvga_print("Unknown key down");
        } else if (scancode <= 0x39 + 0x80) {
            kvga_print("key up ");
            kbd_scan_decode(scancode - 0x80);
        } else kvga_print("Unknown key up");
        break;
    }
}

static void kbd_cb(struct kisr_registers regs)
{
    (void)regs;
    u8 scancode = port_read_byte(0x60);

    char sc_ascii[32];
    itoa(scancode, sc_ascii);

    kvga_print("Keyboard scancode: ");
    kvga_print(sc_ascii);
    kvga_print(", ");
    kbd_scan_decode(scancode);
    kvga_print("\n");
}

void kbd_init()
{
    kisr_reg_irq_hndlr(IRQ1, kbd_cb);
}
