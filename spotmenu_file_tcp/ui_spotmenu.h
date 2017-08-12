/********************************************************************************
** Form generated from reading UI file 'spotmenu.ui'
**
** Created: Wed May 3 21:54:23 2017
**      by: Qt User Interface Compiler version 4.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SPOTMENU_H
#define UI_SPOTMENU_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QScrollArea>
#include <QtGui/QStatusBar>
#include <QtGui/QTabWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include <qcustomplot.h>

QT_BEGIN_NAMESPACE

class Ui_spotmenu
{
public:
    QAction *actionAuthor;
    QAction *actionReadHistory;
    QAction *actionLocal_Only;
    QAction *actionNetWork_Only;
    QAction *actionAuto;
    QAction *actionUsb;
    QAction *actionSD;
    QAction *actionShortcut_para;
    QWidget *centralWidget;
    QScrollArea *scrollArea;
    QWidget *scrollAreaWidgetContents;
    QTabWidget *tabWidget;
    QWidget *welding;
    QGroupBox *groupBox;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLineEdit *value_curr;
    QLineEdit *value_time;
    QLineEdit *value_ratio;
    QLineEdit *value_heat;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_curr;
    QLabel *label_time;
    QLabel *label_ratio;
    QLabel *label_ratio_2;
    QGroupBox *groupBox_2;
    QTextEdit *spotinfo;
    QWidget *I;
    QCustomPlot *curr_plot;
    QWidget *R;
    QCustomPlot *res_plot;
    QWidget *L;
    QCustomPlot *L_plot;
    QWidget *Heat;
    QCustomPlot *heat_plot;
    QWidget *INS;
    QCustomPlot *INS_plot;
    QLineEdit *CurrTime;
    QLineEdit *connect_status;
    QPushButton *PlotButton;
    QPushButton *ShortcutButton;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QMenu *menuSettings;
    QMenu *menuControl_mode;
    QMenu *menuMemory_location;
    QMenu *menuStatus;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;
    QToolBar *toolBar;
    QToolBar *toolBar_2;

    void setupUi(QMainWindow *spotmenu)
    {
        if (spotmenu->objectName().isEmpty())
            spotmenu->setObjectName(QString::fromUtf8("spotmenu"));
        spotmenu->resize(482, 241);
        actionAuthor = new QAction(spotmenu);
        actionAuthor->setObjectName(QString::fromUtf8("actionAuthor"));
        actionReadHistory = new QAction(spotmenu);
        actionReadHistory->setObjectName(QString::fromUtf8("actionReadHistory"));
        actionLocal_Only = new QAction(spotmenu);
        actionLocal_Only->setObjectName(QString::fromUtf8("actionLocal_Only"));
        actionNetWork_Only = new QAction(spotmenu);
        actionNetWork_Only->setObjectName(QString::fromUtf8("actionNetWork_Only"));
        actionAuto = new QAction(spotmenu);
        actionAuto->setObjectName(QString::fromUtf8("actionAuto"));
        actionUsb = new QAction(spotmenu);
        actionUsb->setObjectName(QString::fromUtf8("actionUsb"));
        actionSD = new QAction(spotmenu);
        actionSD->setObjectName(QString::fromUtf8("actionSD"));
        actionShortcut_para = new QAction(spotmenu);
        actionShortcut_para->setObjectName(QString::fromUtf8("actionShortcut_para"));
        centralWidget = new QWidget(spotmenu);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(0, 0, 331, 171));
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        scrollArea->setWidgetResizable(true);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QString::fromUtf8("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 316, 169));
        tabWidget = new QTabWidget(scrollAreaWidgetContents);
        tabWidget->setObjectName(QString::fromUtf8("tabWidget"));
        tabWidget->setGeometry(QRect(0, 0, 341, 181));
        welding = new QWidget();
        welding->setObjectName(QString::fromUtf8("welding"));
        groupBox = new QGroupBox(welding);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(0, 0, 141, 141));
        groupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(255, 255, 247);"));
        widget = new QWidget(groupBox);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(50, 30, 81, 101));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        value_curr = new QLineEdit(widget);
        value_curr->setObjectName(QString::fromUtf8("value_curr"));

        verticalLayout->addWidget(value_curr);

        value_time = new QLineEdit(widget);
        value_time->setObjectName(QString::fromUtf8("value_time"));

        verticalLayout->addWidget(value_time);

        value_ratio = new QLineEdit(widget);
        value_ratio->setObjectName(QString::fromUtf8("value_ratio"));

        verticalLayout->addWidget(value_ratio);

        value_heat = new QLineEdit(widget);
        value_heat->setObjectName(QString::fromUtf8("value_heat"));

        verticalLayout->addWidget(value_heat);

        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QString::fromUtf8("widget1"));
        widget1->setGeometry(QRect(10, 30, 31, 101));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setContentsMargins(11, 11, 11, 11);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_curr = new QLabel(widget1);
        label_curr->setObjectName(QString::fromUtf8("label_curr"));

        verticalLayout_2->addWidget(label_curr);

        label_time = new QLabel(widget1);
        label_time->setObjectName(QString::fromUtf8("label_time"));

        verticalLayout_2->addWidget(label_time);

        label_ratio = new QLabel(widget1);
        label_ratio->setObjectName(QString::fromUtf8("label_ratio"));

        verticalLayout_2->addWidget(label_ratio);

        label_ratio_2 = new QLabel(widget1);
        label_ratio_2->setObjectName(QString::fromUtf8("label_ratio_2"));

        verticalLayout_2->addWidget(label_ratio_2);

        groupBox_2 = new QGroupBox(welding);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(140, 0, 161, 141));
        spotinfo = new QTextEdit(groupBox_2);
        spotinfo->setObjectName(QString::fromUtf8("spotinfo"));
        spotinfo->setGeometry(QRect(0, 20, 181, 121));
        tabWidget->addTab(welding, QString());
        I = new QWidget();
        I->setObjectName(QString::fromUtf8("I"));
        curr_plot = new QCustomPlot(I);
        curr_plot->setObjectName(QString::fromUtf8("curr_plot"));
        curr_plot->setGeometry(QRect(0, 0, 311, 141));
        tabWidget->addTab(I, QString());
        R = new QWidget();
        R->setObjectName(QString::fromUtf8("R"));
        res_plot = new QCustomPlot(R);
        res_plot->setObjectName(QString::fromUtf8("res_plot"));
        res_plot->setGeometry(QRect(0, 0, 311, 141));
        tabWidget->addTab(R, QString());
        L = new QWidget();
        L->setObjectName(QString::fromUtf8("L"));
        L_plot = new QCustomPlot(L);
        L_plot->setObjectName(QString::fromUtf8("L_plot"));
        L_plot->setGeometry(QRect(0, 0, 311, 141));
        tabWidget->addTab(L, QString());
        Heat = new QWidget();
        Heat->setObjectName(QString::fromUtf8("Heat"));
        heat_plot = new QCustomPlot(Heat);
        heat_plot->setObjectName(QString::fromUtf8("heat_plot"));
        heat_plot->setGeometry(QRect(0, 0, 311, 141));
        tabWidget->addTab(Heat, QString());
        INS = new QWidget();
        INS->setObjectName(QString::fromUtf8("INS"));
        INS_plot = new QCustomPlot(INS);
        INS_plot->setObjectName(QString::fromUtf8("INS_plot"));
        INS_plot->setGeometry(QRect(0, 0, 311, 141));
        tabWidget->addTab(INS, QString());
        scrollArea->setWidget(scrollAreaWidgetContents);
        CurrTime = new QLineEdit(centralWidget);
        CurrTime->setObjectName(QString::fromUtf8("CurrTime"));
        CurrTime->setGeometry(QRect(340, 10, 131, 27));
        connect_status = new QLineEdit(centralWidget);
        connect_status->setObjectName(QString::fromUtf8("connect_status"));
        connect_status->setGeometry(QRect(350, 60, 113, 31));
        PlotButton = new QPushButton(centralWidget);
        PlotButton->setObjectName(QString::fromUtf8("PlotButton"));
        PlotButton->setGeometry(QRect(350, 100, 98, 27));
        ShortcutButton = new QPushButton(centralWidget);
        ShortcutButton->setObjectName(QString::fromUtf8("ShortcutButton"));
        ShortcutButton->setGeometry(QRect(350, 130, 101, 27));
        spotmenu->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(spotmenu);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 482, 28));
        menuBar->setMouseTracking(true);
        menuBar->setAcceptDrops(true);
        menuBar->setAutoFillBackground(false);
        menuBar->setDefaultUp(false);
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuControl_mode = new QMenu(menuSettings);
        menuControl_mode->setObjectName(QString::fromUtf8("menuControl_mode"));
        menuMemory_location = new QMenu(menuSettings);
        menuMemory_location->setObjectName(QString::fromUtf8("menuMemory_location"));
        menuStatus = new QMenu(menuBar);
        menuStatus->setObjectName(QString::fromUtf8("menuStatus"));
        spotmenu->setMenuBar(menuBar);
        mainToolBar = new QToolBar(spotmenu);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        spotmenu->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(spotmenu);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        spotmenu->setStatusBar(statusBar);
        toolBar = new QToolBar(spotmenu);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        spotmenu->addToolBar(Qt::TopToolBarArea, toolBar);
        toolBar_2 = new QToolBar(spotmenu);
        toolBar_2->setObjectName(QString::fromUtf8("toolBar_2"));
        spotmenu->addToolBar(Qt::TopToolBarArea, toolBar_2);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuBar->addAction(menuStatus->menuAction());
        menuFile->addAction(actionReadHistory);
        menuAbout->addAction(actionAuthor);
        menuSettings->addAction(menuControl_mode->menuAction());
        menuSettings->addAction(menuMemory_location->menuAction());
        menuControl_mode->addAction(actionLocal_Only);
        menuControl_mode->addAction(actionNetWork_Only);
        menuControl_mode->addAction(actionAuto);
        menuMemory_location->addAction(actionUsb);
        menuMemory_location->addAction(actionSD);
        menuStatus->addAction(actionShortcut_para);

        retranslateUi(spotmenu);

        tabWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(spotmenu);
    } // setupUi

    void retranslateUi(QMainWindow *spotmenu)
    {
        spotmenu->setWindowTitle(QApplication::translate("spotmenu", "spotmenu", 0, QApplication::UnicodeUTF8));
        actionAuthor->setText(QApplication::translate("spotmenu", "author", 0, QApplication::UnicodeUTF8));
        actionReadHistory->setText(QApplication::translate("spotmenu", "readHistory", 0, QApplication::UnicodeUTF8));
        actionLocal_Only->setText(QApplication::translate("spotmenu", "Local Only", 0, QApplication::UnicodeUTF8));
        actionNetWork_Only->setText(QApplication::translate("spotmenu", "NetWork Only", 0, QApplication::UnicodeUTF8));
        actionAuto->setText(QApplication::translate("spotmenu", "Auto", 0, QApplication::UnicodeUTF8));
        actionUsb->setText(QApplication::translate("spotmenu", "Usb", 0, QApplication::UnicodeUTF8));
        actionSD->setText(QApplication::translate("spotmenu", "SD", 0, QApplication::UnicodeUTF8));
        actionShortcut_para->setText(QApplication::translate("spotmenu", "Shortcut para", 0, QApplication::UnicodeUTF8));
#ifndef QT_NO_WHATSTHIS
        tabWidget->setWhatsThis(QApplication::translate("spotmenu", "<html><head/><body><p><br/></p></body></html>", 0, QApplication::UnicodeUTF8));
#endif // QT_NO_WHATSTHIS
        groupBox->setTitle(QApplication::translate("spotmenu", "welding para", 0, QApplication::UnicodeUTF8));
        label_curr->setText(QApplication::translate("spotmenu", "curr", 0, QApplication::UnicodeUTF8));
        label_time->setText(QApplication::translate("spotmenu", "time", 0, QApplication::UnicodeUTF8));
        label_ratio->setText(QApplication::translate("spotmenu", "ratio", 0, QApplication::UnicodeUTF8));
        label_ratio_2->setText(QApplication::translate("spotmenu", "heat", 0, QApplication::UnicodeUTF8));
        groupBox_2->setTitle(QApplication::translate("spotmenu", "spot status", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(welding), QApplication::translate("spotmenu", "welding", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(I), QApplication::translate("spotmenu", "I", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(R), QApplication::translate("spotmenu", "R", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(L), QApplication::translate("spotmenu", "L", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(Heat), QApplication::translate("spotmenu", "Heat", 0, QApplication::UnicodeUTF8));
        tabWidget->setTabText(tabWidget->indexOf(INS), QApplication::translate("spotmenu", "INS", 0, QApplication::UnicodeUTF8));
        PlotButton->setText(QApplication::translate("spotmenu", "Plot", 0, QApplication::UnicodeUTF8));
        ShortcutButton->setText(QApplication::translate("spotmenu", "Short-cut Test", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("spotmenu", "file", 0, QApplication::UnicodeUTF8));
        menuAbout->setTitle(QApplication::translate("spotmenu", "about", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("spotmenu", "settings", 0, QApplication::UnicodeUTF8));
        menuControl_mode->setTitle(QApplication::translate("spotmenu", "control mode", 0, QApplication::UnicodeUTF8));
        menuMemory_location->setTitle(QApplication::translate("spotmenu", "memory location", 0, QApplication::UnicodeUTF8));
        menuStatus->setTitle(QApplication::translate("spotmenu", "Status", 0, QApplication::UnicodeUTF8));
        toolBar->setWindowTitle(QApplication::translate("spotmenu", "toolBar", 0, QApplication::UnicodeUTF8));
        toolBar_2->setWindowTitle(QApplication::translate("spotmenu", "toolBar_2", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class spotmenu: public Ui_spotmenu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SPOTMENU_H
