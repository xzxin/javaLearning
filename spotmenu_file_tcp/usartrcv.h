#ifdef __cplusplus
extern "C"{
#endif
#ifndef USARTRCV_H
#define USARTRCV_H
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
//#include <asm/termios.h>
#include "serial.h"
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#define DEV_NAME  "/dev/ttySP1"
int usart_init(void);
#endif
#ifdef __cplusplus
}
#endif
