#include "NewConnectionWindow.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QMessageBox>

NewConnectionWindow::NewConnectionWindow(QWidget *parent) : QDialog(parent) {
    mUi.setupUi(this);

    setFont(QFont("Segoe UI", 12));

    connect(mUi.buttonConnect, SIGNAL (clicked()), this, SLOT (buttonConnectClicked()));

    mPorts = QSerialPortInfo::availablePorts();

    mUi.selectPort->clear();
    for (auto &port : mPorts) {
        mUi.selectPort->addItem(QString("%1\n\r%2").arg(port.systemLocation(), port.description()));
    }
}

NewConnectionWindow::~NewConnectionWindow() {}

void NewConnectionWindow::buttonConnectClicked() {
    if (this->getBaudRate() == 0) {
        QMessageBox box;
        box.setText("Entered incorrect baud rate");
        box.setIcon(QMessageBox::Icon::Critical);
        box.setStandardButtons(QMessageBox::Ok);
        box.exec();
    } else {
        this->accept();
    }
}

QString NewConnectionWindow::getPort() {
    return mPorts[mUi.selectPort->currentIndex()].systemLocation();
}

int NewConnectionWindow::getBaudRate() {
    return mUi.selectBaudRate->currentText().toUInt();
}

int NewConnectionWindow::getDataBits() {
    return mUi.selectDataBits->currentText().toUInt();
}

QSerialPort::StopBits NewConnectionWindow::getStopBits() {
    switch (mUi.selectStopBits->currentIndex()) {
        case 0:
            return QSerialPort::StopBits::OneStop;
        case 1:
            return QSerialPort::StopBits::OneAndHalfStop;
        case 2:
            return QSerialPort::StopBits::TwoStop;
    }

    return QSerialPort::StopBits::OneStop;
}

QSerialPort::Parity NewConnectionWindow::getParity() {
    switch (mUi.selectParity->currentIndex()) {
        case 0:
            return QSerialPort::Parity::NoParity;
        case 1:
            return QSerialPort::Parity::OddParity;
        case 2:
            return QSerialPort::Parity::EvenParity;
    }

    return QSerialPort::Parity::NoParity;
}
