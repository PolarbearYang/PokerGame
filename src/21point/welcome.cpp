#include "welcome.h"
#include "ui_welcome.h"
QString welcome::m_name = "Dallas";
int welcome::m_ava = 1;
welcome::welcome(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::welcome)
{
    ui->setupUi(this);
    this->setWindowTitle("BlackJack");
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    QFont ft("Times New Roman", 13, 75);
    QPalette pa;
    nameedt = new QLineEdit;
    nameedt->setParent(this);
    nameedt->move(660,200);
    nameedt->setMaxLength(10);
    nameedt->resize(180,30);
    nameedt->setFont(ft);
    nameedt->setText(welcome::m_name);
    nameedt->hide();
    pa.setColor(QPalette::WindowText,Qt::white);
    change1 = new QLabel;
    change2 = new QLabel;
    showok = new QLabel;
    showname = new QLabel;
    showava1 = new QLabel;
    showava2 = new QLabel;
    showname->setText("Name: " + welcome::m_name);
    showname->setFont(ft);
    showname->setPalette(pa);
    showname->setParent(this);
    showname->move(200, 220);
    showname->resize(250, 30);
    showname->hide();
    showava1->setText("Avatar: ");
    showava1->setFont(ft);
    showava1->setPalette(pa);
    showava1->setParent(this);
    showava1->move(200, 250);
    showava1->hide();
    QPixmap pix;
    switch (welcome::m_ava) {
        case 1:
            pix.load(":/images/Dallas.png");
            break;
        case 2:
            pix.load(":/images/Chains.png");
            break;
        case 3:
            pix.load(":/images/Wolf.png");
            break;
        case 4:
            pix.load(":/images/Houston.png");
            break;
        case 5:
            pix.load(":/images/Jacket.png");
            break;
        case 6:
            pix.load(":/images/Bain.png");
            break;
        default:
            pix.load(":/images/Bot.png");
            break;
    }
    //pix = pix.scaled(QSize(150,150),Qt::KeepAspectRatio);
    showava2->setPixmap(pix);
    showava2->setParent(this);
    showava2->move(200, 280);
    showava2->hide();
    change1->setText("Set your new name: ");
    change1->setFont(ft);
    change1->setPalette(pa);
    change1->setParent(this);
    change1->move(450, 200);
    change1->hide();
    change2->setText("Choose your new avatar: ");
    change2->setFont(ft);
    change2->setPalette(pa);
    change2->setParent(this);
    change2->move(450, 250);
    change2->hide();
    showok->setText("Only A-Z, a-z, 0-9 and _ , make it in 10 characters.");
    showok->setFont(ft);
    showok->setPalette(pa);
    showok->setParent(this);
    showok->move(450, 230);
    showok->hide();
    setava1 = new QPushButton;
    setava2 = new QPushButton;
    setava3 = new QPushButton;
    setava4 = new QPushButton;
    setava5 = new QPushButton;
    setava6 = new QPushButton;
    pix.load(":/images/Dallas.png");
    setava1->setIcon(pix);
    setava1->setIconSize(QSize(100,100));
    setava1->setFixedSize(100,100);
    setava1->move(500,280);
    setava1->setParent(this);
    setava1->hide();
    pix.load(":/images/Bain.png");
    setava6->setIcon(pix);
    setava6->setIconSize(QSize(100,100));
    setava6->setFixedSize(100,100);
    setava6->move(720,390);
    setava6->setParent(this);
    setava6->hide();
    pix.load(":/images/Chains.png");
    setava2->setIcon(pix);
    setava2->setIconSize(QSize(100,100));
    setava2->setFixedSize(100,100);
    setava2->move(610,280);
    setava2->setParent(this);
    setava2->hide();
    pix.load(":/images/Wolf.png");
    setava3->setIcon(pix);
    setava3->setIconSize(QSize(100,100));
    setava3->setFixedSize(100,100);
    setava3->move(720,280);
    setava3->setParent(this);
    setava3->hide();
    pix.load(":/images/Houston.png");
    setava4->setIcon(pix);
    setava4->setIconSize(QSize(100,100));
    setava4->setFixedSize(100,100);
    setava4->move(500,390);
    setava4->setParent(this);
    setava4->hide();
    pix.load(":/images/Jacket.png");
    setava5->setIcon(pix);
    setava5->setIconSize(QSize(100,100));
    setava5->setFixedSize(100,100);
    setava5->move(610,390);
    setava5->setParent(this);
    setava5->hide();
    hhelp = new QLabel;
    hhelp->setPixmap(QPixmap(":/images/hhelp.jpg"));
    hhelp->setParent(this);
    hhelp->move(0,0);
    hhelp->hide();
    this_begin_btn = new mybutton;
    exit_btn = new mybutton;
    setself_btn = new mybutton;
    help_btn = new mybutton;
    host_btn = new mybutton;
    guest_btn = new mybutton;
    help_back_btn = new mybutton;
    solo_btn = new mybutton;
    self_back_btn = new mybutton;
    self_ok_btn = new mybutton;
    self_back_btn->pix = new QPixmap(":/images/back11 .png");
    self_back_btn->pix_blue = new QPixmap(":/images/back2.png");
    self_back_btn->setIcon(*self_back_btn->pix);
    self_back_btn->setIconSize(QSize(140,50));
    self_back_btn->setFixedSize(140,50);
    self_back_btn->move(535,500);
    self_back_btn->setParent(this);
    self_back_btn->hide();
    self_ok_btn->pix = new QPixmap(":/images/ok2.png");
    self_ok_btn->pix_blue = new QPixmap(":/images/ok1.png");
    self_ok_btn->setIcon(*self_ok_btn->pix);
    self_ok_btn->setIconSize(QSize(140,50));
    self_ok_btn->setFixedSize(140,50);
    self_ok_btn->move(335,500);
    self_ok_btn->setParent(this);
    self_ok_btn->hide();
    solo_btn->pix = new QPixmap(":/images/solo1.png");
    solo_btn->pix_blue = new QPixmap(":/images/solo2.png");
    solo_btn->setIcon(*solo_btn->pix);
    solo_btn->setIconSize(QSize(140,50));
    solo_btn->setFixedSize(140,50);
    solo_btn->move(435,180);
    solo_btn->setParent(this);
    solo_btn->hide();
    bro_btn = new mybutton;
    bro_btn->pix = new QPixmap(":/images/bro1.png");
    bro_btn->pix_blue = new QPixmap(":/images/bro2.png");
    bro_btn->setIcon(*bro_btn->pix);
    bro_btn->setIconSize(QSize(140,50));
    bro_btn->setFixedSize(140,50);
    bro_btn->move(435,250);
    bro_btn->setParent(this);
    bro_btn->hide();
    triple_btn = new mybutton;
    triple_btn->pix = new QPixmap(":/images/triple1.png");
    triple_btn->pix_blue = new QPixmap(":/images/triple2.png");
    triple_btn->setIcon(*triple_btn->pix);
    triple_btn->setIconSize(QSize(140,50));
    triple_btn->setFixedSize(140,50);
    triple_btn->move(435,320);
    triple_btn->setParent(this);
    triple_btn->hide();
    group_btn = new mybutton;
    group_btn->pix = new QPixmap(":/images/group1.png");
    group_btn->pix_blue = new QPixmap(":/images/group2.png");
    group_btn->setIcon(*group_btn->pix);
    group_btn->setIconSize(QSize(140,50));
    group_btn->setFixedSize(140,50);
    group_btn->move(435,390);
    group_btn->setParent(this);
    group_btn->hide();
    host_back_btn = new mybutton;
    host_back_btn->pix = new QPixmap(":/images/back11 .png");
    host_back_btn->pix_blue = new QPixmap(":/images/back2.png");
    host_back_btn->setIcon(*host_back_btn->pix);
    host_back_btn->setIconSize(QSize(140,50));
    host_back_btn->setFixedSize(140,50);
    host_back_btn->move(435,460);
    host_back_btn->setParent(this);
    host_back_btn->hide();
    help_back_btn->pix = new QPixmap(":/images/back11 .png");
    help_back_btn->pix_blue = new QPixmap(":/images/back2.png");
    help_back_btn->setIcon(*help_back_btn->pix);
    help_back_btn->setIconSize(QSize(140,50));
    help_back_btn->setFixedSize(140,50);
    help_back_btn->move(800,70);
    help_back_btn->setParent(this);
    guest_btn->pix = new QPixmap(":/images/search1.png");
    guest_btn->pix_blue = new QPixmap(":/images/search2.png");
    guest_btn->setIcon(*guest_btn->pix);
    guest_btn->setIconSize(QSize(140,50));
    guest_btn->setFixedSize(140,50);
    guest_btn->move(435,320);
    guest_btn->setParent(this);
    host_btn->pix = new QPixmap(":/images/create1_p.png");
    host_btn->pix_blue = new QPixmap(":/images/create2.png");
    host_btn->setIcon(*host_btn->pix);
    host_btn->setIconSize(QSize(140,50));
    host_btn->setFixedSize(140,50);
    host_btn->move(435,250);
    host_btn->setParent(this);
    setself_btn->pix = new QPixmap(":/images/self1.png");
    setself_btn->pix_blue = new QPixmap(":/images/self2.png");
    setself_btn->setIcon(*setself_btn->pix);
    setself_btn->setIconSize(QSize(140,50));
    setself_btn->setFixedSize(140,50);
    setself_btn->move(435,390);
    setself_btn->setParent(this);
    help_btn->pix = new QPixmap(":/images/help1.png");
    help_btn->pix_blue = new QPixmap(":/images/help2.png");
    help_btn->setIcon(*help_btn->pix);
    help_btn->setIconSize(QSize(140,50));
    help_btn->setFixedSize(140,50);
    help_btn->move(435,460);
    help_btn->setParent(this);
    exit_btn->pix = new QPixmap(":/images/exit1 .png");
    exit_btn->pix_blue = new QPixmap(":/images/exit2.png");
    exit_btn->setIcon(*exit_btn->pix);
    exit_btn->setIconSize(QSize(140,50));
    exit_btn->setFixedSize(140,50);
    exit_btn->move(435,530);
    exit_btn->setParent(this);
    this_begin_btn->pix = new QPixmap(":/images/local1.png");
    this_begin_btn->pix_blue = new QPixmap(":/images/local2.png");
    this_begin_btn->setIcon(*this_begin_btn->pix);
    this_begin_btn->setIconSize(QSize(140,50));
    this_begin_btn->setFixedSize(140,50);
    this_begin_btn->move(435,180);
    this_begin_btn->setParent((this));
    this_begin_btn->show();
    exit_btn->show();
    help_btn->show();
    setself_btn->show();
    guest_btn->show();
    host_btn->show();
    help_back_btn->hide();
    connect(this_begin_btn,SIGNAL(clicked()),this,SLOT(newthis4man()));
    connect(exit_btn,SIGNAL(clicked()),this,SLOT(endgame()));
    connect(help_btn,SIGNAL(clicked()),this,SLOT(helpshow()));
    connect(help_back_btn,SIGNAL(clicked()),this,SLOT(helpback()));
    connect(guest_btn,SIGNAL(clicked()),this,SLOT(findgame()));
    connect(host_btn,SIGNAL(clicked()),this,SLOT(sethost()));
    connect(solo_btn,SIGNAL(clicked()),this,SLOT(solohost()));
    connect(bro_btn,SIGNAL(clicked()),this,SLOT(brohost()));
    connect(triple_btn,SIGNAL(clicked()),this,SLOT(triplehost()));
    connect(group_btn,SIGNAL(clicked()),this,SLOT(grouphost()));
    connect(host_back_btn,SIGNAL(clicked()),this,SLOT(hostback()));
    connect(setself_btn,SIGNAL(clicked()),this,SLOT(setself()));
    connect(self_back_btn,SIGNAL(clicked()),this,SLOT(selfback()));
    connect(setava1,SIGNAL(clicked()),this,SLOT(set1()));
    connect(setava2,SIGNAL(clicked()),this,SLOT(set2()));
    connect(setava3,SIGNAL(clicked()),this,SLOT(set3()));
    connect(setava4,SIGNAL(clicked()),this,SLOT(set4()));
    connect(setava5,SIGNAL(clicked()),this,SLOT(set5()));
    connect(setava6,SIGNAL(clicked()),this,SLOT(set6()));
    connect(self_ok_btn,SIGNAL(clicked()),this,SLOT(setname()));
}

welcome::~welcome()
{
    delete ui;
}

void welcome::newthis4man(){
    this4man = new form4;
    this4man->show();
    this->close();
    connect(this4man, SIGNAL(form4show()), this, SLOT(showwelcome()));
}

void welcome::helpshow(){
    this_begin_btn->hide();
    exit_btn->hide();
    help_btn->hide();
    setself_btn->hide();
    guest_btn->hide();
    host_btn->hide();
    help_back_btn->show();
    hhelp->show();
}

void welcome::helpback(){
    this_begin_btn->show();
    exit_btn->show();
    help_btn->show();
    setself_btn->show();
    guest_btn->show();
    host_btn->show();
    help_back_btn->hide();
    hhelp->hide();
}

void welcome::sethost(){
    this_begin_btn->hide();
    exit_btn->hide();
    help_btn->hide();
    setself_btn->hide();
    guest_btn->hide();
    host_btn->hide();
    host_back_btn->show();
    solo_btn->show();
    bro_btn->show();
    triple_btn->show();
    group_btn->show();
}

void welcome::hostback(){
    this_begin_btn->show();
    exit_btn->show();
    help_btn->show();
    setself_btn->show();
    guest_btn->show();
    host_btn->show();
    host_back_btn->hide();
    solo_btn->hide();
    bro_btn->hide();
    triple_btn->hide();
    group_btn->hide();
}

void welcome::solohost(){
    host1man = new rform0;
    host1man->show();
    this->close();
    connect(host1man, SIGNAL(rform0show()), this, SLOT(showwelcome()));
}

void welcome::brohost(){
    host2man = new rform1;
    host2man->show();
    this->close();
    connect(host2man, SIGNAL(rform1show()), this, SLOT(showwelcome()));
}

void welcome::triplehost(){
    host3man = new rform2;
    host3man->show();
    this->close();
    connect(host3man, SIGNAL(rform2show()), this, SLOT(showwelcome()));
}

void welcome::grouphost(){
    host4man = new Form;
    host4man->show();
    this->close();
    connect(host4man, SIGNAL(Formshow()), this, SLOT(showwelcome()));
}
void welcome::findgame(){
    findsever = new host;
    findsever->show();
    this->close();
    connect(findsever, SIGNAL(Hostshow()), this, SLOT(showwelcome()));
}

void welcome::setself(){
    this_begin_btn->hide();
    exit_btn->hide();
    help_btn->hide();
    setself_btn->hide();
    guest_btn->hide();
    host_btn->hide();
    self_back_btn->show();
    self_ok_btn->show();
    setava1->show();
    setava2->show();
    setava3->show();
    setava4->show();
    setava5->show();
    setava6->show();
    showname->show();
    showava1->show();
    showava2->show();
    showok->show();
    change1->show();
    change2->show();
    nameedt->show();
}

void welcome::selfback(){
    this_begin_btn->show();
    exit_btn->show();
    help_btn->show();
    setself_btn->show();
    guest_btn->show();
    host_btn->show();
    self_back_btn->hide();
    self_ok_btn->hide();
    setava1->hide();
    setava2->hide();
    setava3->hide();
    setava4->hide();
    setava5->hide();
    setava6->hide();
    showname->hide();
    showava1->hide();
    showava2->hide();
    showok->hide();
    change1->hide();
    change2->hide();
    nameedt->hide();
}

void welcome::set1(){
    welcome::m_ava = 1;
    showava2->setPixmap(QPixmap(":/images/Dallas.png"));
}

void welcome::set2(){
    welcome::m_ava = 2;
    showava2->setPixmap(QPixmap(":/images/Chains.png"));
}

void welcome::set3(){
    welcome::m_ava = 3;
    showava2->setPixmap(QPixmap(":/images/Wolf.png"));
}

void welcome::set4(){
    welcome::m_ava = 4;
    showava2->setPixmap(QPixmap(":/images/Houston.png"));
}

void welcome::set5(){
    welcome::m_ava = 5;
    showava2->setPixmap(QPixmap(":/images/Jacket.png"));
}

void welcome::set6(){
    welcome::m_ava = 6;
    showava2->setPixmap(QPixmap(":/images/Bain.png"));
}

void welcome::setname(){
    QString newname;
    newname = nameedt->displayText();
    bool err = false;
    for (int i = 0; i < newname.length(); i++){
        if (((newname[i] <='z') && (newname[i] >='a')) || ((newname[i] <='Z') && (newname[i] >='A')) || ((newname[i] <='9') && (newname[i] >='0')) || (newname[i] == '_')){

        } else {
            err = true;
        }
    }
    if (err) {
        showok->setText("Illegal character! Only A-Z, a-z, 0-9 and _ !");
    } else {
        showname->setText("Name: " + newname);
        welcome::m_name.clear();
        welcome::m_name = newname;
    }
}

void welcome::endgame(){
    exit(0);
}

void welcome::showwelcome(){
    this->show();
}
