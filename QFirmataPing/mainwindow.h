#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTableWidget>
#include <QComboBox>
#include <QCheckBox>
#include <QLabel>
#include <QPushButton>
#include <QScrollArea>
#include <QSpinBox>
#include <QSignalMapper>
#include <QModelIndex>
#include "qcustomplot.h"

#include "analogpin.h"
#include "digitalpin.h"


#define SAFEDISTANCE 15 //front
#define TARGETDISTANCE 10 //from side wall
#define TARGET 30
// Assume left motor is A
// A1B pin 10
// A1A pin 5
// B1A pin 11
// B1B pin 3
#define LEFTPWM 5
#define LEFTDIR 10
#define RIGHTPWM 11
#define RIGHTDIR 3

#define FAST 125
#define SLOW 75
#define CFAST 255-FAST
#define CSLOW 255-SLOW
#define TURNSLOW 50
#define DELAYTIME 200
#define STOP 0
#include "qfirmata.h"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    void setupRealtimeDataDemo(QCustomPlot *customPlot);
    ~MainWindow();
    void goStraight();
    void goSmoothLeft();
    void goSharpLeft();
    void goSmoothRight();
    void goSharpRight();
    void goTurnLeft();

private:
    Ui::MainWindow *ui;
    QFirmata *_firmata;
    int _firstDigitalPinIndex;

    QTableWidget *_configTableWidget;
    QComboBox *_portComboBox;
    QVector<QSpinBox*> _ioAnalogInputSpinBoxVec;
    QVector<QComboBox*> _ioDigitalPinModeComboBoxVec;
    QVector<QCheckBox*> _ioDigitalCheckBoxVec;
    QVector<QSlider*> _ioDigitalPinSliderVec;
    QVector<QSpinBox*> _ioDigitalPinSpinBoxVec;

    QPushButton *_connectButton;
    QPushButton *_disconnectButton;
    QLabel *_firmwareLabel;

    QScrollArea *_ioDigitalContainerWidget;
    QScrollArea *_ioAnalogInputContainerWidget;
    QWidget *_analogPinWidget;
    QWidget *_digitalPinWidget;

    QVector<AnalogPin*> _analogPinVec;
    QVector<DigitalPin*> _digitalPinVec;
    QString address;
    bool Flag;
    int Task;
    //double var1;
    //double var2;
    QString demoName;
    QTimer dataTimer;
    double frontSensor;
    double leftFront;
    double leftRear;
    double heading; // direction
    double distance;


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();

    void onPinModeComboBoxChange(int index);
    void onDigitalPinWidgetValueChanged(unsigned int id, unsigned int value, bool pwm);

    void onFirmwareVersionReceived(const int majorVersion, const int minorVersion);
    void onFirmwareNameReceived(QString firmwareName);
    void onInitialized(const int majorVersion, const int minorVersion, QString firmwareName);
    void onDigitalPinChanged(int pin);
    void onAnalogPinChanged(int pin);
    void onSysExReceived(const QVector<unsigned char> message);
    void onStringReceived(const QString message);
    void onAnalogPinReportinChange(unsigned int pin, bool value);
    void onDigitalPinModeChange(unsigned int pin, int mode);
    void on_connectButton_4_clicked();
    void on_connectButton_2_clicked();
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void realtimeDataSlot();
    void robotController();
};

#endif // MAINWINDOW_H
