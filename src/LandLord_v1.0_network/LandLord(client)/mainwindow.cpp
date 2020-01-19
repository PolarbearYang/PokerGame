#pragma warning(disable:4267)
#include "Card.h"
#include <iostream>
#include "require.h"

using namespace std;

//std::vector<std::vector<int>> JudgeNorm;//这个全局变量存储了所有的牌型
//编号对应牌型见PokerGame文件夹下“牌型-编号记录.xlsx”

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




int tempint;//用于输入输出整数的全局变量
int cardnum;//记录当前玩家的手牌数量
bool Overflag=false;
QSound *GameStart0=new QSound("./SE/GameStart.wav");
QSound *ButtonClick01=new QSound("./SE/ButtonClick01.wav");
QSound *ButtonClick02=new QSound("./SE/ButtonClick02.wav");
QSound *Pass=new QSound("./SE/Pass.wav");
QSound *givecard=new QSound("./SE/givecard.wav");
QString MainWindow::ipp;
QString Message;//用于显示对话框中的消息
Pile* P; //建立牌堆
choose* ch;//上一位玩家出的牌
choose* ch1;//当前玩家出的牌
choose* chcheck;//用于检查当前玩家出牌是否合理, 以决定出牌按钮状态


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
    GenerateNorm();//生成用于比对牌型的矩阵
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
    //初始化sendMesSocket
    this->TCP_sendMesSocket = new QTcpSocket();
    //终止之前的连接，重置套接字
    TCP_sendMesSocket->abort();
    //给定IP和端口号，连接服务器
    //qDebug() << this->ip;
    this->TCP_sendMesSocket->connectToHost(MainWindow::ipp,8888);
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

    //thisplayer=ip.toInt()+1;

    {
        ui->groupBox->setStyleSheet("QGroupBox{border:none}");
        HideUI();//初始阶段隐藏UI
        HidePlayerText();//初始阶段隐藏玩家编号
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




//功能函数, 供各个部分调用
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
    //生成王炸
    temp.push_back(2);
    temp.push_back(2);
    JudgeNorm.push_back(temp);
    temp.clear();

    //生成只有一种值的所有牌型, 即炸弹, 三条, 对子, 单牌
    temp.push_back(8);
    for (int i = 0; i < 8; i++) {
        JudgeNorm.push_back(temp);
        temp[0]--;
    }
    temp.clear();

    //所有的顺子
    for (int i = 0; i < 5; i++) {
        temp.push_back(1);
    }
    for (int i = 0; i < 8; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(1);
    }
    temp.clear();

    //所有的连对
    temp.push_back(2); temp.push_back(2); temp.push_back(2);
    for (int i = 0; i < 10; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(2);
    }
    temp.clear();

    //所有的飞机
    temp.push_back(3); temp.push_back(3);
    for (int i = 0; i < 11; i++) {
        JudgeNorm.push_back(temp);
        temp.push_back(3);
    }
    temp.clear();

    //所有的三带对
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
    //地址分配, 并决定好每个对象的位置
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
    //游戏结束时清除所有label
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
    //Player对应玩家编号, j对应手牌下标
    //即返回Player的第j张手牌
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
    //flag没用, 仅作重载区分
    if(!flag)
        return Qcard[0];
    if(num>=16)
        return Qcard[num+37];
    else
        return Qcard[(num-3)*4+color];
}

void MainWindow::PrintinitCard(){
    //游戏开始时所有牌均背面朝上
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
    //记得先删除再更新座位!
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
        ui->Playerseat0Control->setText(QString(str2qstr(string("电脑"))));
    }
    else
        ui->Playerseat0Control->setText(QString(str2qstr(string("人类"))));
    if(P->Player[seat[1]].AIcontrol==1){
        ui->Playerseat1Control->setText(QString(str2qstr(string("电\n脑"))));
    }
    else
        ui->Playerseat1Control->setText(QString(str2qstr(string("人\n类"))));
    if(P->Player[seat[2]].AIcontrol==1){
        ui->Playerseat2Control->setText(QString(str2qstr(string("电脑"))));
    }
    else
        ui->Playerseat2Control->setText(QString(str2qstr(string("人类"))));
    if(P->Player[seat[3]].AIcontrol==1){
        ui->Playerseat3Control->setText(QString(str2qstr(string("电\n脑"))));
    }
    else
        ui->Playerseat3Control->setText(QString(str2qstr(string("人\n类"))));
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
//序言
//游戏开始与游戏结束的定义
//--------------------------------------------------
void MainWindow::GameStart(){
    pointerdecide();
    P=new Pile;
}

void MainWindow::GameStart2(){
    ui->groupBox_AIcontrol->hide();
    //这个位置有未知BUG
    qDebug()<<"Error Not here... flag1";
    P->Allocation(); //发牌
    qDebug()<<"Error Not here... flag2";
    P->PrintPlayerCard(); //呈现所有玩家的手牌
    P->PrintHoleCard(); //呈现底牌
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
    //显示叫分界面
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
    banker=(banker+1)%4;//按照逆时针顺序轮流成为庄家
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
//第一部分
//主界面按钮功能
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
    sendmessage="p"+QString::number(thisplayer); //p开头表示准备信号
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    GameStart();
    ui->ButtonConfirm->setEnabled(false);
    ui->StatusNum->hide();
}




//--------------------------------------------------
//第二部分
//叫地主算法
//--------------------------------------------------
void MainWindow::on_Chief3Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(1); //叫了一分
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"1"; //0开头表示叫分信号
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick01->play();
}



void MainWindow::on_Chief2Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(2); //叫了二分
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"2"; //0开头表示叫分信号
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick01->play();

}

void MainWindow::on_Chief1Score_clicked()
{
    ui->Chief0Score->hide();
    ui->Chief1Score->hide();
    ui->Chief2Score->hide();
    ui->Chief3Score->hide();
    //HumanLandLordDecided(3);  //叫了三分
    sendmessage.clear();
    sendmessage="0"+QString::number(thisplayer)+"3"; //0开头表示叫分信号
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
    sendmessage="0"+QString::number(thisplayer)+"0"; //0开头表示叫分信号
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    ButtonClick02->play();
}

void MainWindow::AILandLordDecided(){
    LandLordDecidecount++;

    int choice = 0;
    P->Player[LandLordRoundCurrentPlayer].AICard(); choice = 4 - P->Player[LandLordRoundCurrentPlayer].chief;
    //cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << P->Player[LandLordRoundCurrentPlayer].chief << "分!";
    if (choice < 1 || choice > 4) {
        LandLordRoundCurrentPlayer--;
        cout << "无此选项!请重新输入." << endl;
    }
    if (choice == 1) {
        BackupChief = LandLordRoundCurrentPlayer; //叫了3分
        CurrentScore = 3;
        //直接结束叫牌阶段
        cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << 3 << "分!";
        EndLandLordDecide();
        return;
    }
    if (choice == 2) {
        if (CurrentScore < 2) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 2;
            cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << 2 << "分!";
        }
        else{
            cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << "不叫!";
        }
    }
    if (choice == 3) {
        if (CurrentScore < 1) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 1;
            cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << 1 << "分!";
        }
        else{
            cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << "不叫!";
        }
    }
    if(!choice){
        cout << "AI玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << "不叫!";
    }
    LandLordRoundCurrentPlayer=(LandLordRoundCurrentPlayer+1)%4; //玩家改变!
    cout << "当前叫分: " << CurrentScore << endl;
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
        //所有玩家均已叫分, 准备开始游戏
    }
    //否则等待人类输入
}

void MainWindow::HumanLandLordDecided(int choice){
    LandLordDecidecount++;

    if(choice){P->Player[LandLordRoundCurrentPlayer].chief=4-choice;}
    //cout << "人类玩家" << LandLordRoundCurrentPlayer + 1 << "选择了" << P->Player[LandLordRoundCurrentPlayer].chief << "分!";
    if (choice < 1 || choice > 4) {
        //LandLordRoundCurrentPlayer--;
        cout << "人类玩家" << LandLordRoundCurrentPlayer + 1 << "选择了不叫!";
    }
    if (choice == 1) {
        BackupChief = LandLordRoundCurrentPlayer; //叫了3分
        CurrentScore = 3;
        EndLandLordDecide();
        cout << "人类玩家" << LandLordRoundCurrentPlayer + 1 << "选择了3分!";
        return;
    }
    if (choice == 2) {
        if (CurrentScore < 2) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 2;
            cout << "人类玩家" << LandLordRoundCurrentPlayer + 1 << "选择了2分!";
        }
        //cout << "你忘记做按钮失效的功能了!" << endl;
    }
    if (choice == 3) {
        if (CurrentScore < 1) {
            BackupChief = LandLordRoundCurrentPlayer;
            CurrentScore = 1;
            cout << "人类玩家" << LandLordRoundCurrentPlayer + 1 << "选择了1分!";
        }
        //cout << "你忘记做按钮失效的功能了!" << endl;
    }
    LandLordRoundCurrentPlayer=(LandLordRoundCurrentPlayer+1)%4;
    cout << "当前叫分: " << CurrentScore << endl;
    ui->label4_3->setText(QString::number(CurrentScore));
    RecoverLandLordButton();
    DisableLandLordButton();
    RefreshCardStatus();
    ShowLandLordRoundCurrentPlayer();

    if(P->Player[LandLordRoundCurrentPlayer].AIcontrol && LandLordDecidecount<4){
        AILandLordDecided();
    }
    //否则等待人类输入
    if(LandLordDecidecount>=4){
        EndLandLordDecide();
        //所有玩家均已叫分, 准备开始游戏
    }
}

void MainWindow::EndLandLordDecide(){
    PrintHoleCard();
    if(P->Player[0].chief<=0 || P->Player[0].chief >= 4)
        if (P->Player[1].chief <= 0 || P->Player[1].chief >= 4)
            if (P->Player[2].chief <= 0 || P->Player[2].chief >= 4)
                if (P->Player[3].chief <= 0 || P->Player[3].chief >= 4) {
                    if (CurrentScore == 0) {
                        cout << "没有地主!重新开局!" << endl;
                        GameOver();
                        return;
                    }
                }
    P->Player[BackupChief].chief = 1;
    P->Player[BackupChief] += P->HoleCard;
    firstplayer = BackupChief;
    cout << "现在玩家" << BackupChief + 1 << "是地主!" << endl;
    string str1="玩家";
    str1=str1+to_string(BackupChief+1)+"是地主";
    QLabel* w=new QLabel;
    QString text;
    QFont font("宋体",18,75);
    w->setAlignment(Qt::AlignCenter);
    w->setFont(font);
    text+=QString(str2qstr(string("叫牌阶段结束\n")));
    text+=QString(str2qstr(str1));
    w->resize(200,100);
    w->move(750,400);
    w->setText(text);
    //w->setAlignment(Qt::AlignCenter);
    //w->setfont(QFontDialog::getFont(false,QFont("宋体",18,QFont::Bold)));
    w->show();
    //QMessageBox::information(this,QString(str2qstr(string("叫牌阶段结束"))),QString(str2qstr(str1)));
    HideUI();
    //将用到的临时变量复原
    ui->label4_2->setVisible(false);
    ui->label4_3->setVisible(false);
    LandLordDecidecount=0;//已叫分几次?

    pround = firstplayer - 1; //标记上一个出牌的玩家
    initround = 0;//仅仅用做判断是否该玩家是否是第一次出牌, 或全员PASS后第一个出牌的
    CurrentPlayer = firstplayer - 1; //当前的出牌者
    ch=new choose(pround+1, P->Player, JudgeNorm);//上一位玩家出的牌
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
//第三部分
//出牌算法
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
    //改变牌显示的选中状态, 以及每张牌是否被选中的状态
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
    //还原选中状态
    for(int i=0;i<33;i++){
        if(GoingtoPlay[i]==1){
            GoingtoPlay[i]=0;
            lowerlabel[i].setPixmap(PrintCard(seat[0], i));
            upperlabel[i].clear();
        }
    }
    ClearCards();//清除显示
}

/*
void MainWindow::PlayButtonSet(){
    std::vector<int> GoingtoPlayIndex2;
    for(int i=0;i<33;i++){
        if(GoingtoPlay[i]==1)
            GoingtoPlayIndex2.push_back(i);
    }
    chcheck->choice(GoingtoPlayIndex2, true);
    chcheck->Frequency();//牌频统计
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
    //此处编写检查函数判断出牌按钮是否能够点击
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
    //出牌之前初始化
    ShowPlayerText1();
    //用于出牌的部分初始化
    GoingtoPlayIndex.clear();//待打出的牌下标的初始化
    for(int i=0;i<33;i++)
        GoingtoPlay[i]=0;//每张牌是否打出的初始化

    CurrentPlayer = (CurrentPlayer + 1) % 4; //当前玩家逆时针下移一位
    /*
    if(!P->Player[CurrentPlayer].AIcontrol){
        int temp=0;
        for(int i=0;i<4;i++){
            temp+=(int)P->Player[i].AIcontrol;
        }

        if(temp<=2){//只有一名人类玩家则不必提示
            string str1="人类玩家";
            str1=str1+to_string(CurrentPlayer+1)+"即将出牌";
            for(int i=0;i<33;i++){
                upperlabel[i].clear();
                lowerlabel[i].setPixmap(Qcard[0]);
            }//隐藏牌
            QMessageBox::information(this,QString(str2qstr(string("人类玩家的轮次"))),QString(str2qstr(str1)));
        }
    }
    */
    if (pround == CurrentPlayer){
        initround = 0; //0表示没有上家
        PlayerPlayedCard[(CurrentPlayer+1)%4].pass=false;
        PlayerPlayedCard[(CurrentPlayer+2)%4].pass=false;
        PlayerPlayedCard[(CurrentPlayer+3)%4].pass=false;
        //pass无效化
    }
    ui->Play->setEnabled(true);
    //判断不出按钮是否可用
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
    P->PrintPlayerCard(); //呈现所有玩家的手牌, 控制台测试函数
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
    ch1=new choose(CurrentPlayer,P->Player,JudgeNorm);//玩家i出牌阶段打出的牌
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
    //出牌按钮
    ui->Play->setEnabled(false);
    ui->DoNotPlay->setEnabled(false);
    sendmessage.clear();
    sendmessage="1"+QString::number(thisplayer); //0开头表示叫分信号
    for(int i=0;i<33;i++){
        sendmessage+=QString::number(GoingtoPlay[i]);
    }
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());

    //IndexCalculate();
    //flag = ch1->choice(GoingtoPlayIndex, true);//手动出牌!要添加手动出牌算法!
    //HumanPlayCard();
}

void MainWindow::on_DoNotPlay_clicked()
{
    //不出按钮
    ui->Play->setEnabled(false);
    ui->DoNotPlay->setEnabled(false);
    sendmessage.clear();
    sendmessage="P"+QString::number(thisplayer); //P开头表示不出信号
    this->TCP_sendMesSocket->write(sendmessage.toLatin1());
    //flag = ch1->choice(GoingtoPlayIndex, false);//不出牌
    //HumanPlayCard();
}

void MainWindow::AIPlayCard(){
    //机器出牌
    if(initround){ //有上家
        temp.clear();
        P->Player[CurrentPlayer].AICard(temp,*ch,ch->Category);
        flag = ch1->choice(temp); //AI出牌
    }
    else { //无上家
        temp.clear();
        P->Player[CurrentPlayer].AICard(temp);
        flag = ch1->choice(temp); //AI出牌
    }
    JudegePlayedCard();
}

void MainWindow::HumanPlayCard(){
    //玩家出牌
    JudegePlayedCard();
}

void MainWindow::JudegePlayedCard(){
    //监控出牌是否正确
    bool RoundEndFlag=false;
    if (flag == -1) {
        if (P->Player[CurrentPlayer].AIcontrol == 1) {
            cout << "您已跳过出牌阶段" << endl << endl;
            //continue;
            RoundEndFlag=true;
            PlayerPlayedCard[CurrentPlayer].num.clear();
            PlayerPlayedCard[CurrentPlayer].color.clear();
            PlayerPlayedCard[CurrentPlayer].count=0;
            Pass->play();
            RoundEnd(2);
            return;
        }
        cout << "输入数组异常!请重新输入" << endl << endl;
        CurrentPlayer = (CurrentPlayer + 3) % 4;
        //continue;
        RoundEndFlag=true;
        RoundEnd(1);
        return;
    }
    else
        if (flag == 0) {
            cout << "您已跳过出牌阶段" << endl << endl;
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
        ch1->Frequency(); //监控玩家1选择出牌的牌型, 接下来判定是否合法, 若是则顺利出牌
        if (!ch1->LegalJudge()) {
            //万一AI故障, 跳出其出牌阶段以强行修正BUG
            if (P->Player[CurrentPlayer].AIcontrol == 1) {
                cout << "您已跳过出牌阶段" << endl << endl;
                //continue;
                RoundEndFlag=true;
                PlayerPlayedCard[CurrentPlayer].num.clear();
                PlayerPlayedCard[CurrentPlayer].color.clear();
                PlayerPlayedCard[CurrentPlayer].count=0;
                Pass->play();
                RoundEnd(2);
                return;
            }
            //BUG结束
            if(!RoundEndFlag){
                cout << "但是您的出牌不合法!请重新出牌." << endl << endl;
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
                //万一AI故障, 跳出其出牌阶段以强行修正BUG
                if (P->Player[CurrentPlayer].AIcontrol == 1) {
                    cout << "您已跳过出牌阶段" << endl << endl;
                    //continue;
                    RoundEndFlag=true;
                    PlayerPlayedCard[CurrentPlayer].num.clear();
                    PlayerPlayedCard[CurrentPlayer].color.clear();
                    PlayerPlayedCard[CurrentPlayer].count=0;
                    Pass->play();
                    RoundEnd(2);//跳出出牌阶段处理
                    return;
                }
                //BUG结束
                if(!RoundEndFlag){
                    cout << "您的牌并未大过上家!请重新出牌." << endl << endl;
                    CurrentPlayer = (CurrentPlayer + 3) % 4;
                    //continue;
                    RoundEnd(1);//出牌无效处理
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
    RoundEnd(0);//正常结束
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


    //int problem分别表示如下几种情况
    //0:出牌有效
    //1:出牌无效
    //2:跳出出牌阶段
    if(problem==0){
        if(P->Player[CurrentPlayer].AIcontrol){
            P->Player[CurrentPlayer] -= (*ch1);//这一句暂时不明
        }
        else{
            ch->HumanPlayCardDelete(P->Player[CurrentPlayer], GoingtoPlayIndex);
        }
        (*ch) = (*ch1);
        pround = CurrentPlayer;
        initround++;
        ClearPlayedCard();//清除上家牌型
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
    //这里先显示一次, 表示自己的确出了牌
    InTimePlayedCard();
    sleep(1000);//这里需要注意一下
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
            QFont font("宋体",18,75);
            w->setAlignment(Qt::AlignCenter);
            w->setFont(font);
            text+=QString(str2qstr(string("游戏结束\n")));
            text+=QString(str2qstr(string("地主胜利")));
            w->resize(200,100);
            w->move(750,400);
            w->setText(text);
            //w->setAlignment(Qt::AlignCenter);
            //w->setfont(QFontDialog::getFont(false,QFont("宋体",18,QFont::Bold)));
            w->show();
            //QMessageBox::information(this,QString(str2qstr(string("游戏结束"))),QString(str2qstr(string("地主胜利"))));
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
            QFont font("宋体",18,75);
            w->setAlignment(Qt::AlignCenter);
            w->setFont(font);
            text+=QString(str2qstr(string("游戏结束\n")));
            text+=QString(str2qstr(string("农民胜利")));
            w->resize(200,100);
            w->move(750,400);
            w->setText(text);
            //w->setAlignment(Qt::AlignCenter);
            //w->setfont(QFontDialog::getFont(false,QFont("宋体",18,QFont::Bold)));
            w->show();
            //QMessageBox::information(this,QString(str2qstr(string("游戏结束"))),QString(str2qstr(string("农民胜利"))));
            HidePlayerText();
        }
        GameOver();
        Overflag=true;
        return;
    }
    cout << endl;
    //ui->Play->setEnabled(false);
    delete ch1;

    PrintPlayedCard();//输出新的上家牌型

    //ui->Play->setEnabled(false);
    InitPlay();//开始下一轮出牌
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

//-----------------------------------这是一条游戏和窗口的分界线----------------------------------------------------
//
//
//
//以下均为计算函数
//
//该函数用于生成所有的牌型


// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门提示:
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件


void MainWindow::slot_connected()
{
    this->isconnetion = true;
    //ui->label->setText("Connection succeed");
}

void MainWindow::slot_recvmessage()
{
    //接收来自服务器的消息
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
        flag = ch1->choice(GoingtoPlayIndex, true);//手动出牌!要添加手动出牌算法!
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
        ui->StatusNum->setText(QString(str2qstr(string("编号信息接收成功"))));
    }
    if(recvMessage[0]=='P'){
        flag = ch1->choice(GoingtoPlayIndex, false);//不出牌
        qDebug()<<"flag = "<<flag;
        HumanPlayCard();
    }
}

void MainWindow::slot_disconnect()
{
    QMessageBox::warning(this,"Warning","Connection down!",QMessageBox::Ok);
    //关闭并随后删除socket
    TCP_sendMesSocket->close();
    TCP_sendMesSocket->deleteLater();
}
