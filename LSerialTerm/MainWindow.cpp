#include "MainWindow.h"
#include "ui_MainWindow.h"
#include "NewConnectionWindow.h"
#include "HexConsole.h"

#include <QtSerialPort/QSerialPortInfo>
#include <QShortcut>

inline QString _getParityStr(QSerialPort::Parity parity) {
    switch (parity) {
        case QSerialPort::Parity::NoParity:
            return QString("without parity");
        case QSerialPort::Parity::OddParity:
            return QString("odd parity");
        case QSerialPort::Parity::EvenParity:
            return QString("even parity");
        case QSerialPort::SpaceParity:
            return QString("space parity");
        case QSerialPort::MarkParity:
            return QString("mark parity");
    }

    return QString("");
}

inline QString _getStopBitsStr(QSerialPort::StopBits stopBits) {
    switch (stopBits) {
        case QSerialPort::OneStop:
            return QString("1 stop bit");
        case QSerialPort::OneAndHalfStop:
            return QString("1.5 stop bits");
        case QSerialPort::TwoStop:
            return QString("2 stop bits");
    }

    return QString("");
}


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    mUi.setupUi(this);
    mPort = new QSerialPort(this);
    mConsole = new HexConsole(this);

    mUi.verticalLayout->insertWidget(1, mConsole);

    connect(mUi.buttonConnection, SIGNAL (clicked()), this, SLOT (buttonConnectionClicked()));
    connect(mUi.buttonSend, SIGNAL (clicked()), this, SLOT (buttonSendClicked()));
    connect(mPort, SIGNAL (readyRead()), this, SLOT (readData()));

    auto returnShortcut = new QShortcut(QKeySequence("Return"), mUi.centralwidget);
    connect(returnShortcut, SIGNAL(activated()), mUi.buttonSend, SLOT(click()));
}

MainWindow::~MainWindow() {}

void MainWindow::buttonConnectionClicked() {
    auto dialog = NewConnectionWindow(this);

    if (dialog.exec() != QDialog::DialogCode::Accepted) {
        return;
    }

    QSerialPort port(dialog.getPort());
    QSerialPortInfo portInfo(port);

    mUi.buttonConnection->setText(QString("%1 \n\r %2 • %3 baud • %4 bits • %5 • %6").arg(
        portInfo.description(),
        dialog.getPort(),
        QString::number(dialog.getBaudRate()),
        QString::number(dialog.getDataBits()),
        _getParityStr(dialog.getParity()),
        _getStopBitsStr(dialog.getStopBits())
    ));

    if (mPort->isOpen()) {
        mPort->close();
    }

    mPort->setPortName(port.portName());
    mPort->setBaudRate(dialog.getBaudRate());
    mPort->setDataBits(static_cast<QSerialPort::DataBits>(dialog.getDataBits()));
    mPort->setParity(dialog.getParity());
    mPort->setStopBits(static_cast<QSerialPort::StopBits>(dialog.getDataBits()));

    mPort->open(QIODevice::ReadWrite);
}

void MainWindow::buttonSendClicked() {
    auto text = mUi.editSend->text();

    if (text.length() > 0 && mPort->isOpen()) {
        text += '\n';
        mPort->write(text.toStdString().c_str());
        mConsole->append(text.toStdString().c_str(), HexConsole::DataDirection::Out);
        mUi.editSend->clear();
    }
}

void MainWindow::readData() {
    QByteArray data = mPort->readAll();
    mConsole->append(data, HexConsole::DataDirection::In);
}
