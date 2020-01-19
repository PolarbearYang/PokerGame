#include "Drawbtnlab.h"


gamelabel::gamelabel(QWidget *parent) : QPushButton(parent)
{
    this ->setMouseTracking(true);
}

//按钮初始化函数
gamelabel::gamelabel(QString &path1, QString &path2,int w ,int h, QWidget *parent ):

    QPushButton(parent)
    {
        a = w;
        b = h;
        Img1 = QPixmap(path1);
        Img2 = QPixmap(path2);
        setFixedSize(QSize(w,h));
    }

gamelabel::~gamelabel()
    { }


//图片显示函数
void gamelabel::paintEvent(QPaintEvent *)
{
    QPainter painter(this); //
    switch (m_status)
    {
        case NORMAL:
        painter.drawPixmap(rect(),Img1,QRect(0,0,a,b));
        break;

        case PRESSED:
        painter.drawPixmap(rect(),Img2,QRect(0,0,a,b));
    }   
}

bool gamelabel::event(QEvent *e)
{
    if (e->type()==QEvent::MouseButtonPress)
    {
        m_status = PRESSED;
        update();
       // flag = 1;
    }
    return QPushButton::event(e);
}


void gamelabel::enterEvent(QEvent *)
{
    m_status = PRESSED;
    update();
}


void gamelabel::leaveEvent(QEvent *)
{
    //if (flag !=1){
    m_status = NORMAL;
    update();
   // }
}
