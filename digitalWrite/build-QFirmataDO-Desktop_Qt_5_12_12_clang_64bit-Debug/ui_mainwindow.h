/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.12
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *connectButton;
    QPushButton *discButton;
    QPushButton *connectButton_2;
    QPushButton *connectButton_3;
    QPushButton *connectButton_4;
    QComboBox *comboBox;
    QPushButton *pushButton;
    QPushButton *connectButton_5;
    QPushButton *connectButton_6;
    QPushButton *connectButton_7;
    QSlider *horizontalSlider;
    QLabel *label;
    QLabel *status;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 501);
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        connectButton = new QPushButton(centralwidget);
        connectButton->setObjectName(QString::fromUtf8("connectButton"));
        connectButton->setGeometry(QRect(170, 50, 99, 27));
        discButton = new QPushButton(centralwidget);
        discButton->setObjectName(QString::fromUtf8("discButton"));
        discButton->setGeometry(QRect(280, 50, 99, 27));
        connectButton_2 = new QPushButton(centralwidget);
        connectButton_2->setObjectName(QString::fromUtf8("connectButton_2"));
        connectButton_2->setGeometry(QRect(60, 180, 99, 27));
        connectButton_3 = new QPushButton(centralwidget);
        connectButton_3->setObjectName(QString::fromUtf8("connectButton_3"));
        connectButton_3->setGeometry(QRect(60, 220, 99, 27));
        connectButton_4 = new QPushButton(centralwidget);
        connectButton_4->setObjectName(QString::fromUtf8("connectButton_4"));
        connectButton_4->setGeometry(QRect(60, 260, 99, 27));
        comboBox = new QComboBox(centralwidget);
        comboBox->setObjectName(QString::fromUtf8("comboBox"));
        comboBox->setGeometry(QRect(50, 50, 79, 22));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(60, 110, 89, 25));
        connectButton_5 = new QPushButton(centralwidget);
        connectButton_5->setObjectName(QString::fromUtf8("connectButton_5"));
        connectButton_5->setGeometry(QRect(310, 260, 99, 27));
        connectButton_6 = new QPushButton(centralwidget);
        connectButton_6->setObjectName(QString::fromUtf8("connectButton_6"));
        connectButton_6->setGeometry(QRect(180, 260, 99, 27));
        connectButton_7 = new QPushButton(centralwidget);
        connectButton_7->setObjectName(QString::fromUtf8("connectButton_7"));
        connectButton_7->setGeometry(QRect(310, 300, 121, 51));
        horizontalSlider = new QSlider(centralwidget);
        horizontalSlider->setObjectName(QString::fromUtf8("horizontalSlider"));
        horizontalSlider->setGeometry(QRect(300, 370, 160, 16));
        horizontalSlider->setMaximum(255);
        horizontalSlider->setOrientation(Qt::Horizontal);
        label = new QLabel(centralwidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(170, 390, 131, 31));
        status = new QLabel(centralwidget);
        status->setObjectName(QString::fromUtf8("status"));
        status->setGeometry(QRect(260, 400, 60, 16));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Firmata DO", nullptr));
        connectButton->setText(QApplication::translate("MainWindow", "connect", nullptr));
        discButton->setText(QApplication::translate("MainWindow", "disconnect", nullptr));
        connectButton_2->setText(QApplication::translate("MainWindow", "Sequencer", nullptr));
        connectButton_3->setText(QApplication::translate("MainWindow", "Traffic Ctrl", nullptr));
        connectButton_4->setText(QApplication::translate("MainWindow", "Flip : pin 13", nullptr));
        pushButton->setText(QApplication::translate("MainWindow", "RU there", nullptr));
        connectButton_5->setText(QApplication::translate("MainWindow", "Flash : pin 13", nullptr));
        connectButton_6->setText(QApplication::translate("MainWindow", "Flip : pin 12", nullptr));
        connectButton_7->setText(QApplication::translate("MainWindow", "Stop Flash : pin 13", nullptr));
        label->setText(QApplication::translate("MainWindow", "pin 3 status: ", nullptr));
        status->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
