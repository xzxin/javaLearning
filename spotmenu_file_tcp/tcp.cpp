
#include "tcp.h"
#include "stdlib.h"
#include "stdio.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>
#include <QTextCodec>
#include <QString>
#include <QDir>
#include "spotmenu.h"
//extern    HandleClient_Thread *handleclient_thread;
extern QString Connect_Status;
extern int Normal_or_Instant_or_AC;
extern QByteArray SpotStatus,R_all,L_all,I_all,Instant_para;
extern int realtime_update_labview;
extern QString FILE_BASEPATH;
extern int control_mode;
extern void get_ethernetdata();
void HandleClient_Thread::readData()
{
    QByteArray block,Message;
     QString base_path=FILE_BASEPATH;//"/media/usb-sda1/spot/";
    char *receivebuf;
    int rcv_length;
    block=tcp_socket->readAll();
    rcv_length=block.length();
    receivebuf=block.data();
    if (block[0]==0x55 && block[1]==0xAA)
    {
        if (block[2]==0x00 && block[3]==0x00)
        {
            lookup_spotfile_day(base_path);
        }
        else if (block[2]==0x00 && block[3]==0x01)
        {
            block.remove(0,4);
            QString base_day_path=FILE_BASEPATH;//"/media/usb-sda1/spot/";
             qDebug()<<"block="<<block;
            // printf("block_len=%d\n",block.length());
            // printf("block[8]=%d\n",block[7]);
            base_day_path.append(block);
            qDebug()<<"path="<<base_day_path;
            lookup_spotfile_car(base_day_path);
        }
        else if (block[2]==0x00 && block[3]==0x02)
        {
            block.remove(0,4);
            QString base_day_car_path=FILE_BASEPATH;//"/media/usb-sda1/spot/";
             qDebug()<<"block="<<block;
            base_day_car_path.append(block);
            qDebug()<<"path="<<base_day_car_path;
            lookup_spotfile_spot(base_day_car_path);
        }
        else if (block[2]==0x00 && block[3]==0x03)
        {
            block.remove(0,4);
            QString file_path=FILE_BASEPATH;//"/media/usb-sda1/spot/";
            file_path.append(block);
             qDebug()<<block;
            //qDebug()<<file_path;
            lookup_spotfile_curve(file_path);
        }
        else if (block[2]==0x00 && block[3]==0x08)//change memeory location USB
        {
            if (control_mode==0||control_mode==2){
                FILE_BASEPATH="/media/usb-sda1/spot/";
            }
        }
        else if (block[2]==0x00 && block[3]==0x09)//change memeory location SD
        {
            if (control_mode==0||control_mode==2){
                FILE_BASEPATH="/media/sd-mmcblk0p1/spot";
            }
        }
        else if (block[2]==0x00 && block[3]==0x0A)//if data realtime update
        {
             if (realtime_update_labview==0){
                 realtime_update_labview=1;
             }
             else{
                 realtime_update_labview=0;
             }
        }
    }
    //printf("length=%");
    for (int i=0;i<rcv_length;i++)
    {
     //   printf("%02x ",receivebuf[i]);
    }

}
void HandleClient_Thread::handleDisconnect()
{
    realtime_update_labview=0;
    Connect_Status = "Disconnected!";
    emit showConnect_Status();
    qDebug()<<"Disconnected!";
    tcp_socket->disconnectFromHost();
    tcp_socket->deleteLater();
    this->quit();
    this->wait();
    delete this;
   // delete handleclient_thread;
   // handleclient_thread->wait();
}
void HandleClient_Thread::get_signalRealTime_update()
{
    qDebug()<<"ready send"<<"realtime_update="<<realtime_update_labview;
    if (realtime_update_labview&&Connect_Status!="Disconnected!"&&tcp_socket->isOpen()&&tcp_socket->isWritable()&&tcp_socket->isValid())
    {
        if (Normal_or_Instant_or_AC==0)
        {
            get_ethernetdata();
            tcp_socket->write(SpotStatus);
            // qDebug()<<"SpotStatus="<<SpotStatus.toHex();
             tcp_socket->write(I_all);
             // qDebug()<<"I_all="<<I_all[100];
              tcp_socket->write(R_all);
            // qDebug()<<"R_all="<<R_all[100];
              tcp_socket->write(L_all);
            // qDebug()<<"L_all="<<L_all[100];
         }
        else
        {
            Instant_para.append("\r\n");
            tcp_socket->write(SpotStatus);
            tcp_socket->write(Instant_para);
        }
    }
}
void HandleClient_Thread::run()
{
    char *cIP_str;
    char send_data[10]={1,2,3,4,5,6,7,8,9,10};
    QTcpSocket *new_socket = new QTcpSocket(this);
    tcp_socket = new_socket;
    tcp_socket->open(QIODevice::ReadWrite);
    if (!tcp_socket->setSocketDescriptor(SocketDescriptor))
         {qDebug()<<"socket error";return;}

    tcp_socket->waitForConnected(30000);
   // connect(tcp_socket,SIGNAL(readyRead()),handleclient_thread,SLOT(readData()),Qt::UniqueConnection);
     connect(tcp_socket,SIGNAL(readyRead()),this,SLOT(readData()));
    connect(tcp_socket,SIGNAL(disconnected()),this,SLOT(handleDisconnect()));
    address = tcp_socket->peerAddress();
    client_IP = "Connected:\n";
    //client_IP.append(address.toString());
    Connect_Status=client_IP;
    emit showConnect_Status();
    cIP_str=client_IP.toLatin1().data();
    printf("%s\n",cIP_str);
    qDebug()<<"write successfully!";
    exec();
}
void HandleClient_Thread::lookup_spotfile_day(QString base_path)
{
    QDir dir(base_path);
    QStringList days;
    QString day;
    QByteArray block;
    block.clear();
    qDebug()<<"In lookup day";
    foreach(QFileInfo mfi,dir.entryInfoList())
    {
            if (mfi.fileName()=="."||mfi.fileName()=="..") continue;
            day = mfi.absoluteFilePath();
            day=  day.right(strlen("17-03-21"));
             days+=  day;
             block.append(day);
             block.append("\r\n");
    }
    block.append("\r\n");
    tcp_socket->write(block);
    qDebug()<<block;
}
void HandleClient_Thread::lookup_spotfile_car(QString base_day_path)
{
    QDir dir(base_day_path);
    QStringList cars;
    QString car;
    QByteArray block;
    block.clear();
    qDebug()<<"In lookup car";
    foreach(QFileInfo mfi,dir.entryInfoList())
    {
        if (mfi.fileName()=="."||mfi.fileName()=="..") continue;
        car = mfi.absoluteFilePath();
        car=  car.section("\/",5,5);
         cars+=  car;
         block.append(car);
         block.append("\r\n");
    }
    block.append("\r\n");
    tcp_socket->write(block);
    qDebug()<<block;
}
void HandleClient_Thread::lookup_spotfile_spot(QString base_day_car_path)
{
    QDir dir(base_day_car_path);
    QStringList spots;
    QString spot;
    QByteArray block;
    block.clear();
    qDebug()<<"In lookup spot";
    foreach(QFileInfo mfi,dir.entryInfoList())
    {
        if (mfi.fileName()=="."||mfi.fileName()=="..") continue;
        spot = mfi.absoluteFilePath();
        spot=  spot.section("\/",6,6);
         spots+=  spot;
         block.append(spot);
         block.append("\r\n");
    }
    block.append("\r\n");
    tcp_socket->write(block);
    qDebug()<<block;
}
void HandleClient_Thread::lookup_spotfile_curve(QString file_path)
{
    //QString file_path="/media/usb-sda1/spot/17-03-15/CAR_50/Spot_99.txt";
    QStringList lines;
    QByteArray block;
    block.clear();
    QFile file(file_path.toLatin1().data());
    qDebug()<<"In lookup curve";
    if (file.open(QIODevice::ReadOnly))
    {
        QTextStream stream(&file);
        QString line;
        int n=1;
        while(!stream.atEnd())
        {
            line=stream.readLine();
            block.append(line);
            block.append(QString("\r\n"));
            //printf("%3d:%s\n",n++,line.toLatin1().data());
            lines+=line;
        }
        block.append(QString("\r\n"));
        tcp_socket->write(block);
        tcp_socket->flush();
        file.close();
    }
}


