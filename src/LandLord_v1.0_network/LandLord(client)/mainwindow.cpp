#pragma warning(disable:4267)
#include "Card.h"
#include <iostream>
#include "require.h"

using namespace std;

//std::vector<std::vector<int>> JudgeNorm;//���ȫ�ֱ����洢�����е�����
//��Ŷ�Ӧ���ͼ�PokerGame�ļ����¡�����-��ż�¼.xlsx��

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QtWidgets>
#include "MyQGroupBox.h"
#include <QString>
#include <QLabel>
#include <QPicture>
#include <QPixmap>
#include <QApplication>
#include <QTime>
#include <QSound>
#include <math.h>




int tempint;//�����������������ȫ�ֱ���
int cardnum;//��¼��ǰ��ҵ���������
bool Overflag=false;
QSound *GameStart0=new QSound("./SE/GameStart.wav");
QSound *ButtonClick01=new QSound("./SE/ButtonClick01.wav");
QSound *ButtonClick02=new QSound("./SE/ButtonClick02.wav");
QSound *Pass=new QSound("./SE/Pass.wav");
QSound *givecard=new QSound("./SE/givecard.wav");
QString MainWindow::ipp;
QString Message;//������ʾ�Ի����е���Ϣ
Pile* P; //�����ƶ�
choose* ch;//��һλ��ҳ�����
choose* ch1;//��ǰ��ҳ�����
choose* chcheck;//���ڼ�鵱ǰ��ҳ����Ƿ����, �Ծ������ư�ť״̬


QString GetMessage(){
    return Message;
}

QString str2qstr(const string str)
{
    return QString::fromLocal8Bit(str.data());
}

string qstr2str(const QString qstr)
{
    QByteArray cdata = qstr.toLocal8Bit();
    return string(cdata);
}

void sleep(unsigned int msec){
    QTime reachTime=QTime::currentTime().addMSecs(msec);
    while(QTime::currentTime()<reachTime){
        QCoreApplication::processEvents(QEventLoop::AllEvents,100);
    }
}


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    GenerateNorm();//�������ڱȶ����͵ľ���
    initval();
    for(int i=0;i<4;i++){
        seat.push_back(i);
    }
    for(int i=0;i<33;i++){
        GoingtoPlay.push_back(0);
    }
    //qDebug() << this->ip;

    QPixmapCache::setCacheLimit(1);
    Qcardinit();
    this->isconnetion = false;
    //��ʼ��sendMesSocket
    this->TCP_sendMesSocket = new QTcpSocket();
    //��ֹ֮ǰ�����ӣ������׽���
    TCP_sendMesSocket->abort();
    //����IP�Ͷ˿ںţ����ӷ�����
    //qDebug() << this->ip;
    this->TCP_sendMesSocket->connectToHost(MainWindow::ipp,8888);
    //this->TCP_sendMesSocket->connectToHost("127.0.0.1",8888);
    //�ɹ����ӷ�������connected()�ź����ӵ�slot_connected() (ע�⣺����connect()�ź�)
    //connect(ui->sendbtn,SIGNAL(clicked()),this,SLOT(slot_sendmessage()));
    connect(TCP_sendMesSocket,SIGNAL(connected()),this,SLOT(slot_connected()));
    //���Ͱ�ť��clicked()�ź����ӵ�slot_sendmessage()
    //connect(ui->pushButton_send,SIGNAL(clicked()),this,SLOT(slot_sendmessage()));
    //�������ݵ���ʱ��readyread()�ź����ӵ�slot_recvmessage()
    connect(TCP_sendMesSocket,SIGNAL(readyRead()),this,SLOT(slot_recvmessage()));
    //��������Ͽ����ӵ�disconnected()�ź����ӵ�slot_disconnect()
    connect(TCP_sendMesSocket,SIGNAL(disconnected()),this,SLOT(slot_disconnect()));

    //thisplayer=ip.toInt()+1;

    {
        ui->groupBox->setStyleSheet("QGroupBox{border:none}");
        HideUI();//��ʼ�׶�����UI
        HidePlayerText();//��ʼ�׶�������ұ��
        ui->label->setStyleSheet("color: rgb(255,255,255)");
        ui->label2->setStyleSheet("color: rgb(255,255,255)");
        ui->label3->setStyleSheet("color: rgb(255,255,255)");
        ui->label4->setStyleSheet("color: rgb(255,255,255)");
        ui->label4_2->setStyleSheet("color: rgb(255,255,255)");
        ui->label4_3->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat0->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat0Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat0_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat1->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat1Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat1_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat2->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat2Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat2_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat3->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat3Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat3_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Head0->hide();
        ui->Head1->hide();
        ui->Head2->hide();
        ui->Head3->hide();
        ui->PASS0->hide();
        ui->PASS1->hide();
        ui->PASS2->hide();
        ui->PASS3->hide();
        for(int i=0;i<4;i++){
            //if(i!=thisplayer && i==0){
                ui->Player1_AIcontrol->setEnabled(false);
            //}
            //if(i!=thisplayer && i==1){
                ui->Player2_AIcontrol->setEnabled(false);
            //}
            //if(i!=thisplayer && i==2){
                ui->Player3_AIcontrol->setEnabled(false);
            //}
            //if(i!=thisplayer && i==3){
                ui->Player4_AIcontrol->setEnabled(false);
            //}
        }
    }
}


MainWindow::~MainWindow()
{
    delete ui;
}




//���ܺ���, ���������ֵ���
void MainWindow::HideUI(){
    ui->Chief0Score->setVisible(false);
    ui->Chief1Score->setVisible(false);
    ui->Chief2Score->setVisible(false);
    ui->Chief3Score->setVisible(false);
    ui->DoNotPlay->setVisible(false);
    ui->Play->setVisible(false);
    ui->label->setVisible(false);
    ui->label2->setVisible(false);
    ui->label3->setVisible(false);
    ui->label4->setVisible(false);
    ui->label4_2->setVisible(false);
    ui->label4_3->setVisible(false);
}

void MainWindow::GenerateNorm() {
    std::vector<int> temp;
    //������ը
    temp.push_back(2);
    temp.push_back(2);
    JudgeNorm.push_back(temp);
    temp.clear();

    //����ֻ��һ��ֵ����������, ��ը��, ����, ����, ����
    temp.push_back(8);
    for (int i = 0; i < 8; i++) {
        JudgeNorm.push_back(temp);
        temp[0]--;
    }
    temp.clear();

    //���е�˳��
    for (int i = 0; i < 5; i++) {
        temp.push_back(1);
    }
    for (int i = 0; i < 8; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(1);
    }
    temp.clear();

    //���е�����
    temp.push_back(2); temp.push_back(2); temp.push_back(2);
    for (int i = 0; i < 10; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(2);
    }
    temp.clear();

    //���еķɻ�
    temp.push_back(3); temp.push_back(3);
    for (int i = 0; i < 11; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(3);
    }
    temp.clear();

    //���е�������
    temp.push_back(3); temp.push_back(2);
    for (int i = 0; i < 11; i++) {
        JudgeNorm.push_back(temp);
        temp.insert(temp.begin(), 3);
        temp.push_back(2);
    }
    temp.clear();
}

void MainWindow::PrintJudgeNorm() {
    for (int i = 0; i < (int)JudgeNorm.size(); i++) {
        cout << i << ": ";
        for (int j = 0; j < (int)(JudgeNorm[i]).size(); j++)
            cout << JudgeNorm[i][j] << " ";
        cout << endl;
    }
}

void MainWindow::Qcardinit(){
    Qcard[0].load("./images/cb.png");
    Qcard[1].load("./images/3s.png");
    Qcard[2].load("./images/3h.png");
    Qcard[3].load("./images/3c.png");
    Qcard[4].load("./images/3d.png");
    Qcard[5].load("./images/4s.png");
    Qcard[6].load("./images/4h.png");
    Qcard[7].load("./images/4c.png");
    Qcard[8].load("./images/4d.png");
    Qcard[9].load("./images/5s.png");
    Qcard[10].load("./images/5h.png");
    Qcard[11].load("./images/5c.png");
    Qcard[12].load("./images/5d.png");
    Qcard[13].load("./images/6s.png");
    Qcard[14].load("./images/6h.png");
    Qcard[15].load("./images/6c.png");
    Qcard[16].load("./images/6d.png");
    Qcard[17].load("./images/7s.png");
    Qcard[18].load("./images/7h.png");
    Qcard[19].load("./images/7c.png");
    Qcard[20].load("./images/7d.png");
    Qcard[21].load("./images/8s.png");
    Qcard[22].load("./images/8h.png");
    Qcard[23].load("./images/8c.png");
    Qcard[24].load("./images/8d.png");
    Qcard[25].load("./images/9s.png");
    Qcard[26].load("./images/9h.png");
    Qcard[27].load("./images/9c.png");
    Qcard[28].load("./images/9d.png");
    Qcard[29].load("./images/ts.png");
    Qcard[30].load("./images/th.png");
    Qcard[31].load("./images/tc.png");
    Qcard[32].load("./images/td.png");
    Qcard[33].load("./images/js.png");
    Qcard[34].load("./images/jh.png");
    Qcard[35].load("./images/jc.png");
    Qcard[36].load("./images/jd.png");
    Qcard[37].load("./images/qs.png");
    Qcard[38].load("./images/qh.png");
    Qcard[39].load("./images/qc.png");
    Qcard[40].load("./images/qd.png");
    Qcard[41].load("./images/ks.png");
    Qcard[42].load("./images/kh.png");
    Qcard[43].load("./images/kc.png");
    Qcard[44].load("./images/kd.png");
    Qcard[45].load("./images/as.png");
    Qcard[46].load("./images/ah.png");
    Qcard[47].load("./images/ac.png");
    Qcard[48].load("./images/ad.png");
    Qcard[49].load("./images/2s.png");
    Qcard[50].load("./images/2h.png");
    Qcard[51].load("./images/2c.png");
    Qcard[52].load("./images/2d.png");
    Qcard[53].load("./images/LJ.png");
    Qcard[54].load("./images/JO.png");
    Qhead[0].load("./images/Farmer.png");
    Qhead[1].load("./images/LandLord.png");
}

void MainWindow::ButtonPosRecover(){
    for(int i=0;i<33;i++){
        labelbox[i].setGeometry(QRect(276+24*i,780,72,120));
    }
}


void MainWindow::pointerdecide(){
    //��ַ����, ��������ÿ�������λ��
    crosslabel=new QLabel[33];
    for(int i=0;i<33;i++){
        crosslabel[i].setParent(this);
        crosslabel[i].setGeometry(QRect(276+24*i,120,72,96));
    }
    leftlabel=new QLabel[33];
    for(int i=0;i<33;i++){
        leftlabel[i].setParent(this);
        leftlabel[i].setGeometry(QRect(90,168+18*i,72,96));
    }
    rightlabel=new QLabel[33];
    for(int i=0;i<33;i++){
        rightlabel[i].setParent(this);
        rightlabel[i].setGeometry(QRect(1238,168+18*i,72,96));
    }
    ui->label->setGeometry(QRect(276,300,71,81));
    Holecard=new QLabel[8];
    for(int i=0;i<8;i++){
        Holecard[i].setParent(this);
        Holecard[i].setGeometry(QRect(400+80*i,340,72,96));
    }
    ui->label2->setGeometry(QRect(276,400,120,80));
    ui->label3->setGeometry(QRect(416,400,180,80));
    ui->label4->setGeometry(QRect(596,400,20,80));
    ui->label4_2->setGeometry(QRect(276,400,180,80));
    ui->label4_3->setGeometry(QRect(396,400,20,80));
    LastPlayerCard=new QLabel[33];
    for(int i=0;i<33;i++){
        LastPlayerCard[i].setParent(this);
        LastPlayerCard[i].setGeometry(QRect(336+24*i,515,72,96));
    }
    labelbox=new MyGroupBox[33];
    for(int i=0;i<33;i++){
        labelbox[i].setParent(this);
        labelbox[i].setGeometry(QRect(276+24*i,780,72,120));
        labelbox[i].setStyleSheet("QGroupBox{border:none}");
        labelbox[i].setindex(i);
        labelbox[i].BackupGoingToPlay=GoingtoPlay;
        labelbox[i].setfather(this);
        labelbox[i].CurrentPlayer=&(CurrentPlayer);
        labelbox[i].thisplayer=&(thisplayer);
    }
    upperlabel=new QLabel[33];
    for(int i=0;i<33;i++){
        upperlabel[i].setParent(&labelbox[i]);
        upperlabel[i].setGeometry(QRect(0,0,72,96));
    }
    lowerlabel=new QLabel[33];
    for(int i=0;i<33;i++){
        lowerlabel[i].setParent(&labelbox[i]);
        lowerlabel[i].setGeometry(QRect(0,24,72,96));
    }
    ui->Play->setGeometry(QRect(500,700,150,56));
    ui->DoNotPlay->setGeometry(QRect(750,700,150,56));
    ui->Chief3Score->setGeometry(QRect(350,700,150,56));
    ui->Chief2Score->setGeometry(QRect(550,700,150,56));
    ui->Chief1Score->setGeometry(QRect(750,700,150,56));
    ui->Chief0Score->setGeometry(QRect(950,700,150,56));
}

void MainWindow::pointerdelete(){
    //��Ϸ����ʱ�������label
    delete []lowerlabel;
    delete []upperlabel;
    delete []labelbox;
    delete []LastPlayerCard;
    delete []Holecard;
    delete []crosslabel;
    delete []leftlabel;
    delete []rightlabel;
    delete []seatlabel0;
    delete []seatlabel1;
    delete []seatlabel2;
    delete []seatlabel3;
}

const QPixmap MainWindow::PrintCard(int Player, int j){
    //Player��Ӧ��ұ��, j��Ӧ�����±�
    //������Player�ĵ�j������
    if(Player<0)
        return Qcard[0];
    int temp=0;
    switch(P->Player[Player].card[j].color){
        case Spade:temp=1;break;
        case Hearts:temp=2;break;
        case Club:temp=3;break;
        case Diamonds:temp=4;break;
        default:temp=0;break;
   }
   if(P->Player[Player].card[j].num<16){
       return Qcard[(P->Player[Player].card[j].num-3)*4+temp];
   }
   else
       return Qcard[P->Player[Player].card[j].num+37];
}

const QPixmap MainWindow::PrintCard(int num, int color, int flag){
    //flagû��, ������������
    if(!flag)
        return Qcard[0];
    if(num>=16)
        return Qcard[num+37];
    else
        return Qcard[(num-3)*4+color];
}

void MainWindow::PrintinitCard(){
    //��Ϸ��ʼʱ�����ƾ����泯��
    for(int j=0;j<(int)P->Player[seat[1]].num;j++){
        rightlabel[j].show();
        rightlabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[2]].num;j++){
        crosslabel[j].show();
        crosslabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[3]].num;j++){
        leftlabel[j].show();
        leftlabel[j].setPixmap(Qcard[0]);
    }
}

void MainWindow::PrintinitHoleCard(){
    for(int j=0;j<8;j++){
        Holecard[j].show();
        Holecard[j].setPixmap(Qcard[0]);
    }
}

void MainWindow::PrintHoleCard(){
    for(int j=0;j<8;j++){
        Holecard[j].show();
        Holecard[j].setPixmap(PrintCard(P->HoleCard.card[j].num, P->HoleCard.card[j].color, 1));
    }
}

void MainWindow::PrintPlayedCard(){
    cout<<"ch->card.size"<<ch->card.size()<<endl;
    if(PlayerPlayedCard[CurrentPlayer].num.empty()){
        return;
    }
    for(int j=0;j<(int)PlayerPlayedCard[CurrentPlayer].num.size();j++){
        LastPlayerCard[j].show();
        LastPlayerCard[j].setPixmap(PrintCard(PlayerPlayedCard[CurrentPlayer].num[j], PlayerPlayedCard[CurrentPlayer].color[j], 1));
    }
}

void MainWindow::ClearPlayedCard(){
    for(int j=0;j<33;j++){
        LastPlayerCard[j].clear();
    }
}

void MainWindow::ClearCards(){
    //�ǵ���ɾ���ٸ�����λ!
    for(int j=0;j<(int)P->Player[seat[1]].num;j++){
        rightlabel[j].clear();
    }
    for(int j=0;j<(int)P->Player[seat[2]].num;j++){
        crosslabel[j].clear();
    }
    for(int j=0;j<(int)P->Player[seat[3]].num;j++){
        leftlabel[j].clear();
    }
    for(int j=0;j<33;j++){
        lowerlabel[j].clear();
        upperlabel[j].clear();
    }
}

void MainWindow::ShowLandLordRoundCurrentPlayer(){
    ClearCards();
    //seat[0]=LandLordRoundCurrentPlayer;
    seat[0]=thisplayer;
    for(int i=1;i<=3;i++){
        seat[i]=(seat[0]+i)%4;
    }
    for(int j=0;j<(int)P->Player[seat[1]].num;j++){
        rightlabel[j].show();
        rightlabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[2]].num;j++){
        crosslabel[j].show();
        crosslabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[3]].num;j++){
        leftlabel[j].show();
        leftlabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[0]].num;j++){
        labelbox[j].show();
        lowerlabel[j].show();
        if(P->Player[seat[0]].AIcontrol)
            lowerlabel[j].setPixmap(Qcard[0]);
        else
            lowerlabel[j].setPixmap(PrintCard(seat[0], j));
    }
    cardnum=P->Player[seat[0]].num;
}

void MainWindow::ShowCurrentPlayerCards(){
    ClearCards();
    ButtonPosRecover();
    //seat[0]=CurrentPlayer;
    seat[0]=thisplayer;
    for(int i=1;i<=3;i++){
        seat[i]=(seat[0]+i)%4;
    }
    for(int j=0;j<(int)P->Player[seat[1]].num;j++){
        rightlabel[j].show();
        rightlabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[2]].num;j++){
        crosslabel[j].show();
        crosslabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[3]].num;j++){
        leftlabel[j].show();
        leftlabel[j].setPixmap(Qcard[0]);
    }
    for(int j=0;j<(int)P->Player[seat[0]].num;j++){
        labelbox[j].show();
        lowerlabel[j].show();
        if(P->Player[seat[0]].AIcontrol)
            lowerlabel[j].setPixmap(Qcard[0]);
        else
            lowerlabel[j].setPixmap(PrintCard(seat[0], j));
    }
    for(int j=(int)P->Player[seat[0]].num;j<33;j++){
        labelbox[j].setGeometry(QRect(-72,-96,72,96));
    }
}
void MainWindow::RecoverLandLordButton(){
    ui->Chief0Score->setEnabled(true);
    ui->Chief1Score->setEnabled(true);
    ui->Chief2Score->setEnabled(true);
    ui->Chief3Score->setEnabled(true);
}

void MainWindow::DisableLandLordButton(){
    if(CurrentScore>0){
        ui->Chief1Score->setEnabled(false);
        if(CurrentScore>1){
            ui->Chief2Score->setEnabled(false);
        }
    }
}

void MainWindow::PlayerTextShow(){
    ui->Playerseat0_NUM->setText(QString::number(seat[0]+1));
    ui->Playerseat1_NUM->setText(QString::number(seat[1]+1));
    ui->Playerseat2_NUM->setText(QString::number(seat[2]+1));
    ui->Playerseat3_NUM->setText(QString::number(seat[3]+1));
    if(P->Player[seat[0]].AIcontrol==1){
        ui->Playerseat0Control->setText(QString(str2qstr(string("����"))));
    }
    else
        ui->Playerseat0Control->setText(QString(str2qstr(string("����"))));
    if(P->Player[seat[1]].AIcontrol==1){
        ui->Playerseat1Control->setText(QString(str2qstr(string("��\n��"))));
    }
    else
        ui->Playerseat1Control->setText(QString(str2qstr(string("��\n��"))));
    if(P->Player[seat[2]].AIcontrol==1){
        ui->Playerseat2Control->setText(QString(str2qstr(string("����"))));
    }
    else
        ui->Playerseat2Control->setText(QString(str2qstr(string("����"))));
    if(P->Player[seat[3]].AIcontrol==1){
        ui->Playerseat3Control->setText(QString(str2qstr(string("��\n��"))));
    }
    else
        ui->Playerseat3Control->setText(QString(str2qstr(string("��\n��"))));
}

void MainWindow::HidePlayerText(){
    ui->Playerseat0->hide();
    ui->Playerseat0Control->hide();
    ui->Playerseat0_NUM->hide();
    ui->Playerseat1->hide();
    ui->Playerseat1Control->hide();
    ui->Playerseat1_NUM->hide();
    ui->Playerseat2->hide();
    ui->Playerseat2Control->hide();
    ui->Playerseat2_NUM->hide();
    ui->Playerseat3->hide();
    ui->Playerseat3Control->hide();
    ui->Playerseat3_NUM->hide();
}

void MainWindow::ShowPlayerText1(){
    ui->Playerseat0->show();
    ui->Playerseat0_NUM->show();
    ui->Playerseat1->show();
    ui->Playerseat1_NUM->show();
    ui->Playerseat2->show();
    ui->Playerseat2_NUM->show();
    ui->Playerseat3->show();
    ui->Playerseat3_NUM->show();
}

void MainWindow::ShowPlayerText2(){
    ui->Playerseat0Control->show();
    ui->Playerseat1Control->show();
    ui->Playerseat2Control->show();
    ui->Playerseat3Control->show();
}




//--------------------------------------------------
//����
//��Ϸ��ʼ����Ϸ�����Ķ���
//--------------------------------------------------
void MainWindow::GameStart(){
    pointerdecide();
    P=new Pile;
}

void MainWindow::GameStart2(){
    ui->groupBox_AIcontrol->hide();
    //���λ����δ֪BUG
    qDebug()<<"Error Not here... flag1";
    P->Allocation(); //����
    qDebug()<<"Error Not here... flag2";
    P->PrintPlayerCard(); //����������ҵ�����
    P->PrintHoleCard(); //���ֵ���
    for (int i = 0; i < 4; i++){
        P->Player[i].AIcontrol=AIinitStatus[i];
        seat[i]=(thisplayer+4+i)%4;
    }
    //ui->groupBox_AIcontrol->setWindowFlags(Qt::WindowStaysOnBottomHint);
    PrintinitHoleCard();
    InitInTimePlayedCard();

    Overflag=false;
    PrintinitCard();
    LandLordDecidecount=0;
    //��ʾ�зֽ���
    ui->label->show();
    ui->label4_2->show();
    ui->label4_3->show();

    ui->groupBox_2->hide();
    LandLordRoundCurrentPlayer=banker;
    RefreshCardStatus();
    ShowLandLordRoundCurrentPlayer();
    if(LandLordRoundCurrentPlayer==thisplayer){
        ui->Chief0Score->show();
        ui->Chief1Score->show();
        ui->Chief2Score->show();
        ui->Chief3Score->show();
    }
    if(P->Player[LandLordRoundCurrentPlayer].AIcontrol){
        AILandLordDecided();
    }
    if(!Overflag){
        ShowPlayerText1();
    }
    PlayerTextShow();
    GameStart0->play();
}

void MainWindow::GameOver(){
    banker=(banker+1)%4;//������ʱ��˳��������Ϊׯ��
    //HideInterface();
    ui->groupBox_AIcontrol->show();
    ui->groupBox_2->show();
    ShowScoreText();
    HidePlayerText();
    delete P;
    delete ch;
    firstplayer=-1;
    ui->Play->setEnabled(false);
    ui->ButtonConfirm->setEnabled(true);
    delete ch1;
    HideUI();
    for(int i=0;i<33;i++){
        leftlabel[i].clear();
        rightlabel[i].clear();
        crosslabel[i].clear();
    }
    for(int i=0;i<8;i++){
        Holecard[i].clear();
    }
    //for(int i=0;i<4;i++){
    //    PlayerPlayedCard[CurrentPlayer].num.clear();
    //   PlayerPlayedCard[CurrentPlayer].color.clear();
    //}
    for(int i=0;i<4;i++){
        PlayerPlayedCard[i].num.clear();
        PlayerPlayedCard[i].color.clear();
        PlayerPlayedCard[i].count=0;
        PlayerPlayedCard[i].pass=false;
    }
    ui->Playerseat0->hide();
    ui->Playerseat0Control->hide();
    ui->Playerseat0_NUM->hide();
    ui->Playerseat1->hide();
    ui->Playerseat1Control->hide();
    ui->Playerseat1_NUM->hide();
    ui->Playerseat2->hide();
    ui->Playerseat2Control->hide();
    ui->Playerseat2_NUM->hide();
    ui->Playerseat3->hide();
    ui->Playerseat3Control->hide();
    ui->Playerseat3_NUM->hide();
    ui->Head0->hide();
    ui->Head1->hide();
    ui->Head2->hide();
    ui->Head3->hide();
    ui->PASS0->hide();
    ui->PASS1->hide();
    ui->PASS2->hide();
    ui->PASS3->hide();
    ClearCards();
    pointerdelete();
}




//--------------------------------------------------
//��һ����
//�����水ť����
//--------------------------------------------------
void MainWindow::on_Player1_AI_clicked()
{
    AIinitStatus[0]=1;
}

void MainWindow::on_Player2_AI_clicked()
{
    AIinitStatus[1]=1;
}

void MainWindow::on_Player3_AI_clicked()
{
    AIinitStatus[2]=1;
}

void MainWindow::on_Player4_AI_clicked()
{
    AIinitStatus[3]=1;
}

void MainWindow::on_Player1_human_clicked()
{
    AIinitStatus[0]=0;
}

void MainWindow::on_Player2_human_clicked()
{
    AIinitStatus[1]=0;
}

void MainWindow::on_Player3_human_clicked()
{
    AIinitStatus[2]=0;
}

void MainWindow::on_Player4_human_clicked()
{
    AIinitStatus[3]=0;
}

void MainWindow::on_ButtonConfirm_clicked()
{
    sendmessage.clear();
    sendmessage="p"+QString::number(thisplayer); //p��ͷ��ʾ׼���ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    GameStart();
    ui->ButtonConfirm->setEnabled(false);
    ui->StatusNum->hide();
}




//--------------------------------------------------
//�ڶ�����
//�е����㷨
//--------------------------------------------------
void MainWindow::on_Chief3Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(1); //����һ��
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"1"; //0��ͷ��ʾ�з��ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick01->play();
}



void MainWindow::on_Chief2Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(2); //���˶���
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"2"; //0��ͷ��ʾ�з��ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick01->play();

}

void MainWindow::on_Chief1Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(3);  //��������
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"3"; //0��ͷ��ʾ�з��ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick01->play();
}


void MainWindow::on_Chief0Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(0);
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"0"; //0��ͷ��ʾ�з��ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick02->play();
}

void MainWindow::AILandLordDecided(){
    LandLordDecidecount++;

    int choice = 0;
    P->Player[LandLordRoundCurrentPlayer].AICard(); choice = 4 - P->Player[LandLordRoundCurrentPlayer].chief;
    //cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << P->Player[LandLordRoundCurrentPlayer].chief << "��!";
    if (choice < 1 || choice > 4) {
        LandLordRoundCurrentPlayer--;
        cout << "�޴�ѡ��!����������." << endl;
    }
    if (choice == 1) {
        BackupChief = LandLordRoundCurrentPlayer; //����3��
        CurrentScore = 3;
        //ֱ�ӽ������ƽ׶�
        cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << 3 << "��!";
        EndLandLordDecide();
        return;
    }
    if (choice == 2) {
        if (CurrentScore < 2) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 2;
            cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << 2 << "��!";
        }
        else{
            cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << "����!";
        }
    }
    if (choice == 3) {
        if (CurrentScore < 1) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 1;
            cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << 1 << "��!";
        }
        else{
            cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << "����!";
        }
    }
    if(!choice){
        cout << "AI���" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << "����!";
    }
    LandLordRoundCurrentPlayer=(LandLordRoundCurrentPlayer+1)%4; //��Ҹı�!
    cout << "��ǰ�з�: " << CurrentScore << endl;
    ui->label4_3->setText(QString::number(CurrentScore));
    RecoverLandLordButton();
    DisableLandLordButton();
    RefreshCardStatus();
    ShowLandLordRoundCurrentPlayer();
    PlayerTextShow();
    if(P->Player[LandLordRoundCurrentPlayer].AIcontrol && LandLordDecidecount<4){
        AILandLordDecided();
    }
    if(LandLordDecidecount>=4){
        EndLandLordDecide();
        //������Ҿ��ѽз�, ׼����ʼ��Ϸ
    }
    //����ȴ���������
}

void MainWindow::HumanLandLordDecided(int choice){
    LandLordDecidecount++;

    if(choice){P->Player[LandLordRoundCurrentPlayer].chief=4-choice;}
    //cout << "�������" << LandLordRoundCurrentPlayer + 1 << "ѡ����" << P->Player[LandLordRoundCurrentPlayer].chief << "��!";
    if (choice < 1 || choice > 4) {
        //LandLordRoundCurrentPlayer--;
        cout << "�������" << LandLordRoundCurrentPlayer + 1 << "ѡ���˲���!";
    }
    if (choice == 1) {
        BackupChief = LandLordRoundCurrentPlayer; //����3��
        CurrentScore = 3;
        EndLandLordDecide();
        cout << "�������" << LandLordRoundCurrentPlayer + 1 << "ѡ����3��!";
        return;
    }
    if (choice == 2) {
        if (CurrentScore < 2) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 2;
            cout << "�������" << LandLordRoundCurrentPlayer + 1 << "ѡ����2��!";
        }
        //cout << "����������ťʧЧ�Ĺ�����!" << endl;
    }
    if (choice == 3) {
        if (CurrentScore < 1) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 1;
            cout << "�������" << LandLordRoundCurrentPlayer + 1 << "ѡ����1��!";
        }
        //cout << "����������ťʧЧ�Ĺ�����!" << endl;
    }
    LandLordRoundCurrentPlayer=(LandLordRoundCurrentPlayer+1)%4;
    cout << "��ǰ�з�: " << CurrentScore << endl;
    ui->label4_3->setText(QString::number(CurrentScore));
    RecoverLandLordButton();
    DisableLandLordButton();
    RefreshCardStatus();
    ShowLandLordRoundCurrentPlayer();

    if(P->Player[LandLordRoundCurrentPlayer].AIcontrol && LandLordDecidecount<4){
        AILandLordDecided();
    }
    //����ȴ���������
    if(LandLordDecidecount>=4){
        EndLandLordDecide();
        //������Ҿ��ѽз�, ׼����ʼ��Ϸ
    }
}

void MainWindow::EndLandLordDecide(){
    PrintHoleCard();
    if(P->Player[0].chief<=0 || P->Player[0].chief >= 4)
        if (P->Player[1].chief <= 0 || P->Player[1].chief >= 4)
            if (P->Player[2].chief <= 0 || P->Player[2].chief >= 4)
                if (P->Player[3].chief <= 0 || P->Player[3].chief >= 4) {
                    if (CurrentScore == 0) {
                        cout << "û�е���!���¿���!" << endl;
                        GameOver();
                        return;
                    }
                }
    P->Player[BackupChief].chief = 1;
    P->Player[BackupChief] += P->HoleCard;
    firstplayer = BackupChief;
    cout << "�������" << BackupChief + 1 << "�ǵ���!" << endl;
    string str1="���";
    str1=str1+to_string(BackupChief+1)+"�ǵ���";
    QLabel* w=new QLabel;
    QString text;
    QFont font("����",18,75);
    w->setAlignment(Qt::AlignCenter);
    w->setFont(font);
    text+=QString(str2qstr(string("���ƽ׶ν���\n")));
    text+=QString(str2qstr(str1));
    w->resize(200,100);
    w->move(750,400);
    w->setText(text);
    //w->setAlignment(Qt::AlignCenter);
    //w->setfont(QFontDialog::getFont(false,QFont("����",18,QFont::Bold)));
    w->show();
    //QMessageBox::information(this,QString(str2qstr(string("���ƽ׶ν���"))),QString(str2qstr(str1)));
    HideUI();
    //���õ�����ʱ������ԭ
    ui->label4_2->setVisible(false);
    ui->label4_3->setVisible(false);
    LandLordDecidecount=0;//�ѽзּ���?

    pround = firstplayer - 1; //�����һ�����Ƶ����
    initround = 0;//���������ж��Ƿ������Ƿ��ǵ�һ�γ���, ��ȫԱPASS���һ�����Ƶ�
    CurrentPlayer = firstplayer - 1; //��ǰ�ĳ�����
    ch=new choose(pround+1, P->Player, JudgeNorm);//��һλ��ҳ�����
    RecoverLandLordButton();
    RefreshCardStatus();
    ui->Play->setVisible(1);
    ui->DoNotPlay->setVisible(1);
    ui->label->show();
    ui->label2->show();
    ui->label3->show();
    ui->label4->show();
    chcheck=new choose(CurrentPlayer,P->Player,JudgeNorm);
    //ui->Play->setEnabled(false);
    ui->DoNotPlay->setEnabled(false);
    ui->Play->setEnabled(true);
    ShowPlayerText2();
    PlayerTextShow();
    ui->Head0->show();
    ui->Head1->show();
    ui->Head2->show();
    ui->Head3->show();
    LandLordExhibit();
    InitPlay();
}


//--------------------------------------------------
//��������
//�����㷨
//--------------------------------------------------
void MainWindow::ChangeToSelected(int index){
    GoingtoPlay[index]=1;
    upperlabel[index].setPixmap(PrintCard(seat[0], index));
    lowerlabel[index].clear();
    return;
}

void MainWindow::ChangeToUnselected(int index){
    GoingtoPlay[index]=0;
    lowerlabel[index].setPixmap(PrintCard(seat[0], index));
    upperlabel[index].clear();
    return;
}

void MainWindow::MyGroupBox::labelStatusChange(){
    if(index>=P->Player[*thisplayer].num){
        return;
    }
    if(P->Player[*thisplayer].AIcontrol==1){
        return;
    }
    //�ı�����ʾ��ѡ��״̬, �Լ�ÿ�����Ƿ�ѡ�е�״̬
    if(BackupGoingToPlay[index]==0){
        //ChangeToSelected
        BackupGoingToPlay[index]=1;
        father->ChangeToSelected(index);
        return;
    }
    if(BackupGoingToPlay[index]==1){
        //ChangeToUnselected
        BackupGoingToPlay[index]=0;
        father->ChangeToUnselected(index);
        return;
    }
}

void MainWindow::MyGroupBox::mouseReleaseEvent(QMouseEvent *e){
    QGroupBox::mouseReleaseEvent(e);
}

void MainWindow::RefreshCardStatus(){
    //��ԭѡ��״̬
    for(int i=0;i<33;i++){
        if(GoingtoPlay[i]==1){
            GoingtoPlay[i]=0;
            lowerlabel[i].setPixmap(PrintCard(seat[0], i));
            upperlabel[i].clear();
        }
    }
    ClearCards();//�����ʾ
}

/*
void MainWindow::PlayButtonSet(){
    std::vector<int> GoingtoPlayIndex2;
    for(int i=0;i<33;i++){
        if(GoingtoPlay[i]==1)
            GoingtoPlayIndex2.push_back(i);
    }
    chcheck->choice(GoingtoPlayIndex2, true);
    chcheck->Frequency();//��Ƶͳ��
    if(CheckAvailable()){
        ui->Play->setEnabled(true);
    }
    else{
        ui->Play->setEnabled(false);
    }
}
*/

void MainWindow::MyGroupBox::mousePressEvent(QMouseEvent *e){
    //when an error happens, e is not initialized
    cout<<e->isAccepted()<<endl;
    //if(e->button() == Qt::LeftButton && e->isAccepted()) {
        labelStatusChange();
    //}
    //�˴���д��麯���жϳ��ư�ť�Ƿ��ܹ����
    //father->PlayButtonSet();

    QGroupBox::mousePressEvent(e);
    //else {
    //    QGroupBox::mousePressEvent(e);
    //}
}

void MainWindow::LandLordExhibit(){
    if(seat[0]!=BackupChief){
        ui->Playerseat0->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat0Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat0_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Head0->setPixmap(Qhead[0]);
    }
    else{
        ui->Playerseat0->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat0Control->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat0_NUM->setStyleSheet("color: rgb(255,0,0)");
        ui->Head0->setPixmap(Qhead[1]);
    }
    if(seat[1]!=BackupChief){
        ui->Playerseat1->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat1Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat1_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Head1->setPixmap(Qhead[0]);
    }
    else{
        ui->Playerseat1->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat1Control->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat1_NUM->setStyleSheet("color: rgb(255,0,0)");
        ui->Head1->setPixmap(Qhead[1]);
    }
    if(seat[2]!=BackupChief){
        ui->Playerseat2->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat2Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat2_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Head2->setPixmap(Qhead[0]);
    }
    else{
        ui->Playerseat2->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat2Control->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat2_NUM->setStyleSheet("color: rgb(255,0,0)");
        ui->Head2->setPixmap(Qhead[1]);
    }
    if(seat[3]!=BackupChief){
        ui->Playerseat3->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat3Control->setStyleSheet("color: rgb(255,255,255)");
        ui->Playerseat3_NUM->setStyleSheet("color: rgb(255,255,255)");
        ui->Head3->setPixmap(Qhead[0]);
    }
    else{
        ui->Playerseat3->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat3Control->setStyleSheet("color: rgb(255,0,0)");
        ui->Playerseat3_NUM->setStyleSheet("color: rgb(255,0,0)");
        ui->Head3->setPixmap(Qhead[1]);
    }
}

void MainWindow::InitPlay(){
    //����֮ǰ��ʼ��
    ShowPlayerText1();
    //���ڳ��ƵĲ��ֳ�ʼ��
    GoingtoPlayIndex.clear();//����������±�ĳ�ʼ��
    for(int i=0;i<33;i++)
        GoingtoPlay[i]=0;//ÿ�����Ƿ����ĳ�ʼ��

    CurrentPlayer = (CurrentPlayer + 1) % 4; //��ǰ�����ʱ������һλ
    /*
    if(!P->Player[CurrentPlayer].AIcontrol){
        int temp=0;
        for(int i=0;i<4;i++){
            temp+=(int)P->Player[i].AIcontrol;
        }

        if(temp<=2){//ֻ��һ����������򲻱���ʾ
            string str1="�������";
            str1=str1+to_string(CurrentPlayer+1)+"��������";
            for(int i=0;i<33;i++){
                upperlabel[i].clear();
                lowerlabel[i].setPixmap(Qcard[0]);
            }//������
            QMessageBox::information(this,QString(str2qstr(string("������ҵ��ִ�"))),QString(str2qstr(str1)));
        }
    }
    */
    if (pround == CurrentPlayer){
        initround = 0; //0��ʾû���ϼ�
        PlayerPlayedCard[(CurrentPlayer+1)%4].pass=false;
        PlayerPlayedCard[(CurrentPlayer+2)%4].pass=false;
        PlayerPlayedCard[(CurrentPlayer+3)%4].pass=false;
        //pass��Ч��
    }
    ui->Play->setEnabled(true);
    //�жϲ�����ť�Ƿ����
    if(P->Player[CurrentPlayer].AIcontrol==1){
        ui->Play->setEnabled(false);
        ui->DoNotPlay->setEnabled(false);
    }
    if(CurrentPlayer!=thisplayer){
        ui->Play->setEnabled(false);
        ui->DoNotPlay->setEnabled(false);
    }
    else{
        if(initround){
            ui->DoNotPlay->setEnabled(true);
        }
        else
            ui->DoNotPlay->setEnabled(false);
    }
    P->PrintPlayerCard(); //����������ҵ�����, ����̨���Ժ���
    ShowCurrentPlayerCards();
    for(int i=0;i<33;i++){
        leftlabel[i].clear();
        rightlabel[i].clear();
        crosslabel[i].clear();
    }
    for(int i=0;i<P->Player[seat[1]].num;i++)
        rightlabel[i].setPixmap(Qcard[0]);
    for(int i=0;i<P->Player[seat[2]].num;i++)
        crosslabel[i].setPixmap(Qcard[0]);
    for(int i=0;i<P->Player[seat[3]].num;i++)
        leftlabel[i].setPixmap(Qcard[0]);
    PlayerTextShow();
    LandLordExhibit();
    InTimePlayedCard();
    ch1=new choose(CurrentPlayer,P->Player,JudgeNorm);//���i���ƽ׶δ������
    if(P->Player[CurrentPlayer].AIcontrol==1){
        sleep(1000);
    }

    if (P->Player[CurrentPlayer].AIcontrol){AIPlayCard();}
}

void MainWindow::IndexCalculate(){
    for(int i=0;i<P->Player[CurrentPlayer].num;i++){
        if(GoingtoPlay[i]==1){
            GoingtoPlayIndex.push_back(i);
        }
    }
}

void MainWindow::on_Play_clicked()
{
    //���ư�ť
    ui->Play->setEnabled(false);
    ui->DoNotPlay->setEnabled(false);
    sendmessage.clear();
    sendmessage="1"+QString::number(thisplayer); //0��ͷ��ʾ�з��ź�
    for(int i=0;i<33;i++){
        sendmessage+=QString::number(GoingtoPlay[i]);
    }
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());

    //IndexCalculate();
    //flag = ch1->choice(GoingtoPlayIndex, true);//�ֶ�����!Ҫ����ֶ������㷨!
    //HumanPlayCard();
}

void MainWindow::on_DoNotPlay_clicked()
{
    //������ť
    ui->Play->setEnabled(false);
    ui->DoNotPlay->setEnabled(false);
    sendmessage.clear();
    sendmessage="P"+QString::number(thisplayer); //P��ͷ��ʾ�����ź�
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    //flag = ch1->choice(GoingtoPlayIndex, false);//������
    //HumanPlayCard();
}

void MainWindow::AIPlayCard(){
    //��������
    if(initround){ //���ϼ�
        temp.clear();
        P->Player[CurrentPlayer].AICard(temp,*ch,ch->Category);
        flag = ch1->choice(temp); //AI����
    }
    else { //���ϼ�
        temp.clear();
        P->Player[CurrentPlayer].AICard(temp);
        flag = ch1->choice(temp); //AI����
    }
    JudegePlayedCard();
}

void MainWindow::HumanPlayCard(){
    //��ҳ���
    JudegePlayedCard();
}

void MainWindow::JudegePlayedCard(){
    //��س����Ƿ���ȷ
    bool RoundEndFlag=false;
    if (flag == -1) {
        if (P->Player[CurrentPlayer].AIcontrol == 1) {
            cout << "�����������ƽ׶�" << endl << endl;
            //continue;
            RoundEndFlag=true;
            PlayerPlayedCard[CurrentPlayer].num.clear();
            PlayerPlayedCard[CurrentPlayer].color.clear();
            PlayerPlayedCard[CurrentPlayer].count=0;
            Pass->play();
            RoundEnd(2);
            return;
        }
        cout << "���������쳣!����������" << endl << endl;
        CurrentPlayer = (CurrentPlayer + 3) % 4;
        //continue;
        RoundEndFlag=true;
        RoundEnd(1);
        return;
    }
    else
        if (flag == 0) {
            cout << "�����������ƽ׶�" << endl << endl;
            //continue;
            RoundEndFlag=true;
            PlayerPlayedCard[CurrentPlayer].num.clear();
            PlayerPlayedCard[CurrentPlayer].color.clear();
            PlayerPlayedCard[CurrentPlayer].count=0;
            Pass->play();
            RoundEnd(2);
            return;
        }
    if(!RoundEndFlag){
        ch1->Frequency(); //������1ѡ����Ƶ�����, �������ж��Ƿ�Ϸ�, ������˳������
        if (!ch1->LegalJudge()) {
            //��һAI����, ��������ƽ׶���ǿ������BUG
            if (P->Player[CurrentPlayer].AIcontrol == 1) {
                cout << "�����������ƽ׶�" << endl << endl;
                //continue;
                RoundEndFlag=true;
                PlayerPlayedCard[CurrentPlayer].num.clear();
                PlayerPlayedCard[CurrentPlayer].color.clear();
                PlayerPlayedCard[CurrentPlayer].count=0;
                Pass->play();
                RoundEnd(2);
                return;
            }
            //BUG����
            if(!RoundEndFlag){
                cout << "�������ĳ��Ʋ��Ϸ�!�����³���." << endl << endl;
                CurrentPlayer = (CurrentPlayer + 3) % 4;
                //continue;
                RoundEndFlag=true;
                RoundEnd(1);
                return;
            }
        }
    }
    if(!RoundEndFlag){
        if (initround) {
            if (!(*ch1 > *ch)) {
                //��һAI����, ��������ƽ׶���ǿ������BUG
                if (P->Player[CurrentPlayer].AIcontrol == 1) {
                    cout << "�����������ƽ׶�" << endl << endl;
                    //continue;
                    RoundEndFlag=true;
                    PlayerPlayedCard[CurrentPlayer].num.clear();
                    PlayerPlayedCard[CurrentPlayer].color.clear();
                    PlayerPlayedCard[CurrentPlayer].count=0;
                    Pass->play();
                    RoundEnd(2);//�������ƽ׶δ���
                    return;
                }
                //BUG����
                if(!RoundEndFlag){
                    cout << "�����Ʋ�δ����ϼ�!�����³���." << endl << endl;
                    CurrentPlayer = (CurrentPlayer + 3) % 4;
                    //continue;
                    RoundEnd(1);//������Ч����
                    return;
                }
            }
        }
    }
    if(P->Player[CurrentPlayer].AIcontrol){
        PlayerPlayedCard[CurrentPlayer].num.clear();
        PlayerPlayedCard[CurrentPlayer].color.clear();
        PlayerPlayedCard[CurrentPlayer].count=0;
        for(int i=0;i<(int)temp.size();i++){
            PlayerPlayedCard[CurrentPlayer].num.push_back(P->Player[CurrentPlayer].card[temp[i]].num);
            PlayerPlayedCard[CurrentPlayer].color.push_back(P->Player[CurrentPlayer].card[temp[i]].color);
            PlayerPlayedCard[CurrentPlayer].count++;
        }
    }
    else{
        PlayerPlayedCard[CurrentPlayer].num.clear();
        PlayerPlayedCard[CurrentPlayer].color.clear();
        PlayerPlayedCard[CurrentPlayer].count=0;
        for(int i=0;i<(int)GoingtoPlayIndex.size();i++){
            PlayerPlayedCard[CurrentPlayer].num.push_back(P->Player[CurrentPlayer].card[GoingtoPlayIndex[i]].num);
            PlayerPlayedCard[CurrentPlayer].color.push_back(P->Player[CurrentPlayer].card[GoingtoPlayIndex[i]].color);
            PlayerPlayedCard[CurrentPlayer].count++;
        }
    }
    RoundEnd(0);//��������
}

/*
bool MainWindow::CheckAvailable(){
    if (!ch1->LegalJudge()) {
        return false;
    }
    if (initround) {
        if (!(*ch1 > *ch)) {
            return false;
        }
    }
    return true;
}
*/

void MainWindow::RoundEnd(int problem){


    //int problem�ֱ��ʾ���¼������
    //0:������Ч
    //1:������Ч
    //2:�������ƽ׶�
    if(problem==0){
        if(P->Player[CurrentPlayer].AIcontrol){
            P->Player[CurrentPlayer] -= (*ch1);//��һ����ʱ����
        }
        else{
            ch->HumanPlayCardDelete(P->Player[CurrentPlayer], GoingtoPlayIndex);
        }
        (*ch) = (*ch1);
        pround = CurrentPlayer;
        initround++;
        ClearPlayedCard();//����ϼ�����
        ui->label4->setText(QString::number(CurrentPlayer+1));
        PlayerPlayedCard[CurrentPlayer].pass=false;
        givecard->play();
    }
    if(problem==2){
        PlayerPlayedCard[CurrentPlayer].pass=true;
        PlayerPlayedCard[CurrentPlayer].num.clear();
        PlayerPlayedCard[CurrentPlayer].color.clear();
        PlayerPlayedCard[CurrentPlayer].count=0;
    }
    //��������ʾһ��, ��ʾ�Լ���ȷ������
    InTimePlayedCard();
    sleep(1000);//������Ҫע��һ��
    if (P->Player[CurrentPlayer].num == 0) {
        if (pround==BackupChief){
            cout << endl << "LandLord wins!" << endl << endl;
            for(int i=0;i<4;i++){
                if(i!=BackupChief){
                    PlayerScore[i]-=100*CurrentScore;
                    PMPlayerScore[i]=-100*CurrentScore;
                }
                else{
                    PlayerScore[i]+=300*CurrentScore;
                    PMPlayerScore[i]=300*CurrentScore;
                }
            }
            QLabel *w=new QLabel;
            QString text;
            QFont font("����",18,75);
            w->setAlignment(Qt::AlignCenter);
            w->setFont(font);
            text+=QString(str2qstr(string("��Ϸ����\n")));
            text+=QString(str2qstr(string("����ʤ��")));
            w->resize(200,100);
            w->move(750,400);
            w->setText(text);
            //w->setAlignment(Qt::AlignCenter);
            //w->setfont(QFontDialog::getFont(false,QFont("����",18,QFont::Bold)));
            w->show();
            //QMessageBox::information(this,QString(str2qstr(string("��Ϸ����"))),QString(str2qstr(string("����ʤ��"))));
            HidePlayerText();
        }
        else{
            cout << endl << "Farmer wins!" << endl << endl;
            for(int i=0;i<4;i++){
                if(i!=BackupChief){
                    PlayerScore[i]+=100*CurrentScore;
                    PMPlayerScore[i]=100*CurrentScore;
                }
                else{
                    PlayerScore[i]-=300*CurrentScore;
                    PMPlayerScore[i]=-300*CurrentScore;
                }
            }
            QLabel *w=new QLabel;
            QString text;
            QFont font("����",18,75);
            w->setAlignment(Qt::AlignCenter);
            w->setFont(font);
            text+=QString(str2qstr(string("��Ϸ����\n")));
            text+=QString(str2qstr(string("ũ��ʤ��")));
            w->resize(200,100);
            w->move(750,400);
            w->setText(text);
            //w->setAlignment(Qt::AlignCenter);
            //w->setfont(QFontDialog::getFont(false,QFont("����",18,QFont::Bold)));
            w->show();
            //QMessageBox::information(this,QString(str2qstr(string("��Ϸ����"))),QString(str2qstr(string("ũ��ʤ��"))));
            HidePlayerText();
        }
        GameOver();
        Overflag=true;
        return;
    }
    cout << endl;
    //ui->Play->setEnabled(false);
    delete ch1;

    PrintPlayedCard();//����µ��ϼ�����

    //ui->Play->setEnabled(false);
    InitPlay();//��ʼ��һ�ֳ���
}

void MainWindow::InTimePlayedCard(){

    ui->PASS0->hide();
    ui->PASS1->hide();
    ui->PASS2->hide();
    ui->PASS3->hide();
    ClearInTimePlayedCard();
    if(PlayerPlayedCard[seat[0]].pass){ui->PASS0->show();}
    if(PlayerPlayedCard[seat[1]].pass){ui->PASS1->show();}
    if(PlayerPlayedCard[seat[2]].pass){ui->PASS2->show();}
    if(PlayerPlayedCard[seat[3]].pass){ui->PASS3->show();}
    for(int i=0;i<4;i++){
        int number=(int)PlayerPlayedCard[seat[i]].num.size();
        int initnum=floor((33-number)/2);
        for(int j=0;j<number;j++){
            if(i==0)
                seatlabel0[initnum+j].setPixmap(PrintCard(PlayerPlayedCard[seat[i]].num[j],PlayerPlayedCard[seat[i]].color[j],1));
            if(i==1)
                seatlabel1[initnum+j].setPixmap(PrintCard(PlayerPlayedCard[seat[i]].num[j],PlayerPlayedCard[seat[i]].color[j],1));
            if(i==2)
                seatlabel2[initnum+j].setPixmap(PrintCard(PlayerPlayedCard[seat[i]].num[j],PlayerPlayedCard[seat[i]].color[j],1));
            if(i==3)
                seatlabel3[initnum+j].setPixmap(PrintCard(PlayerPlayedCard[seat[i]].num[j],PlayerPlayedCard[seat[i]].color[j],1));
        }
    }
}

void MainWindow::InitInTimePlayedCard(){
    for(int i=0;i<4;i++){
        if(i==0){
            seatlabel0=new QLabel[33];
            for(int j=0;j<33;j++){
                seatlabel0[j].setParent(this);
                seatlabel0[j].setGeometry(QRect(276+24*j,620,72,96));
                seatlabel0[j].show();
                //seatlabel0[j].setGeometry(QRect(0,0,72,120));
            }
        }
        if(i==1){
            seatlabel1=new QLabel[33];
            for(int j=0;j<33;j++){
                seatlabel1[j].setParent(this);
                seatlabel1[j].setGeometry(QRect(1100,168+18*j,72,96));
                seatlabel1[j].show();
                //seatlabel1[j].setGeometry(QRect(0,0,72,120));
            }
        }
        if(i==2){
            seatlabel2=new QLabel[33];
            for(int j=0;j<33;j++){
                seatlabel2[j].setParent(this);
                seatlabel2[j].setGeometry(QRect(276+24*j,230,72,96));
                seatlabel2[j].show();
                //seatlabel2[j].setGeometry(QRect(0,0,72,120));
            }
        }
        if(i==3){
            seatlabel3=new QLabel[33];
            for(int j=0;j<33;j++){
                seatlabel3[j].setParent(this);
                seatlabel3[j].setGeometry(QRect(200,168+18*j,72,96));
                seatlabel3[j].show();
                //seatlabel3[j].setGeometry(QRect(0,0,72,120));
            }
        }
    }
}

void MainWindow::ClearInTimePlayedCard(){
    for(int j=0;j<33;j++){
        seatlabel0[j].clear();
        seatlabel1[j].clear();
        seatlabel2[j].clear();
        seatlabel3[j].clear();
    }
}

void MainWindow::ShowScoreText(){
    for(int i=0;i<4;i++){
        string temp="";
        int OriginalScore=PlayerScore[i]-PMPlayerScore[i];
        temp+=to_string(OriginalScore);
        temp+='(';
        if(PMPlayerScore[i]>=0){
            temp+='+';
        }
        temp+=to_string(PMPlayerScore[i]);
        temp+=")=";
        temp+=to_string(PlayerScore[i]);
        if(i==0){
            ui->Player1LabelScore->setText(str2qstr(temp));
        }
        if(i==1){
            ui->Player2LabelScore->setText(str2qstr(temp));
        }
        if(i==2){
            ui->Player3LabelScore->setText(str2qstr(temp));
        }
        if(i==3){
            ui->Player4LabelScore->setText(str2qstr(temp));
        }
    }
}

//-----------------------------------����һ����Ϸ�ʹ��ڵķֽ���----------------------------------------------------
//
//
//
//���¾�Ϊ���㺯��
//
//�ú��������������е�����


// ���г���: Ctrl + F5 ����� >����ʼִ��(������)���˵�
// ���Գ���: F5 ����� >����ʼ���ԡ��˵�

// ������ʾ:
//   1. ʹ�ý��������Դ�������������/�����ļ�
//   2. ʹ���Ŷ���Դ�������������ӵ�Դ�������
//   3. ʹ��������ڲ鿴���������������Ϣ
//   4. ʹ�ô����б��ڲ鿴����
//   5. ת������Ŀ��>���������Դ����µĴ����ļ�����ת������Ŀ��>�����������Խ����д����ļ���ӵ���Ŀ
//   6. ��������Ҫ�ٴδ򿪴���Ŀ����ת�����ļ���>���򿪡�>����Ŀ����ѡ�� .sln �ļ�


void MainWindow::slot_connected()
{
    this->isconnetion = true;
    //ui->label->setText("Connection succeed");
}

void MainWindow::slot_recvmessage()
{
    //�������Է���������Ϣ
    QByteArray byteArray = this->TCP_sendMesSocket->readAll();
    recvMessage = byteArray;
    if(recvMessage[0]=='0'){
        qDebug()<<"Called";
        int a=(recvMessage.mid(2,1)).toInt();
        HumanLandLordDecided(a);
        if(thisplayer==LandLordRoundCurrentPlayer && thisplayer!=BackupChief){
            ui->Chief0Score->show();
            ui->Chief1Score->show();
            ui->Chief2Score->show();
            ui->Chief3Score->show();
        }
    }
    if(recvMessage[0]=='1'){
        for(int i=2;i<35;i++){
            if(recvMessage[i]=='0')
                GoingtoPlay[i-2]=0;
            else
                GoingtoPlay[i-2]=1;
        }
        IndexCalculate();
        flag = ch1->choice(GoingtoPlayIndex, true);//�ֶ�����!Ҫ����ֶ������㷨!
        HumanPlayCard();
    }
    if(recvMessage[0]=='s'){
        for(int i=0;i<108;i++){
            P->perm[i]=(recvMessage.mid(3*i+1,3)).toInt();
            qDebug()<<"String i: "<<recvMessage.mid(3*i+1,3);
            qDebug()<<"Int i: "<<recvMessage.mid(3*i+1,3).toInt();
        }
        GameStart2();
    }
    if(recvMessage[0]=='N' && thisplayer==0){
        thisplayer=(recvMessage.mid(1,1)).toInt();
        ui->ButtonConfirm->setEnabled(true);
        ui->StatusNum->setText(QString(str2qstr(string("�����Ϣ���ճɹ�"))));
    }
    if(recvMessage[0]=='P'){
        flag = ch1->choice(GoingtoPlayIndex, false);//������
        qDebug()<<"flag = "<<flag;
        HumanPlayCard();
    }
}

void MainWindow::slot_disconnect()
{
    QMessageBox::warning(this,"Warning","Connection down!",QMessageBox::Ok);
    //�رղ����ɾ��socket
    TCP_sendMesSocket->close();
    TCP_sendMesSocket->deleteLater();
}
