#pragma once

#include <QtWidgets/QAbstractScrollArea>


class HexConsole : public QAbstractScrollArea {
Q_OBJECT
public:
    enum class DataDirection {
        In,
        Out
    };

    struct HexConsoleChunk {
        QByteArray data;
        DataDirection dir;
    };
public:
    HexConsole(QWidget *parent = nullptr);

    void append(QByteArray data, DataDirection direction);

    void showHex(bool show);

protected:
    void paintEvent(QPaintEvent *event);

private:
    QList<HexConsoleChunk> mData;
    bool mShowHex = false;
};
