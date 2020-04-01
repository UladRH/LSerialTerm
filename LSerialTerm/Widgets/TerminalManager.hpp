#pragma once

#include <QtWidgets/QLayout>
#include <QtWidgets/QAbstractScrollArea>

class TerminalManager : public QWidget {
Q_OBJECT

public:
    enum TerminalView {
        Log,
        HexLog,
        Naive
    };

    enum MessageDirection {
        In,
        Out
    };

    struct Message {
        QByteArray data;
        MessageDirection direction;
    };

public:
    TerminalManager(QWidget *parent = nullptr);

    void changeView(TerminalView view);

    void append(MessageDirection direction, QByteArray data);

    void clear();

private:
    QList<Message> mMsgs;

    QVBoxLayout *mLayout = nullptr;

    QAbstractScrollArea *mCurrentView = nullptr;
    QAbstractScrollArea *mLogTerminal = nullptr;
    QAbstractScrollArea *mHexLogTerminal = nullptr;
};
