
#ifdef __cplusplus
extern "C"{
#endif
#ifndef SPI_IO_QT_H
#define SPI_IO_QT_H
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#define SPI_DEVICE	"/dev/spidev1.0"
#define GPIO_IN1 83   //P2.19-PA15
#define GPIO_IN2 50    //P1.18-PD14
#define SIZE_WELDBUFF 100
#define SIZE_INSTANT_LEN 20
int gpio_export(int pin);
int gpio_unexport(int pin);
int gpio_direction(int pin, int dir);
int gpio_write(int pin, int value);
//int gpio_read(int pin);
int io_init(void);
int spi_init(void);
int gpio_openread(int pin);
int gpio_read(int fd);
#endif
#ifdef __cplusplus
}
#endif

