#include "mybutton.h"

mybutton::mybutton()
{
    setStyleSheet("QPushButton{color:white；background:black}");
}

void mybutton::enterEvent(QEvent *)
{
    setIcon(*pix_blue);
}

void mybutton::leaveEvent(QEvent *)
{
    setIcon(*pix);
}
