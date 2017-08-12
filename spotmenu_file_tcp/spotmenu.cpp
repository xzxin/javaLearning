#include <QtGui>
#include <QTime>
#include <QDir>
#include <QString>
#include <QMutex>
#include <QWaitCondition>
#include <QFileDialog>
#include <QMessageBox>
#include "ui_spotmenu.h"
#include "filewrite.h"
#include "spotmenu.h"
#include "usartrcv.h"
extern spotmenu *mainwindow;
void Calc_MAX_MIN();
QWaitCondition CalcCond,aftCalcCond;
QString FILE_BASEPATH;
UsartThread *usartthread;
GPIOThread *gpiothread;
QMutex CalcMutex,aftCalcMutex;
QString Connect_Status;
int fd_file,fd_usart,fd_readfile;
char buf_usart[4];
extern unsigned char buf_weldpara[SIZE_WELDBUFF*30];
extern unsigned char buf_AC[40*80],buf_theta[1200];
extern unsigned char buf_weldpara_Instant[SIZE_WELDBUFF*SIZE_INSTANT_LEN*2];
extern unsigned char buf_spotinfo[30];
extern struct spi_ioc_transfer tr_txrx[7];
extern int fd_spi;
QVector<int> FstU;
QVector<int> FstI;
QVector<int> FstDeltaI;
QVector<int> FstDeltaT;
QVector<int> HafU;
QVector<int> HafI;
QVector<int> HafDeltaI;
QVector<int> HafDeltaT;
QVector<double> Avg_U;
QVector<double> Avg_I;
QVector<double> WeldTime;
QVector<int> HafCycCount;
QVector<double> Power;
QVector<double> Heat_Input;
QVector<int> duty_num;
QVector<int> flag_1;
QVector<int> flag_2;
///media/sd-mmcblk0p1/
QVector<double> R;
QVector<double> R_Avg;
QVector<double> L;
QVector <int> Instant_value;
QVector <int> Instant_Curr;
QVector <int> Instant_Volt;
QVector <int> I_AC,U_AC,UP_AC,fire_fai,conduct_theta,Data_Index;
int write_end_AC;
double R_temp,L_temp;
double heat_input;
double power;
int rcvSPIdata_len;
int halfcyccount,weldtime,duty;
int temp_halfcyccount;
double maxR,minR,maxL,minL,maxI,minI,maxI_AC,minI_AC;
int maxInstant,minInstant;
double AvgI,AvgII;
int last_rcv=0;
char Avg_ok=0;
int data_index;
int CarType,CarNum,GroupNum,ProcessType,SpotNum,VoltRatio,CurRatio;
int Volt_base,Cur_base;
int Normal_or_Instant_or_AC,Instant_mode=0,Instant_halfcycCnt;
int PlotCurve;
int Length;
int NeedCalcDetail;
int file_location;//默认值：usb
int realtime_update_labview;//默认值：本机上传
int control_mode;//模式0 默认模式 当本机联网时，存储位置和是否上传由上位机设置；不联网时，由本机设置;
double total_weldtime;
int fd_calc;
int oversample;
//模式1 可配置模式 所有指令由本机控制 模式2 所有指令由上位机控制
QByteArray SpotStatus,R_all,L_all,I_all,Instant_para;
void get_ethernetdata();

spotmenu::spotmenu(QWidget *parent):
    QMainWindow(parent),
    ui(new Ui::spotmenu)
{
    ui->setupUi(this);
    FILE_BASEPATH="/media/sd-mmcblk0p1/spot/";//"/media/usb-sda1/spot/";
    timer = new QTimer;
    realtime_update_labview=0;
    PlotCurve=0;
    Normal_or_Instant_or_AC=0;
    control_mode=0;//auto mode
    usartthread= new UsartThread;
    calcthread = new CalcThread;
    filethread = new FileThread;
  // gpiothread = new GPIOThread;
   // io_init();
    printf("Inital Started!\n");
    spi_init();
    fd_usart=usart_init();
    tcp_server = new MyTcpServer(this);
    printf("TCP server is on\n");
    tcp_server->listen(QHostAddress::Any,8000);
    timer->start(1000);
    connect(usartthread,SIGNAL(signalSPI()),this,SLOT(get_signalSPI()));
    connect(usartthread,SIGNAL(signalWelding()),this,SLOT(get_signalWelding()));
    connect(timer,SIGNAL(timeout()),this,SLOT(get_signalTimer()));
    //connect(calcthread,SIGNAL(signalPlot()),this,SLOT(get_signalPlot()));
    connect(usartthread,SIGNAL(signalFinishWelding()),this,SLOT(get_signalFinishWelding()));
    connect(tcp_server,SIGNAL(newConnection(int)),this,SLOT(get_signalCreateTcpThread(int)));


   // connect(gpiothread,SIGNAL(signalGPIO()),this,SLOT(get_signalGPIO()));
    printf("Inital finished!\n");
    usartthread->start();
   // calcthread->start();
  filethread->start();
}
void spotmenu::get_signalTimer()
{
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    ui->CurrTime->setText(dt.toString("yy-MM-dd_hh:mm:ss"));
}
UsartThread::UsartThread(QObject *parent):
    QThread(parent)
{

}
void UsartThread::run()
{
    char res;
    int res1;
    while (1)
    {

        res =  read(fd_usart,buf_usart,4);
        if (res>=4)
        {
            if (buf_usart[0]==0x55&&buf_usart[1]==0xAA)
            {
                if (buf_usart[2]==0x00&&buf_usart[3]==0x01)
                {
                    ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                    Normal_or_Instant_or_AC=0;
                    emit signalWelding();
                }
               //  write(fd_usart,buf_usart,4);
              //  ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                 else if (buf_usart[2]==0x00&&buf_usart[3]==0xFF)
                {
                    res1=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[5]);
                    qDebug()<<"normal_spircv"<<res1;
                    Normal_or_Instant_or_AC=0;
                    emit signalSPI();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0xFE)
                {
                    Normal_or_Instant_or_AC=0;
                     emit signalFinishWelding();
                }
               else if (buf_usart[2]==0x00&&buf_usart[3]==0x04)//电流实时上传开始
                {
                    ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                    Normal_or_Instant_or_AC=1;
                    Instant_mode=0;
                     emit signalWelding();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x05)//电压实时上传开始
                 {
                     ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                     Normal_or_Instant_or_AC=1;
                     Instant_mode=1;
                      emit signalWelding();
                 }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x06)//电流电压同时实时上传开始
                 {
                     ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                     Normal_or_Instant_or_AC=1;
                     Instant_mode=2;
                      emit signalWelding();
                 }
                 else if (buf_usart[2]==0x00&&buf_usart[3]==0x07)//电流实时上传数据包
                {
                    res1=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[3]);
                    qDebug()<<"instant_spircv"<<res1;
                    Normal_or_Instant_or_AC=1;
                    Instant_mode=0;
                    emit signalSPI();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x08)//电压实时上传数据包
               {
                   res1=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[3]);
                   qDebug()<<"instant_spircv"<<res1;
                   Normal_or_Instant_or_AC=1;
                   Instant_mode=1;
                   emit signalSPI();
               }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x09)//电流电压实时上传数据包
               {
                   res1=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[3]);
                   qDebug()<<"instant_spircv"<<res1;
                   Normal_or_Instant_or_AC=1;
                   Instant_mode=2;
                   emit signalSPI();
               }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x0A)
                {
                       Normal_or_Instant_or_AC=1;

                     emit signalFinishWelding();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x0B)
                {
                       Normal_or_Instant_or_AC=2;
                       qDebug("AC_start");
                       ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);
                       emit signalWelding();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x0C)
                {
                       Normal_or_Instant_or_AC=2;
                       res1=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[6]);
                       qDebug()<<"AC_spircv"<<res1;
                       emit signalSPI();
                }
                else if (buf_usart[2]==0x00&&buf_usart[3]==0x0D)
                {
                       Normal_or_Instant_or_AC=2;
                     emit signalFinishWelding();
                }
             }
            buf_usart[0]=0;
        }
        //usleep(20);
    }
}
CalcThread::CalcThread(QObject *parent):
    QThread(parent)
{

}
void Calc_MAX_MIN()
{
        if (R_temp>maxR && R_temp<5) maxR=R_temp;
        if (R_temp<minR && R_temp>0.05) minR=R_temp;
        if (L_temp>maxL && L_temp<10) maxL=L_temp;
        if (L_temp<minL && L_temp>0.2) minL=L_temp;

        if (AvgII>maxI) maxI=AvgII;
        if (AvgII<minI) minI=AvgII;
        if (abs(AvgI-AvgII)<0.02) Avg_ok=1;
        if (!Avg_ok) AvgI=AvgII;
}

void CalcThread::run()
{
    QString temp;
    while (1)
    {
    CalcMutex.lock();
    CalcCond.wait(&CalcMutex);
//HafDeltaI is a negative num. this equality consider this situation
    qDebug()<<"in clac thread";
    for (int i=last_rcv;i<(last_rcv+rcvSPIdata_len);i++)
    {
        base=double(FstI[i]*FstDeltaT[i]*HafDeltaI[i]+HafI[i]*HafDeltaT[i]*FstDeltaI[i])/1e3/VoltRatio/CurRatio;
        R_temp=((HafU[i]*HafDeltaT[i]*FstDeltaI[i]+FstU[i]*FstDeltaT[i]*HafDeltaI[i])/base/1e3/VoltRatio/CurRatio);
        L_temp=(double(FstU[i]*HafI[i]-HafU[i]*FstI[i])*FstDeltaT[i]*HafDeltaT[i]/base/1e6/VoltRatio/CurRatio);
        R.append(R_temp);
        L.append(L_temp);
        /*
        temp = QString::number(R[i],10,4);
        temp=temp.left(6);
        R_all.append(temp);//left 6 digits
        temp = QString::number(L[i],10,4);
        temp=temp.left(6);
        L_all.append(temp);
        temp = QString::number(double(Avg_I[i])/1000,10,4);
        temp=temp.left(6);
        I_all.append(temp);*/
        AvgII=Avg_I[i];
       // halfcyccount=i;
        Calc_MAX_MIN();
        //emit signalPlot();
    }
    CalcMutex.unlock();

    }
}
FileThread::FileThread(QObject *parent):
    QThread(parent)
{

}
void FileThread::run()
{
    while (1)
    {
        aftCalcMutex.lock();
        aftCalcCond.wait(&aftCalcMutex);
        temp_halfcyccount=halfcyccount;
        file_write(fd_file);
       // close(fd_file);
        if (NeedCalcDetail&&Normal_or_Instant_or_AC==0)
        {
            calc_detail_write(fd_calc);
            close(fd_calc);
        }
        aftCalcMutex.unlock();
    }
}
GPIOThread::GPIOThread(QObject *parent):
    QThread(parent)
{

}
void GPIOThread::run()
{

}

void spotmenu::get_signalGPIO()
{

}
void spotmenu::get_signalSPI()
{
    QString temp;
    double base;
    int temp_value,temp_hafcyc;
    int temp_value1,temp_value2,temp_value3;
    double temp_value_double;
    qDebug()<<"in spi slot";
    //int res=ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[5]);
   // qDebug()<<"res="<<res;
    if (Normal_or_Instant_or_AC==0)
    {
        rcvSPIdata_len=SIZE_WELDBUFF;
         for (int i=0;i<SIZE_WELDBUFF;i++)
         {
             if ((256*buf_weldpara[24+i*30]+buf_weldpara[25+i*30])==0)
              {
                   rcvSPIdata_len=i;
                   break;
              }
            FstU.append((256*buf_weldpara[0+i*30]+buf_weldpara[1+i*30]-Volt_base));//oversample
            FstI.append((256*buf_weldpara[2+i*30]+buf_weldpara[3+i*30]-Cur_base));//oversample
            FstDeltaI.append(256*buf_weldpara[4+i*30]+buf_weldpara[5+i*30]);
            FstDeltaT.append(256*buf_weldpara[6+i*30]+buf_weldpara[7+i*30]);
            HafU.append((256*buf_weldpara[8+i*30]+buf_weldpara[9+i*30]-Volt_base));//oversample
            HafI.append((256*buf_weldpara[10+i*30]+buf_weldpara[11+i*30]-Cur_base));//oversample
            HafDeltaI.append(256*buf_weldpara[12+i*30]+buf_weldpara[13+i*30]);
            HafDeltaT.append( 256*buf_weldpara[14+i*30]+buf_weldpara[15+i*30]);
            Avg_U.append(double(256*buf_weldpara[16+i*30]+buf_weldpara[17+i*30]-Volt_base)/VoltRatio);//单位 换算到V
            Avg_I.append(double(256*buf_weldpara[18+i*30]+buf_weldpara[19+i*30]-Cur_base)/CurRatio);//单位 A 单位换算到KA
            total_weldtime+=(double)(256*buf_weldpara[20+i*30]+buf_weldpara[21+i*30])/100;//10us为单位，换算到毫秒
            WeldTime.append(total_weldtime);
            HafCycCount.append(256*buf_weldpara[22+i*30]+buf_weldpara[23+i*30]);
            duty_num.append(256*buf_weldpara[24+i*30]+buf_weldpara[25+i*30]);
           // flag_1.append(256*buf_weldpara[26+i*30]+buf_weldpara[27+i*30]);
           // flag_2.append(256*buf_weldpara[28+i*30]+buf_weldpara[29+i*30]);

         }


             memset(buf_weldpara,0,sizeof(buf_weldpara));
            qDebug()<<"rcvSPIdata_len="<<rcvSPIdata_len;

            //CalcCond.wakeOne();
             for (int i=last_rcv;i<(last_rcv+rcvSPIdata_len);i++)
                 {
                 //除以ratio之后 U化为V I化为KA 时间化为ms 计算得到毫欧和微亨
                     base=double((double)FstI[i]*FstDeltaT[i]/2.0*HafDeltaI[i]+(double)HafI[i]*HafDeltaT[i]/2.0*FstDeltaI[i])/1e3/CurRatio/CurRatio;
                    R_temp=(((double)HafU[i]*HafDeltaT[i]/2*FstDeltaI[i]+(double)FstU[i]*FstDeltaT[i]/2.0*HafDeltaI[i])/base/1e3/VoltRatio/CurRatio);
                    L_temp=(((double)FstU[i]*HafI[i]-(double)HafU[i]*FstI[i])*FstDeltaT[i]/2.0*HafDeltaT[i]/2/base/1e6/VoltRatio/CurRatio);
                //

                     R.append(R_temp);
                     L.append(L_temp);
                    R_Avg.append(Avg_U[i]/Avg_I[i]);
                    power=Avg_U[i]*Avg_I[i];
                    Power.append(power);
                    heat_input+=power*0.5;
                    Heat_Input.append(heat_input);
                    AvgII=Avg_I[i];
                    halfcyccount=i;
                     Calc_MAX_MIN();

                }
             last_rcv+=rcvSPIdata_len;
         //emit signalPlot();
       }
    /*for (int i=0;i<24;i++)
    {
        printf("%d ",buf_weldpara[i]);
    }
    printf("\n");*/

    else if (Normal_or_Instant_or_AC==1)
        {
        if (Instant_mode==0)
        {
            for (int i=0;i<SIZE_WELDBUFF;i++)
            {
                for (int j=0;j<SIZE_INSTANT_LEN;j++)
                {
                    temp_value=256*buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j]+buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j+1];
                    if (temp_value==0)
                    {
                        break;
                    }

                    //Instant_halfcycCnt++;
                    Instant_Curr.append(temp_value-Cur_base);
                }
                Instant_halfcycCnt++;
                HafCycCount.append(Instant_halfcycCnt);
                if (temp_value==0)
                {
                    break;
                }
            }
           // qDebug()<<Instant_Curr;

             /*
            for (int i=0;i<SIZE_WELDBUFF*SIZE_INSTANT_LEN/2;i++)
             {
              temp_value=256*buf_weldpara_Instant[2*i]+buf_weldpara_Instant[2*i+1];
                Instant_value.append(temp_value);
                if (temp_value>maxInstant) maxInstant=temp_value;
                if (temp_value<minInstant) minInstant=temp_value;
                int count=Instant_para.size();
                Instant_para[count]=buf_weldpara_Instant[2*i];
                Instant_para[count+1]=buf_weldpara_Instant[2*i+1];
             }*/
        }
        else if (Instant_mode==1)
        {
            for (int i=0;i<SIZE_WELDBUFF;i++)
            {
                for (int j=0;j<SIZE_INSTANT_LEN;j++)
                {
                    temp_value=256*buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j]+buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j+1];
                    if (temp_value==0)
                    {
                        break;
                    }

                    //Instant_halfcycCnt++;
                    Instant_Volt.append(temp_value-Volt_base);
                }
                Instant_halfcycCnt++;
                HafCycCount.append(Instant_halfcycCnt);
                if (temp_value==0)
                {
                    break;
                }
            }
        }
        else if (Instant_mode==2)
        {
            for (int i=0;i<SIZE_WELDBUFF;i++)
            {
                for (int j=0;j<SIZE_INSTANT_LEN/2;j++)
                {
                    temp_value=256*buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j]+buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j+1];
                    if (temp_value==0)
                    {
                        qDebug()<<"0 in Curr";
                        break;
                    }
                    Instant_Curr.append(temp_value-Cur_base);
                }
                for (int j=SIZE_INSTANT_LEN/2;j<SIZE_INSTANT_LEN;j++)
                {
                    temp_value=256*buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j]+buf_weldpara_Instant[2*i*SIZE_INSTANT_LEN+2*j+1];
                    if (temp_value==0)
                    {
                         qDebug()<<"0 in Volt";
                        break;
                    }
                    Instant_Volt.append(temp_value-Volt_base);
                }
                Instant_halfcycCnt++;
                HafCycCount.append(Instant_halfcycCnt);
                if (temp_value==0)
                {
                    break;
                }
            }
        }
           // qDebug()<<"instant_value="<<Instant_para;
        aftCalcCond.wakeOne();
         }

    else //Normal_or_Instant_or_AC=2
    {
            halfcyccount+=2;
            for (int i=0;i<266;i++)//1600下被6整除的树
            {
                    temp_value1=256*buf_AC[6*i]+buf_AC[6*i+1];
                    temp_value2=256*buf_AC[6*i+2]+buf_AC[6*i+3];
                    temp_value3=256*buf_AC[6*i+4]+buf_AC[6*i+5];

                    if (temp_value1==0&&temp_value2==0&&temp_value3==0)
                    {
                        data_index+=i;
                            break;
                    }

                    //temp_value_double=double(temp_value1-Cur_base)/CurRatio;
                    I_AC.append(temp_value1);
                    //temp_value_double=double(temp_value2-Volt_base)/VoltRatio;
                    U_AC.append(temp_value2);
                    //temp_value_double=double(temp_value3-Volt_base)/VoltRatio;
                    UP_AC.append(temp_value3);
             }

           // Data_Index.append(data_index);
            for (int i=0;i<266;i++)//1600下被6整除的树
            {
                    temp_value1=256*buf_AC[6*i+1600]+buf_AC[6*i+1+1600];
                    temp_value2=256*buf_AC[6*i+2+1600]+buf_AC[6*i+3+1600];
                    temp_value3=256*buf_AC[6*i+4+1600]+buf_AC[6*i+5+1600];

                    if (temp_value1==0&&temp_value2==0&&temp_value3==0)
                    {
                        data_index+=i;
                            break;
                    }

                    //temp_value_double=double(temp_value1-Cur_base)/CurRatio;
                    I_AC.append(temp_value1);
                    //temp_value_double=double(temp_value2-Volt_base)/VoltRatio;
                    U_AC.append(temp_value2);
                    //temp_value_double=double(temp_value3-Volt_base)/VoltRatio;
                    UP_AC.append(temp_value3);
             }
             //Data_Index.append();
            write_end_AC=0;
           // temp_halfcyccount=halfcyccount;
            qDebug()<<"I_AC_SIZE="<<I_AC.size()<<"  I_AC_CAPACITY="<<I_AC.capacity();
            Data_Index.append(data_index);
          // qDebug()<<I_AC;
            //file_write(fd_file);
           // aftCalcCond.wakeOne();
        }
}
void spotmenu::get_signalPlot()
{

  //  ui->res_plot->graph(0)->addData(halfcyccount,R);
  //  ui->L_plot->graph(0)->addData(halfcyccount,L);
  //  ui->curr_plot->graph(0)->addData(halfcyccount,(double)AvgII/1000);

}
void spotmenu::get_signalFinishWelding()
{
    int temp_value_int;
    double temp_value;
    showWeldStatus();
    Length=FstU.size();
    if (Normal_or_Instant_or_AC==0)
    {
        qDebug()<<"length="<<Length;
        //file_curve_init();
        aftCalcCond.wakeOne();
      //  halfcyccount=R.size();on_actionReadHistory_triggered
       // weldtime=WeldTime[Length-1];
        duty=duty_num[Length-1];
        showWeldPara();
       // qDebug()<<"FstU="<<FstU;
       // qDebug()<<"FstI="<<FstI;
       // qDebug()<<"FstDeltaI="<<FstDeltaI;
       // qDebug()<<"FstDeltaT="<<FstDeltaT;
       // qDebug()<<"HafU="<<HafU;
       // qDebug()<<"HafI="<<HafI;
       // qDebug()<<"HafDeltaI="<<HafDeltaI;
       // qDebug()<<"HafDeltaT="<<HafDeltaT;
    }
    else if (Normal_or_Instant_or_AC==1)
    {
        qDebug()<<"length="<<Instant_Curr.size();
    }
    else if (Normal_or_Instant_or_AC==2)
    {
        //qDebug()<<"length="<<Instant_Curr.size();
        ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[2]);
        qDebug()<<Data_Index;
        for (int i=0;i<1200/4;i++)
        {
           temp_value_int=256*buf_theta[4*i]+buf_theta[4*i+1];
           if (temp_value_int==0)
                        break;
           temp_value=double(temp_value_int)/1000/10*180;
           fire_fai.append(temp_value);
           temp_value=256*buf_theta[4*i+2]+buf_theta[4*i+3];
            temp_value=double(temp_value)/1000/10*180;
           conduct_theta.append(temp_value);
        }
        for (int i=0;i<100;i++)
        {
            for (int j=0;j<12;j++)
            {
               // printf("%x ",buf_theta[i*12+j]);
            }
           // printf("\n");
        }

        write_end_AC=1;
        //aftCalcCond.wakeOne();
        file_write(fd_file);
        //close(fd_file);

        showWeldPara();
    }
    emit signalRealTime_update();
   // get_plotdata();
   // plot_Curve();
}
void spotmenu::file_curve_init(void)
{
    QString path,temp,path_calc;
    QDir dir;
    char *path_str,*path_calc_str,*time_str;
    qDebug()<<"show spot status";
    path=FILE_BASEPATH;
   // path="/media/usb-sda1/spot/";
    path.append(dt.toString("yy-MM-dd"));
    path.append("/CAR_");
    temp=QString::number(CarNum);
    path.append(temp);
    dir.mkpath(path);
    path.append("/Spot_");
    temp=QString::number(SpotNum);
    path.append(temp);
    path_calc=path;
    path_calc.append("calc.txt");
    path.append(".txt");
    QByteArray ba=path.toLatin1();
    path_str=ba.data();
    path_calc_str=path_calc.toLatin1().data();
    dt.setTime(time.currentTime());
    dt.setDate(date.currentDate());
    ba=dt.toString("yy-MM-dd_hh:mm:ss").toLatin1();
    time_str=ba.data();
    if (Normal_or_Instant_or_AC==0)
    {
        NeedCalcDetail=0;
    }
    else
    {
        NeedCalcDetail=0;
    }
    fd_file=file_init(path_str,path_calc_str,time_str);


    qDebug()<<"file init";
/*
    ui->res_plot->clearGraphs();
    ui->L_plot->clearGraphs();
    ui->curr_plot->clearGraphs();
    ui->res_plot->addGraph();
    ui->L_plot->addGraph();
    ui->curr_plot->addGraph();
*/
}
void spotmenu::showWeldPara()
{
    QString temp;
    double temp_double;
    temp_double=AvgI;
    temp=QString::number(temp_double,'g',3);
    temp.append("kA");
    ui->value_curr->setText(temp);
    temp=QString::number(duty/10);
    temp.append("%");
    ui->value_ratio->setText(temp);
    temp=QString::number(total_weldtime,'f',0);
    //temp=QString::number(weldtime/10);
    temp.append("ms");
    ui->value_time->setText(temp);
    temp=QString::number(heat_input,'f',0);
    //temp=QString::number(weldtime/10);
    temp.append("J");
    ui->value_heat->setText(temp);
}
void spotmenu::plot_Curve()
{
    qDebug()<<"halfcyccount="<<halfcyccount;
    ui->res_plot->xAxis->setRange(0,total_weldtime);//weldtime)
    ui->res_plot->yAxis->setRange(minR-0.1*(maxR-minR),maxR+0.1*(maxR-minR));
   // ui->res_plot->yAxis->setRange(0,0.5);
    ui->L_plot->xAxis->setRange(0,total_weldtime);
    ui->L_plot->yAxis->setRange(minL-0.1*(maxL-minL),maxL+0.1*(maxL-minL));
  //  ui->L_plot->yAxis->setRange(0.5,5.5);
    ui->curr_plot->xAxis->setRange(0,total_weldtime);
    ui->curr_plot->yAxis->setRange(minI-0.1*(maxI-minI),maxI+0.1*(maxI-minI));
    ui->heat_plot->xAxis->setRange(0,total_weldtime);
    ui->heat_plot->yAxis->setRange(0,heat_input);
   // ui->curr_plot->yAxis->setRange(0,5);
    ui->res_plot->replot();
    ui->L_plot->replot();
    ui->curr_plot->replot();
    ui->heat_plot->replot();

}
void spotmenu::get_signalWelding()
{
    unsigned short Instant_para_head[4]={0x55,0xAA,0x00,0x0B};
    unsigned short SpotSatus_head[4]={0x55,0xAA,0x00,0x04};
    unsigned short I_all_head[4]={0x55,0xAA,0x00,0x05};
    unsigned short R_all_head[4]={0x55,0xAA,0x00,0x06};
    unsigned short L_all_head[4]={0x55,0xAA,0x00,0x07};
    total_weldtime=0;
    maxInstant=0;
    minInstant=65535;
    maxI=0;
    minI=65535;
    maxR=0;
    minR=65535;
    maxL=0;
    minL=65535;
    Avg_ok=0;
    last_rcv=0;
    heat_input=0;
    data_index=0;
    Power.clear();
    I_AC.clear();
    U_AC.clear();
    UP_AC.clear();
    Data_Index.clear();
    Data_Index.append(0);
    Heat_Input.clear();
    Instant_halfcycCnt=0;
    Instant_value.clear();
    Instant_para.clear();
    Instant_Curr.clear();
    Instant_Volt.clear();
    qDebug()<<"FstU_Capacity="<<FstU.capacity();

    SpotStatus.clear();
    SpotStatus[0]=SpotSatus_head[0];
    SpotStatus[1]=SpotSatus_head[1];
    SpotStatus[2]=SpotSatus_head[2];
    SpotStatus[3]=SpotSatus_head[3];
    Instant_para[0]=Instant_para_head[0];
    Instant_para[1]=Instant_para_head[1];
    Instant_para[2]=Instant_para_head[2];
    Instant_para[3]=Instant_para_head[3];
    FstU.clear();
    FstI.clear();
    FstDeltaI.clear();
    FstDeltaT.clear();
    HafU.clear();
    HafI.clear();
    HafDeltaI.clear();
    HafDeltaT.clear();
    Avg_U.clear();
    Avg_I.clear();
    R_Avg.clear();
    R.clear();
    L.clear();
    WeldTime.clear();
    HafCycCount.clear();
    duty_num.clear();
    flag_1.clear();
    flag_2.clear();
    /*
    FstU.erase(FstU.begin(),FstU.end());
    FstI.erase(FstI.begin(),FstI.end());
    FstDeltaI.erase(FstDeltaI.begin(),FstDeltaI.end());
    FstDeltaT.erase(FstDeltaT.begin(),FstDeltaT.end());
    HafU.erase(HafU.begin(),HafU.end());
    HafI.erase(HafI.begin(),HafI.end());
    HafDeltaI.erase(HafDeltaI.begin(),HafDeltaI.end());
    HafDeltaT.erase(HafDeltaT.begin(),HafDeltaT.end());
    Avg_U.erase(Avg_U.begin(),Avg_U.end());
    Avg_I.erase(Avg_I.begin(),Avg_I.end());
    R.erase(R.begin(),R.end());
    L.erase(L.begin(),L.end());
    WeldTime.erase(WeldTime.begin(),WeldTime.end());
    HafCycCount.erase(HafCycCount.begin(),HafCycCount.end());*/
    qDebug()<<"FstU_Capacity="<<FstU.capacity();
     qDebug()<<"FstU_Size="<<FstU.size();
    printf("Welding slot\n");
    //ioctl(fd_spi, SPI_IOC_MESSAGE(1), &tr_txrx[4]);

    halfcyccount=0;
    R_all.clear();
    R_all[0]=R_all_head[0];
    R_all[1]=R_all_head[1];
    R_all[2]=R_all_head[2];
    R_all[3]=R_all_head[3];
    L_all.clear();
    L_all[0]=L_all_head[0];
    L_all[1]=L_all_head[1];
    L_all[2]=L_all_head[2];
    L_all[3]=L_all_head[3];
    I_all.clear();
    I_all[0]=I_all_head[0];
    I_all[1]=I_all_head[1];
    I_all[2]=I_all_head[2];
    I_all[3]=I_all_head[3];
    CarType      = 256*buf_spotinfo[0]+buf_spotinfo[1];
    CarNum       = 256*buf_spotinfo[2]+buf_spotinfo[3];
    GroupNum     = 256*buf_spotinfo[4]+buf_spotinfo[5];
    ProcessType  = 256*buf_spotinfo[6]+buf_spotinfo[7];
    SpotNum      = 256*buf_spotinfo[8]+buf_spotinfo[9];
    VoltRatio    = 256*buf_spotinfo[10]+buf_spotinfo[11];
    CurRatio     = 256*buf_spotinfo[12]+buf_spotinfo[13];
    Volt_base    = 256*buf_spotinfo[14]+buf_spotinfo[15];
    Cur_base     = 256*buf_spotinfo[16]+buf_spotinfo[17];
    oversample   = 256*buf_spotinfo[18]+buf_spotinfo[19];
    qDebug()<<"oversample="<<oversample;
    qDebug()<<"Volt_base="<<Volt_base;
    qDebug()<<"Cur_base="<<Cur_base;
    qDebug()<<"Volt_ratio="<<VoltRatio;
    qDebug()<<"Cur_base="<<CurRatio;
    SpotStatus.append(buf_spotinfo[0]);
    SpotStatus.append(buf_spotinfo[1]);
    SpotStatus.append(buf_spotinfo[2]);
    SpotStatus.append(buf_spotinfo[3]);
    SpotStatus.append(buf_spotinfo[4]);
    SpotStatus.append(buf_spotinfo[5]);
    SpotStatus.append(buf_spotinfo[6]);
    SpotStatus.append(buf_spotinfo[7]);
    SpotStatus.append(buf_spotinfo[8]);
    SpotStatus.append(buf_spotinfo[9]);
    SpotStatus.append(buf_spotinfo[10]);
    SpotStatus.append(buf_spotinfo[11]);
    SpotStatus.append(buf_spotinfo[12]);
    SpotStatus.append(buf_spotinfo[13]);
    SpotStatus.append("\r\n");
//showWeldStatus();
    memset(buf_spotinfo,0,sizeof(buf_spotinfo));
    printf("Start Welding!\n");
   // if (Normal_or_Instant_or_AC==1)
   // {
         file_curve_init();
   // }

}



void spotmenu::get_plotdata()
{
    for (int i=0;i<Length;i++)
    {
        ui->res_plot->graph(0)->addData(WeldTime[i],R[i]);
        ui->L_plot->graph(0)->addData(WeldTime[i],L[i]);
        ui->curr_plot->graph(0)->addData(WeldTime[i],Avg_I[i]);
        ui->heat_plot->graph(0)->addData(WeldTime[i],Heat_Input[i]);
       // qDebug()<<"R[i]="<<R[i];
    }
}
void get_ethernetdata()
{
    QString temp;
    for (int i=0;i<Length;i++)
    {
        temp = QString::number(R[i],10,4);
         temp=temp.left(6);
        R_all.append(temp);//left 6 digits
        temp = QString::number(L[i],10,4);
        temp=temp.left(6);
        L_all.append(temp);
        temp = QString::number(Avg_I[i],10,4);
        temp=temp.left(6);
        I_all.append(temp);
    }
    R_all.append("\r\n");
    I_all.append("\r\n");
    L_all.append("\r\n");
}
void spotmenu::plot_CurveInstant()
{
    if (Normal_or_Instant_or_AC==1)
    {
    ui->INS_plot->xAxis->setRange(0,Instant_value.size());
    ui->INS_plot->yAxis->setRange(minInstant-0.1*(maxInstant-minInstant),maxInstant+0.1*(maxInstant-minInstant));
    ui->INS_plot->replot();
    }
    else if(Normal_or_Instant_or_AC==2)
    {
        ui->curr_plot->xAxis->setRange(0,I_AC.size());
        ui->curr_plot->yAxis->setRange(minI_AC-0.1*(maxI_AC-minI_AC),maxI_AC+0.1*(maxI_AC-minI_AC));
        ui->curr_plot->replot();
    }
}
void spotmenu::get_plotdataInstant()
{
    if (Normal_or_Instant_or_AC==1)
    {
    for (int i=0;i<Instant_value.size();i++)
    {
        ui->INS_plot->graph(0)->addData(i,Instant_value[i]);
    }
    }
    else if (Normal_or_Instant_or_AC==2)
    {
        maxI_AC=0;
        minI_AC=1000000;
        for (int i=0;i<I_AC.size();i++)
        {
            if (I_AC[i]>maxI_AC) maxI_AC=I_AC[i];
            if (I_AC[i]<minI_AC) minI_AC=I_AC[i];
            ui->curr_plot->graph(0)->addData(i,I_AC[i]);
        }
        qDebug()<<"maxI_AC="<<maxI_AC;
        qDebug()<<"minI_AC="<<minI_AC;
    }
}
void spotmenu::showWeldStatus()
{
    QString temp_info;
    temp_info="CarType = ";
    temp_info.append(QString::number(CarType));
    temp_info.append("\n");
    temp_info.append("CarNum = ");
    temp_info.append(QString::number(CarNum));
    temp_info.append("\n");
    temp_info.append("GroupNum = ");
    temp_info.append(QString::number(GroupNum));
    temp_info.append("\n");
    temp_info.append("ProcessType = ");
    temp_info.append(QString::number(ProcessType));
    temp_info.append("\n");
    temp_info.append("SpotNum = ");
    temp_info.append(QString::number(SpotNum));
    temp_info.append("\n");
    temp_info.append("VoltRatio = ");
    temp_info.append(QString::number(VoltRatio));
    temp_info.append("\n");
    temp_info.append("CurRatio = ");
    temp_info.append(QString::number(CurRatio));
    temp_info.append("\n");
    ui->spotinfo->setText(temp_info);
}
void spotmenu::on_actionAuthor_triggered()
{

}

void spotmenu::get_signalShowConnect_Status()
{
    ui->connect_status->setText(Connect_Status);
}
HandleClient_Thread::HandleClient_Thread(int socketDescriptor,QObject *parent):
    QThread(parent)
{
    SocketDescriptor=socketDescriptor;
}
    MyTcpServer::MyTcpServer(QObject *parent)
{

}
void spotmenu::get_signalCreateTcpThread(int socketDescriptor)
{
    handleclient_thread = new HandleClient_Thread(socketDescriptor,this);
    connect(handleclient_thread,SIGNAL(showConnect_Status()),this,SLOT(get_signalShowConnect_Status()));
    connect(this,SIGNAL(signalRealTime_update()),handleclient_thread,SLOT(get_signalRealTime_update()));
   // HandleClient_Thread.SocketDescriptor=socketDescriptor;
    printf("received client\n");
    handleclient_thread->start();
}
void MyTcpServer::incomingConnection(int socketDescriptor)
{
   // QMessageBox::information(0,tr("attention"),tr("new connection!"));
    emit newConnection(socketDescriptor);
    /*
    handleclient_thread = new HandleClient_Thread(socketDescriptor,mainwindow);
     connect(handleclient_thread,SIGNAL(showConnect_Status()),mainwindow,SLOT(get_signalShowConnect_Status()));
     connect(mainwindow,SIGNAL(signalRealTime_update()),handleclient_thread,SLOT(get_signalRealTime_update()));
   // HandleClient_Thread.SocketDescriptor=socketDescriptor;
    printf("received client\n");
    handleclient_thread->start();*/
}

void spotmenu::on_actionReadHistory_triggered()
{
    char *path_str,read_line[300],*read_word,read_bit,weldstatus[10];
   
    int row_count=0;
    int word_count=0;
    int read_count=0;
    unsigned int i;
    QString path=QFileDialog::getOpenFileName(this,tr("open txt"),".",tr("txt files(*.txt *.txtH)"));
    if (path.length()!=0)
    {
        QMessageBox::information(NULL,tr("Path"),tr("You selected")+path);
        ui->res_plot->clearGraphs();
        ui->L_plot->clearGraphs();
        ui->curr_plot->clearGraphs();
        ui->heat_plot->clearGraphs();
        ui->res_plot->addGraph();
        ui->L_plot->addGraph();
        ui->curr_plot->addGraph();
        ui->heat_plot->addGraph();
        QByteArray ba=path.toLatin1();
        path_str=ba.data();
        printf("file=%s\n",path_str);
        fd_readfile=open(path_str,O_RDONLY,0x777);
        printf("fd_readfile=%d\n",fd_readfile);
        while (1)
        {
            if (read(fd_readfile,&read_bit,1)==0)
            {break;}

            //printf("%c ",read_bit);
            if (read_bit=='\n')
            {
                read_line[read_count]='\0';
               // printf("read_line=%s\n",read_line);

                row_count++;
                if (row_count==1||row_count==3)
                {
                    //break;
                }

                else if (row_count==2)
                {
                    read_word=strtok(read_line,",");

                    while (read_word)
                    {
                        word_count++;
                        switch (word_count)
                        {
                        case 1:
                            for (i=strlen("CAR_TYPE = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("CAR_TYPE = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("CAR_TYPE = ")]='\0';
                            CarType   = atoi(weldstatus);
                            break;
                        case 2:
                            for (i=strlen("CAR_NUM = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("CAR_NUM = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("CAR_NUM = ")]='\0';
                            CarNum  = atoi(weldstatus);
                            break;
                        case 3:
                            for (i=strlen("GROUP_NUM = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("GROUP_NUM = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("GROUP_NUM = ")]='\0';
                            GroupNum   = atoi(weldstatus);
                            break;
                        case 4:
                            for (i=strlen("PROCESS_TYPE = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("PROCESS_TYPE = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("PROCESS_TYPE = ")]='\0';
                            ProcessType   = atoi(weldstatus);
                            break;
                        case 5:
                            for (i=strlen("SPOT_NUM = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("SPOT_NUM = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("SPOT_NUM = ")]='\0';
                            SpotNum   = atoi(weldstatus);
                            break;
                        case 6:
                            for (i=strlen("VOLT_RATIO = ");i<strlen(read_word);i++)
                            {
                                weldstatus[i-strlen("VOLT_RATIO = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("VOLT_RATIO = ")]='\0';
                            VoltRatio   = atoi(weldstatus);
                            break;
                        case 7:
                            for (i=strlen("CURR_RATIO = ");i<strlen(read_word);i++)
                            {
                              weldstatus[i-strlen("CURR_RATIO = ")]=read_word[i];
                            }
                            weldstatus[i-strlen("CURR_RATIO = ")]='\0';
                            CurRatio   = atoi(weldstatus);
                            break;
                        default: break;
                        }//switch
                         memset(weldstatus,0,10);
                        read_word=strtok(NULL,",");
                    }//read
                    showWeldStatus();
                }//end row 2
                else
                {
                  //  printf("Handle row%d\n",row_count);
                    read_word=strtok(read_line," ");
                    while (read_word)
                    {
                      //  printf("%s ",read_word);
                        word_count++;
                        if (word_count==1)
                        {
                            halfcyccount=atoi(read_word);
                        }
                        if (word_count==2)
                        {
                            total_weldtime=atof(read_word);
                        }
                        if (word_count==3)//12)
                        {
                            duty=atoi(read_word);
                        }
                        if (word_count==4)//12)
                        {
                            AvgII=atof(read_word);
                        }
                        if (word_count==7)
                        {
                            heat_input=atof(read_word);
                        }
                        if (word_count==8)
                        {
                            R_temp=atof(read_word);
                        }
                        if (word_count==9)
                        {
                            L_temp=atof(read_word);
                        }
                        read_word=strtok(NULL," ");
                    }//while (read_word)
                    ui->res_plot->graph(0)->addData(total_weldtime,R_temp);
                    ui->L_plot->graph(0)->addData(total_weldtime,L_temp);
                    ui->curr_plot->graph(0)->addData(total_weldtime,AvgII);
                    ui->heat_plot->graph(0)->addData(total_weldtime,heat_input);
                    Calc_MAX_MIN();

                }//row number != 123
                 word_count=0;
                 //read_line="";
                 memset(read_line,0,300);
                 read_count=0;
            }//read_bit=='\n'
            else//not \n
            {
                read_line[read_count++]=read_bit;
            }
        }
        printf("HANDLE OK!\n");
        showWeldPara();
        plot_Curve();


    }
}
spotmenu::~spotmenu()
{

}




//void spotmenu::on_actionControl_mode_triggered()
//{

//}

//void spotmenu::on_actionMemory_location_triggered()
//{

//}


void spotmenu::on_PlotButton_clicked()
{
    PlotCurve=1;
    if(Normal_or_Instant_or_AC==0)
    {
        ui->res_plot->clearGraphs();
        ui->L_plot->clearGraphs();
        ui->curr_plot->clearGraphs();
        ui->heat_plot->clearGraphs();
        ui->res_plot->addGraph();
        ui->L_plot->addGraph();
        ui->curr_plot->addGraph();
        ui->heat_plot->addGraph();
        ui->curr_plot->xAxis->setLabel("time (ms)");
        ui->curr_plot->yAxis->setLabel("curr (kA)");
        ui->res_plot->xAxis->setLabel("time (ms)");
        ui->res_plot->yAxis->setLabel("res (miliohm)");
        ui->L_plot->xAxis->setLabel("time (ms)");
        ui->L_plot->yAxis->setLabel("L (uH)");
        ui->curr_plot->xAxis->setLabel("time (ms)");
        ui->heat_plot->yAxis->setLabel("heat (J)");

        get_plotdata();
        plot_Curve();
    }
    else if (Normal_or_Instant_or_AC==1)
    {
        ui->INS_plot->clearGraphs();
        ui->INS_plot->addGraph();
        get_plotdataInstant();
        plot_CurveInstant();
    }
    else
    {
       ui->curr_plot->clearGraphs();
       ui->curr_plot->addGraph();
       get_plotdataInstant();
       plot_CurveInstant();
    }

}

void spotmenu::on_actionAuto_triggered()
{
    control_mode=0;
}

void spotmenu::on_actionNetWork_Only_triggered()
{
    control_mode=2;
}

void spotmenu::on_actionLocal_Only_triggered()
{
    control_mode=1;
}

void spotmenu::on_actionUsb_triggered()
{
    if (control_mode==1||(control_mode==0&&Connect_Status=="Disconnected!"))
    {
        FILE_BASEPATH="/media/usb-sda1/spot/";
    }
}

void spotmenu::on_actionSD_triggered()
{
    if (control_mode==1||(control_mode==0&&Connect_Status=="Disconnected!"))
    {
        FILE_BASEPATH="/media/sd-mmcblk0p1/spot";
    }
}
