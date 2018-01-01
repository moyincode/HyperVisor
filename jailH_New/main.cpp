/*
 * This module is Entry point to JailHouse GUI application
 *
 *  Author :
 *
 *  Copyright (C) 2017 , All Rights Reserved.
 */

#include "mainwindow.h"
#include <QApplication>
#include "eula.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
//    MainWindow w;
//    w.show();
    Eula e ;
    e.show();

    return a.exec();
}
