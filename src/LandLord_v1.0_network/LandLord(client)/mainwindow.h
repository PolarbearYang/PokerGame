#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <vector>
#include <QWidget>
#include <QString>
#include <QMessageBox>
#include <QLabel>
#include <QGroupBox>

#include<QWidget>
#include<QMainWindow>
#include "MyQGroupBox.h"
#include <QPicture>
#include <QPixmap>
#include <iostream>
#include <QSound>

#include <QTcpServer>
#include <QTcpSocket>
#include <QUdpSocket>
#include <QtNetwork>

QString GetMessage();

namespace Ui {
  class MainWindow;
}



class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    static QString ipp;

public:

    class MyGroupBox: public QGroupBox{
        int index;//标记按钮下标
        void (MainWindow::*func)();
        //void (MainWindow::*func2)(int i);
        MainWindow* father;

        //int num;//实际手牌数
    public:
        std::vector<int> BackupGoingToPlay;
        MyGroupBox(int i=0, QWidget *parent = 0):QGroupBox(parent), index(i){
            //connect(this,SIGNAL(clicked()),this,labelStatusChange());
        }
        int* CurrentPlayer;
        int* thisplayer;
        void setindex(int i){index=i;}
        //void setfuncptr(void (MainWindow::*fun1)(int), void (MainWindow::*fun2)(int)){func1=fun1;func2=fun2;}
        void setfuncptr(void (MainWindow::*fun)()){func=fun;}
        void setfather(MainWindow* father){this->father=father;}
        int Getindex(){return index;}
        void labelStatusChange();//改变牌的显示状态
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        //void setnum(int num){this->num=num;}
    };

    struct Card {
        bool pass=false;
        int count=0;
        std::vector<int> num;//点数
        std::vector<int> color;//花色
    };//每位玩家出过的牌, pass或牌

    MyGroupBox* labelbox;//手牌对应按钮
    QLabel* upperlabel;//输出手牌(已选定)
    QLabel* lowerlabel;//输出手牌(未选定)
    QLabel* leftlabel;//输出左边的手牌(背面朝上)
    QLabel* crosslabel;//输出上面的手牌(背面朝上)
    QLabel* rightlabel;//输出右边的手牌
    QLabel* Holecard;//底牌
    QLabel* LastPlayerCard;//上家出的牌
    int banker=0;//当前的庄家
    int firstplayer=-1; //从哪一个玩家开始
    int CurrentScore = 0; //与叫牌功能关联, 叫牌阶段结束后即为地主叫的真正分数
    int BackupChief = -1; //与叫牌功能关联, 叫牌阶段结束后即为真正成为地主的人
    int LandLordRoundCurrentPlayer=banker;
    int LandLordDecidecount=0;//已叫分几次?

    int pround = -1;
    int initround = 0;//仅仅用做判断是否该玩家是否是第一次出牌, 或全员PASS后第一个出牌的
    int CurrentPlayer = -1; //当前的出牌者
    int flag;

    std::vector<int> seat; //分别对应当前,右边,对面,左边(逆时针顺序)每位玩家对应的座次
    std::vector<int> GoingtoPlay;//存放每一张牌是否要打出?是为1, 否为0, 长度为固定长度33
    std::vector<int> GoingtoPlayIndex;//存放要打出的牌的下标

    friend class MyGroupBox;
    struct Card PlayerPlayedCard[4];
    std::vector<int> temp;
    //需要从外部引入Pile

private slots:
    void on_Player1_AI_clicked();

    void on_Player2_AI_clicked();

    void on_Player3_AI_clicked();

    void on_Player4_AI_clicked();

    void on_Player1_human_clicked();

    void on_Player2_human_clicked();

    void on_Player3_human_clicked();

    void on_Player4_human_clicked();

    void on_ButtonConfirm_clicked();

    void on_Chief3Score_clicked();

    void on_Play_clicked();

    void on_Chief2Score_clicked();

    void on_Chief1Score_clicked();

    void on_DoNotPlay_clicked();

    void on_Chief0Score_clicked();

    //*网络函数开始
    void slot_connected();
    //void slot_sendmessage();
    void slot_recvmessage();
    void slot_disconnect();
    //网络函数结束

private:
    int tempint;//输入输出整数的媒介
    std::vector<int> AIinitStatus;//输入输出数组的媒介
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> JudgeNorm;
    void initval(){
        for(int i=0;i<4;i++){
            AIinitStatus.push_back(0);
        }
    }
    void GenerateNorm();
    void PrintJudgeNorm();
    void pointerdecide();//决定指针, 初始化时使用
    void GameStart();
    void GameOver();
    void Qcardinit();
    void PrintinitCard();
    void PrintHoleCard();
    void PrintPlayedCard();
    void ClearPlayedCard();
    void AILandLordDecided();
    void HumanLandLordDecided(int choice);
    void EndLandLordDecide();
    void HideUI();
    void PrintinitHoleCard();
    void ShowLandLordRoundCurrentPlayer();//输出即将叫地主者当前的手牌
    void ClearCards();//清空显示, 为手牌显示更新做准备
    void ShowCurrentPlayerCards();
    void RecoverLandLordButton();
    void DisableLandLordButton();
    void ChangeToSelected(int index);
    void ChangeToUnselected(int index);
    void RefreshCardStatus();//将所有手牌还原为未选中状态
    void AIPlayCard();//人类出牌算法
    void HumanPlayCard();//AI出牌算法
    void InitPlay();//出牌阶段之前初始化
    void RoundEnd(int problem);//出牌阶段结束的处理
    void JudegePlayedCard();
    void IndexCalculate();
    void pointerdelete();//清除所有卡牌显示
    void PlayerTextShow();//显示玩家编号
    void ShowPlayerText1();
    void ShowPlayerText2();
    void HidePlayerText();
    void LandLordExhibit();
    void InTimePlayedCard();
    void InitInTimePlayedCard();
    void ClearInTimePlayedCard();
    void ButtonPosRecover();
    void ShowScoreText();
    void GameStart2();
    //bool CheckAvailable();//检查牌是否能打出, 仅对人类玩家生效
    //void PlayButtonSet();
    //void HumanPlayCardDelete();//修正用的函数
    const QPixmap PrintCard(int Player, int j);//返回卡牌值
    const QPixmap PrintCard(int num, int color, int flag);//另一种返回卡牌值的方式
    QPixmap Qcard[55];
    QPixmap Qhead[2];
    QLabel* seatlabel0;
    QLabel* seatlabel1;
    QLabel* seatlabel2;
    QLabel* seatlabel3;
    int PlayerScore[4]={1000,1000,1000,1000};
    int PMPlayerScore[4]={0,0,0,0};

public:
    QString ip="0";
    QString sendmessage="0";
    int thisplayer=0;
//网络函数
private:
    bool isconnetion; //判断是否连接到服务器的标志位
    QTcpSocket *TCP_sendMesSocket;
    QString recvMessage="0";
    //Player m_House;
    //Player p1Player;
    //Player p2Player;
    //Player p3Player;

};

#endif // MAINWINDOW_H
