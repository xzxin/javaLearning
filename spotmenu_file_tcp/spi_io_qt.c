/*
 * SPI testing utility (using spidev driver)
 *
 * Copyright (c) 2007  MontaVista Software, Inc.
 * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License.
 *
 * Cross-compile with cross-gcc -I/path/to/cross-kernel/include
 */
/*PE9-P1.17 PD14-P1.18*/

#include "spi_io_qt.h"

int fd_spi;
static uint8_t mode = 0;
static uint8_t bits = 8;
static uint32_t speed = 5000000;
static uint32_t delay = 0;
char buf_rxprotocol[7];
char buf_txprotocol[]="ok\n";
unsigned char buf_volt[1000];
unsigned char buf_theta[1200];
unsigned char buf_AC[40*80];
unsigned char buf_spotinfo[30];
unsigned char buf_weldpara[SIZE_WELDBUFF*30];
unsigned char buf_weldpara_Instant[SIZE_WELDBUFF*SIZE_INSTANT_LEN*2];
struct spi_ioc_transfer tr_txrx[7];


int gpio_export(int pin)
{
    char buffer[64];
    int len;
    int fd;

    fd = open("/sys/class/gpio/export", O_WRONLY);
    if (fd < 0) {
        printf("Failed to open export for writing!\n");
        return(-1);
    }
    //printf("\n%d\n",fd);
    len = snprintf(buffer, sizeof(buffer),"%d", pin);
    printf("%s len=%d",buffer,len);
    if (write(fd, buffer, len) < 0) {
    	printf("Failed to export gpio!");
        return -1;
    }

    close(fd);
    return 0;
}

int gpio_unexport(int pin)
{
    char buffer[64];
    int len;
    int fd;

    fd = open("/sys/class/gpio/unexport", O_WRONLY);
    if (fd < 0) {
    	printf("Failed to open unexport for writing!\n");
        return -1;
    }

    len = snprintf(buffer, sizeof(buffer),"%d", pin);
    if (write(fd, buffer, len) < 0) {
    	printf("Failed to unexport gpio!");
        return -1;
    }

    close(fd);
    return 0;
}

//dir: 0-->IN, 1-->OUT
int gpio_direction(int pin, int dir)
{
    static const char dir_str[] = "in\0out";
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/direction", pin);
    //printf("\n%s\n",path);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
    	printf("Failed to open gpio direction for writing!\n");
        return -1;
    }

    if (write(fd, &dir_str[dir == 0 ? 0 : 3], dir == 0 ? 2 : 3) < 0) {
    	printf("Failed to set direction!\n");
        return -1;
    }

    close(fd);
    return 0;
}

//value: 0-->LOW, 1-->HIGH
int gpio_write(int pin, int value)
{
    static const char values_str[] = "01";
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
    	printf("Failed to open gpio value for writing!\n");
        return -1;
    }

    if (write(fd, &values_str[value == 0 ? 0 : 1], 1) < 0) {
    	printf("Failed to write value!\n");
        return -1;
    }

    close(fd);
    return 0;
}
/*
int gpio_read(int pin)
{
    char path[64];
    char value_str[3];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
    printf("fd=%d\n",fd);
    if (fd < 0) {
    	printf("Failed to open gpio value for reading!\n");
        return -1;
    }
	lseek(fd,0,SEEK_SET);
    if (read(fd, value_str, 3) < 0) {
    	printf("Failed to read value!\n");
        return -1;
    }

    close(fd);
    printf("read value=%d!\n",atoi(value_str));
    return (atoi(value_str));
}
*/
int gpio_openread(int pin)
{
    char path[64];
    int fd;

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/value", pin);
    fd = open(path, O_RDONLY);
   // printf("%s\n",path);
    if (fd < 0) {
   //     printf("Failed to open gpio value for reading!\n");
        return -1;
    }
    return (fd);
}
int gpio_read(int fd)
{
    char value_str[3];
    lseek(fd,0,SEEK_SET);
    //printf("read_len=%d",read(fd, value_str, 3));
    read(fd, value_str, 3);
    //if (read(fd, value_str, 3) < 0) {
    //    printf("Failed to read value!\n");
    //    return -1;
    //}
  //  printf("read value=%d!\n",atoi(value_str));
    return (atoi(value_str));
}
// 0-->none, 1-->rising, 2-->falling, 3-->both
int gpio_edge(int pin, int edge)
{
	const char dir_str[] = "none\0rising\0falling\0both";
	char ptr;
	char path[64];
    int fd;
    switch(edge){
				case 0:
				ptr = 0;
				break;
				case 1:
					ptr = 5;
					break;
				case 2:
					ptr = 12;
					break;
				case 3:
					ptr = 20;
					break;
				default:
					ptr = 0;
    			}

    snprintf(path, sizeof(path), "/sys/class/gpio/gpio%d/edge", pin);
    fd = open(path, O_WRONLY);
    if (fd < 0) {
    	printf("Failed to open gpio edge for writing!\n");
        return -1;
    }

    if (write(fd, &dir_str[ptr], strlen(&dir_str[ptr])) < 0) {
    	printf("Failed to set edge!\n");
        return -1;
    }

    close(fd);
    return 0;
}

int io_init(void)
{
	gpio_export(GPIO_IN1);
    //gpio_export(GPIO_IN2);
	gpio_direction(GPIO_IN1, 0);//0 standfor in
    //gpio_direction(GPIO_IN2, 0);
	return 0;
}
int spi_init(void)
{
	int ret=0;
	tr_txrx[0].tx_buf = (unsigned long)buf_txprotocol;
	tr_txrx[0].rx_buf      = 0;
	tr_txrx[0].len         = 2;
	tr_txrx[0].delay_usecs = delay;
	tr_txrx[0].speed_hz    = speed;
	tr_txrx[0].bits_per_word = bits;//send protocol

	tr_txrx[1].tx_buf =  0;
	tr_txrx[1].rx_buf      =  (unsigned long)buf_rxprotocol;
	tr_txrx[1].len         = 7;
	tr_txrx[1].delay_usecs = delay;
	tr_txrx[1].speed_hz    = speed;
	tr_txrx[1].bits_per_word = bits;//rcv protocol

	tr_txrx[2].tx_buf =  0;
    tr_txrx[2].rx_buf      =  (unsigned long)buf_theta;
    tr_txrx[2].len         = 1200;
	tr_txrx[2].delay_usecs = delay;
	tr_txrx[2].speed_hz    = speed;
	tr_txrx[2].bits_per_word = bits;//volt rcv buf

	tr_txrx[3].tx_buf = 0;
    tr_txrx[3].rx_buf      = (unsigned long) buf_weldpara_Instant;
    tr_txrx[3].len         = SIZE_WELDBUFF*SIZE_INSTANT_LEN*2;
	tr_txrx[3].delay_usecs = delay;
	tr_txrx[3].speed_hz    = speed;
	tr_txrx[3].bits_per_word = bits;//send protocol

    tr_txrx[4].tx_buf = 0;
    tr_txrx[4].rx_buf      = (unsigned long)buf_spotinfo;
    tr_txrx[4].len         = 30;
    tr_txrx[4].delay_usecs = delay;
    tr_txrx[4].speed_hz    = speed;
    tr_txrx[4].bits_per_word = bits;//send protocol

    tr_txrx[5].tx_buf = 0;
    tr_txrx[5].rx_buf      = (unsigned long)buf_weldpara;
    tr_txrx[5].len         = SIZE_WELDBUFF*30;
    tr_txrx[5].delay_usecs = delay;
    tr_txrx[5].speed_hz    = speed;
    tr_txrx[5].bits_per_word = bits;//send protocol

    tr_txrx[6].tx_buf = 0;
    tr_txrx[6].rx_buf      = (unsigned long)buf_AC;
    tr_txrx[6].len         = 80*40;
    tr_txrx[6].delay_usecs = delay;
    tr_txrx[6].speed_hz    = speed;
    tr_txrx[6].bits_per_word = bits;//send protocol



    fd_spi = open(SPI_DEVICE, O_RDONLY);
	if (fd_spi < 0) {
		printf("can't open %s \n", SPI_DEVICE);
		return -1;
	}

	ret = ioctl(fd_spi, SPI_IOC_WR_MODE, &mode);			/* set spi mode 		*/
	if (ret == -1) {
		printf("can't set wr spi mode\n");
		return -1;
	}

	ret = ioctl(fd_spi, SPI_IOC_WR_BITS_PER_WORD, &bits);		/* set spi bits per word	*/
	if (ret == -1) {
		printf("can't set bits per word\n");
		return -1;
	}

	ret = ioctl(fd_spi, SPI_IOC_WR_MAX_SPEED_HZ, &speed);		/* max speed hz			*/
	if (ret == -1)	{
		printf("can't set max speed hz\n");
		return -1;
	}

}
/*
int main(int argc, char *argv[])
{
	int ret       = 0;
	int i;
	int readValue;
	printf("io test started!\n");
	while (1){
			readValue=(gpio_read(GPIO_IN1));

			usleep(100);
			if (readValue=='1')
			{
				printf("io test passed!\n");
				ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[2]);
				ret = ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[3]);
				 for (i=0;i<256;i++)
					 {
					    printf("%d ",buf_volt[i]);
					 }
					    //printf("\n");

				 for (i=0;i<256;i++)
					  {
					    printf("%d ",buf_curr[i]);
					  }
			}
		}

	close(fd_spi);

	return ret;
}
*/
