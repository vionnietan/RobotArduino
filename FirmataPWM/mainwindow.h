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
#include <QTimer>
#include <thread>

#include "analogpin.h"
#include "digitalpin.h"

#include "qfirmata.h"
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

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QFirmata *_firmata;


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

    bool LSense;
    bool RSense;
    bool CSense;
    int _firstDigitalPinIndex;
    //-----------------------------
    float Distance;

    int enA = 10;
    int in1 = 9;
    int in2 = 8;

    int enB = 5;
    int in3 = 7;
    int in4 = 6;
    void RobotForward(int delay);


private slots:
    void onConnectButtonClicked();
    void onDisconnectButtonClicked();
    void onFirmwareVersionReceived(const int majorVersion, const int minorVersion);
    void onFirmwareNameReceived(QString firmwareName);
    void onInitialized(const int majorVersion, const int minorVersion, QString firmwareName);
    void onDigitalPinChanged(int pin);
    void onAnalogPinChanged(int pin);
    void onSysExReceived(const QVector<unsigned char> message);
    void onDigitalPinWidgetValueChanged(unsigned int id, unsigned int value, bool pwm);
    void onAnalogPinReportinChange(unsigned int pin, bool value);
//    void on_horizontalSlider_valueChanged(int valueA);
//    void on_horizontalSlider_2_valueChanged(int valueB);
//    void demoOne();
//    void demoTwo();
//    void loop();
    void goStraight();
    void goRight();
    void goRightLow();
    void goLeft();
    void goLeftLow();
    void Park();
    void Neutral();
    void Reverse();
    void Test();
    void RobotController();
    void on_horizontalSlider_valueChanged(int value);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_pushButton_4_clicked();
    void on_pushButton_5_clicked();
};

#endif // MAINWINDOW_H
