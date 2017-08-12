#ifndef SPOTMENU_H
#define SPOTMENU_H

#include <QMainWindow>
#include <QThread>
#include <QDebug>
#include <QMutex>
#include <QTime>
#include <QDate>
 #include "spi_io_qt.h"
#include <QScrollBar>
#include "tcp.h"
namespace Ui {
class spotmenu;
}
class GPIOThread : public QThread
{
    Q_OBJECT
public:
    explicit GPIOThread(QObject *parent = 0);
    void stop();
    friend class spotmenu;

    int fd_value;
protected:
    void run();
private:
    volatile bool stopped;
signals:
    void signalGPIO();

public slots:



};
class UsartThread : public QThread
{
    Q_OBJECT
public:
    explicit UsartThread(QObject *parent = 0);
    friend class spotmenu;

protected:
    void run();
private:
    int fd_temp;
signals:
    void signalSPI();
    void signalWelding();
    void signalFinishWelding();
};
class CalcThread : public QThread
{
    Q_OBJECT
public:
    explicit CalcThread(QObject *parent = 0);
    friend class spotmenu;
private:
    double base;
protected:
    void run();
signals:
        void signalPlot();

};
class FileThread : public QThread
{
    Q_OBJECT
public:
    explicit FileThread(QObject *parent = 0);
    friend class spotmenu;

protected:
    void run();


};
class spotmenu : public QMainWindow
{
    Q_OBJECT

public:
    explicit spotmenu(QWidget *parent = 0);
    ~spotmenu();
    friend class MyThread;
    QTime time;
    QTimer *timer;
    QDate date;
    QDateTime dt;
    void showWeldStatus();
    void showWeldPara();
    void plot_Curve();
    void get_plotdata();
    void plot_CurveInstant();
    void get_plotdataInstant();
    void showConnectStatus(QString);
    void file_curve_init(void);
    QTcpServer *tcp_server;
    HandleClient_Thread *handleclient_thread;
    quint16 port;
public slots:
    void get_signalGPIO();
    void get_signalSPI();
    void get_signalTimer();
    void get_signalPlot();
    void get_signalWelding();
    void get_signalFinishWelding();
    void get_signalShowConnect_Status();
    void get_signalCreateTcpThread(int socketDescriptor);
private slots:
    void on_actionAuthor_triggered();

    void on_actionReadHistory_triggered();




  //  void on_actionControl_mode_triggered();

 //   void on_actionMemory_location_triggered();


    void on_PlotButton_clicked();

    void on_actionAuto_triggered();

    void on_actionNetWork_Only_triggered();

    void on_actionLocal_Only_triggered();

    void on_actionUsb_triggered();

    void on_actionSD_triggered();

signals:
    void signalRealTime_update(void);
private:
    Ui::spotmenu *ui;

    CalcThread *calcthread;
    FileThread *filethread;
    QScrollBar *slider;



};


#endif // SPOTMENU_H
