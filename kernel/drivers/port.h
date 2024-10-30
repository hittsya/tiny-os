#ifndef _PORT_H_
#define _PORT_H_

#include "../kdefines.h"

u8 port_read_byte(u16 port);
void port_write_byte(u16 port, u8 data);

u16 port_read_word(u16 port);
void port_write_word(u16 port, u16 data);

#endif /* _PORT_H_ */
