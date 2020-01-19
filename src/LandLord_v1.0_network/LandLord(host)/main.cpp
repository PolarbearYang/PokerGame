#include "mainwindow.h"
#include <QApplication>
#include <QtGui>
#include <QTextCodec>

int count=0;
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //a.setQuitOnLastWindowClosed(true);
    //QTextCodec::setCodecForCStrings(QTextCodec::codecForName("GBK"));
    w.setFixedSize(w.width(),w.height());
    w.show();
    return a.exec();
}
