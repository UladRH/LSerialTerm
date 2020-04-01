#pragma once

#include <QtWidgets/QAbstractScrollArea>
#include "TerminalManager.hpp"


class HexConsole : public QAbstractScrollArea {
Q_OBJECT
public:
    HexConsole(QList<TerminalManager::Message> *data, bool showHex, QWidget *parent = nullptr);

    void showHex(bool show);

protected:
    void paintEvent(QPaintEvent *event) override;

private:
    QList<TerminalManager::Message> *mData;
    bool mShowHex = false;
};
