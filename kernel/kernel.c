#include "drivers/port.h"
#include "drivers/vga.h"

#include "util.h"

void kmain() {
    kvga_clear();

    for (int i = 0; i < 24; i++) {
        char str[255];
        itoa(i, str);
        kvga_putstr(str, 0, i);
    }

    kvga_print_c("\ntest1\n");
    kvga_print_c("test2\n");
    kvga_print_c("test3\n");
}
