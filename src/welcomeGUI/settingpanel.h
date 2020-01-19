#ifndef SETTINGPANEL_H
#define SETTINGPANEL_H

#include<game.h>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QTimer>
#include<Drawbtnlab.h>
#include<QSlider>


class settingpanel : public QWidget
{
    Q_OBJECT
public:
    settingpanel(QWidget *parent = 0);
    ~settingpanel();
    gamelabel *headpicframe;
    //gamelabel *modelchoose_sta;
    //gamelabel *modelchoose_con;
    //改变头像

    QString headpath;
   // bool sta =true;
   // bool con =false;//判断是否选中
    void init();
private:
    QLabel *lab;
    QSlider *volum;

    /*QString co_1 = ":/images/lian2.png";
    QString co_2 = ":/images/lian1.png";
    QString sa_1 = ":/images/dan2.png";
    QString sa_2 = ":/images/dan1.png";
    */

public slots:
    void setLabelText(int pos);
    void openfile();
    void modelstaclick();
    void modelconclick();
};

#endif // SETTINGPANEL_H
