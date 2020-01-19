#include "form.h"
#include "ui_form.h"
#include <welcome.h>

int Form::num_player=0;
int Form::all_num=3;
int Form::pre_num=0;
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    Form::pre_num = 0;
    Form::num_player = 0;
    Deck::c_left = 52;
    Player::p1_total = 0;
    Player::p2_total = 0;
    Player::p3_total = 0;
    Player::p4_total = 0;
    House::h_total = 0;
    this->setWindowTitle("BlackJack");
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
    connect(stand_btn,SIGNAL(clicked()),this,SLOT(player4stay()));
    connect(hit_btn,SIGNAL(clicked()),this,SLOT(player4hit()));
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
    //c2->setname("Chains");
    //c2->setava(2);
    //c3->setname("Bain");
    //c3->setava(6);
    //c4->setname("Houston");
    //c4->setava(4);
    c4->setava(welcome::m_ava);
    c4->setname(welcome::m_name);
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
    c4back->move(630, 500);
    c4a->move(635, 510);
    c4n->setText("P4: " + c4->c_name);
    c4m->setText("Money: " + QString::number(p4Player.m_money));
    c4n->move(720, 525);
    c4m->setFont(ft);
    c4m->setPalette(pa);
    c4n->setFont(ft);
    c4n->setPalette(pa);
    c4m->move(720, 555);
    c1back->setPixmap(QPixmap(":/images/back1.png"));
    c1back->move(630, 200);
    c1m->setText("Money: " + QString::number(p1Player.m_money));
    c1m->move(720, 255);
    c1m->setFont(ft);
    c1m->setPalette(pa);
    c2back->setPixmap(QPixmap(":/images/back1.png"));
    c2back->move(200, 100);
    c2m->setText("Money: " + QString::number(p2Player.m_money));
    c2m->move(290, 155);
    c2m->setFont(ft);
    c2m->setPalette(pa);
    c3back->setPixmap(QPixmap(":/images/back1.png"));
    c3back->move(200, 400);
    c3m->setText("Money: " + QString::number(p3Player.m_money));
    c3m->move(290, 450);
    c3m->setFont(ft);
    c3m->setPalette(pa);
    /*c1->setname("Dallas");
    c1n->setText("P1: " + c1->c_name);
    c1n->setFont(ft);
    c1n->setPalette(pa);
    c1n->move(720, 220);
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
    c1a->move(635, 210);
    c2n->setText("P2: " + c2->c_name);
    c2n->setFont(ft);
    c2n->setPalette(pa);
    c2n->move(290, 120);
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
    c2a->move(205, 110);
    c3n->setText("P3: " + c3->c_name);
    c3n->setFont(ft);
    c3n->setPalette(pa);
    c3n->move(290, 415);
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
    c3a->move(205, 410);*/
    this->setWindowTitle("BlackJack");
    ui->label_12->setText(c4->c_name + ": ");
    //ui->label_4->setText(c1->c_name + ": ");
    //ui->label_8->setText(c2->c_name + ": ");
    //ui->label_10->setText(c3->c_name + ": ");
    ui->label_7->setText(QString::number(Deck::c_left));
    ui->label_5->setText(QString::number(Player::p1_total));
    ui->label_3->setText(QString::number(House::h_total));
    ui->label_9->setText(QString::number(Player::p2_total));
    ui->label_11->setText(QString::number(Player::p3_total));
    ui->label_13->setText(QString::number(Player::p4_total));
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
    mSocket = new QUdpSocket();
    mSocket->bind(QHostAddress::AnyIPv4,6666);
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
    TCP_server = new QTcpServer();
    TCP_connectSocket1 = nullptr;
    TCP_connectSocket2 = nullptr;
    TCP_connectSocket3 = nullptr;
    ui->label_3->setText(QString::number(House::h_total));
    ui->label_5->setText(QString::number(Player::p1_total));
    ui->label_7->setText(QString::number(Deck::c_left));
    connect(ui->beginbtn,SIGNAL(clicked()),this,SLOT(begin()));
    connect(ui->shufflebtn,SIGNAL(clicked()),this,SLOT(shuffle()));
    //调用listen函数监听同时绑定IP和端口号
    if(TCP_server->listen(QHostAddress("0.0.0.0"),8888)) //判断listen是否成功，成功则继续执行，连接新接收信号槽
    {
        this->connect(TCP_server,SIGNAL(newConnection()),this,SLOT(slot_newconnect()));  //将服务器的新连接信号连接到接收新连接的槽
    } else {
        QMessageBox::critical(this,"Error","IP wrong!");
    }
}
void Form::read_data(){
    QByteArray array;
    QHostAddress address;
    quint16 port;
    array.resize(mSocket->bytesAvailable());
    mSocket->readDatagram(array.data(),array.size(),&address,&port);
    QString s;
    s.prepend(array);
    QString ip;
    if (s[0]=='f'){
        ip = "s";
        ip += QString::number(Form::num_player);
        ip += QString::number(Form::all_num);
        ip += QString::number(welcome::m_ava);
        ip += welcome::m_name;
        array=ip.toLatin1();
        mSocket->writeDatagram(array,address,port);
    } else {
        if(s[0]=='c'){
            ip = "c";
            ip += QString::number(Form::pre_num);
            ip += QString::number(Form::all_num);
            Form::pre_num++;
            array=ip.toLatin1();
            mSocket->writeDatagram(array,address,port);
        }
    }
}
Form::~Form()
{
    delete ui;
}

//建立新连接的槽
void Form::slot_newconnect()
{
    QString sendMessage;
    sendMessage = "N";
    sendMessage += c4->c_name;
    sendMessage += QString::number(c4->c_ava);
    if(TCP_server->hasPendingConnections())  //查询是否有新连接
    {
        if (Form::num_player==0){
            TCP_connectSocket1 = TCP_server->nextPendingConnection();
            ui->label->setText("P1 ready!");
            Form::num_player++;
            this->connect(TCP_connectSocket1,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
            this->connect(TCP_connectSocket1,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
            TCP_connectSocket1->write(sendMessage.toLatin1());
        } else {
            if (Form::num_player==1){
                TCP_connectSocket2 = TCP_server->nextPendingConnection();
                ui->label_14->setText("P2 ready!");
                Form::num_player++;
                this->connect(TCP_connectSocket2,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
                this->connect(TCP_connectSocket2,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
                sendMessage += "#";
                sendMessage += c1->c_name;
                sendMessage += QString::number(c1->c_ava);
                TCP_connectSocket2->write(sendMessage.toLatin1());
            } else {
                if (Form::num_player==2){
                    TCP_connectSocket3 = TCP_server->nextPendingConnection();
                    ui->label_15->setText("P3 ready!");
                    Form::num_player++;
                    this->connect(TCP_connectSocket3,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
                    this->connect(TCP_connectSocket3,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));
                    sendMessage += "#";
                    sendMessage += c1->c_name;
                    sendMessage += QString::number(c1->c_ava);
                    sendMessage += "#";
                    sendMessage += c2->c_name;
                    sendMessage += QString::number(c2->c_ava);
                    TCP_connectSocket3->write(sendMessage.toLatin1());
                } else {
                    QMessageBox::critical(this,"Error","Too many players!");
                }
            }
        }

    }
}

void Form::shuffle(){
    if (m_Deck.GetNum()!=52){
        if (m_Deck.GetNum()>=10){
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
            hit_btn->hide();
            stand_btn->hide();
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
            QString sendMessage = "c";
            if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket1->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket2->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket3->write(sendMessage.toLatin1());
            }
            this->play();
        } else {
            this->begin();
            QMessageBox::critical(this,"Warning","No cards!");
        }
    } else {
        this->begin();
    }
}

void Form::begin()
{
    if (num_player == 3){
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
            hit_btn->hide();
            stand_btn->hide();
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
            QString sendMessage;
            vector<card*>::const_iterator iter;
            for (iter = m_Deck.m_cards.begin(); iter != m_Deck.m_cards.end(); ++iter){
                    if ((*iter)->m_Suit == card::SPADES) {
                        switch ((*iter)->m_Rank) {
                            case card::ACE :
                                sendMessage += "as";
                                break;
                            case card::TWO :
                                sendMessage += "2s";
                                break;
                            case card::THREE :
                                sendMessage += "3s";
                                break;
                            case card::FOUR :
                                sendMessage += "4s";
                                break;
                            case card::FIVE :
                                sendMessage += "5s";
                                break;
                            case card::SIX :
                                sendMessage += "6s";
                                break;
                            case card::SEVEN :
                                sendMessage += "7s";
                                break;
                            case card::EIGHT :
                                sendMessage += "8s";
                                break;
                            case card::NINE :
                                sendMessage += "9s";
                                break;
                            case card::TEN :
                                sendMessage += "ts";
                                break;
                            case card::JACK :
                                sendMessage += "js";
                                break;
                            case card::QUEEN :
                                sendMessage += "qs";
                                break;
                            default:
                                sendMessage += "ks";
                                break;
                        }
                    } else if ((*iter)->m_Suit == card::HEARTS) {
                        switch ((*iter)->m_Rank) {
                            case card::ACE :
                                sendMessage += "ah";
                                break;
                            case card::TWO :
                                sendMessage += "2h";
                                break;
                            case card::THREE :
                                sendMessage += "3h";
                                break;
                            case card::FOUR :
                                sendMessage += "4h";
                                break;
                            case card::FIVE :
                                sendMessage += "5h";
                                break;
                            case card::SIX :
                                sendMessage += "6h";
                                break;
                            case card::SEVEN :
                                sendMessage += "7h";
                                break;
                            case card::EIGHT :
                                sendMessage += "8h";
                                break;
                            case card::NINE :
                                sendMessage += "9h";
                                break;
                            case card::TEN :
                                sendMessage += "th";
                                break;
                            case card::JACK :
                                sendMessage += "jh";
                                break;
                            case card::QUEEN :
                                sendMessage += "qh";
                                break;
                            default:
                                sendMessage += "kh";
                                break;
                        }
                    } else if ((*iter)->m_Suit == card::CLUBS) {
                        switch ((*iter)->m_Rank) {
                            case card::ACE :
                                sendMessage += "ac";
                                break;
                            case card::TWO :
                                sendMessage += "2c";;
                                break;
                            case card::THREE :
                                sendMessage += "3c";
                                break;
                            case card::FOUR :
                                sendMessage += "4c";
                                break;
                            case card::FIVE :
                                sendMessage += "5c";
                                break;
                            case card::SIX :
                                sendMessage += "6c";
                                break;
                            case card::SEVEN :
                                sendMessage += "7c";
                                break;
                            case card::EIGHT :
                                sendMessage += "8c";
                                break;
                            case card::NINE :
                                sendMessage += "9c";
                                break;
                            case card::TEN :
                                sendMessage += "tc";
                                break;
                            case card::JACK :
                                sendMessage += "jc";
                                break;
                            case card::QUEEN :
                                sendMessage += "qc";
                                break;
                            default:
                                sendMessage += "kc";
                                break;
                        }
                    } else {
                        switch ((*iter)->m_Rank) {
                            case card::ACE :
                                sendMessage += "ad";
                                break;
                            case card::TWO :
                                sendMessage += "2d";
                                break;
                            case card::THREE :
                                sendMessage += "3d";
                                break;
                            case card::FOUR :
                                sendMessage += "4d";
                                break;
                            case card::FIVE :
                                sendMessage += "5d";
                                break;
                            case card::SIX :
                                sendMessage += "6d";
                                break;
                            case card::SEVEN :
                                sendMessage += "7d";
                                break;
                            case card::EIGHT :
                                sendMessage += "8d";
                                break;
                            case card::NINE :
                                sendMessage += "9d";
                                break;
                            case card::TEN :
                                sendMessage += "td";
                                break;
                            case card::JACK :
                                sendMessage += "jd";
                                break;
                            case card::QUEEN :
                                sendMessage += "qd";
                                break;
                            default:
                                sendMessage += "kd";
                                break;
                        }
                    }
            }
            if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket1->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket2->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket3->write(sendMessage.toLatin1());
            }
            this->play();
    } else {
        QMessageBox::critical(this,"Error","Need players!");
    }
}

void Form::slot_recvmessage()
{
    QFont ft("Times New Roman", 11, 75);
    QPalette pa;
    pa.setColor(QPalette::WindowText,Qt::white);
    if(TCP_connectSocket1 != nullptr)
    {
        QByteArray array = TCP_connectSocket1->readAll();
        QString sendMessage;
        sendMessage += array;
        if (sendMessage[0] == '0'){
            player1stay();
            sendMessage.clear();
            sendMessage += "I0"; //I:P1, O:P2, P:P3
            if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket2->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket3->write(sendMessage.toLatin1());
            }
        } else {
            if (sendMessage[0] == '1'){
                player1hit();
                if (m_Deck.GetNum()!=42){
                    sendMessage.clear();
                    sendMessage += "I1";
                    if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket2->write(sendMessage.toLatin1());
                    }
                    if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket3->write(sendMessage.toLatin1());
                    }
                }
            } else {
                    if (sendMessage[0] == "N"){
                        QString c1name;
                        for (int i=1; i<sendMessage.length()-1; i++){
                            c1name += sendMessage[i];
                        }
                        c1->setname(c1name);
                        c1n->setText("P1: " + c1->c_name);
                        c1n->setFont(ft);
                        c1n->setPalette(pa);
                        c1n->move(720, 220);
                        int avv;
                        QString avvv;
                        avvv += sendMessage[sendMessage.length()-1];
                        avv = avvv.toInt();
                        c1->setava(avv);
                        QPixmap pixx;
                        switch (c1->c_ava) {
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
                            default:
                                pixx.load(":/images/Bain.png");
                                break;
                        }
                        pixx = pixx.scaled(QSize(80,80),Qt::KeepAspectRatio);
                        c1a->setPixmap(pixx);
                        c1a->move(635, 210);
                        sendMessage.clear();
                        sendMessage += "IN";
                        sendMessage += c1name;
                        sendMessage += avvv;
                        ui->label_4->setText(c1->c_name + ": ");
                        if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket3->write(sendMessage.toLatin1());
                        }
                        if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket2->write(sendMessage.toLatin1());
                        }
                    }
            }
        }
    }
    if(TCP_connectSocket2 != nullptr)
    {
        QByteArray array = TCP_connectSocket2->readAll();
        QString sendMessage;
        sendMessage += array;
        if (sendMessage[0] == '0'){
            player2stay();
            sendMessage.clear();
            sendMessage += "O0"; //I:P1, O:P2, P:P3
            if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket1->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket3->write(sendMessage.toLatin1());
            }
        } else {
            if (sendMessage[0] == '1'){
                player2hit();
                if (m_Deck.GetNum()!=42){
                    sendMessage.clear();
                    sendMessage += "O1"; //I:P1, O:P2, P:P3
                    if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket1->write(sendMessage.toLatin1());
                    }
                    if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket3->write(sendMessage.toLatin1());
                    }
                }
            }  else {
                    if (sendMessage[0] == "N"){
                        QString c2name;
                        for (int i=1; i<sendMessage.length()-1; i++){
                            c2name += sendMessage[i];
                        }
                        c2->setname(c2name);
                        c2n->setText("P2: " + c2->c_name);
                        c2n->setFont(ft);
                        c2n->setPalette(pa);
                        c2n->move(290, 120);
                        int avv;
                        QString avvv;
                        avvv += sendMessage[sendMessage.length()-1];
                        avv = avvv.toInt();
                        c2->setava(avv);
                        QPixmap pix;
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
                        c2a->move(205, 110);
                        sendMessage.clear();
                        sendMessage += "ON";
                        sendMessage += c2name;
                        sendMessage += avvv;
                        ui->label_8->setText(c2->c_name + ": ");
                        if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket1->write(sendMessage.toLatin1());
                        }
                        if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket3->write(sendMessage.toLatin1());
                        }
                    }
           }
        }
    }
    if(TCP_connectSocket3 != nullptr)
    {
        QByteArray array = TCP_connectSocket3->readAll();
        QString sendMessage;
        sendMessage += array;
        if (sendMessage[0] == '0'){
            player3stay();
            sendMessage.clear();
            sendMessage += "P0"; //I:P1, O:P2, P:P3
            if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket2->write(sendMessage.toLatin1());
            }
            if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
            {
                TCP_connectSocket1->write(sendMessage.toLatin1());
            }
        } else {
            if (sendMessage[0] == '1'){
                player3hit();
                if (m_Deck.GetNum()!=42){
                    sendMessage.clear();
                    sendMessage += "P1"; //I:P1, O:P2, P:P3
                    if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket2->write(sendMessage.toLatin1());
                    }
                    if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
                    {
                        TCP_connectSocket1->write(sendMessage.toLatin1());
                    }
                }
            } else {
                    if (sendMessage[0] == "N"){
                        QString c3name;
                        for (int i=1; i<sendMessage.length()-1; i++){
                            c3name += sendMessage[i];
                        }
                        c3->setname(c3name);
                        c3n->setText("P3: " + c3->c_name);
                        c3n->setFont(ft);
                        c3n->setPalette(pa);
                        c3n->move(290, 415);
                        int avv;
                        QString avvv;
                        avvv += sendMessage[sendMessage.length()-1];
                        avv = avvv.toInt();
                        c3->setava(avv);
                        QPixmap pix;
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
                        c3a->move(205, 410);
                        sendMessage.clear();
                        sendMessage += "PN";
                        sendMessage += c3name;
                        sendMessage += avvv;
                        ui->label_10->setText(c3->c_name + ": ");
                        if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket1->write(sendMessage.toLatin1());
                        }
                        if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
                        {
                            TCP_connectSocket2->write(sendMessage.toLatin1());
                        }
                    }
            }
        }
    }
}

//取消连接的槽
void Form::slot_disconnect()
{
    if(TCP_connectSocket1 != nullptr)
    {
        ui->label->setText("P1 logout!");
        TCP_connectSocket1->close();
        TCP_connectSocket1->deleteLater();
    }
    if(TCP_connectSocket2 != nullptr)
    {
        ui->label_14->setText("P2 logout!");
        TCP_connectSocket2->close();
        TCP_connectSocket2->deleteLater();
    }
    if(TCP_connectSocket3 != nullptr)
    {
        ui->label_15->setText("P3 logout!");
        TCP_connectSocket3->close();
        TCP_connectSocket3->deleteLater();
    }
    mSocket->deleteLater();
    TCP_server->deleteLater();
    this->leavenum++;
    emit Formshow();
    this->close();
    if (this->leavenum == 3){
        QMessageBox::warning(this,"Warning","Players left!");
        //delete this;
        this->close();
    }
}
void Form::player1hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p1Player);
        int card_num = p1Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c1_list[i]->hide();
        }
        cleanPlayer1cards();
        showPlayer1cards(p1Player);
        for (int i = 0; i < card_num ; i++){
            c1_list[i]->move(880,(card_num-1-i)*100+200);
            c1_list[i]->show();
        }
        if (p1Player.GetTotal() <= 21){
            Player::p1_total = p1Player.GetTotal();
            ui->label_5->setText(QString::number(Player::p1_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            ui->label_5->setText("Bust");
            p1Player.Bust();
        }
    } else {
        this->begin();
        QMessageBox::critical(this,"Warning","No cards!");
    }
}
void Form::player2hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p2Player);
        int card_num = p2Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c2_list[i]->hide();
        }
        cleanPlayer2cards();
        showPlayer2cards(p2Player);
        for (int i = 0; i < card_num ; i++){
            c2_list[i]->move(435+(card_num-1-i)*100,100);
            c2_list[i]->show();
        }
        if (p2Player.GetTotal() <= 21){
            Player::p2_total = p2Player.GetTotal();
            ui->label_9->setText(QString::number(Player::p2_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            ui->label_9->setText("Bust");
            p2Player.Bust();
        }
    } else {
        this->begin();
        QMessageBox::critical(this,"Warning","No cards!");
    }
}
void Form::player3hit(){
    if (m_Deck.GetNum()>=1){
        m_Deck.Deal(p3Player);
        int card_num = p3Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c3_list[i]->hide();
        }
        cleanPlayer3cards();
        showPlayer3cards(p3Player);
        for (int i = 0; i < card_num ; i++){
            c3_list[i]->move(30, (card_num-1-i)*100+200);
            c3_list[i]->show();
        }
        if (p3Player.GetTotal() <= 21){
            Player::p3_total = p3Player.GetTotal();
            ui->label_11->setText(QString::number(Player::p3_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
            ui->label_11->setText("Bust");
            p3Player.Bust();
            hit_btn->show();
            stand_btn->show();
        }
    } else {
        this->begin();
        QMessageBox::critical(this,"Warning","No cards!");
    }
}
void Form::player1stay(){

}
void Form::player2stay(){

}
void Form::player3stay(){
    hit_btn->show();
    stand_btn->show();
}
void Form::play(){
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
        m_House.FlipFirstCard();
        showHousecards(m_House);
        h_list[0]->move(435,300);
        h_list[1]->move(535,300);
        h_list[0]->show();
        h_list[1]->show();
        showPlayer1cards(p1Player);
        c1_list[0]->move(880,300);
        c1_list[1]->move(880,200);
        c1_list[0]->show();
        c1_list[1]->show();
        showPlayer2cards(p2Player);
        c2_list[0]->move(535,100);
        c2_list[1]->move(435,100);
        c2_list[0]->show();
        c2_list[1]->show();
        showPlayer3cards(p3Player);
        c3_list[0]->move(30,300);
        c3_list[1]->move(30,200);
        c3_list[0]->show();
        c3_list[1]->show();
        showPlayer4cards(p4Player);
        c4_list[0]->move(435,500);
        c4_list[1]->move(535,500);
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
        ui->label_9->setText(QString::number(Player::p2_total));
        ui->label_11->setText(QString::number(Player::p3_total));
        ui->label_13->setText(QString::number(Player::p4_total));
        ui->label_7->setText(QString::number(Deck::c_left));
}
void Form::player4hit(){
    if (m_Deck.GetNum()>=1){
        QString sendMessage = "1";
        if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty()) //确保有客户端连接，并且发送内容不为空
        {
            TCP_connectSocket1->write(sendMessage.toLatin1());   //发送消息到客户端
        }
        if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
        {
            TCP_connectSocket2->write(sendMessage.toLatin1());
        }
        if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
        {
            TCP_connectSocket3->write(sendMessage.toLatin1());
        }
        m_Deck.Deal(p4Player);
        int card_num = p4Player.GetNum();
        for (int i = 0; i < (card_num - 1); i++){
            c4_list[i]->hide();  //隐藏所有手牌
        }
        cleanPlayer4cards(); //清空记录手牌的全局变量
        showPlayer4cards(p4Player                     );
        for (int i = 0; i < card_num ; i++){
            c4_list[i]->move(535-(card_num-1-i)*100,500);
            c4_list[i]->show();
        }
        if (p4Player.GetTotal() <= 21){
            Player::p4_total = p4Player.GetTotal();
            ui->label_13->setText(QString::number(Player::p4_total));
            Deck::c_left = m_Deck.GetNum();
            ui->label_7->setText(QString::number(Deck::c_left));
        } else {
            Deck::c_left = m_Deck.GetNum();  //爆了后开始庄家结算
            ui->label_7->setText(QString::number(Deck::c_left));
            hit_btn->hide();
            stand_btn->hide();
            QLabel *w = new QLabel;
            w->setAlignment(Qt::AlignCenter);
            w->resize(200,100);
            w->move(750,400);
            ui->label_13->setText("Bust");
            //pPlayer.Bust();
            p4Player.Bust();
            w->setText("You bust!");
            w->show();
            endgame();
        }
    } else {
        this->begin();
        QMessageBox::critical(this,"Warning","No cards!");
    }
}

void Form::player4stay(){  //不叫牌后开始庄家结算，和庄家比大小
    QString sendMessage = "0";
    if(TCP_connectSocket1 != nullptr && !sendMessage.isEmpty()) //确保有客户端连接，并且发送内容不为空
    {
        TCP_connectSocket1->write(sendMessage.toLatin1());   //发送消息到客户端
    }
    if(TCP_connectSocket2 != nullptr && !sendMessage.isEmpty())
    {
        TCP_connectSocket2->write(sendMessage.toLatin1());
    }
    if(TCP_connectSocket3 != nullptr && !sendMessage.isEmpty())
    {
        TCP_connectSocket3->write(sendMessage.toLatin1());
    }
    hit_btn->hide();
    stand_btn->hide();
    Player::p1_total = p1Player.GetTotal();
    Player::p2_total = p2Player.GetTotal();
    Player::p3_total = p3Player.GetTotal();
    Player::p4_total = p4Player.GetTotal();
    House::h_total = m_House.GetTotal();
    ui->label_13->setText(QString::number(Player::p4_total));
    endgame();
}
void Form::endgame(){
    QTime t;
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
        edd += c1->c_name + " Loses!\n";
        edd += c2->c_name + " Loses!\n";
        edd += c3->c_name + " Loses!\n";
        edd += "You Lose!\n";
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
                ui->label_3->setText(QString::number(House::h_total));
            } else {
                ui->label_3->setText("Bust");
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
                edd += "You win!\n";
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
                    edd += "You win!\n";
                } else if (p4Player.GetTotal() < m_House.GetTotal()){
                    p4Player.Lose();
                    edd += "You lose!\n";
                } else {
                    p4Player.Push();
                    edd += "You push!\n";
                }
            }else {
                edd += "You lose!\n";
            }
        }
    }
    w->setText(edd);
    this->sleep(1000);
    w->show();
}
void Form::showPlayer1cards(Player &aGenericPlayer){
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
void Form::showPlayer2cards(Player &aGenericPlayer){
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
void Form::showPlayer3cards(Player &aGenericPlayer){
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
void Form::showPlayer4cards(Player &aGenericPlayer){
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
void Form::showHousecards(House &aGenericPlayer){
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
void Form::cleanHousecards(){
    h_list.clear();
}

void Form::cleanPlayer1cards(){
    c1_list.clear();
}

void Form::cleanPlayer2cards(){
    c2_list.clear();
}

void Form::cleanPlayer3cards(){
    c3_list.clear();
}

void Form::cleanPlayer4cards(){
    c4_list.clear();
}
void Form::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void Form::on_pushButton_clicked()
{
    if(TCP_connectSocket1 != nullptr)
    {
        ui->label->setText("P1 logout!");
        TCP_connectSocket1->close();
        TCP_connectSocket1->deleteLater();
    }
    if(TCP_connectSocket2 != nullptr)
    {
        ui->label_14->setText("P2 logout!");
        TCP_connectSocket2->close();
        TCP_connectSocket2->deleteLater();
    }
    if(TCP_connectSocket3 != nullptr)
    {
        ui->label_15->setText("P3 logout!");
        TCP_connectSocket3->close();
        TCP_connectSocket3->deleteLater();
    }
    mSocket->deleteLater();
    TCP_server->deleteLater();
    emit Formshow();
    this->close();
}
