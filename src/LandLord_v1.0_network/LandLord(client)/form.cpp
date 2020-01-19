#include "form.h"
#include "ui_form.h"
#include <QString>
#include <string>

int Form::m_order;

QString Form::ip;
Form::Form(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form)
{
    ui->setupUi(this);
    mSocket = new QUdpSocket();
    connect(mSocket,SIGNAL(readyRead()),this,SLOT(read_data()));
}

Form::~Form()
{
    delete ui;
}

void Form::on_pushButton_clicked()
{
    player=new MainWindow;
    player->show();
    //Debug() << Form::ip;
}

void Form::on_freshbtn_clicked()
{
    QString xx;
    xx += "aug";
    QByteArray yy = xx.toLatin1();
    mSocket->writeDatagram(yy,QHostAddress::Broadcast,6666);
    qDebug() << 2;
}
void Form::read_data(){
    qDebug() << 5;
    Form::ip.clear();
    QByteArray array;
    QHostAddress address;
    quint16 port;
    //qDebug()<<mSocket->bytesAvailable();
    //array.resize(mSocket->bytesAvailable());
    array.resize(mSocket->pendingDatagramSize());
    QString str;
    mSocket->readDatagram(array.data(),array.size(),&address,&port);
    str.prepend(array);
    //for (int i=0; i<str.length();i++){
        //if (str[i] != '#'){
            //Form::ip += str[i];
        //} else {
            //break;
        //}
    //}
    Form::ip.prepend(address.toString());
    //qDebug() << Form::ip;
    MainWindow::ipp += Form::ip;
    //qDebug() << address.toString();
    QString order;
    order += str[str.length()-1];
    Form::m_order=order.toInt();
    ui->pushButton->setEnabled(true);
    ui->label->setText(QString::fromLocal8Bit(std::string("连接成功!").data()));
    //qDebug() << Form::m_order;
}
