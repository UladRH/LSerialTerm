#include "HexConsole.h"

#include <QPainter>
#include <QPaintEvent>
#include <QScrollBar>
#include <utility>

// TODO: Cleanup

HexConsole::HexConsole(QList<TerminalManager::Message> *data, bool showHex, QWidget *parent)
    : QAbstractScrollArea(parent) {
    setFont(QFont("Consolas", 11));
    mShowHex = showHex;
    mData = data;
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

    int pxOfsX = verticalScrollBar()->value() * charH;

    int fromDl = 0,
        fromDlOffset = 0,
        toDl = mData->size();

    int linesHeight = 0;
    for (auto &i : *mData) {
        int dlHeight = int(ceil(double(i.data.size()) / chars) * charH + linePad);

        if (linesHeight < pxOfsX) {
            fromDl++;
            fromDlOffset += dlHeight;
        }

        if (linesHeight > pxOfsX + height()) {
            toDl--;
        }

        linesHeight += dlHeight;
    }
    linesHeight /= charH;
    linesHeight -= height() / charH;

    if (fromDl > 0) {
        fromDl--;
        fromDlOffset -= int(ceil(double(mData->at(fromDl).data.size()) / chars) * charH + linePad);
    }

    if (verticalScrollBar()->value() == verticalScrollBar()->maximum()) {
        verticalScrollBar()->setRange(0, linesHeight);
        verticalScrollBar()->setValue(verticalScrollBar()->maximum());
    } else {
        verticalScrollBar()->setRange(0, linesHeight);
    }

    int yOffset = -pxOfsX + fromDlOffset;

    painter.fillRect(event->rect(), viewport()->palette().color(QPalette::Base));

    for (int i = fromDl; i < toDl; ++i) {
        QColor bgColor = viewport()->palette().color(QPalette::Base);
        if (mData->at(i).direction == TerminalManager::In) {
            bgColor = QColor(232, 255, 232);
        } else if (mData->at(i).direction == TerminalManager::Out) {
            bgColor = QColor(255, 232, 232);
        }

        for (int offset = 0; offset < mData->at(i).data.size(); offset += chars) {
            painter.fillRect(QRect(0, yOffset, event->rect().width(), charH), bgColor);
            int yCord = linePad + charH + yOffset - linePad * 2;

            painter.drawText(10, yCord, mData->at(i).data.mid(offset, chars).toStdString().c_str());

            if (mShowHex) {
                painter.drawText(div + 10, yCord, mData->at(i).data.mid(offset, chars).toHex(' ').toUpper());
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
