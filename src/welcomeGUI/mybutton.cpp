#include "Drawbtnlab.h"


mybutton::mybutton(QWidget *parent) : QPushButton (parent)
{
    this ->setMouseTracking(true);

}

//按钮初始化函数
mybutton::mybutton(QString &path1, QString &path2, QWidget *parent):

    QPushButton (parent)
    {
        Img1 = QPixmap(path1);
        Img2 = QPixmap(path2);
        QSize sz = Img1.size();
        setFixedSize(QSize(sz.width(),sz.height()));
    }

mybutton::~mybutton()
    { }

    //图片显示函数
void mybutton::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    int W = width();    //不知道为什么在selectwin中很受影响,只能显示一半(已解决<!--size设置反了--->)
    int H = height();

    switch (m_status)
    {
        case NORMAL:
        painter.drawPixmap(rect(),Img1,QRect(0,0,W,H));
        break;

        case PRESSED:
        painter.drawPixmap(rect(),Img2,QRect(0,0,W,H));
    }

}

//鼠标响应事件
bool mybutton::event(QEvent *e)
{
    if (e->type()==QEvent::MouseButtonPress)
    {   m_status = PRESSED;
        update();

    }else if (e->type()==QEvent::MouseMove) {
        m_status = PRESSED;
        update();
    }

    return QPushButton::event(e);
}

void mybutton::leaveEvent(QEvent *)
{
        m_status = NORMAL;
        update();

}
