#include "MenuPanel.h"

class settingpanel;

//对主界面的GUI的设计类，没啥好看的
welcomewin::welcomewin(QWidget *parent)
    : QWidget(parent)
{
    QPushButton *close = new QPushButton(this);
    close -> setStyleSheet("QPushButton{background-image:url(:/images/close.png);background-repeat:none;background-position:center;ba}");
    connect(close,  SIGNAL(clicked()),  this,  SLOT(close()));

    QLabel *textlab = new QLabel(this);
    textlab -> setStyleSheet("QLabel{image:url(:/images/title.png);image-position: left}");

    //设置按钮
    QString setpath1 =":/images/setting_1.png";
    QString setpath2 =":/images/setting.png";
    gamelabel *settingbutton = new gamelabel(setpath1,setpath2,200,200,this);
    settingbutton ->setMouseTracking(true);
    connect(settingbutton,SIGNAL(clicked()),this,SLOT(onsettingclick()));

    QString g1 =":/images/z1.png";
    QString g2 =":/images/d1.png";
    gamelabel *cenlabel = new gamelabel(g1,g2,500,200,this);
    connect(cenlabel,SIGNAL(clicked()),this,SLOT(Launch21point()));

    QString zx1 =":/images/z2.png";
    QString zx2 =":/images/d2.png";
    gamelabel *zxLabel = new gamelabel(zx1,zx2,500,200,this);
    connect(zxLabel,SIGNAL(clicked()),this,SLOT(LaunchLandlord()));


    flowlab = new QLabel(this);

    strScrollCation = QString("welcome to this game and click the game below to get start!");
    flowlab -> setAlignment(Qt::AlignCenter);
    timer = new QTimer();
    timer ->setInterval(200);
    timer ->start();
    connect(timer,  SIGNAL(timeout()),  this,  SLOT(onTimerout()));
    flowlab -> setStyleSheet("QLabel{content: width: 0;height: 3px;background: #337ab7;position: absolute;bottom: 0;left: 50%;transition: all .2s;}");

    //顶部的水平布局
    QHBoxLayout *layout1 = new QHBoxLayout;
    layout1 -> addWidget(textlab);
    layout1 -> addWidget(settingbutton);
    layout1 -> setContentsMargins(0,0,0,0);


    //总体的布局
    QVBoxLayout *main_layout =  new QVBoxLayout;
    main_layout -> addWidget(close);
    main_layout -> addLayout(layout1);
    main_layout -> addWidget(flowlab);
    main_layout -> addWidget(cenlabel);
    main_layout -> addWidget(zxLabel);

    main_layout -> setSpacing(0);//上下距离调整
    main_layout -> setMargin(0);//左右距离调整


    //设置主界面的背景
    QPixmap pixmap(":/images/mainbg.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this -> setPalette(palette);
    this -> setLayout(main_layout);
    this -> setGeometry(700,200,400,600);
    this -> setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint); //去掉标题栏
}

//跑马灯槽函数
void welcomewin::onTimerout()
{
    static int nPos = 0;
    // 当截取的位置比字符串长时，从头开始
    if (nPos > strScrollCation.length())
        nPos = 0;
    flowlab ->setText(strScrollCation.mid(nPos));
    nPos++;
}


//设置面版槽函数
void welcomewin::onsettingclick()
{
    setting -> show();
}



welcomewin::~welcomewin()
{

}

void welcomewin::Launch21point(){
    player1=new Form2;
    player1->show();
    this->close();
}

void welcomewin::LaunchLandlord(){
    player2=new Form1;
    player2->show();
    this->close();
}
