#include "drivers/port.h"
#include "drivers/vga.h"

void kmain() {
    kvga_clear();
    kvga_putstr_c("test", 0, 0);
    kvga_putstr_c("test2345", 0, 1);
}
