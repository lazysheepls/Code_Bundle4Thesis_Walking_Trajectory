#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //Screen Size fixed for iphone 5s:640x1136
    w.show();

    return a.exec();
}
