#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QDebug>
#include <QComboBox>
#include <QPushButton>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QStatusBar>
#include <QLabel>
#include <QGroupBox>
#include <QScrollArea>
#include <QTableWidget>
#include <QHeaderView>

#include <QSlider>
#define TASKMAX 8
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      _firmata(new QFirmata(this)),
      _firstDigitalPinIndex(2),
       ui (new Ui::MainWindow)
{
    ui->setupUi(this);
//    for(unsigned int i = 0; i <= 5; i++)
//    {
//        _analogPinVec.push_back(new AnalogPin(i, this));
//        connect(_analogPinVec[i], SIGNAL(pinReportingChanged(uint,bool)), this, SLOT(onAnalogPinReportinChange(uint,bool)));
//    }
//    for(unsigned int i = 2; i <= 13; i++)
//    {
//        _digitalPinVec.push_back(new DigitalPin(i, this));
//        connect(_digitalPinVec.last(), SIGNAL(pinModeChanged(uint,int)), this, SLOT(onDigitalPinModeChange(uint,int)));
//        connect(_digitalPinVec.last(), SIGNAL(valueChanged(uint,uint,bool)), this, SLOT(onDigitalPinWidgetValueChanged(uint,uint,bool)));
//    }

//    _portComboBox = new QComboBox(this);
    foreach (const QSerialPortInfo &info, QSerialPortInfo::availablePorts())
    {
        ui->comboBox->addItem(info.portName());
    }

//    _connectButton = new QPushButton(tr("connect"),this);
//    _disconnectButton = new QPushButton(tr("disconnect"),this);
//    _firmwareLabel = new QLabel();


//    QWidget *widget = new QWidget(this);


//    QVBoxLayout *layout = new QVBoxLayout(widget);

//    QWidget *serialWidget = new QWidget(this);
//    QHBoxLayout *serialWidgetLayout = new QHBoxLayout(serialWidget);
//    serialWidget->setLayout(serialWidgetLayout);
//    serialWidgetLayout->addWidget(_portComboBox);
//    serialWidgetLayout->addWidget(_connectButton);
//    serialWidgetLayout->addWidget(_disconnectButton);
//    serialWidgetLayout->addWidget(_firmwareLabel);
//    serialWidgetLayout->addSpacerItem(new QSpacerItem(1,1,QSizePolicy::Expanding));

//    QLabel *serialLabel = new QLabel("Serial settings");
//    QFont font = serialLabel->font();
//    font.setBold(true);
//    font.setPointSize(20);
//    serialLabel->setFont(font);



//    layout->addWidget(serialLabel);
//    layout->addWidget(serialWidget);

//    QWidget *pinWidget = new QWidget(this);
//    _analogPinWidget = new QWidget(this);
//    _digitalPinWidget = new QWidget(this);

//    QHBoxLayout *pinLayout = new QHBoxLayout(pinWidget);
//    QVBoxLayout *analogPinLayout = new QVBoxLayout(_analogPinWidget);
//    analogPinLayout->setSpacing(0);
//    analogPinLayout->setMargin(0);
//    QVBoxLayout *digitalPinLayout = new QVBoxLayout(_digitalPinWidget);
//    digitalPinLayout->setSpacing(0);
//    digitalPinLayout->setMargin(0);
//    pinWidget->setLayout(pinLayout);
//    _analogPinWidget->setLayout(analogPinLayout);
//    _digitalPinWidget->setLayout(digitalPinLayout);

//    layout->addWidget(pinWidget);

//    pinLayout->addWidget(_analogPinWidget);
//    pinLayout->addWidget(_digitalPinWidget);

//    QLabel *analogPinLabel = new QLabel("Analog input pins");
//    QFont pinFont = analogPinLabel->font();
//    pinFont.setBold(true);
//    pinFont.setPointSize(16);
//    analogPinLabel->setFont(pinFont);
//    analogPinLayout->addWidget(analogPinLabel);
//    analogPinLayout->addSpacerItem(new QSpacerItem(1,1, QSizePolicy::Expanding));

//    foreach(AnalogPin *pin, _analogPinVec)
//    {
//        analogPinLayout->addWidget(pin);
//    }

//    QLabel *digitalPinLabel = new QLabel("Digitale pins");
//    digitalPinLabel->setFont(pinFont);
//    digitalPinLayout->addWidget(digitalPinLabel);
//    foreach(DigitalPin *pin, _digitalPinVec)
//    {
//        digitalPinLayout->addWidget(pin);
//    }



//    widget->setLayout(layout);
//    setCentralWidget(widget);



    connect(ui->connectButton, SIGNAL(clicked()), this, SLOT(onConnectButtonClicked()));
    connect(ui->discButton, SIGNAL(clicked()), this, SLOT(onDisconnectButtonClicked()));

    connect(_firmata, SIGNAL(firmwareVersionReceived(int, int)), this, SLOT(onFirmwareVersionReceived(int,int)));
    connect(_firmata, SIGNAL(firmwareNameReceived(QString)), this, SLOT(onFirmwareNameReceived(QString)));
    connect(_firmata, SIGNAL(initialized(int,int,QString)), this, SLOT(onInitialized(int,int,QString)));
    connect(_firmata, SIGNAL(digitalPinChanged(int)), this, SLOT(onDigitalPinChanged(int)));
    connect(_firmata, SIGNAL(analogPinChanged(int)), this, SLOT(onAnalogPinChanged(int)));
    connect(_firmata, SIGNAL(sysExReceived(QVector<unsigned char>)), this, SLOT(onSysExReceived(QVector<unsigned char>)));
    Flag = false;
    setupRealtimeDataDemo(ui->customPlot);
    QTimer *timer = new QTimer(this); // try get data periodically
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_4_clicked()));
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_2_clicked())); //ping button will be clicked by the timer
    connect(timer, SIGNAL(timeout()), this, SLOT(on_pushButton_3_clicked()));
    timer->start(500);
//    timer2 = new QTimer(this);
//    connect(timer2, SIGNAL(timeout()), this, SLOT(on_connectButton_4_clicked()));

//    analogPinWidget->setDisabled(true);
//    _digitalPinWidget->setDisabled(true);
    QTimer *timerController = new QTimer(this);
    connect(timerController, SIGNAL(timeout()), this, SLOT(robotController()));
    timerController->start(1000); // every 1 second the robotcontroller will be called

}

MainWindow::~MainWindow()
{

}

void MainWindow::onConnectButtonClicked()
{
    if(_firmata->open(ui->comboBox->currentText()))
    {
        statusBar()->showMessage(tr("[Notice] Successfully opened connection"), 5000);
        _firmata->sendDigitalPinMode(0, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(1, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(2, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(3, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(4, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(5, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(6, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(7, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(8, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(9, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(10, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(11, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(13, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(14, ARD_INPUT);
//        _firmata->sendDigitalPinReporting(14, ARD_INPUT);

    }
    else
    {
        statusBar()->showMessage(tr("[Error] Could not open connection"), 5000);
    }

}
void MainWindow::onDisconnectButtonClicked()
{
    _firmata->close();
    ui->connectButton->show();
    ui->discButton->hide();
//    ui->Label->setText("");
    statusBar()->showMessage(tr("[Notice] Successfully closed connection"), 5000);

}


void MainWindow::onPinModeComboBoxChange(int index)
{
    qDebug()<<"pinmode changed"<<_ioDigitalPinModeComboBoxVec[index]->currentText();
    switch(_ioDigitalPinModeComboBoxVec[index]->currentIndex())
    {
    case 0: _firmata->sendDigitalPinReporting(index+2, ARD_OFF); break;
    case 1: _firmata->sendDigitalPinReporting(index+2, ARD_ON); _firmata->sendDigitalPinMode(index+2, ARD_INPUT); _ioDigitalCheckBoxVec[index]->show(); _ioDigitalCheckBoxVec[index]->setEnabled(false); _ioDigitalPinSliderVec[index]->hide(); break;
    case 2: _firmata->sendDigitalPinMode(index+2, ARD_OUTPUT); _ioDigitalCheckBoxVec[index]->show(); _ioDigitalCheckBoxVec[index]->setEnabled(true); _ioDigitalPinSliderVec[index]->hide(); break;
    case 3: _firmata->sendDigitalPinMode(index+2, ARD_PWM); _ioDigitalCheckBoxVec[index]->hide(); _ioDigitalPinSliderVec[index]->show(); _ioDigitalPinSliderVec[index]->setEnabled(true); break;
    }
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
    _firmata->sendDigitalPinMode(13, ARD_OUTPUT);
    _firmata->sendDigitalPinMode(12, ARD_OUTPUT);
    _firmata->sendDigitalPinMode(2, ARD_INPUT);
    _firmata->sendDigitalPinReporting(2, ARD_INPUT);
    _firmata->sendAnalogPinReporting(0, ARD_ANALOG);

}
void MainWindow::onDigitalPinChanged(int pin)
{
    qDebug()<<"digital pin"<<pin<<"changed. new value"<<_firmata->getDigital(pin);
//    _digitalPinVec[pin-2]->setValue(_firmata->getDigital(pin));
}

void MainWindow::onAnalogPinChanged(int pin) // Front sensor
{
//    if(pin < _analogPinVec.size())
//    {
//        _analogPinVec[pin]->setValue(_firmata->getAnalog(pin));
//    }
    if (pin==0){
        int value = _firmata->getAnalog(pin);
        qDebug()<<"analog pin"<<pin<<"changed. new value"<<_firmata->getAnalog(pin);
        //
//        ui->lcdNumber->display(5.0* value*100.0/1024.0);
        ui->lcdNumber_4->display((6762.0/(value-9.0))-4.0);
        frontSensor = ((6762.0/(value-9.0))-4.0);

    }
    else if (pin==1){
        int value = _firmata->getAnalog(pin);
        qDebug()<<"analog pin"<<pin<<"changed. new value"<<_firmata->getAnalog(pin);

//        ui->lcdNumber_2->display(5.0* value*100.0/1024.0);
        //ui->lcdNumber_2->display((6762.0/(value-9.0))-4.0);
          //x2 = ((6762.0/(value-9.0))-4.0);

    }
}
void MainWindow::onSysExReceived(QVector<unsigned char> message) // Ultrasonic
{
    QString str;
    QVector<unsigned char>::iterator it;
    unsigned char buffer, address;

    qDebug()<<"sysExReceived"<<message;
    it = message.begin();
    address = *it;
    it++; // skip the first byte, which is the string command
    while( it != message.end() ) {
            buffer = *it;
            it++;
//            buffer += *it;// << 7;
//            it++;
            str+=buffer;
    }
    if (address == SONAR_DATA+0x00)
    {
        ui->lcdNumber->display(str);
        leftFront = str.toDouble();
    }
    else if (address == SONAR_DATA+0x01)
    {
        ui->lcdNumber_2->display(str);
        leftRear = str.toDouble();
    }
}

void MainWindow::onStringReceived(const QString message)
{
    qDebug()<<"StringReceived"<<message;

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

void MainWindow::onDigitalPinModeChange(unsigned int pin, int mode)
{
    switch(mode)
    {
        //none
    case 0: _firmata->sendDigitalPinReporting(pin, ARD_OFF);
        break;
    case 1: _firmata->sendDigitalPinMode(pin, ARD_INPUT); _firmata->sendDigitalPinReporting(pin, ARD_ON);
        break;
    case 2: _firmata->sendDigitalPinReporting(pin, ARD_OFF); _firmata->sendDigitalPinMode(pin, ARD_OUTPUT);
        break;
    case 3: _firmata->sendDigitalPinReporting(pin, ARD_OFF); _firmata->sendDigitalPinMode(pin, ARD_PWM);
        break;
    default:
        break;
    }

}

void MainWindow::on_connectButton_4_clicked() // pin 13 blinking
{
  Flag = !Flag;
  if(Flag)
   _firmata->sendDigital(13,ARD_ON);
  else
   _firmata->sendDigital(13,ARD_OFF);
}

void MainWindow::on_connectButton_2_clicked()
{ //sequencer

    switch(Task)
    {
      case 0:
      case 1:
        _firmata->sendDigital(0,ARD_OFF);  //R
        _firmata->sendDigital(1,ARD_OFF); //Y
        _firmata->sendDigital(2,ARD_ON);  //G
        _firmata->sendDigital(3,ARD_ON);  //R
        _firmata->sendDigital(4,ARD_OFF);  //Y
        _firmata->sendDigital(5,ARD_OFF);  //G
        _firmata->sendDigital(6,ARD_ON);//R
        _firmata->sendDigital(7,ARD_OFF); //Y
        _firmata->sendDigital(8,ARD_OFF);  //G
        _firmata->sendDigital(9,ARD_ON);//R
        _firmata->sendDigital(10,ARD_OFF);
        _firmata->sendDigital(11,ARD_OFF);  //G
      break;
//    case 1:
//      _firmata->sendDigital(0,ARD_ON);  //R
//      _firmata->sendDigital(1,ARD_OFF); //Y
//      _firmata->sendDigital(2,ARD_OFF);  //G
//      _firmata->sendDigital(3,ARD_OFF); //R
//      _firmata->sendDigital(4,ARD_OFF);
//      _firmata->sendDigital(5,ARD_ON);   //G
//      _firmata->sendDigital(6,ARD_ON);//R
//      _firmata->sendDigital(7,ARD_OFF);
//      _firmata->sendDigital(8,ARD_OFF);  //G
//      _firmata->sendDigital(9,ARD_ON);//R
//      _firmata->sendDigital(10,ARD_OFF);
//      _firmata->sendDigital(11,ARD_OFF);  //G
//    break;
    case 2:
      _firmata->sendDigital(0,ARD_ON);  //R
      _firmata->sendDigital(1,ARD_OFF); //Y
      _firmata->sendDigital(2,ARD_OFF);  //G
      _firmata->sendDigital(3,ARD_ON); //R
      _firmata->sendDigital(4,ARD_OFF);
      _firmata->sendDigital(5,ARD_OFF);  //G
      _firmata->sendDigital(6,ARD_OFF);//R
      _firmata->sendDigital(7,ARD_OFF);
      _firmata->sendDigital(8,ARD_ON);  //G
      _firmata->sendDigital(9,ARD_ON);//R
      _firmata->sendDigital(10,ARD_OFF);
      _firmata->sendDigital(11,ARD_OFF);  //G
    break;
    case 3:
      _firmata->sendDigital(0,ARD_ON);  //R
      _firmata->sendDigital(1,ARD_OFF); //Y
      _firmata->sendDigital(2,ARD_OFF);  //G
      _firmata->sendDigital(3,ARD_ON); //R
      _firmata->sendDigital(4,ARD_OFF);
      _firmata->sendDigital(5,ARD_OFF);  //G
      _firmata->sendDigital(6,ARD_ON);//R
      _firmata->sendDigital(7,ARD_OFF);
      _firmata->sendDigital(8,ARD_OFF);  //G
      _firmata->sendDigital(9,ARD_OFF);//R
      _firmata->sendDigital(10,ARD_OFF);
      _firmata->sendDigital(11,ARD_ON);  //G
    break;
    }
    Task ++;
    if (Task >= TASKMAX)
        Task = 0;
}

void MainWindow::on_pushButton_clicked()
{
//    _firmata->sendSysEx(RU_THERE,{0});
}

void MainWindow::on_pushButton_2_clicked()
{
    _firmata->sendSysEx(SONAR_CONFIG,{0});
}


void MainWindow::on_pushButton_3_clicked()
{
    _firmata->sendSysEx(SONAR_CONFIG,{1});
}

void MainWindow::on_pushButton_4_clicked()
{
   ui->lcdNumber_4->display(_firmata->getAnalog(0));
}

void MainWindow::setupRealtimeDataDemo(QCustomPlot *customPlot)
{
   demoName = "Real Time Data Demo";

   // include this section to fully disable antialiasing for higher performance:
   /*
   customPlot->setNotAntialiasedElements(QCP::aeAll);
   QFont font;
   font.setStyleStrategy(QFont::NoAntialias);
   customPlot->xAxis->setTickLabelFont(font);
   customPlot->yAxis->setTickLabelFont(font);
   customPlot->legend->setFont(font);
   */
   customPlot->addGraph(); // blue line - left front sensor (Ultrasonic)
   customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
   customPlot->addGraph(); // red line - left rear sensor (Ultrasonic)
   customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));
   customPlot->addGraph(); // green line - IR Sensor
   customPlot->graph(2)->setPen(QPen(QColor(40, 225, 110)));


   QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
   timeTicker->setTimeFormat("%h:%m:%s");
   customPlot->xAxis->setTicker(timeTicker);
   customPlot->axisRect()->setupFullAxesBox();
   customPlot->yAxis->setRange(0, 100);

   // make left and bottom axes transfer their ranges to right and top axes:
   connect(customPlot->xAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->xAxis2, SLOT(setRange(QCPRange)));
   connect(customPlot->yAxis, SIGNAL(rangeChanged(QCPRange)), customPlot->yAxis2, SLOT(setRange(QCPRange)));

   // setup a timer that repeatedly calls MainWindow::realtimeDataSlot:
   connect(&dataTimer, SIGNAL(timeout()), this, SLOT(realtimeDataSlot()));
   dataTimer.start(0); // Interval 0 means to refresh as fast as possible
}

void MainWindow::realtimeDataSlot()
{
   static QTime time(QTime::currentTime());
   // calculate two new data points:
   double key = time.elapsed()/1000.0; // time elapsed since start of demo, in seconds
   static double lastPointKey = 0;
   if (key-lastPointKey > 0.002) // at most add point every 2 ms
   {
     // add data to lines:
     //Mofify these lines
     ui->customPlot->graph(0)->addData(key, leftFront);
     ui->customPlot->graph(1)->addData(key, leftRear);
     ui->customPlot->graph(2)->addData(key, frontSensor);
     // rescale value (vertical) axis to fit the current data:
     //ui->customPlot->graph(0)->rescaleValueAxis();
     //ui->customPlot->graph(1)->rescaleValueAxis(true);
     lastPointKey = key;
   }
   // make key axis range scroll with the data (at a constant range size of 8):
   ui->customPlot->xAxis->setRange(key, 8, Qt::AlignRight);
   ui->customPlot->replot();

   // calculate frames per second:
   static double lastFpsKey;
   static int frameCount;
   ++frameCount;
   /*
   if (key-lastFpsKey > 2) // average fps over 2 seconds
   {
     ui->statusBar->showMessage(
           QString("%1 FPS, Total Data points: %2")
           .arg(frameCount/(key-lastFpsKey), 0, 'f', 0)
           .arg(ui->customPlot->graph(0)->data()->size()+ui->customPlot->graph(1)->data()->size())
           , 0);
     lastFpsKey = key;
     frameCount = 0;
   }
   */
}

void MainWindow::robotController()
// distance = (leftFront+leftRear)/2
// heading = leftFront - leftRear
// 0 = parallel to the wall
// - = approaching
// + = leaving
// x = dont care
{
    /* Decision Table
     * frontSensor | distance  | heading | action
     *
     * >SAFEDISTANCE | >TARGETDISTANCE | APPROACHING (-) | STRAIGHT (0)
     *                                     PARALLEL         SMOOTHLEFT
     *                                      LEAVING         SHARPLEFT
     *
     * >SAFEDISTANCE | =TARGETDISTANCE | APPROACHING (-) | SMOOTHRIGHT
     *                                     PARALLEL         STRAIGHT
     *                                      LEAVING         SMOOTHLEFT
     *
     * >SAFEDISTANCE | <TARGETDISTANCE | APPROACHING (-) | SHARPRIGHT
     *                                     PARALLEL         SMOOTHRIGHT
     *                                      LEAVING         STRAIGHT
     *
     * <=SAFEDISTANCE | x | APPROACHING (-) | TURNLEFT    // THIS COULD MEAN NO WAY
     *                                     PARALLEL         TURNLEFT
     *                                      LEAVING         TURNLEFT
     * */

    distance = (leftFront+leftRear)/2;
    heading = leftFront - leftRear;

    if ((frontSensor > SAFEDISTANCE)&&(distance > TARGETDISTANCE)&&(heading < 0))
    {
        goStraight();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance > TARGETDISTANCE)&&(heading == 0))
    {
        goSmoothLeft();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance > TARGETDISTANCE)&&(heading > 0))
    {
        goSharpLeft();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance == TARGETDISTANCE)&&(heading < 0))
    {
        goSmoothRight();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance == TARGETDISTANCE)&&(heading == 0))
    {
        goStraight();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance == TARGETDISTANCE)&&(heading > 0))
    {
        goSmoothLeft();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance < TARGETDISTANCE)&&(heading < 0))
    {
        goSharpRight();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance < TARGETDISTANCE)&&(heading == 0))
    {
        goSmoothRight();
    }
    else if ((frontSensor > SAFEDISTANCE)&&(distance < TARGETDISTANCE)&&(heading > 0))
    {
        goStraight();
    }
    else if (frontSensor <= SAFEDISTANCE)
    {
        goTurnLeft();
    }
}

void MainWindow::goStraight()
{
    qDebug()<<"goStraight ";
    _firmata->sendDigital(LEFTDIR, ARD_LOW); // Control direction
    _firmata->sendPWM(LEFTPWM, SLOW); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_LOW);
    _firmata->sendPWM(RIGHTPWM, SLOW);
}

void MainWindow::goSmoothLeft()
{
    qDebug()<<"goSmoothLeft ";
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, TURNSLOW); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, CFAST);
}

void MainWindow::goSharpLeft()
{
    qDebug()<<"goSharpLeft ";
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, CSLOW); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, CFAST);
}

void MainWindow::goSmoothRight()
{
    qDebug()<<"goSmoothRight ";
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, CFAST); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, TURNSLOW);
}

void MainWindow::goSharpRight()
{
    qDebug()<<"goSharpRight ";
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, CFAST); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, CSLOW);
}

void MainWindow::goTurnLeft()
{
    qDebug()<<"goTurnLeft ";
    _firmata->sendDigital(LEFTDIR, ARD_HIGH); // Control direction
    _firmata->sendPWM(LEFTPWM, CFAST); // SPeed of motor

    _firmata->sendDigital(RIGHTDIR, ARD_HIGH);
    _firmata->sendPWM(RIGHTPWM, CSLOW);
}

