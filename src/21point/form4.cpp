#include "form4.h"
#include "ui_form4.h"
#include <welcome.h>
form4::form4(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::form4)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    Deck::c_left = 52;
    Player::p1_total = 0;
    Player::p2_total = 0;
    Player::p3_total = 0;
    Player::p4_total = 0;
    House::h_total = 0;
    c1 = new client;
    c2 = new client;
    c3 = new client;
    c4 = new client;
    c2->setname("Chains");
    c2->setava(2);
    c3->setname("Wolf");
    c3->setava(3);
    c4->setname("Houston");
    c4->setava(4);
    c1->setava(welcome::m_ava);
    c1->setname(welcome::m_name);
    QFont ft("Times New Roman", 11, 75);
    //ft.setPointSize(11,75);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    c1back = new QLabel;
    c1a = new QLabel;
    c1n = new QLabel;
    c1m = new QLabel;
    c1back->setParent(this);
    c1a->setParent(this);
    c1n->setParent(this);
    c1m->setParent(this);
    QPixmap pix;
    switch (c1->c_ava) {
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
        default:
            pix.load(":/images/Bain.png");
            break;
    }
    pix = pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    c1a->setPixmap(pix);
    c1back->setPixmap(QPixmap(":/images/back1.png"));
    c1back->move(630, 500);
    c1a->move(635, 510);
    c1n->setText("P1: " + c1->c_name);
    c1m->setText("Money: " + QString::number(p1Player.m_money));
    c1m->move(720, 555);
    c1m->setFont(ft);
    c1m->setPalette(pa);
    c1n->setFont(ft);
    c1n->setPalette(pa);
    c1n->move(720, 520);
    c2back = new QLabel;
    c2a = new QLabel;
    c2n = new QLabel;
    c2m = new QLabel;
    c2back->setParent(this);
    c2a->setParent(this);
    c2n->setParent(this);
    c2m->setParent(this);
    switch (c2->c_ava) {
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
        default:
            pix.load(":/images/Bain.png");
            break;
    }
    pix = pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    c2a->setPixmap(pix);
    c2back->setPixmap(QPixmap(":/images/back1.png"));
    c2back->move(630, 200);
    c2a->move(635, 210);
    c2n->setText("P2: " + c2->c_name);
    c2m->setText("Money: " + QString::number(p2Player.m_money));
    c2m->move(720, 255);
    c2m->setFont(ft);
    c2m->setPalette(pa);
    c2n->setFont(ft);
    c2n->setPalette(pa);
    c2n->move(720, 220);
    c3back = new QLabel;
    c3a = new QLabel;
    c3n = new QLabel;
    c3m = new QLabel;
    c3back->setParent(this);
    c3a->setParent(this);
    c3n->setParent(this);
    c3m->setParent(this);
    switch (c3->c_ava) {
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
        default:
            pix.load(":/images/Bain.png");
            break;
    }
    pix = pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    c3a->setPixmap(pix);
    c3back->setPixmap(QPixmap(":/images/back1.png"));
    c3back->move(200, 100);
    c3a->move(205, 110);
    c3n->setText("P3: " + c3->c_name);
    c3m->setText("Money: " + QString::number(p3Player.m_money));
    c3m->move(290, 155);
    c3m->setFont(ft);
    c3m->setPalette(pa);
    c3n->setFont(ft);
    c3n->setPalette(pa);
    c3n->move(290, 120);
    c4back = new QLabel;
    c4a = new QLabel;
    c4n = new QLabel;
    c4m = new QLabel;
    c4back->setParent(this);
    c4a->setParent(this);
    c4n->setParent(this);
    c4m->setParent(this);
    switch (c4->c_ava) {
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
        default:
            pix.load(":/images/Bain.png");
            break;
    }
    pix = pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    c4a->setPixmap(pix);
    c4back->setPixmap(QPixmap(":/images/back1.png"));
    c4back->move(200, 400);
    c4a->move(205, 410);
    c4n->setText("P4: " + c4->c_name);
    c4m->setText("Money: " + QString::number(p4Player.m_money));
    c4n->move(290, 415);
    c4m->setFont(ft);
    c4m->setPalette(pa);
    c4n->setFont(ft);
    c4n->setPalette(pa);
    c4m->move(290, 450);
    this->setWindowTitle("BlackJack");
    ui->label_3->setText(c1->c_name + ": ");
    ui->label_10->setText(c2->c_name + ": ");
    ui->label_12->setText(c3->c_name + ": ");
    ui->label_14->setText(c4->c_name + ": ");
    ui->label_7->setText(QString::number(Deck::c_left));
    ui->label_6->setText(QString::number(Player::p1_total));
    ui->label_8->setText(QString::number(House::h_total));
    ui->label_11->setText(QString::number(Player::p2_total));
    ui->label_13->setText(QString::number(Player::p3_total));
    ui->label_15->setText(QString::number(Player::p4_total));
    connect(ui->Beginbtn,SIGNAL(clicked()),this,SLOT(begin()));
    connect(ui->shuffleButton,SIGNAL(clicked()),this,SLOT(shuffle()));
    p1_hit_btn = new mybutton;
    p1_stand_btn = new mybutton;
    p1_hit_btn->pix = new QPixmap(":/images/hit1.png");
    p1_hit_btn->pix_blue = new QPixmap(":/images/hit2.png");
    p1_hit_btn->setIcon(*p1_hit_btn->pix);
    p1_hit_btn->setIconSize(QSize(80,40));
    p1_hit_btn->setFixedSize(60,30);
    p1_hit_btn->move(435,450);
    p1_hit_btn->setParent(this);
    p1_stand_btn->pix = new QPixmap(":/images/stand1.png");
    p1_stand_btn->pix_blue = new QPixmap(":/images/stand2.png");
    p1_stand_btn->setIcon(*p1_stand_btn->pix);
    p1_stand_btn->setIconSize(QSize(80,40));
    p1_stand_btn->setFixedSize(60,30);
    p1_stand_btn->move(535,450);
    p1_stand_btn->setParent((this));
    connect(p1_stand_btn,SIGNAL(clicked()),this,SLOT(p1stay()));
    connect(p1_hit_btn,SIGNAL(clicked()),this,SLOT(p1hit()));
    p2_hit_btn = new mybutton;
    p2_stand_btn = new mybutton;
    p2_hit_btn->pix = new QPixmap(":/images/hit1.png");
    p2_hit_btn->pix_blue = new QPixmap(":/images/hit2.png");
    p2_hit_btn->setIcon(*p2_hit_btn->pix);
    p2_hit_btn->setIconSize(QSize(80,40));
    p2_hit_btn->setFixedSize(60,30);
    p2_hit_btn->move(780,300);
    p2_hit_btn->setParent(this);
    p2_stand_btn->pix = new QPixmap(":/images/stand1.png");
    p2_stand_btn->pix_blue = new QPixmap(":/images/stand2.png");
    p2_stand_btn->setIcon(*p2_stand_btn->pix);
    p2_stand_btn->setIconSize(QSize(80,40));
    p2_stand_btn->setFixedSize(60,30);
    p2_stand_btn->move(780,350);
    p2_stand_btn->setParent((this));
    connect(p2_stand_btn,SIGNAL(clicked()),this,SLOT(p2stay()));
    connect(p2_hit_btn,SIGNAL(clicked()),this,SLOT(p2hit()));
    p3_hit_btn = new mybutton;
    p3_stand_btn = new mybutton;
    p3_hit_btn->pix = new QPixmap(":/images/hit1.png");
    p3_hit_btn->pix_blue = new QPixmap(":/images/hit2.png");
    p3_hit_btn->setIcon(*p3_hit_btn->pix);
    p3_hit_btn->setIconSize(QSize(80,40));
    p3_hit_btn->setFixedSize(60,30);
    p3_hit_btn->move(435,230);
    p3_hit_btn->setParent(this);
    p3_stand_btn->pix = new QPixmap(":/images/stand1.png");
    p3_stand_btn->pix_blue = new QPixmap(":/images/stand2.png");
    p3_stand_btn->setIcon(*p3_stand_btn->pix);
    p3_stand_btn->setIconSize(QSize(80,40));
    p3_stand_btn->setFixedSize(60,30);
    p3_stand_btn->move(535,230);
    p3_stand_btn->setParent((this));
    connect(p3_stand_btn,SIGNAL(clicked()),this,SLOT(p3stay()));
    connect(p3_hit_btn,SIGNAL(clicked()),this,SLOT(p3hit()));
    p4_hit_btn = new mybutton;
    p4_stand_btn = new mybutton;
    p4_hit_btn->pix = new QPixmap(":/images/hit1.png");
    p4_hit_btn->pix_blue = new QPixmap(":/images/hit2.png");
    p4_hit_btn->setIcon(*p4_hit_btn->pix);
    p4_hit_btn->setIconSize(QSize(80,40));
    p4_hit_btn->setFixedSize(60,30);
    p4_hit_btn->move(130,250);
    p4_hit_btn->setParent(this);
    p4_stand_btn->pix = new QPixmap(":/images/stand1.png");
    p4_stand_btn->pix_blue = new QPixmap(":/images/stand2.png");
    p4_stand_btn->setIcon(*p4_stand_btn->pix);
    p4_stand_btn->setIconSize(QSize(80,40));
    p4_stand_btn->setFixedSize(60,30);
    p4_stand_btn->move(130,300);
    p4_stand_btn->setParent((this));
    connect(p4_stand_btn,SIGNAL(clicked()),this,SLOT(p4stay()));
    connect(p4_hit_btn,SIGNAL(clicked()),this,SLOT(p4hit()));
    p1_hit_btn->hide();
    p1_stand_btn->hide();
    p2_hit_btn->hide();
    p2_stand_btn->hide();
    p3_hit_btn->hide();
    p3_stand_btn->hide();
    p4_hit_btn->hide();
    p4_stand_btn->hide();
    c1back->hide();
    c1m->hide();
    c1n->hide();
    c1a->hide();
    c2back->hide();
    c2m->hide();
    c2n->hide();
    c2a->hide();
    c3back->hide();
    c3m->hide();
    c3n->hide();
    c3a->hide();
    c4back->hide();
    c4m->hide();
    c4n->hide();
    c4a->hide();
}

form4::~form4()
{
    delete ui;
}
void form4::play(){
    if (m_Deck.GetNum()>=10){
        cleanPlayer1cards();
        cleanPlayer2cards();
        cleanPlayer3cards();
        cleanPlayer4cards();
        cleanHousecards();
        for (int i=0; i < 2; ++i){
            m_Deck.Deal(p1Player);
            m_Deck.Deal(p2Player);
            m_Deck.Deal(p3Player);
            m_Deck.Deal(p4Player);
            m_Deck.Deal(m_House);
        }
        showPlayer1cards(p1Player);
        c1_list[0]->move(435,500);
        c1_list[1]->move(535,500);
        c1_list[0]->show();
        c1_list[1]->show();
        Player::p1_total = p1Player.GetTotal();
        showPlayer2cards(p2Player);
        c2_list[0]->move(880,300);
        c2_list[1]->move(880,200);
        c2_list[0]->show();
        c2_list[1]->show();
        Player::p2_total = p2Player.GetTotal();
        showPlayer3cards(p3Player);
        c3_list[0]->move(535,100);
        c3_list[1]->move(435,100);
        c3_list[0]->show();
        c3_list[1]->show();
        Player::p3_total = p3Player.GetTotal();
        showPlayer4cards(p4Player);
        c4_list[0]->move(30,300);
        c4_list[1]->move(30,200);
        c4_list[0]->show();
        c4_list[1]->show();
        Player::p4_total = p4Player.GetTotal();
        Deck::c_left = m_Deck.GetNum();
        ui->label_7->setText(QString::number(Deck::c_left));
        ui->label_6->setText(QString::number(Player::p1_total));
        ui->label_11->setText(QString::number(Player::p2_total));
        ui->label_13->setText(QString::number(Player::p3_total));
        ui->label_15->setText(QString::number(Player::p4_total));
        m_House.FlipFirstCard();
        showHousecards(m_House);
        h_list[0]->move(435,300);
        h_list[1]->move(535,300);
        h_list[0]->show();
        h_list[1]->show();
        House::h_total = m_House.GetTotal();
        ui->label_8->setText(QString::number(House::h_total));
        p1_hit_btn->show();
        p1_stand_btn->show();
    } else {
        QMessageBox::critical(this,"Warning","No cards!");
        this->begin();
    }
}
void form4::p1hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p1Player);
        int card_num = p1Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c1_list[i]->hide();
        }
        cleanPlayer1cards();
        showPlayer1cards(p1Player);
        for (int i = 0; i < card_num ; i++){
            c1_list[i]->move(535-(card_num-1-i)*100,500);
            c1_list[i]->show();
        }
        if (p1Player.GetTotal() <= 21){
            Player::p1_total = p1Player.GetTotal();
            ui->label_6->setText(QString::number(Player::p1_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            p1_hit_btn->hide();
            p1_stand_btn->hide();
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            ui->label_6->setText("Bust");
            p1Player.Bust();
            w->setText(c1->c_name + " bustes!");
            w->show();
            p2_hit_btn->show();
            p2_stand_btn->show();
        }
    } else {
        QMessageBox::critical(this,"Warning","No cards!");
        this->begin();
    }
}
void form4::p2hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p2Player);
        int card_num = p2Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c2_list[i]->hide();
        }
        cleanPlayer2cards();
        showPlayer2cards(p2Player);
        for (int i = 0; i < card_num ; i++){
            c2_list[i]->move(880,200+(card_num-1-i)*100);
            c2_list[i]->show();
        }
        if (p2Player.GetTotal() <= 21){
            Player::p2_total = p2Player.GetTotal();
            ui->label_11->setText(QString::number(Player::p2_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            p2_hit_btn->hide();
            p2_stand_btn->hide();
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            ui->label_11->setText("Bust");
            p2Player.Bust();
            w->setText(c2->c_name + " bustes!");
            w->show();
            p3_hit_btn->show();
            p3_stand_btn->show();
        }
    } else {
        QMessageBox::critical(this,"Warning","No cards!");
        this->begin();
    }
}
void form4::p3hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p3Player);
        int card_num = p3Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c3_list[i]->hide();
        }
        cleanPlayer3cards();
        showPlayer3cards(p3Player);
        for (int i = 0; i < card_num ; i++){
            c3_list[i]->move(435+(card_num-1-i)*100,100);
            c3_list[i]->show();
        }
        if (p3Player.GetTotal() <= 21){
            Player::p3_total = p3Player.GetTotal();
            ui->label_13->setText(QString::number(Player::p3_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            p3_hit_btn->hide();
            p3_stand_btn->hide();
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            ui->label_13->setText("Bust");
            p3Player.Bust();
            w->setText(c3->c_name + " bustes!");
            w->show();
            p4_hit_btn->show();
            p4_stand_btn->show();
        }
    } else {
        QMessageBox::critical(this,"Warning","No cards!");
        this->begin();
    }
}
void form4::p4hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p4Player);
        int card_num = p4Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c4_list[i]->hide();  //隐藏所有手牌
        }
        cleanPlayer4cards();
        showPlayer4cards(p4Player);
        for (int i = 0; i < card_num ; i++){
            c4_list[i]->move(30,(card_num-1-i)*100+200);
            c4_list[i]->show();
        }
        if (p4Player.GetTotal() <= 21){
            Player::p4_total = p4Player.GetTotal();
            ui->label_15->setText(QString::number(Player::p4_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            p4_hit_btn->hide();
            p4_stand_btn->hide();
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            ui->label_15->setText("Bust");
            p4Player.Bust();
            w->setText(c4->c_name + " bustes!");
            w->show();
            endgame();
        }
    } else {
        QMessageBox::critical(this,"Warning","No cards!");
        this->begin();
    }
}
void form4::endgame(){
    m_House.FlipFirstCard();
    House::h_total = m_House.GetTotal();
    cleanHousecards();
    QString edd="";
    showHousecards(m_House);
    h_list[0]->move(435,300);
    h_list[1]->move(535,300);
    h_list[0]->show();
    h_list[1]->show();
    ui->label_8->setText(QString::number(House::h_total));
    QLabel *w = new QLabel;
    w->resize(200,100);
    w->move(750,400);
    w->setAlignment(Qt::AlignCenter);
    if ((p1Player.GetTotal() > 21) && (p2Player.GetTotal() > 21) && (p3Player.GetTotal() > 21) && (p4Player.GetTotal() > 21)){
        edd += c1->c_name + " Loses!\n";
        edd += c2->c_name + " Loses!\n";
        edd += c3->c_name + " Loses!\n";
        edd += c4->c_name + " Loses!\n";
    } else {
        while (m_House.IsHitting() && (m_Deck.GetNum()>=1)){
            this->sleep(1000);
            m_Deck.Deal(m_House);
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            int card_num = m_House.GetNum();
            for (int i = 0; i < (card_num - 1); i++){
                h_list[i]->hide();
            }
            cleanHousecards();
            showHousecards(m_House);
            for (int i = 0; i < (card_num); i++){
                h_list[i]->move(535-(card_num-1-i)*100,300);
                h_list[i]->show();
            }
            if (m_House.GetTotal()<=21) {
                House::h_total = m_House.GetTotal();
                ui->label_8->setText(QString::number(House::h_total));
            } else {
                ui->label_8->setText("Bust");
            }
        }
        if (m_House.IsBusted()){
            if (!(p1Player.IsBusted())){
                p1Player.Win();
                edd += c1->c_name + " wins!\n";
            }
            if (!(p2Player.IsBusted())){
                p2Player.Win();
                edd += c2->c_name + " wins!\n";
            }
            if (!(p3Player.IsBusted())){
                p3Player.Win();
                edd += c3->c_name + " wins!\n";
            }
            if (!(p4Player.IsBusted())){
                p4Player.Win();
                edd += c4->c_name + " wins!\n";
            }
        } else {
            if (!(p1Player.IsBusted())){
                if (p1Player.GetTotal() > m_House.GetTotal()){
                    p1Player.Win();
                    edd += c1->c_name + " wins!\n";
                } else if (p1Player.GetTotal() < m_House.GetTotal()){
                    p1Player.Lose();
                    edd += c1->c_name + " loses!\n";
                } else {
                    p1Player.Push();
                    edd += c1->c_name + " pushes!\n";
                }
            } else {
                edd += c1->c_name + " loses!\n";
            }
            if (!(p2Player.IsBusted())){
                if (p2Player.GetTotal() > m_House.GetTotal()){
                    p2Player.Win();
                    edd += c2->c_name + " wins!\n";
                } else if (p2Player.GetTotal() < m_House.GetTotal()){
                    p2Player.Lose();
                    edd += c2->c_name + " loses!\n";
                } else {
                    p2Player.Push();
                    edd += c2->c_name + " pushes!\n";
                }
            }else {
                edd += c2->c_name + " loses!\n";
            }
            if (!(p3Player.IsBusted())){
                if (p3Player.GetTotal() > m_House.GetTotal()){
                    p3Player.Win();
                    edd += c3->c_name + " wins!\n";
                } else if (p3Player.GetTotal() < m_House.GetTotal()){
                    p3Player.Lose();
                    edd += c3->c_name + " loses!\n";
                } else {
                    p3Player.Push();
                    edd += c3->c_name + " pushes!\n";
                }
            }else {
                edd += c3->c_name + " loses!\n";
            }
            if (!(p4Player.IsBusted())){
                if (p4Player.GetTotal() > m_House.GetTotal()){
                    p4Player.Win();
                    edd += c4->c_name + " wins!\n";
                } else if (p4Player.GetTotal() < m_House.GetTotal()){
                    p4Player.Lose();
                    edd += c4->c_name + " loses!\n";
                } else {
                    p4Player.Push();
                    edd += c4->c_name + " pushes!\n";
                }
            }else {
                edd += c4->c_name + " loses!\n";
            }
        }
    }
    w->setText(edd);
    this->sleep(1000);
    w->show();
}
void form4::p1stay(){
    p1_hit_btn->hide();
    p1_stand_btn->hide();
    p2_hit_btn->show();
    p2_stand_btn->show();
}
void form4::p2stay(){
    p2_hit_btn->hide();
    p2_stand_btn->hide();
    p3_hit_btn->show();
    p3_stand_btn->show();
}
void form4::p3stay(){
    p3_hit_btn->hide();
    p3_stand_btn->hide();
    p4_hit_btn->show();
    p4_stand_btn->show();
}

void form4::p4stay(){
    p4_hit_btn->hide();
    p4_stand_btn->hide();
    endgame();
}
void form4::shuffle(){
    if (m_Deck.GetNum()!=52){
        c1back->hide();
        c1m->hide();
        c1n->hide();
        c1a->hide();
        c2back->hide();
        c2m->hide();
        c2n->hide();
        c2a->hide();
        c3back->hide();
        c3m->hide();
        c3n->hide();
        c3a->hide();
        c4back->hide();
        c4m->hide();
        c4n->hide();
        c4a->hide();
        c1back->show();
        c1m->setText("Money: " + QString::number(p1Player.m_money));
        c1m->show();
        c1n->show();
        c1a->show();
        c2back->show();
        c2m->setText("Money: " + QString::number(p2Player.m_money));
        c2m->show();
        c2n->show();
        c2a->show();
        c3back->show();
        c3m->setText("Money: " + QString::number(p3Player.m_money));
        c3m->show();
        c3n->show();
        c3a->show();
        c4back->show();
        c4m->setText("Money: " + QString::number(p4Player.m_money));
        c4m->show();
        c4n->show();
        c4a->show();
        p1_hit_btn->hide();
        p1_stand_btn->hide();
        p2_hit_btn->hide();
        p2_stand_btn->hide();
        p3_hit_btn->hide();
        p3_stand_btn->hide();
        p4_hit_btn->hide();
        p4_stand_btn->hide();
        int card_num = p1Player.GetNum();
        for (int i = 0; i < card_num; i++){
            c1_list[i]->hide();
        }
        card_num = p2Player.GetNum();
        for (int i = 0; i < card_num; i++){
            c2_list[i]->hide();
        }
        card_num = p3Player.GetNum();
        for (int i = 0; i < card_num; i++){
            c3_list[i]->hide();
        }
        card_num = p4Player.GetNum();
        for (int i = 0; i < card_num; i++){
            c4_list[i]->hide();
        }
        card_num = m_House.GetNum();
        for (int i = 0; i < card_num; i++){
            h_list[i]->hide();
        }
        p1Player.Clear();
        p2Player.Clear();
        p3Player.Clear();
        p4Player.Clear();
        m_House.Clear();
        this->play();
    } else {
        //QMessageBox::critical(this,"Warning","No deck!");
        this->begin();
    }

}
void form4::begin(){
    c1back->hide();
    c1m->hide();
    c1n->hide();
    c1a->hide();
    c2back->hide();
    c2m->hide();
    c2n->hide();
    c2a->hide();
    c3back->hide();
    c3m->hide();
    c3n->hide();
    c3a->hide();
    c4back->hide();
    c4m->hide();
    c4n->hide();
    c4a->hide();
    c1back->show();
    c1m->setText("Money: " + QString::number(p1Player.m_money));
    c1m->show();
    c1n->show();
    c1a->show();
    c2back->show();
    c2m->setText("Money: " + QString::number(p2Player.m_money));
    c2m->show();
    c2n->show();
    c2a->show();
    c3back->show();
    c3m->setText("Money: " + QString::number(p3Player.m_money));
    c3m->show();
    c3n->show();
    c3a->show();
    c4back->show();
    c4m->setText("Money: " + QString::number(p4Player.m_money));
    c4m->show();
    c4n->show();
    c4a->show();
    p1_hit_btn->hide();
    p1_stand_btn->hide();
    p2_hit_btn->hide();
    p2_stand_btn->hide();
    p3_hit_btn->hide();
    p3_stand_btn->hide();
    p4_hit_btn->hide();
    p4_stand_btn->hide();
    int card_num = p1Player.GetNum();
    for (int i = 0; i < card_num; i++){
        c1_list[i]->hide();
    }
    card_num = p2Player.GetNum();
    for (int i = 0; i < card_num; i++){
        c2_list[i]->hide();
    }
    card_num = p3Player.GetNum();
    for (int i = 0; i < card_num; i++){
        c3_list[i]->hide();
    }
    card_num = p4Player.GetNum();
    for (int i = 0; i < card_num; i++){
        c4_list[i]->hide();
    }
    card_num = m_House.GetNum();
    for (int i = 0; i < card_num; i++){
        h_list[i]->hide();
    }
    p1Player.Clear();
    p2Player.Clear();
    p3Player.Clear();
    p4Player.Clear();
    m_House.Clear();
    srand(static_cast<unsigned int>(time(0)));
    m_Deck.Populate();
    m_Deck.Shuffle();
    this->play();
}

void form4::showPlayer1cards(Player &aGenericPlayer){
    //int card_num = aGenericPlayer.GetNum();
    vector<card*>::const_iterator iter;
    for (iter = aGenericPlayer.m_cards.begin(); iter != aGenericPlayer.m_cards.end(); ++iter){
        QLabel *label = new QLabel;
        if (!(*iter)->m_IsFaceUp) {
            label->setPixmap(QPixmap(":/images/cb.png"));
        } else {
            if ((*iter)->m_Suit == card::SPADES) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/as.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2s.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3s.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4s.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5s.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6s.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7s.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8s.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9s.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/ts.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/js.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qs.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/ks.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::HEARTS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ah.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2h.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3h.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4h.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5h.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6h.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7h.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8h.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9h.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/th.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jh.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qh.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kh.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::CLUBS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ac.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2c.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3c.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4c.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5c.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6c.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7c.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8c.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9c.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/tc.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jc.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qc.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kc.png"));
                        break;
                }
            } else {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ad.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2d.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3d.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4d.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5d.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6d.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7d.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8d.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9d.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/td.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jd.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qd.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kd.png"));
                        break;
                }
            }
        }
        label->setParent(this); //设定父类一起显示
        c1_list.append(label);
    }
}
void form4::showPlayer2cards(Player &aGenericPlayer){
    //int card_num = aGenericPlayer.GetNum();
    vector<card*>::const_iterator iter; //采取枚举的显示牌的方式（开始挨骂）
    for (iter = aGenericPlayer.m_cards.begin(); iter != aGenericPlayer.m_cards.end(); ++iter){
        QLabel *label = new QLabel;
        if (!(*iter)->m_IsFaceUp) {
            label->setPixmap(QPixmap(":/images/cb.png"));
        } else {
            if ((*iter)->m_Suit == card::SPADES) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/as.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2s.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3s.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4s.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5s.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6s.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7s.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8s.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9s.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/ts.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/js.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qs.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/ks.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::HEARTS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ah.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2h.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3h.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4h.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5h.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6h.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7h.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8h.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9h.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/th.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jh.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qh.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kh.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::CLUBS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ac.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2c.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3c.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4c.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5c.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6c.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7c.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8c.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9c.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/tc.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jc.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qc.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kc.png"));
                        break;
                }
            } else {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ad.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2d.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3d.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4d.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5d.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6d.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7d.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8d.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9d.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/td.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jd.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qd.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kd.png"));
                        break;
                }
            }
        }
        label->setParent(this); //设定父类一起显示
        c2_list.append(label);
    }
}
void form4::showPlayer3cards(Player &aGenericPlayer){
    //int card_num = aGenericPlayer.GetNum();
    vector<card*>::const_iterator iter; //采取枚举的显示牌的方式（开始挨骂）
    for (iter = aGenericPlayer.m_cards.begin(); iter != aGenericPlayer.m_cards.end(); ++iter){
        QLabel *label = new QLabel;
        if (!(*iter)->m_IsFaceUp) {
            label->setPixmap(QPixmap(":/images/cb.png"));
        } else {
            if ((*iter)->m_Suit == card::SPADES) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/as.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2s.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3s.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4s.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5s.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6s.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7s.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8s.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9s.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/ts.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/js.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qs.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/ks.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::HEARTS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ah.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2h.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3h.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4h.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5h.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6h.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7h.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8h.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9h.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/th.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jh.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qh.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kh.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::CLUBS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ac.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2c.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3c.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4c.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5c.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6c.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7c.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8c.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9c.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/tc.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jc.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qc.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kc.png"));
                        break;
                }
            } else {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ad.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2d.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3d.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4d.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5d.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6d.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7d.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8d.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9d.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/td.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jd.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qd.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kd.png"));
                        break;
                }
            }
        }
        label->setParent(this); //设定父类一起显示
        c3_list.append(label);
    }
}
void form4::showPlayer4cards(Player &aGenericPlayer){
    //int card_num = aGenericPlayer.GetNum();
    vector<card*>::const_iterator iter;
    for (iter = aGenericPlayer.m_cards.begin(); iter != aGenericPlayer.m_cards.end(); ++iter){
        QLabel *label = new QLabel;
        if (!(*iter)->m_IsFaceUp) {
            label->setPixmap(QPixmap(":/images/cb.png"));
        } else {
            if ((*iter)->m_Suit == card::SPADES) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/as.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2s.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3s.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4s.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5s.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6s.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7s.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8s.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9s.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/ts.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/js.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qs.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/ks.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::HEARTS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ah.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2h.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3h.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4h.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5h.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6h.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7h.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8h.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9h.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/th.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jh.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qh.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kh.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::CLUBS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ac.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2c.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3c.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4c.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5c.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6c.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7c.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8c.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9c.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/tc.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jc.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qc.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kc.png"));
                        break;
                }
            } else {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ad.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2d.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3d.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4d.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5d.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6d.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7d.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8d.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9d.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/td.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jd.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qd.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kd.png"));
                        break;
                }
            }
        }
        label->setParent(this);
        c4_list.append(label);
    }
}
void form4::showHousecards(House &aGenericPlayer){
    //int card_num = aGenericPlayer.GetNum();
    vector<card*>::const_iterator iter;
    for (iter = aGenericPlayer.m_cards.begin(); iter != aGenericPlayer.m_cards.end(); ++iter){
        QLabel *label = new QLabel;
        if (!(*iter)->m_IsFaceUp) {
            label->setPixmap(QPixmap(":/images/cb.png"));
        } else {
            if ((*iter)->m_Suit == card::SPADES) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/as.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2s.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3s.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4s.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5s.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6s.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7s.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8s.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9s.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/ts.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/js.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qs.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/ks.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::HEARTS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ah.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2h.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3h.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4h.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5h.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6h.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7h.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8h.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9h.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/th.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jh.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qh.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kh.png"));
                        break;
                }
            } else if ((*iter)->m_Suit == card::CLUBS) {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ac.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2c.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3c.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4c.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5c.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6c.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7c.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8c.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9c.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/tc.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jc.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qc.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kc.png"));
                        break;
                }
            } else {
                switch ((*iter)->m_Rank) {
                    case card::ACE :
                        label->setPixmap(QPixmap(":/images/ad.png"));
                        break;
                    case card::TWO :
                        label->setPixmap(QPixmap(":/images/2d.png"));
                        break;
                    case card::THREE :
                        label->setPixmap(QPixmap(":/images/3d.png"));
                        break;
                    case card::FOUR :
                        label->setPixmap(QPixmap(":/images/4d.png"));
                        break;
                    case card::FIVE :
                        label->setPixmap(QPixmap(":/images/5d.png"));
                        break;
                    case card::SIX :
                        label->setPixmap(QPixmap(":/images/6d.png"));
                        break;
                    case card::SEVEN :
                        label->setPixmap(QPixmap(":/images/7d.png"));
                        break;
                    case card::EIGHT :
                        label->setPixmap(QPixmap(":/images/8d.png"));
                        break;
                    case card::NINE :
                        label->setPixmap(QPixmap(":/images/9d.png"));
                        break;
                    case card::TEN :
                        label->setPixmap(QPixmap(":/images/td.png"));
                        break;
                    case card::JACK :
                        label->setPixmap(QPixmap(":/images/jd.png"));
                        break;
                    case card::QUEEN :
                        label->setPixmap(QPixmap(":/images/qd.png"));
                        break;
                    default:
                        label->setPixmap(QPixmap(":/images/kd.png"));
                        break;
                }
            }
        }
        label->setParent(this);
        h_list.append(label);
    }
}
void form4::cleanHousecards(){
    h_list.clear();
}

void form4::cleanPlayer1cards(){
    c1_list.clear();
}

void form4::cleanPlayer2cards(){
    c2_list.clear();
}

void form4::cleanPlayer3cards(){
    c3_list.clear();
}

void form4::cleanPlayer4cards(){
    c4_list.clear();
}

void form4::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void form4::on_exitbtn_clicked()
{
    this->close();
    emit form4show();
}
