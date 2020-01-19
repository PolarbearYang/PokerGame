#include "form1.h"
#include "ui_form1.h"
#include <welcome.h>
#include <host.h>
Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
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
    hit_btn = new mybutton;
    stand_btn = new mybutton;
    hit_btn->pix = new QPixmap(":/images/hit1.png");
    hit_btn->pix_blue = new QPixmap(":/images/hit2.png");
    hit_btn->setIcon(*hit_btn->pix);
    hit_btn->setIconSize(QSize(80,40));
    hit_btn->setFixedSize(60,30);
    hit_btn->move(435,450);
    hit_btn->setParent(this);
    stand_btn->pix = new QPixmap(":/images/stand1.png");
    stand_btn->pix_blue = new QPixmap(":/images/stand2.png");
    stand_btn->setIcon(*stand_btn->pix);
    stand_btn->setIconSize(QSize(80,40));
    stand_btn->setFixedSize(60,30);
    stand_btn->move(535,450);
    stand_btn->setParent((this));
    hit_btn->hide();
    stand_btn->hide();
    connect(stand_btn,SIGNAL(clicked()),this,SLOT(player1stay()));
    connect(hit_btn,SIGNAL(clicked()),this,SLOT(player1hit()));
    c1 = new client;
    c2 = new client;
    c3 = new client;
    c4 = new client;
    QFont ft("Times New Roman", 11, 75);
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
    c2back = new QLabel;
    c2a = new QLabel;
    c2n = new QLabel;
    c2m = new QLabel;
    c2back->setParent(this);
    c2a->setParent(this);
    c2n->setParent(this);
    c2m->setParent(this);
    c3back = new QLabel;
    c3a = new QLabel;
    c3n = new QLabel;
    c3m = new QLabel;
    c3back->setParent(this);
    c3a->setParent(this);
    c3n->setParent(this);
    c3m->setParent(this);
    c4back = new QLabel;
    c4a = new QLabel;
    c4n = new QLabel;
    c4m = new QLabel;
    c4back->setParent(this);
    c4a->setParent(this);
    c4n->setParent(this);
    c4m->setParent(this);
    QPixmap pix;
    c1->setava(welcome::m_ava);
    c1->setname(welcome::m_name);
    //c2->setava(2);
    //c2->setname("Chains");
    //c3->setava(6);
    //c3->setname("Bain");
    //c4->setava(5);
    //c4->setname("Jacket");
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
        case 6:
            pix.load(":/images/Bain.png");
            break;
        default:
            pix.load(":/images/Bot.png");
            break;
    }
    pix = pix.scaled(QSize(80,80),Qt::KeepAspectRatio);
    c1a->setPixmap(pix);
    c1back->setPixmap(QPixmap(":/images/back1.png"));
    c1back->move(630, 500);
    c1a->move(635, 510);
    c1n->setText("P1: " + c1->c_name);
    c1m->setText("Money: " + QString::number(p1Player.m_money));
    c1n->move(720, 525);
    c1m->setFont(ft);
    c1m->setPalette(pa);
    c1n->setFont(ft);
    c1n->setPalette(pa);
    c1m->move(720, 555);
    c2back->setPixmap(QPixmap(":/images/back1.png"));
    c2back->move(630, 200);
    c2m->setText("Money: " + QString::number(p2Player.m_money));
    c2m->move(720, 255);
    c2m->setFont(ft);
    c2m->setPalette(pa);
    c3back->setPixmap(QPixmap(":/images/back1.png"));
    c3back->move(200, 100);
    c3m->setText("Money: " + QString::number(p3Player.m_money));
    c3m->move(290, 155);
    c3m->setFont(ft);
    c3m->setPalette(pa);
    c4back->setPixmap(QPixmap(":/images/back1.png"));
    c4back->move(200, 400);
    c4m->setText("Money: " + QString::number(p4Player.m_money));
    c4m->move(290, 450);
    c4m->setFont(ft);
    c4m->setPalette(pa);
    /*c4n->setText("P4: " + c4->c_name);
    c4n->setFont(ft);
    c4n->setPalette(pa);
    c4n->move(290, 415);
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
    c4a->move(205, 410);
    c2n->setText("P2: " + c2->c_name);
    c2n->setFont(ft);
    c2n->setPalette(pa);
    c2n->move(720, 220);
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
    c2a->move(635, 210);
    c3n->setText("P3: " + c3->c_name);
    c3n->setFont(ft);
    c3n->setPalette(pa);
    c3n->move(290, 120);
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
    c3a->move(205, 110);*/
    //ui->label_13->setText(c4->c_name + ": ");
    ui->label_4->setText(c1->c_name + ": ");
    //ui->label_6->setText(c2->c_name + ": ");
    //ui->label_8->setText(c3->c_name + ": ");
    this->setWindowTitle("BlackJack");
    this->isconnetion = false;
    //初始化sendMesSocket
    this->TCP_sendMesSocket = new QTcpSocket();
    //终止之前的连接，重置套接字
    TCP_sendMesSocket->abort();
    ui->label_3->setText(QString::number(House::h_total));
    ui->label_5->setText(QString::number(Player::p1_total));
    ui->label_7->setText(QString::number(Player::p2_total));
    ui->label_9->setText(QString::number(Player::p3_total));
    ui->label_14->setText(QString::number(Player::p4_total));
    ui->label_11->setText(QString::number(Deck::c_left));
    //给定IP和端口号，连接服务器
    //qDebug() << host::ip;
    this->TCP_sendMesSocket->connectToHost(host::ip,8888);
    //this->TCP_sendMesSocket->connectToHost("127.0.0.1",8888);
    //成功连接服务器的connected()信号连接到slot_connected() (注意：不是connect()信号)
    //connect(ui->sendbtn,SIGNAL(clicked()),this,SLOT(slot_sendmessage()));
    connect(TCP_sendMesSocket,SIGNAL(connected()),this,SLOT(slot_connected()));
    //发送按钮的clicked()信号连接到slot_sendmessage()
    //connect(ui->pushButton_send,SIGNAL(clicked()),this,SLOT(slot_sendmessage()));
    //有新数据到达时的readyread()信号连接到slot_recvmessage()
    connect(TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
    //与服务器断开连接的disconnected()信号连接到slot_disconnect()
    connect(TCP_sendMesSocket,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
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

Form1::~Form1()
{
    delete ui;
}

//处理成功连接到服务器的槽
void Form1::slot_connected()
{
    this->isconnetion = true;
    ui->label->setText("Login!");
    if(this->isconnetion)
    {
        QString sendMessage1;
        sendMessage1 = "N";
        sendMessage1 += c1->c_name;
        sendMessage1 += QString::number(c1->c_ava);
        this->TCP_sendMesSocket->write(sendMessage1.toLatin1());
    }
    else
        QMessageBox::warning(this,"Error","No server!",QMessageBox::Ok);
}

void Form1::shuffle(){
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
    hit_btn->hide();
    stand_btn->hide();
    this->play();
}
//接收来自服务器的消息的槽
void Form1::begin()
{
    /*if(this->isconnetion)
    {
        QString sendMessage1;
        sendMessage1 = "N";
        sendMessage1 += c1->c_name;
        sendMessage1 += QString::number(c1->c_ava);
        this->TCP_sendMesSocket->write(sendMessage1.toLatin1());
    }
    else
        QMessageBox::warning(this,"Error","No server!",QMessageBox::Ok);*/
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
    hit_btn->hide();
    stand_btn->hide();
    this->play();
}
void Form1::slot_recvmessage()
{
    QFont ft("Times New Roman", 11, 75);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    QByteArray byteArray = this->TCP_sendMesSocket->readAll();
    QString recvMessage = byteArray;
        if (recvMessage[0] == 'N'){
            QString c4name;
            for (int i=1; i<recvMessage.length()-1; i++){
                c4name += recvMessage[i];
            }
            c4->setname(c4name);
            c4n->setText("P4: " + c4->c_name);
            c4n->setFont(ft);
            c4n->setPalette(pa);
            c4n->move(290, 415);
            int avv;
            QString avvv;
            avvv += recvMessage[recvMessage.length()-1];
            avv = avvv.toInt();
            c4->setava(avv);
            QPixmap pixx;
            switch (c4->c_ava) {
                case 1:
                    pixx.load(":/images/Dallas.png");
                    break;
                case 2:
                    pixx.load(":/images/Chains.png");
                    break;
                case 3:
                    pixx.load(":/images/Wolf.png");
                    break;
                case 4:
                    pixx.load(":/images/Houston.png");
                    break;
                case 5:
                    pixx.load(":/images/Jacket.png");
                    break;
                case 6:
                    pixx.load(":/images/Bain.png");
                    break;
                default:
                    pixx.load(":/images/Bot.png");
                    break;
            }
            pixx = pixx.scaled(QSize(80,80),Qt::KeepAspectRatio);
            c4a->setPixmap(pixx);
            c4a->move(205, 410);
            ui->label_13->setText(c4->c_name + ": ");
        } else {
            if (recvMessage[0] == '0'){
                player4stay();
            } else {
                if (recvMessage[0] == '1'){
                    player4hit();
                } else {
                    if (recvMessage[0] == 'c'){
                        shuffle();
                    } else {
                        if (recvMessage[0] == 'O'){
                            if (recvMessage[1] == '1'){
                                player2hit();
                            } else {
                                if (recvMessage[1] == '0'){
                                    player2stay();
                                } else {
                                    if (recvMessage[1] == 'N'){
                                        QString c2name;
                                        for (int i=2; i<recvMessage.length()-1; i++){
                                            c2name += recvMessage[i];
                                        }
                                        c2->setname(c2name);
                                        c2n->setText("P2: " + c2->c_name);
                                        c2n->setFont(ft);
                                        c2n->setPalette(pa);
                                        c2n->move(720, 220);
                                        ui->label_6->setText(c2->c_name + ": ");
                                        int avv;
                                        QString avvv;
                                        avvv += recvMessage[recvMessage.length()-1];
                                        avv = avvv.toInt();
                                        c2->setava(avv);
                                        QPixmap pixx;
                                        switch (c2->c_ava) {
                                            case 1:
                                                pixx.load(":/images/Dallas.png");
                                                break;
                                            case 2:
                                                pixx.load(":/images/Chains.png");
                                                break;
                                            case 3:
                                                pixx.load(":/images/Wolf.png");
                                                break;
                                            case 4:
                                                pixx.load(":/images/Houston.png");
                                                break;
                                            case 5:
                                                pixx.load(":/images/Jacket.png");
                                                break;
                                            case 6:
                                                pixx.load(":/images/Bain.png");
                                                break;
                                            default:
                                                pixx.load(":/images/Bot.png");
                                                break;
                                        }
                                        pixx = pixx.scaled(QSize(80,80),Qt::KeepAspectRatio);
                                        c2a->setPixmap(pixx);
                                        c2a->move(635, 210);
                                    }
                                }
                            }
                        } else{
                            if (recvMessage[0] == 'P'){
                                if (recvMessage[1] == '1'){
                                    player3hit();
                                } else {
                                    if (recvMessage[1] == '0'){
                                        player3stay();
                                    } else {
                                        if (recvMessage[1] == '0'){
                                            player2stay();
                                        } else {
                                            if (recvMessage[1] == 'N'){
                                                QString c3name;
                                                for (int i=2; i<recvMessage.length()-1; i++){
                                                    c3name += recvMessage[i];
                                                }
                                                c3->setname(c3name);
                                                c3n->setText("P3: " + c3->c_name);
                                                c3n->setFont(ft);
                                                c3n->setPalette(pa);
                                                c3n->move(290, 120);
                                                int avv;
                                                QString avvv;
                                                avvv += recvMessage[recvMessage.length()-1];
                                                avv = avvv.toInt();
                                                c3->setava(avv);
                                                QPixmap pixx;
                                                switch (c3->c_ava) {
                                                    case 1:
                                                        pixx.load(":/images/Dallas.png");
                                                        break;
                                                    case 2:
                                                        pixx.load(":/images/Chains.png");
                                                        break;
                                                    case 3:
                                                        pixx.load(":/images/Wolf.png");
                                                        break;
                                                    case 4:
                                                        pixx.load(":/images/Houston.png");
                                                        break;
                                                    case 5:
                                                        pixx.load(":/images/Jacket.png");
                                                        break;
                                                    case 6:
                                                        pixx.load(":/images/Bain.png");
                                                        break;
                                                    default:
                                                        pixx.load(":/images/Bot.png");
                                                        break;
                                                }
                                                pixx = pixx.scaled(QSize(80,80),Qt::KeepAspectRatio);
                                                c3a->setPixmap(pixx);
                                                c3a->move(205, 110);
                                                ui->label_8->setText(c3->c_name + ": ");
                                            }
                                       }
                                    }
                                }
                            } else {
                                m_Deck.Clear();
                                for (int i = 0; i < recvMessage.length(); i += 2){
                                    if (recvMessage[i+1] == 's') {
                                        switch (recvMessage[i].toLatin1()) {
                                            case 'a':
                                                m_Deck.Add(new card(card::ACE, card::SPADES));
                                                break;
                                            case '2':
                                                m_Deck.Add(new card(card::TWO, card::SPADES));
                                                break;
                                            case '3':
                                                m_Deck.Add(new card(card::THREE, card::SPADES));
                                                break;
                                            case '4':
                                                m_Deck.Add(new card(card::FOUR, card::SPADES));
                                                break;
                                            case '5':
                                                m_Deck.Add(new card(card::FIVE, card::SPADES));
                                                break;
                                            case '6':
                                                m_Deck.Add(new card(card::SIX, card::SPADES));
                                                break;
                                            case '7':
                                                m_Deck.Add(new card(card::SEVEN, card::SPADES));
                                                break;
                                            case '8':
                                                m_Deck.Add(new card(card::EIGHT, card::SPADES));
                                                break;
                                            case '9':
                                                m_Deck.Add(new card(card::NINE, card::SPADES));
                                                break;
                                            case 't':
                                                m_Deck.Add(new card(card::TEN, card::SPADES));
                                                break;
                                            case 'j':
                                                m_Deck.Add(new card(card::JACK, card::SPADES));
                                                break;
                                            case 'q':
                                                m_Deck.Add(new card(card::QUEEN, card::SPADES));
                                                break;
                                            default:
                                                m_Deck.Add(new card(card::KING, card::SPADES));
                                                break;
                                        }
                                    } else if (recvMessage[i+1] == 'h') {
                                        switch (recvMessage[i].toLatin1()) {
                                            case 'a':
                                                m_Deck.Add(new card(card::ACE, card::HEARTS));
                                                break;
                                            case '2':
                                                m_Deck.Add(new card(card::TWO, card::HEARTS));
                                                break;
                                            case '3':
                                                m_Deck.Add(new card(card::THREE, card::HEARTS));
                                                break;
                                            case '4':
                                                m_Deck.Add(new card(card::FOUR, card::HEARTS));
                                                break;
                                            case '5':
                                                m_Deck.Add(new card(card::FIVE, card::HEARTS));
                                                break;
                                            case '6':
                                                m_Deck.Add(new card(card::SIX, card::HEARTS));
                                                break;
                                            case '7':
                                                m_Deck.Add(new card(card::SEVEN, card::HEARTS));
                                                break;
                                            case '8':
                                                m_Deck.Add(new card(card::EIGHT, card::HEARTS));
                                                break;
                                            case '9':
                                                m_Deck.Add(new card(card::NINE, card::HEARTS));
                                                break;
                                            case 't':
                                                m_Deck.Add(new card(card::TEN, card::HEARTS));
                                                break;
                                            case 'j':
                                                m_Deck.Add(new card(card::JACK, card::HEARTS));
                                                break;
                                            case 'q':
                                                m_Deck.Add(new card(card::QUEEN, card::HEARTS));
                                                break;
                                            default:
                                                m_Deck.Add(new card(card::KING, card::HEARTS));
                                                break;
                                        }
                                    } else if (recvMessage[i+1] == 'c') {
                                        switch (recvMessage[i].toLatin1()) {
                                            case 'a':
                                                m_Deck.Add(new card(card::ACE, card::CLUBS));
                                                break;
                                            case '2':
                                                m_Deck.Add(new card(card::TWO, card::CLUBS));
                                                break;
                                            case '3':
                                                m_Deck.Add(new card(card::THREE, card::CLUBS));
                                                break;
                                            case '4':
                                                m_Deck.Add(new card(card::FOUR, card::CLUBS));
                                                break;
                                            case '5':
                                                m_Deck.Add(new card(card::FIVE, card::CLUBS));
                                                break;
                                            case '6':
                                                m_Deck.Add(new card(card::SIX, card::CLUBS));
                                                break;
                                            case '7':
                                                m_Deck.Add(new card(card::SEVEN, card::CLUBS));
                                                break;
                                            case '8':
                                                m_Deck.Add(new card(card::EIGHT, card::CLUBS));
                                                break;
                                            case '9':
                                                m_Deck.Add(new card(card::NINE, card::CLUBS));
                                                break;
                                            case 't':
                                                m_Deck.Add(new card(card::TEN, card::CLUBS));
                                                break;
                                            case 'j':
                                                m_Deck.Add(new card(card::JACK, card::CLUBS));
                                                break;
                                            case 'q':
                                                m_Deck.Add(new card(card::QUEEN, card::CLUBS));
                                                break;
                                            default:
                                                m_Deck.Add(new card(card::KING, card::CLUBS));
                                                break;
                                        }
                                    } else {
                                        switch (recvMessage[i].toLatin1()) {
                                            case 'a':
                                                m_Deck.Add(new card(card::ACE, card::DIAMONDS));
                                                break;
                                            case '2':
                                                m_Deck.Add(new card(card::TWO, card::DIAMONDS));
                                                break;
                                            case '3':
                                                m_Deck.Add(new card(card::THREE, card::DIAMONDS));
                                                break;
                                            case '4':
                                                m_Deck.Add(new card(card::FOUR, card::DIAMONDS));
                                                break;
                                            case '5':
                                                m_Deck.Add(new card(card::FIVE, card::DIAMONDS));
                                                break;
                                            case '6':
                                                m_Deck.Add(new card(card::SIX, card::DIAMONDS));
                                                break;
                                            case '7':
                                                m_Deck.Add(new card(card::SEVEN, card::DIAMONDS));
                                                break;
                                            case '8':
                                                m_Deck.Add(new card(card::EIGHT, card::DIAMONDS));
                                                break;
                                            case '9':
                                                m_Deck.Add(new card(card::NINE, card::DIAMONDS));
                                                break;
                                            case 't':
                                                m_Deck.Add(new card(card::TEN, card::DIAMONDS));
                                                break;
                                            case 'j':
                                                m_Deck.Add(new card(card::JACK, card::DIAMONDS));
                                                break;
                                            case 'q':
                                                m_Deck.Add(new card(card::QUEEN, card::DIAMONDS));
                                                break;
                                            default:
                                                m_Deck.Add(new card(card::KING, card::DIAMONDS));
                                                break;
                                        }
                                    }
                                }
                                begin();
                            }
                        }
                    }
                }
            }
        }
}
//取消与服务器连接的槽
void Form1::slot_disconnect()
{
    QMessageBox::warning(this,"Warning","Connection down!",QMessageBox::Ok);
    emit Form1show();
    TCP_sendMesSocket->close();
    TCP_sendMesSocket->deleteLater();
    this->close();
}
void Form1::player1hit(){
    if (m_Deck.GetNum()>=1){
        if(this->isconnetion)
        {
            QString sendMessage = "1";
            this->TCP_sendMesSocket->write(sendMessage.toLatin1());
        }
        else
            QMessageBox::warning(this,"Error","No server!",QMessageBox::Ok);
        m_Deck.Deal(p1Player);
        int card_num = p1Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c1_list[i]->hide();  //隐藏所有手牌
        }
        cleanPlayer1cards();
        showPlayer1cards(p1Player);
        for (int i = 0; i < card_num ; i++){
            c1_list[i]->move(535-(card_num-1-i)*100,500); //再显示所有手牌
            c1_list[i]->show();
        }
        if (p1Player.GetTotal() <= 21){
            Player::p1_total = p1Player.GetTotal();
            ui->label_5->setText(QString::number(Player::p1_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
        } else {
            hit_btn->hide();
            stand_btn->hide();
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            p1Player.Bust();
            ui->label_5->setText("Bust");
            w->setText("You bust!");
            w->show();
        }
    } else {
        if(this->isconnetion)
        {
            QString sendMessage = "1";
            this->TCP_sendMesSocket->write(sendMessage.toLatin1());
        }
        else
            QMessageBox::warning(this,"Error","No server!",QMessageBox::Ok);
    }
}
void Form1::player2hit(){
        m_Deck.Deal(p2Player);
        int card_num = p2Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c2_list[i]->hide();  //隐藏所有手牌
        }
        cleanPlayer2cards(); //清空记录手牌的全局变量
        showPlayer2cards(p2Player);
        for (int i = 0; i < card_num ; i++){
            c2_list[i]->move(880,200+(card_num-1-i)*100); //再显示所有手牌
            c2_list[i]->show();
        }
        if (p2Player.GetTotal() <= 21){
            Player::p2_total = p2Player.GetTotal();
            ui->label_7->setText(QString::number(Player::p2_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
            p2Player.Bust();
            ui->label_7->setText("Bust");
        }
}
void Form1::player3hit(){
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
            ui->label_9->setText(QString::number(Player::p3_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            p3Player.Bust();
            ui->label_11->setText(QString::number(Deck::c_left));
            ui->label_9->setText("Bust");
        }
}

void Form1::player4hit(){
        m_Deck.Deal(p4Player);
        int card_num = p4Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c4_list[i]->hide();
        }
        cleanPlayer4cards();
        showPlayer4cards(p4Player);
        for (int i = 0; i < card_num ; i++){
            c4_list[i]->move(30, 200+(card_num-1-i)*100);
            c4_list[i]->show();
        }
        if (p4Player.GetTotal() <= 21){
            Player::p4_total = p4Player.GetTotal();
            ui->label_14->setText(QString::number(Player::p4_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
            ui->label_14->setText("Bust");
            p4Player.Bust();
            endgame();
        }
}
void Form1::player1stay(){
    if(this->isconnetion)
    {
        QString sendMessage = "0";
        this->TCP_sendMesSocket->write(sendMessage.toLatin1());
    }
    else
        QMessageBox::warning(this,"Error","No server!",QMessageBox::Ok);
    hit_btn->hide();
    stand_btn->hide();
}
void Form1::player2stay(){
}
void Form1::player3stay(){
}
void Form1::player4stay(){
    endgame();
}
void Form1::play(){
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
    //qDebug() << p1Player.GetNum();
    m_House.FlipFirstCard();
    showHousecards(m_House);
    h_list[0]->move(435,300);
    h_list[1]->move(535,300);
    h_list[0]->show();
    h_list[1]->show();
    showPlayer1cards(p1Player);
    c1_list[0]->move(435,500);
    c1_list[1]->move(535,500);
    c1_list[0]->show();
    c1_list[1]->show();
    showPlayer2cards(p2Player);
    c2_list[0]->move(880,300);
    c2_list[1]->move(880,200);
    c2_list[0]->show();
    c2_list[1]->show();
    showPlayer3cards(p3Player);
    c3_list[0]->move(535,100);
    c3_list[1]->move(435,100);
    c3_list[0]->show();
    c3_list[1]->show();
    showPlayer4cards(p4Player);
    c4_list[0]->move(30,300);
    c4_list[1]->move(30,200);
    c4_list[0]->show();
    c4_list[1]->show();
    Player::p1_total = p1Player.GetTotal();
    Player::p2_total = p2Player.GetTotal();
    Player::p3_total = p3Player.GetTotal();
    Player::p4_total = p4Player.GetTotal();
    House::h_total = m_House.GetTotal();
    Deck::c_left = m_Deck.GetNum();
    ui->label_3->setText(QString::number(House::h_total));
    ui->label_5->setText(QString::number(Player::p1_total));
    ui->label_7->setText(QString::number(Player::p2_total));
    ui->label_9->setText(QString::number(Player::p3_total));
    ui->label_14->setText(QString::number(Player::p4_total));
    ui->label_11->setText(QString::number(Deck::c_left));
    hit_btn->show();
    stand_btn->show();
}

void Form1::endgame(){
    m_House.FlipFirstCard();
    House::h_total = m_House.GetTotal();
    cleanHousecards();
    QString edd="";
    showHousecards(m_House);
    h_list[0]->move(435,300);
    h_list[1]->move(535,300);
    this->sleep(1000);
    h_list[0]->show();
    h_list[1]->show();
    ui->label_3->setText(QString::number(House::h_total));
    QLabel *w = new QLabel;
    w->resize(200,100);
    w->move(750,400);
    w->setAlignment(Qt::AlignCenter);
    if ((p1Player.GetTotal() > 21) && (p2Player.GetTotal() > 21) && (p3Player.GetTotal() > 21) && (p4Player.GetTotal() > 21)){
        edd += "You Lose!\n";
        edd += c2->c_name + " Loses!\n";
        edd += c3->c_name + " Loses!\n";
        edd += c4->c_name + " Loses!\n";
    } else {
        while (m_House.IsHitting() && (m_Deck.GetNum()>=1)){
            this->sleep(1000);
            m_Deck.Deal(m_House);
            Deck::c_left = m_Deck.GetNum();
            ui->label_11->setText(QString::number(Deck::c_left));
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
                ui->label_3->setText(QString::number(House::h_total));
            } else {
                ui->label_3->setText("Bust");
            }
        }
        if (m_House.IsBusted()){
            if (!(p1Player.IsBusted())){
                p1Player.Win();
                edd += "You win!\n";
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
                    edd += "You win!\n";
                } else if (p1Player.GetTotal() < m_House.GetTotal()){
                    p1Player.Lose();
                    edd += "You lose!\n";
                } else {
                    p1Player.Push();
                    edd += "You push!\n";
                }
            } else {
                edd += "You lose!\n";
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
void Form1::showPlayer1cards(Player &aGenericPlayer){
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
        label->setParent(this);
        c1_list.append(label);
    }
}
void Form1::showPlayer2cards(Player &aGenericPlayer){
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
        label->setParent(this);
        c2_list.append(label);
    }
}
void Form1::showPlayer3cards(Player &aGenericPlayer){
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
        label->setParent(this);
        c3_list.append(label);
    }
}
void Form1::showPlayer4cards(Player &aGenericPlayer){
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
        label->setParent(this);
        c4_list.append(label);
    }
}
void Form1::showHousecards(House &aGenericPlayer){
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
void Form1::cleanHousecards(){
    h_list.clear();
}

void Form1::cleanPlayer1cards(){
    c1_list.clear();
}

void Form1::cleanPlayer2cards(){
    c2_list.clear();
}

void Form1::cleanPlayer3cards(){
    c3_list.clear();
}

void Form1::cleanPlayer4cards(){
    c4_list.clear();
}
void Form1::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void Form1::on_pushButton_clicked()
{
    emit Form1show();
    TCP_sendMesSocket->close();
    TCP_sendMesSocket->deleteLater();
    this->close();
}
