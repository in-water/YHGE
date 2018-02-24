#include "mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.setFixedSize(900,700);
    //QObject::connect(&w,&QPushButton::clicked,&QApplication::quit);
    w.show();
    return a.exec();
}
