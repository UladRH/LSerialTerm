#include <iostream>

#include <QApplication>
#include <QFile>
#include <QtWidgets/QStyleFactory>

#include "MainWindow.h"

int main(int argc, char *argv[]) {
    qunsetenv("QT_DEVICE_PIXEL_RATIO");
    qputenv("QT_AUTO_SCREEN_SCALE_FACTOR", QByteArray("1"));

    QApplication qtApp(argc, argv);

    QFile File(":Stylesheet.qss");
    if (File.open(QFile::ReadOnly)) {
        QString StyleSheet = QLatin1String(File.readAll());
        qtApp.setStyleSheet(StyleSheet);
    }

    MainWindow mainWindow;
    mainWindow.show();

    return qtApp.exec();
}
