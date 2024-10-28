#ifndef _PORT_H_
#define _PORT_H_

unsigned char port_read_byte(unsigned short port);
void port_write_byte(unsigned short port, unsigned char data);

unsigned short port_read_word(unsigned short port);
void port_write_word(unsigned short port, unsigned short data);

#endif /* _PORT_H_ */
