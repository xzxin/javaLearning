
#ifdef __cplusplus
extern "C"{
#endif
#ifndef _SERIAL_H
#define _SERIAL_H 1
#include <termios.h>            /* tcgetattr, tcsetattr */
#include <stdio.h>              /* perror, printf, puts, fprintf, fputs */
#include <unistd.h>             /* read, write, close */
#include <fcntl.h>              /* open */
#include <sys/signal.h>
#include <sys/types.h>
#include <string.h>             /* bzero, memcpy */
#include <limits.h>             /* CHAR_MAX */
//void set_baudrate (struct termios *opt, unsigned int baudrate);
//void set_data_bit (struct termios *opt, unsigned int databit);
//void set_stopbit (struct termios *opt, const char *stopbit);
//void set_parity (struct termios *opt, char parity);

int  set_port_attr (
                          int fd,
                          int  baudrate,          // B1200 B2400 B4800 B9600 .. B115200
                          int  databit,           // 5, 6, 7, 8
                          const char *stopbit,    //  "1", "1.5", "2"
                          char parity,            // N(o), O(dd), E(ven)
                          int vtime,
                          int vmin );


#endif /* serial.c */

#ifdef __cplusplus
}
#endif
