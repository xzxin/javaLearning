#ifndef FILEWRITE_H

#define FILEWRITE_H
#ifdef __cplusplus
extern "C"{
#endif
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <errno.h>
#include <math.h>
#include "spi_io_qt.h"
#ifdef __cplusplus
int file_init(char *s,char *s_calc,char *time);
int file_write(int fd);
int calc_detail_write(int fd);

}
#endif
#endif

