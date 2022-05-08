#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qfirmata.h>
#include <QMainWindow>
#include <analogpin.h>
#include <digitalpin.h>
#include <QDebug>
#include <QTimer>
#include <QThread>

//#define V1 255
//#define V2 0
//#define RIGHT 5
//#define LEFT 6

MainWindow::MainWindow(QWidget *parent) :
     QMainWindow(parent),
     _firmata (new QFirmata (this)),
     _firstDigitalPinIndex(2),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->_connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
    connect(ui->_disconnectButton, SIGNAL(clicked()), this, SLOT(onDisconnectButtonClicked()));
//    connect(ui->startButton, SIGNAL (clicked()), this, SLOT(onTimer1()));
    connect(_firmata, SIGNAL(firmwareVersionReceived(int, int)), this, SLOT(onFirmwareVersionReceived(int,int)));
    connect(_firmata, SIGNAL(firmwareNameReceived(QString)), this, SLOT(onFirmwareNameReceived(QString)));
    connect(_firmata, SIGNAL(initialized(int,int,QString)), this, SLOT(onInitialized(int,int,QString)));
    connect(_firmata, SIGNAL(digitalPinChanged(int)), this, SLOT(onDigitalPinChanged(int)));
    connect(_firmata, SIGNAL(analogPinChanged(int)), this, SLOT(onAnalogPinChanged(int)));

    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->_portComboBox->addItem(info.portName());
    }



}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::onConnectButtonClicked()
{
    if(_firmata->open(ui->_portComboBox->currentText()))
    {
        statusBar()->showMessage(tr("[Notice] Successfully opened connection"), 5000);
        _firmata->sendAnalogPinReporting(0, ARD_ON);
        _firmata->sendAnalogPinReporting(1, ARD_ON);
        //_firmata->sendDigitalPinReporting(enA, ARD_OFF);
        _firmata->sendDigitalPinMode(LEFTPWM, ARD_PWM);
        //_firmata->sendDigitalPinReporting(enB, ARD_OFF);
        _firmata->sendDigitalPinMode(RIGHTPWM, ARD_PWM);
        _firmata->sendDigitalPinReporting(LEFTDIR, ARD_OFF);
        _firmata->sendDigitalPinMode(LEFTDIR, ARD_OUTPUT);
        _firmata->sendDigitalPinReporting(RIGHTDIR, ARD_OFF);
        _firmata->sendDigitalPinMode(RIGHTDIR, ARD_OUTPUT);
        //_firmata->sendDigitalPinReporting(in3, ARD_OFF);
        //_firmata->sendDigitalPinMode(in3, ARD_OUTPUT);
        //_firmata->sendDigitalPinReporting(in4, ARD_OFF);
        //_firmata->sendDigitalPinMode(in4, ARD_OUTPUT);

    }
    else
    {
        statusBar()->showMessage(tr("[Error] Could not open connection"), 5000);
    }
}
void MainWindow::onDisconnectButtonClicked()
{
    _firmata->close();
//    ui->_connectButton->show();
//    ui->_disconnectButton->hide();
    _firmwareLabel->setText("");
    statusBar()->showMessage(tr("[Notice] Successfully closed connection"), 5000);
}

void MainWindow::onFirmwareVersionReceived(const int majorVersion, const int minorVersion)
{
    qDebug()<<"major"<<majorVersion<<"minor"<<minorVersion;
}

void MainWindow::onFirmwareNameReceived(QString firmwareName)
{
    qDebug()<<"firmware name"<<firmwareName;
}

void MainWindow::onInitialized(const int majorVersion, const int minorVersion, QString firmwareName)
{
    qDebug()<<"firmate initialized"<<majorVersion<<minorVersion<<firmwareName;
//    _analogPinWidget->setEnabled(true);
//    _digitalPinWidget->setEnabled(true);
    statusBar()->showMessage(tr("initialized"), 5000);

    QString statusText = QString::number(majorVersion)+"."+QString::number(minorVersion);

//    _firmata->sendDigitalPinMode(11, ARD_INPUT);
//    _firmata->sendDigital(11, ARD_LOW);
//    _firmata->sendDigitalPinMode(12, ARD_INPUT);
//    _firmata->sendDigital(12, ARD_HIGH);
//    _firmata->sendDigitalPinMode(13, ARD_INPUT);
//    _firmata->sendDigital(13, ARD_HIGH);
//    _firmata->sendDigitalPinReporting(enA, ARD_OFF);
//    _firmata->sendDigitalPinMode(enA, ARD_PWM);
//    _firmata->sendDigitalPinReporting(enB, ARD_OFF);
//    _firmata->sendDigitalPinMode(enB, ARD_PWM);
//    _firmata->sendDigitalPinReporting(in1, ARD_OFF);
//    _firmata->sendDigitalPinMode(in1, ARD_OUTPUT);
//    _firmata->sendDigitalPinReporting(in2, ARD_OFF);
//    _firmata->sendDigitalPinMode(in2, ARD_OUTPUT);
//    _firmata->sendDigitalPinReporting(in3, ARD_OFF);
//    _firmata->sendDigitalPinMode(in3, ARD_OUTPUT);
//    _firmata->sendDigitalPinReporting(in4, ARD_OFF);
//    _firmata->sendDigitalPinMode(in4, ARD_OUTPUT);

    _firmata->sendDigitalPinMode(LEFTPWM, ARD_PWM);
    _firmata->sendDigitalPinMode(RIGHTPWM, ARD_PWM);
    _firmata->sendDigitalPinReporting(LEFTDIR, ARD_OFF);
    _firmata->sendDigitalPinMode(LEFTDIR, ARD_OUTPUT);
    _firmata->sendDigitalPinReporting(RIGHTDIR, ARD_OFF);
    _firmata->sendDigitalPinMode(RIGHTDIR, ARD_OUTPUT);

}


void MainWindow::onDigitalPinChanged(int pin)
{
    qDebug()<<"digital pin"<<pin<<"changed. new value"<<_firmata->getDigital(7)<<_firmata->getDigital(8);
//    _digitalPinVec[pin-2]->setValue(_firmata->getDigital(pin));

 if (pin == 11 || pin == 12 || pin==13)
    {
    LSense = _firmata->getDigital(11);
    CSense = _firmata->getDigital(12);
    RSense = _firmata->getDigital(13);

if (RSense && LSense && CSense)
{
    qDebug()<<"stop";
    Park();
}

else if (RSense && LSense && !CSense)
{
    qDebug()<<"Straight";
    goStraight();
}

else if (RSense && !LSense && CSense)
{
    qDebug()<<"Left Steep";
    goLeft();
}

else if (RSense && !LSense && !CSense)
{
    qDebug()<<"Left Low";
    goLeftLow();
}

else if (!RSense && LSense && CSense)
{
    qDebug()<<"Right Steep";
    goRight();
}

else if (!RSense && LSense && !CSense)
{
    qDebug()<<"Right Low";
    goRightLow();
}

else if (!RSense && !LSense && !CSense)
{
    qDebug()<<"stop";
    Park();
}

}
}

void MainWindow::onAnalogPinChanged(int pin)
{
    if(pin < _analogPinVec.size())
    {
        _analogPinVec[pin]->setValue(_firmata->getAnalog(pin));
    }
}

void MainWindow::onSysExReceived(const QVector<unsigned char> message)
{
    qDebug()<<"sysExReceived"<<message;
}

void MainWindow::onDigitalPinWidgetValueChanged(unsigned int id, unsigned int value, bool pwm)
{
    qDebug()<<"digital pin"<<id<<value<<pwm;

    if(pwm)
    {
        _firmata->sendPWM(id, value);
    }
    else
    {
        _firmata->sendDigital(id, value);
    }
}

void MainWindow::onAnalogPinReportinChange(unsigned int pin, bool value)
{
    qDebug()<<"analog pin reporting"<<pin<<"changed. new value"<<value;

    if(value)
    {
        _firmata->sendAnalogPinReporting(pin, ARD_ANALOG);
    }
    else
    {
        _firmata->sendAnalogPinReporting(pin, ARD_OFF);
   }
}


//void MainWindow::on_horizontalSlider_valueChanged(int valueA)
//{
//    pvalueA=valueA;
////    goStraight();
//////    //left
////    _firmata->sendPWM(enA, pvalueA);
//    onDigitalPinChanged(5);
//}

//void MainWindow::on_horizontalSlider_2_valueChanged(int valueB)
//{
//    pvalueB=valueB;
////    goStraight();
////    //right
////    _firmata->sendPWM(enB, pvalueB);
//    onDigitalPinChanged(10);
//}

//void MainWindow::demoOne()
//{
//  //this function will run the motors in both directions at a fixed speed
//  //turn on motor A
//    qDebug()<<"turn";
//  _firmata->sendDigital(in1, ARD_HIGH);
//  _firmata->sendDigital(in2, ARD_LOW);

//  //set speed to 200 out of possible range 0-255
//  _firmata->sendPWM(enA, 200);

//  //turn on motor B
//  _firmata->sendDigital(in3, ARD_HIGH);
//  _firmata->sendDigital(in4, ARD_LOW);

//  //set speed to 200 out of possible range 0-255
//  _firmata->sendPWM(enB, 200);
//  QThread::sleep(2000); //delay(2000);

//  //change motor directions
//  _firmata->sendDigital(in1, ARD_LOW);
//  _firmata->sendDigital(in2, ARD_HIGH);
//  _firmata->sendDigital(in3, ARD_LOW);
//  _firmata->sendDigital(in4, ARD_HIGH);
//  QThread::sleep(2000);

//  //turn off motors
//  _firmata->sendDigital(in1, ARD_LOW);
//  _firmata->sendDigital(in2, ARD_LOW);
//  _firmata->sendDigital(in3, ARD_LOW);
//  _firmata->sendDigital(in4, ARD_LOW);
//}

//void MainWindow::demoTwo()
//{
//  //this function will run the motors across the range of possible speeds
//  //note that the maximum speed is determined by the motor (itself and the operating voltage)
//  //the PWM values sent by analogWrite() are fractions of the maximum speed possible by your hardware

//  //turn on motors
//  _firmata->sendDigital(in1, ARD_LOW);
//  _firmata->sendDigital(in2, ARD_HIGH);
//  _firmata->sendDigital(in3, ARD_LOW);
//  _firmata->sendDigital(in4, ARD_HIGH);

//  //accelerate from zero to maximum speed
//  for (int i=0; i<256; i++)
//  {
//    _firmata->sendPWM (enA, i);
//    _firmata->sendPWM (enB, i);
//    QThread::sleep(20);
//  }

//  //decelerate from maximum speed to zero
//  for (int i=255; i >= 0; --i)
//  {
//    _firmata->sendPWM (enA, i);
//    _firmata->sendPWM (enB, i);
//    QThread::sleep(20);
//  }

//  //turn off motors
//  _firmata->sendDigital (in1, ARD_LOW);
//  _firmata->sendDigital (in2, ARD_LOW);
//  _firmata->sendDigital (in3, ARD_LOW);
//  _firmata->sendDigital (in4, ARD_LOW);
//}

////void MainWindow::loop()
////{
////  demoOne();
////  Thread::sleep(1000);
////  demoTwo();
////  Thread::sleep(1000);
////}

void MainWindow::goStraight()
{
    qDebug()<<"goStraight ";

//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 125);
//    _firmata->sendPWM(enB, 125);

    //_firmata->sendDigital(LEFTDIR, 125); // Control direction
    //_firmata->sendPWM(LEFTPWM, 125); // SPeed of motor

    _firmata->sendDigital(3, ARD_LOW);
    _firmata->sendDigital(10, ARD_LOW);
    _firmata->sendPWM(11, 150);
    _firmata->sendPWM(5, 150);
}

void MainWindow::goRight()
{
//    qDebug()<<"goRight ";

//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 0);
//    _firmata->sendPWM(enB, 180);
}

void MainWindow::goRightLow()
{
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 0);
//    _firmata->sendPWM(enB, 180);

    _firmata->sendDigital(LEFTDIR, ARD_LOW); // Control direction
    _firmata->sendPWM(LEFTPWM, SLOW); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, TURNSLOW);
}

void MainWindow::goLeft()
{
    qDebug()<<"goLeft ";
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 150);
//    _firmata->sendPWM(enB, 0);
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, CSLOW); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_LOW);
    _firmata->sendPWM(RIGHTPWM, CFAST);
}

void MainWindow::goLeftLow()
{
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 150);
//    _firmata->sendPWM(enB, 0);
}

void MainWindow::Park()
{
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_LOW);
//    _firmata->sendDigital(in3, ARD_HIGH);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 0);
//    _firmata->sendPWM(enB, 0);
}

void MainWindow::Neutral()
{
//    qDebug()<<"Neutral ";
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_LOW);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_LOW);

//    _firmata->sendPWM(enA, 0);
//    _firmata->sendPWM(enB, 0);
    _firmata->sendDigital(LEFTDIR, 0); // Control direction
    _firmata->sendPWM(LEFTPWM, 0); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, 0);
    _firmata->sendPWM(RIGHTPWM, 0);
}

void MainWindow::Reverse()
{
//    qDebug()<<"Reverse ";
//    _firmata->sendDigital(in1, ARD_HIGH);
//    _firmata->sendDigital(in2, ARD_LOW);
//    _firmata->sendDigital(in3, ARD_HIGH);
//    _firmata->sendDigital(in4, ARD_LOW);

//    _firmata->sendPWM(enA, 150);
//    _firmata->sendPWM(enB, 150);
    _firmata->sendDigital(3, ARD_HIGH);
    _firmata->sendDigital(10, ARD_HIGH);
    _firmata->sendPWM(11, 150);
    _firmata->sendPWM(5, 150);
}

void MainWindow::Test()
{
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 200);
//    _firmata->sendPWM(enB, 200);
}

void MainWindow::RobotForward(int delay)
{
//    _firmata->sendDigital(in1, ARD_LOW);
//    _firmata->sendDigital(in2, ARD_HIGH);
//    _firmata->sendDigital(in3, ARD_LOW);
//    _firmata->sendDigital(in4, ARD_HIGH);

//    _firmata->sendPWM(enA, 150);
//    _firmata->sendPWM(enB, 180);
//     QThread::sleep(delay);
}
// call this using timer periodically or onAnalogPinChanged(int pin)
void MainWindow::RobotController()
{
  //create your robot algorithm / rules here
  //over simplified example
    if (Distance > TARGET)
        goRight();
    else if (Distance < TARGET)
        goLeft();
    else
        goStraight();
}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{

}

void MainWindow::on_pushButton_clicked()
{
    goStraight();
}
void MainWindow::on_pushButton_2_clicked()
{
    goRightLow();
}

void MainWindow::on_pushButton_3_clicked()
{
    Reverse();
}

void MainWindow::on_pushButton_4_clicked()
{
    goLeft();
}

void MainWindow::on_pushButton_5_clicked()
{
    Neutral();
}
