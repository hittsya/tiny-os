#ifndef _KERNEL_H_
#define _KERNEL_H_

void kpanic(const char *msg);

void handle_usr_input(char *ch);
void irq_irs_install();

#endif /* _KERNEL_H_ */
