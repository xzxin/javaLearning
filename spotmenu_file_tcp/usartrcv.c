#include <usartrcv.h>
#include "serial.h"


int usart_init(void)
{
    int fd;
    int ret;
/*看见我的改动了吗*/
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
/*曾经有一份真挚的爱情放在我面前
我没有珍惜
直到现在我才追悔莫及
如果能给我一个重头再来的机会
我会对那个女孩说
我爱你
如果一定要在这份爱上加一个期限
我希望是
一万年
*/