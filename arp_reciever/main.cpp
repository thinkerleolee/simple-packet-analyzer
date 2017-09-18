//
// Created by thinkerleo on 17-9-16.
// 程序的入口，负责激活窗体
//

#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();
}
