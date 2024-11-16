#ifndef _KEYBOARD_H_
#define _KEYBOARD_H_

#define KSCANCODE_MAX        57
#define KSCANCODE_BACKSPACE  0x0E
#define KSCANCODE_ENTER      0x1C
#define KSCANCODE_LSHIFT1     0x2A
#define KSCANCODE_LSHIFT2     0x36
#define KSCANCODE_LSHIFT_REL1 0xAA
#define KSCANCODE_LSHIFT_REL2 0xB6

void kirq_kbd_init();

#endif /*_KEYBOARD_H_ */
