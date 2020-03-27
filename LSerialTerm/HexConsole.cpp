#include "HexConsole.h"

#include <QPainter>
#include <QPaintEvent>
#include <QScrollBar>

HexConsole::HexConsole(QWidget *parent) : QAbstractScrollArea(parent) {
    setFont(QFont("Consolas", 11));
}

void HexConsole::append(QByteArray data, DataDirection direction) {
    mData.append(HexConsoleChunk{.data = data, .dir = direction});
    viewport()->update();
}

void HexConsole::showHex(bool show) {
    mShowHex = show;
    viewport()->update();
}

void HexConsole::paintEvent(QPaintEvent *event) {
    QPainter painter(viewport());

    int charH = fontMetrics().height(),
        charW = fontMetrics().maxWidth() / 2;

    int totalChars = (width() - 40) / charW,
        chars = mShowHex
                ? ((totalChars - (totalChars / 4)) / 3)
                : (totalChars + 1);

    int div = 20 + chars * charW,
        linePad = charH / 4;

    int linesHeight = 0;
    for (auto &i : mData) {
        linesHeight += int(ceil(double(i.data.size()) / chars) * charH + linePad);
    }
    linesHeight /= charH;
    linesHeight -= height() / charH;

    verticalScrollBar()->setRange(0, linesHeight);

    int pxOfsX = verticalScrollBar()->value() * charH;

    int yOffset = -pxOfsX;

    painter.fillRect(event->rect(), viewport()->palette().color(QPalette::Base));

    for (int i = 0; i < mData.size(); ++i) {
        QColor bgColor = viewport()->palette().color(QPalette::Base);
        if (mData[i].dir == DataDirection::In) {
            bgColor = QColor(232, 255, 232);
        } else if (mData[i].dir == DataDirection::Out) {
            bgColor = QColor(255, 232, 232);
        }

        for (int offset = 0; offset < mData[i].data.size(); offset += chars) {
            painter.fillRect(QRect(0, yOffset, event->rect().width(), charH), bgColor);
            int yCord = linePad + charH + yOffset - linePad * 2;

            painter.drawText(10, yCord, mData[i].data.mid(offset, chars).toStdString().c_str());

            if (mShowHex) {
                painter.drawText(div + 10, yCord, mData[i].data.mid(offset, chars).toHex(' ').toUpper());
            }

            yOffset += charH;
        }
        yOffset += linePad;
    }

    if (mShowHex) {
        painter.setPen(Qt::gray);
        painter.drawLine(div, event->rect().top(), div, height());
    }
}
