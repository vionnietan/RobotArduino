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
    Flag = false;
    setupRealtimeDataDemo(ui->customPlot);
//    analogPinWidget->setDisabled(true);
//    _digitalPinWidget->setDisabled(true);
}

MainWindow::~MainWindow()
{

}

void MainWindow::onConnectButtonClicked()
{
    if(_firmata->open(ui->comboBox->currentText()))
    {
        statusBar()->showMessage(tr("[Notice] Successfully opened connection"), 5000);
    }
    else
    {
        statusBar()->showMessage(tr("[Error] Could not open connection"), 5000);
    }

}
void MainWindow::onDisconnectButtonClicked()
{
    _firmata->close();
    _connectButton->show();
    _disconnectButton->hide();
    _firmwareLabel->setText("");
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
//    qDebug()<<"firmate initialized"<<majorVersion<<minorVersion<<firmwareName;
//    _analogPinWidget->setEnabled(true);
//    _digitalPinWidget->setEnabled(true);
//    statusBar()->showMessage(tr("initialized"), 5000);

//    QString statusText = QString::number(majorVersion)+"."+QString::number(minorVersion);
    _firmata->sendDigitalPinMode(13, ARD_OUTPUT);
    _firmata->sendDigitalPinMode(12, ARD_OUTPUT);
    _firmata->sendAnalogPinReporting(0, ARD_ANALOG);
    _firmata->sendAnalogPinReporting(1, ARD_ANALOG);

}
void MainWindow::onDigitalPinChanged(int pin)
{
    qDebug()<<"digital pin"<<pin<<"changed. new value"<<_firmata->getDigital(pin);
    if(pin==2){
        if(_firmata->getDigital(pin)){
// check if input is HIGH
        }
        else{
// else input is LOW
        }

    }
//    _digitalPinVec[pin-2]->setValue(_firmata->getDigital(pin));

}

void MainWindow::onAnalogPinChanged(int pin)
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
        ui->lcdNumber->display((6762.0/(value-9.0))-4.0);
        x1 = ((6762.0/(value-9.0))-4.0);

    }
    else if (pin==1){
        int value = _firmata->getAnalog(pin);
        qDebug()<<"analog pin"<<pin<<"changed. new value"<<_firmata->getAnalog(pin);

//        ui->lcdNumber_2->display(5.0* value*100.0/1024.0);
          ui->lcdNumber_2->display((6762.0/(value-9.0))-4.0);
          x2 = ((6762.0/(value-9.0))-4.0);

    }
}

void MainWindow::onSysExReceived(const QVector<unsigned char> message)
{
    qDebug()<<"sysExReceived"<<message;
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

void MainWindow::on_connectButton_4_clicked()
{
  Flag = !Flag;
  if(Flag)
   _firmata->sendDigital(13,ARD_ON);
  else
   _firmata->sendDigital(13,ARD_OFF);

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
   customPlot->addGraph(); // blue line
   customPlot->graph(0)->setPen(QPen(QColor(40, 110, 255)));
   customPlot->addGraph(); // red line
   customPlot->graph(1)->setPen(QPen(QColor(255, 110, 40)));

   QSharedPointer<QCPAxisTickerTime> timeTicker(new QCPAxisTickerTime);
   timeTicker->setTimeFormat("%h:%m:%s");
   customPlot->xAxis->setTicker(timeTicker);
   customPlot->axisRect()->setupFullAxesBox();
   customPlot->yAxis->setRange(0, 40);

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
     ui->customPlot->graph(0)->addData(key, x1);
     ui->customPlot->graph(1)->addData(key, x2);
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
 }
