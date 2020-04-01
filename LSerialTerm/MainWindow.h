#pragma once

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <LSerialTerm/Widgets/TerminalManager.hpp>

#include "ui_MainWindow.h"

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
    TerminalManager *mConsole = nullptr;
    bool mShowHex = false;
};
