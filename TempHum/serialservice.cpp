#include "serialservice.h"
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <termios.h>

#define BAUDRATE B115200
//#define COM1 "/dev/tts/0"
//#define COM2 "/dev/ttse/0"
//#define COM2 "/dev/ttyS0"  xxxx
#define COM2 "/dev/ttyS3"

int SerialService::fd = -1;

static struct termios oldtio,newtio;

SerialService::SerialService(QObject *parent) :
    QObject(parent),
    //my_com(0),
    com_state(CLOSE)
{
    read_timer = new QTimer();
    read_timer->start(READTIME);
}

qint64 SerialService::readFromSerial(QByteArray &byte)
{
    char tt[14];
    char txbuff[5];
    char rxbuff[7];
    int i = 0;
    txbuff[0] = 0xAA;
    txbuff[1] = 0xFF;
    txbuff[2] = 0x10;
    txbuff[3] = 0xFF;
    for (i = 2; i < 3; i++) {
        txbuff[3] ^= txbuff[i];
    }
    txbuff[4] = 0xFF;

    int j;
        for(j=0; j<5; j++) {
            write(fd,&txbuff[j],1);
    //		printf(" %x",buf[i]);
            usleep(100);
        }
    fflush(stdout);
    read(fd,rxbuff,7);
    fflush(stdout);

    usleep(500);

    for(i=0;i<7;i++)
    {
        tt[i]=rxbuff[i];
    }

    char txbuff1[5];
    char rxbuff1[7];
    txbuff1[0] = 0xAA;
    txbuff1[1] = 0xFF;
    txbuff1[2] = 0x1D;
    txbuff1[3] = 0xFF;
    for (i = 2; i < 3; i++) {
        txbuff1[3] ^= txbuff1[i];
    }
    txbuff1[4] = 0xFF;

    for(j=0; j<5; j++) {
        write(fd,&txbuff1[j],1);
    //		printf(" %x",buf[i]);
         usleep(100);
     }

    fflush(stdout);
    read(fd,rxbuff1,7);
    fflush(stdout);

    for(i=0;i<7;i++)
    {
        tt[i+7]=rxbuff1[i];
    }
    int n=14;
    if (n > 0) {
        byte = QByteArray(tt, 14);
    }
    return 1;
}

int SerialService::writeToSerial(const QByteArray &byte)
{
   if(OPEN == com_state)
    {
        return 1;
    }
    return -1;
      
}

bool SerialService::openCom()
{
    fd = open(COM2, O_RDWR ); //| O_NONBLOCK);//
        if (fd <0) {
                perror(COM2);
                exit(-1);
        }

        tcgetattr(fd,&oldtio); /* save current modem settings */
        bzero(&newtio, sizeof(newtio));

    //	newtio.c_cflag = oldstdtio.c_cflag;
    //	newtio.c_iflag = oldstdtio.c_iflag;
    //	newtio.c_oflag = oldstdtio.c_oflag;
    // 	newtio.c_lflag = oldstdtio.c_lflag;

        newtio.c_cflag = BAUDRATE | /*CRTSCTS |*/ CS8 | CLOCAL | CREAD ;
        newtio.c_iflag = IGNPAR | ICRNL;
        newtio.c_oflag = 0;
        newtio.c_lflag = 0;

         newtio.c_cc[VINTR]    = 0;     /* Ctrl-c */
         newtio.c_cc[VQUIT]    = 0;     /* Ctrl-\ */
         newtio.c_cc[VERASE]   = 0;     /* del */
         newtio.c_cc[VKILL]    = 0;     /* @ */
         newtio.c_cc[VEOF]     = 4;     /* Ctrl-d */
         newtio.c_cc[VTIME]    = 0;
         newtio.c_cc[VMIN]     = 1;
         newtio.c_cc[VSWTC]    = 0;     /* '\0' */
         newtio.c_cc[VSTART]   = 0;     /* Ctrl-q */
         newtio.c_cc[VSTOP]    = 0;     /* Ctrl-s */
         newtio.c_cc[VSUSP]    = 0;     /* Ctrl-z */
         newtio.c_cc[VEOL]     = 0;     /* '\0' */
         newtio.c_cc[VREPRINT] = 0;     /* Ctrl-r */
         newtio.c_cc[VDISCARD] = 0;     /* Ctrl-u */
         newtio.c_cc[VWERASE]  = 0;     /* Ctrl-w */
         newtio.c_cc[VLNEXT]   = 0;     /* Ctrl-v */
         newtio.c_cc[VEOL2]    = 0;     /* '\0' */


    //	newtio.c_lflag  &= ~(ICANON | ECHO | ECHOE | ISIG);  /*Input*/
    //	newtio.c_oflag  &= ~OPOST;   /*Output*/
        tcflush(fd, TCIFLUSH);
        tcsetattr(fd,TCSANOW,&newtio);/*set attrib	  */

    #if 0
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
        newtio.c_iflag = IGNPAR; /*input flag*/
        newtio.c_oflag = 0;		/*output flag*/
        newtio.c_lflag = 0;
        newtio.c_cc[VMIN]=1;
        newtio.c_cc[VTIME]=0;
    //#else
        newtio.c_cflag = BAUDRATE | CRTSCTS | CS8 | CLOCAL | CREAD;/*ctrol flag*/
    //	newtio.c_iflag = IGNPAR; /*input flag*/
        newtio.c_iflag &= ~(ICRNL|IGNCR | INLCR |IGNBRK |BRKINT ); //input flag
        newtio.c_oflag &= ~OPOST;		/*output flag*/
        newtio.c_lflag = ECHO |NOFLSH;
        newtio.c_cc[VMIN]=1;
        newtio.c_cc[VTIME]=0;
    #endif


    /* now clean the modem line and activate the settings for modem */
    // 	tcflush(fd, TCIFLUSH);
    //	tcsetattr(fd,TCSANOW,&newtio);/*set attrib	  */
    //	signal(SIGTERM,do_exit);
    //	signal(SIGQUIT,do_exit);
    //	signal(SIGINT,do_exit);
        com_state=  OPEN;
        return 0;
}

bool SerialService::closeCom()
{
    tcsetattr(fd,TCSANOW,&oldtio);	 	/* restore old modem setings */
    close(fd);
    com_state=CLOSE;
    return true;
}

void SerialService::releaseSerial()
{
    closeCom();
}

QTimer* SerialService::getTimer()
{
    return read_timer;
}
