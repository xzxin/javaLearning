#include <QtGui/QApplication>
#include "spotmenu.h"
spotmenu *mainwindow;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    spotmenu w;
    mainwindow=&w;
    w.show();
    
    return a.exec();
}
