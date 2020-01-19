#ifndef DRAWBTNLAB_H
#define DRAWBTNLAB_H

#include <QObject>
#include <QPushButton>
#include<QPainter>
#include<QMouseEvent>

//按钮组件绘制规则
class gamelabel : public QPushButton
{
public:
    gamelabel(QWidget *parent = 0);
    gamelabel(QString &path1,QString &path2,int a,int b, QWidget *parent = 0);
    ~gamelabel();
    enum labsta{NORMAL,PRESSED};
    void paintEvent(QPaintEvent *event);
    void enterEvent(QEvent *event);
    void leaveEvent(QEvent *event);
    bool event(QEvent *event);
    int flag = 0;   //判断鼠标点击，如果点击则不能再变换图形

private:
    QPixmap Img1 ;
    QPixmap Img2 ;
    int a;  //长
    int b;  //宽
    labsta m_status = NORMAL;

};

#endif // DRAWBTNLAB_H
