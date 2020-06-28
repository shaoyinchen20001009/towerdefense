#include "mainwindow1.h"
#include <QApplication>
#include<QString>

int main(int argc, char *argv[])
{
    setbuf(stdout, NULL);
    QApplication a(argc, argv);
    MainWindow1 w;
    w.show();


    return a.exec();
}
