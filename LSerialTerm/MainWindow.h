#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>

#include "ui_MainWindow.h"
#include "HexConsole.h"

class MainWindow : public QMainWindow {
Q_OBJECT
public:
    MainWindow(QWidget *parent = nullptr);

    ~MainWindow();

private slots:

    void buttonConnectionClicked();

    void buttonSendClicked();

    void switchShowHex();

    void readData();

private:
    Ui::MainWindow mUi;
    QSerialPort *mPort = nullptr;
    HexConsole *mConsole = nullptr;
    bool mShowHex = false;
};
