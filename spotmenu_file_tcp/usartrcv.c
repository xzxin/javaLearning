#include <usartrcv.h>
#include "serial.h"


int usart_init(void)
{
    int fd;
    int ret;

    fd = open(DEV_NAME, O_RDWR|O_NOCTTY);//|O_APPEND);//|O_NDELAY);
    //fd = open(DEV_NAME, O_RDONLY|O_NOCTTY|O_NDELAY);//|O_NONBLOCK);
        if(fd < 0) {
                perror(DEV_NAME);
                return -1;
        }
        fcntl(fd,F_SETFL,FNDELAY);
	 ret = set_port_attr (
                         	fd,  
                            B115200,          // B1200 B2400 B4800 B9600 .. B115200
                            8,           	  // 5, 6, 7, 8
                          	"1",    	  //  "1", "1.5", "2"
                          	'N',              // N(o), O(dd), E(ven)
                            0,		  //VTIME
                         4);		  //VMINd
     tcflush(fd,TCIFLUSH);
    // printf("result = %d\n",ret);
    return(fd);
}

