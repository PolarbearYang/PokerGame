#ifndef MYBUTTON_H
#define MYBUTTON_H

#include <QPushButton>

class mybutton:public QPushButton
{
    Q_OBJECT
public:
    QPixmap *pix;
    QPixmap *pix_blue;
    mybutton();
protected:
    void enterEvent(QEvent *);
    void leaveEvent(QEvent *);
};

#endif // MYBUTTON_H
