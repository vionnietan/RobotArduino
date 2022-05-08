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
    QTimer *timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_connectButton_4_clicked()));
//    timer->start(1000);
//    timer2 = new QTimer(this);
//    connect(timer2, SIGNAL(timeout()), this, SLOT(on_connectButton_4_clicked()));

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
        _firmata->sendDigitalPinMode(0, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(1, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(2, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(3, ARD_INPUT);
        //_firmata->sendDigitalPinMode(3, PIN_MODE_PULLUP);
        _firmata->sendDigitalPinReporting(3, ARD_INPUT);
//        _firmata->sendDigitalPinMode(4, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(5, ARD_OUTPUT);
//        _firmata->sendDigitalPinMode(6, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(7, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(8, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(9, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(10, ARD_OUTPUT);
        _firmata->sendDigitalPinMode(11, ARD_PWM);
        _firmata->sendDigitalPinMode(12, ARD_OUTPUT);
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

}
void MainWindow::onDigitalPinChanged(int pin)
{
    if (pin == 3)
    {
        if (_firmata->getDigital(pin))
        {
            ui->status->setText("High");
        }
        else
        {
            ui->status->setText("Low");
        }
    }
    qDebug()<<"digital pin"<<pin<<"changed. new value"<<_firmata->getDigital(pin);
//    _digitalPinVec[pin-2]->setValue(_firmata->getDigital(pin));
}

void MainWindow::onAnalogPinChanged(int pin)
{
//    if(pin < _analogPinVec.size())
//    {
//        _analogPinVec[pin]->setValue(_firmata->getAnalog(pin));
//    }
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
  if(Flag){
   _firmata->sendDigital(13,ARD_ON);
   qDebug() << "ARD_ON" << Flag;
  }
  else{
   _firmata->sendDigital(13,ARD_OFF);
   qDebug() << "ARD_OFF" << Flag;
  }
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
    _firmata->sendSysEx(RU_THERE,{0});
}

void MainWindow::on_connectButton_6_clicked()
{
    Flag = !Flag;
    if(Flag){
     _firmata->sendDigital(12,ARD_ON);
     qDebug() << "ARD_ON" << Flag;
    }
    else{
     _firmata->sendDigital(12,ARD_OFF);
     qDebug() << "ARD_OFF" << Flag;
    }
}

void MainWindow::on_connectButton_5_clicked()
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(flash()));
    timer->start(1000);

}

void MainWindow::flash(){
    Flag = !Flag;
    if(Flag){
     _firmata->sendDigital(13,ARD_ON);
     qDebug() << "ARD_ON" << Flag;
    }
    else{
     _firmata->sendDigital(13,ARD_OFF);
     qDebug() << "ARD_OFF" << Flag;
    }
}

void MainWindow::on_connectButton_7_clicked()
{
    timer->stop();
    qDebug() << "Timer Stop: ";
    _firmata->sendDigital(13,ARD_OFF);
}


void MainWindow::on_horizontalSlider_valueChanged(int value)
{
    _firmata->sendPWM(10,value);
    qDebug() << "Send PWM 10 " << value;
}

