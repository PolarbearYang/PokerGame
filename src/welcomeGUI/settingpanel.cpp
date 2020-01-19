#include "settingpanel.h"
#include <QFileDialog>
#include <QRadioButton>
#include <string>

//对于设置的排版设计
QString str2qstr(const std::string str)
{
    return QString::fromLocal8Bit(str.data());
}

settingpanel::settingpanel(QWidget *parent) : QWidget(parent)
{
    headpicframe = new gamelabel(headpath,headpath,200,200,this);
    connect(headpicframe,SIGNAL(clicked()),this,SLOT(openfile()));

    QRadioButton *modelchoose_con = new QRadioButton("联网模式",this);
    QRadioButton *modelchoose_sta = new QRadioButton("单机模式",this);

    connect(modelchoose_sta,SIGNAL(clicked()),this,SLOT(modelstaclick()));
    connect(modelchoose_con,SIGNAL(clicked()),this,SLOT(modelstaclick()));


    volum = new QSlider(Qt::Horizontal,this);
    volum ->setMinimum(0);
    volum ->setMaximum(100);
    volum ->setValue(50);
    volum -> update();
    volum->setStyleSheet("QSlider::groove:horizontal{ margin:0 10;border-radius:3px}\
                          QSlider::add-page:horizontal{background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0#a1a1a1,stop:1#c4c4c4);border-radius:3px;margin-right:10px}\
                          QSlider::sub-page:horizontal{border-radius:3px;margin-left:10px;background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0#1B89CA,stop:1#1077B5)}\
                          QSlider::handle:horizontal{width:20px;margin-top:-3px;margin-bottom:-3px;margin-left:-8px;margin-right:-8px;border-radius:10px;\
                          background:qlineargradient(x1:0,y1:0,x2:0,y2:1,stop:0#F0F0F0,stop:1#5CACEE)}\
                          QSlider::handle:horizontal:hover{background:qradialgradient(cx:0.5,cy:0.5,radius:0.5,fx:0.5,fy:0.5,stop:0.6#F0F0F0,stop:0.778409#1B89CA);}");
    lab = new QLabel(str2qstr(std::string("音量调节")),this);
    //lab = new QLabel("",this);
    connect(volum,SIGNAL(valueChanged(int)),this,SLOT(setLabelText(int)));

    QHBoxLayout *toplayout = new QHBoxLayout;
    toplayout -> addWidget(headpicframe);

    QHBoxLayout *bottomlayout = new QHBoxLayout;
    bottomlayout -> addWidget(modelchoose_con);
    bottomlayout -> addWidget(modelchoose_sta);

    QVBoxLayout *mainlayout = new QVBoxLayout;
    mainlayout -> addLayout(toplayout);
    mainlayout -> addWidget(lab); //音量显示
    mainlayout -> addWidget(volum);
    mainlayout -> addLayout(bottomlayout);

    this -> setLayout(mainlayout);
    this -> setGeometry(750,250,320,240);
    //this -> setWindowFlags(this->windowFlags() | Qt::FramelessWindowHint);
    QPixmap pixmap(":/images/mainbg.png");
    QPalette palette=this->palette();
    palette.setBrush(QPalette::Background,QBrush(pixmap));
    this -> setPalette(palette);
    modelchoose_con->hide();
    modelchoose_sta->hide();
} 

settingpanel::~settingpanel()
{}

//头像上传和更换
void settingpanel::openfile()
{
    QString s = QFileDialog::getOpenFileName(this,"选择头像",":/images","picture(*.png *jpg)");
    if (s.length()<=0){
        return;
    }
    headpath = s;
    update();
}

void settingpanel::init()
{
    headpath.clear();
}

//音量调节
void settingpanel::setLabelText(int pos)
{
    QString str =QString(str2qstr(std::string("音量是：%1"))).arg(pos);
    lab->setText(str);
    // xxx -> setVolume().arg(pos) //赋值给多媒体类
}


//联网模式和单机模式的选择

void settingpanel::modelstaclick() //单机选中
{


}

void settingpanel::modelconclick()
{

}

