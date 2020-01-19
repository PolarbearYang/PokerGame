#include "form4.h"
#include <QApplication>
#include "rform0.h"
#include "rform1.h"
#include "welcome.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //Form w;
    welcome w;
    w.show();

    return a.exec();
}
