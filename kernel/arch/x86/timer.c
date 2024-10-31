#include "timer.h"
#include "isr.h"
#include "../../drivers/vga.h"
#include "../../drivers/port.h"
#include "../../util.h"

static u32 tick = 0;

static void kirq_timer_cb(struct kisr_registers)
{
    tick++;
    kvga_print_c("Tick: ");

    char tick_ascii[256];
    itoa(tick, tick_ascii);
    kvga_print(tick_ascii);
    kvga_print_c("\n");
}

void kirq_timer_init(u32 freq)
{
    kisr_reg_irq_hndlr(IRQ0, kirq_timer_cb);

    u32 divisor = 1193180 / freq;
    u8 low      = (u8)(divisor & 0xFF);
    u8 high     = (u8)((divisor >> 8) & 0xFF);

    port_write_byte(0x43, 0x36);
    port_write_byte(0x40, low );
    port_write_byte(0x40, high);
}
