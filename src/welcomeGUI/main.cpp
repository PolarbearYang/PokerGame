#include "MenuPanel.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    welcomewin w;
    w.show();

    return a.exec();
}
