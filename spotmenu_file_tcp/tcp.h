#ifndef TCP_H
#define TCP_H



#include <QThread>
#include <QHostAddress>
#include <QtNetwork>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>

class MyTcpServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit MyTcpServer(QObject *parent = 0);
protected:
    void incomingConnection(int socketDescriptor);
signals:
    void newConnection(int socketDescriptor);
};

class HandleClient_Thread : public QThread
{
    Q_OBJECT
public:
    explicit HandleClient_Thread(int socketDescriptor,QObject *parent = 0);
    int SocketDescriptor;
    QHostAddress address;
    QString client_IP;
    void lookup_spotfile_day(QString base_path);
    void lookup_spotfile_car(QString base_day_path);
    void lookup_spotfile_spot(QString base_day_car_path);
    void lookup_spotfile_curve(QString file_path);
protected:
    void run();
signals:
    void showConnect_Status(void);
private:
    QTcpSocket *tcp_socket;
public slots:
    void readData();
   void handleDisconnect();
   void get_signalRealTime_update();
};

/*
class MyTcp_Server : public QTcpServer
{
    Q_OBJECT
public :
    explicit MyTcp_Server(QObject *parent = 0);
    ~MyTcp_Server();
signals:
slots:

}
*/

#endif // TCP_H
