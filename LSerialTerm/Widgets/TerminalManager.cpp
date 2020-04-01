#include "TerminalManager.hpp"
#include "HexConsole.h"

#include <QtWidgets/QVBoxLayout>
#include <utility>

TerminalManager::TerminalManager(QWidget *parent) : QWidget(parent) {
    mLayout = new QVBoxLayout(this);
    mLayout->setMargin(0);

    mLogTerminal = new HexConsole(&mMsgs, false, this);
    mHexLogTerminal = new HexConsole(&mMsgs, true, this);

    mLogTerminal->hide();
    mHexLogTerminal->hide();

    changeView(Log);
}

void TerminalManager::changeView(TerminalManager::TerminalView view) {
    if (mCurrentView != nullptr) {
        mLayout->removeWidget(mCurrentView);
        mCurrentView->hide();
    }

    switch (view) {
        case Log:
            mCurrentView = mLogTerminal;
            break;
        case HexLog:
            mCurrentView = mHexLogTerminal;
            break;
        case Naive:
            break;
    }

    mLayout->addWidget(mCurrentView);
    mCurrentView->show();
}

void TerminalManager::append(TerminalManager::MessageDirection direction, QByteArray data) {
    mMsgs.append(Message{std::move(data), direction});
    mCurrentView->viewport()->update();
}

void TerminalManager::clear() {
    mMsgs.clear();
    mCurrentView->viewport()->update();
}
