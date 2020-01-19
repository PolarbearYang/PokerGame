#include "host.h"
#include "ui_host.h"
int host::m_order;
QString host::ip;
host::host(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::host)
{
    ui->setupUi(this);
    this->setWindowTitle("Finding..");
    this->setWindowFlags(this->windowFlags()&~Qt::WindowMaximizeButtonHint);
    this->setFixedSize(this->width(),this->height());
    host::ip.clear();
    ui->listWidget->clear();
    mSocket = new QUdpSocket();
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
    isfound = false;
    getone = false;
}

host::~host()
{
    delete ui;
}

void host::on_pushButton_clicked()
{
    if (getone){
        mSocket->writeDatagram("c",QHostAddress(host::ip),6666);
        getone = false;
        this->sleep(500);
        cconnected();
    }
}

void host::on_freshbtn_clicked()
{
    ui->listWidget->clear();
    iplist.clear();
    mSocket->writeDatagram("f",QHostAddress::Broadcast,6666);
}
void host::read_data(){
    QFont ft("Times New Roman", 15, 75);
    host::ip.clear();
    QByteArray array;
    QHostAddress address;
    quint16 port;
    array.resize(mSocket->bytesAvailable());
    QString str;
    mSocket->readDatagram(array.data(),array.size(),&address,&port);
    str.prepend(array);
    if (str[0]=="c"){
        QString order;
        order += str[1];
        host::m_order=order.toInt();
        order.clear();
        order += str[2];
        max_player=order.toInt();
        host::ip.prepend(address.toString());
        isfound = true;
    } else {
        if (str[0] == "s"){
            QString nowp;
            QString allp;
            QString hname;
            QString show;
            int hava;
            nowp += str[1];
            allp += str[2];
            show += str[3];
            hava = show.toInt();
            show.clear();
            for (int i = 4; i < str.length(); i++){
                hname += str[i];
            }
            show = "     ";
            for (int i = 0; i < 44; i++){
                if (i<hname.length()){
                    show += hname[i];
                } else {
                    show += " ";
                }
            }
            show += nowp + "                       " + allp;
            iplist.append(address.toString());
            ui->listWidget->setIconSize(QSize(100, 100));
            ui->listWidget->setFont(ft);
            QListWidgetItem* lst1 = new QListWidgetItem(QIcon(":/images/Dallas.png"),show, ui->listWidget);
            switch (hava) {
                case 1:
                    lst1->setIcon(QIcon(":/images/Dallas.png"));
                    break;
                case 2:
                    lst1->setIcon(QIcon(":/images/Chains.png"));
                    break;
                case 3:
                    lst1->setIcon(QIcon(":/images/Wolf.png"));
                    break;
                case 4:
                    lst1->setIcon(QIcon(":/images/Houston.png"));
                    break;
                case 5:
                    lst1->setIcon(QIcon(":/images/Jacket.png"));
                    break;
                default:
                    lst1->setIcon(QIcon(":/images/Bain.png"));
                    break;
            }
            ui->listWidget->insertItem(1, lst1);
        }
    }
}

void host::cconnected(){
    if (isfound) {
        if (host::m_order < max_player){
            if (host::m_order==0){
                player1 = new Form1;
                player1->show();
                connect(player1,SIGNAL(Form1show()),this,SLOT(showhost()));
                isfound = false;
                this->close();
            } else {
                if (host::m_order==1) {
                    player2 = new Form2;
                    player2->show();
                    connect(player2,SIGNAL(Form2show()),this,SLOT(showhost()));
                    isfound = false;
                    this->close();
                } else {
                    if (host::m_order==2) {
                        player3 = new Form3;
                        player3->show();
                        connect(player3,SIGNAL(Form3show()),this,SLOT(showhost()));
                        isfound = false;
                        this->close();
                    }
                }
            }
      } else {
        QMessageBox::critical(this,"Error","Too many players!");
      }
    } else {
        QMessageBox::critical(this,"Error","No server!");
    }

}

void host::sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

void host::on_Exit_btn_clicked()
{
    emit Hostshow();
    mSocket->deleteLater();
    this->close();
}

void host::showhost(){
    host::ip.clear();
    ui->listWidget->clear();;
    isfound = false;
    getone = false;
    this->show();
}

void host::on_listWidget_itemClicked(QListWidgetItem *item)
{
    getone = true;
    int currenRow = ui->listWidget->currentRow();
    host::ip.clear();
    host::ip = iplist[currenRow];
}

void host::on_listWidget_itemDoubleClicked(QListWidgetItem *item)
{
    getone = true;
    int currenRow = ui->listWidget->currentRow();
    host::ip.clear();
    host::ip = iplist[currenRow];
    mSocket->writeDatagram("c",QHostAddress(host::ip),6666);
    getone = false;
    this->sleep(500);
    cconnected();
}
