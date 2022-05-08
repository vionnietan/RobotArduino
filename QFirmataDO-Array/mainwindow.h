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

#include "analogpin.h"
#include "digitalpin.h"

#include "qfirmata.h"
namespace Ui {
class MainWindow;
}


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
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
    int LEDState[2][10] = {{ARD_OFF,ARD_ON,ARD_OFF,ARD_ON,ARD_OFF,ARD_ON,
                           ARD_OFF,ARD_ON,ARD_OFF,ARD_ON},
                           {ARD_OFF,ARD_ON,ARD_OFF,ARD_ON,ARD_OFF,ARD_ON,
                            ARD_OFF,ARD_ON,ARD_OFF,ARD_ON}};
    int LEDpin[10] = {3,4,5,6,7,8,9,10,11,12};
    int State = 0;

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

    void onAnalogPinReportinChange(unsigned int pin, bool value);
    void onDigitalPinModeChange(unsigned int pin, int mode);
    void on_connectButton_4_clicked();
    void on_connectButton_2_clicked();
    void on_connectButton_3_clicked();
};

#endif // MAINWINDOW_H
