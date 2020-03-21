#pragma once

#include <QDialog>
#include <QtSerialPort/QSerialPort>

#include "ui_NewConnectionWindow.h"

class NewConnectionWindow : public QDialog {
Q_OBJECT
public:
    NewConnectionWindow(QWidget *parent = nullptr);

    ~NewConnectionWindow();

    QString getPort();

    int getBaudRate();

    int getDataBits();

    QSerialPort::StopBits getStopBits();

    QSerialPort::Parity getParity();

private slots:

    void buttonConnectClicked();

private:
    Ui::Dialog mUi;
    QList<QSerialPortInfo> mPorts;
};
