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
        void setindex(int i){index=i;}
        //void setfuncptr(void (MainWindow::*fun1)(int), void (MainWindow::*fun2)(int)){func1=fun1;func2=fun2;}
        void setfuncptr(void (MainWindow::*fun)()){func=fun;}
        void setfather(MainWindow* father){this->father=father;}
        int Getindex(){return index;}
        void labelStatusChange();//改变牌的显示状态
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        //void setnum(int num){this->num=num;}
    };//为实现批量化卡牌按钮而新生成的类

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

    void on_ButtonConfirm_clicked(); //游戏初始界面确认游戏开始

    void on_Chief3Score_clicked(); //叫牌阶段点击了3分

    void on_Play_clicked(); //出牌按钮

    void on_Chief2Score_clicked(); //叫牌阶段点击了2分

    void on_Chief1Score_clicked(); //叫牌阶段点击了1分

    void on_DoNotPlay_clicked(); //出牌阶段选择不出

    void on_Chief0Score_clicked(); //叫牌阶段选择不叫

private:
    int tempint;//输入输出整数的媒介
    std::vector<int> AIinitStatus;//输入输出数组的媒介
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> JudgeNorm;
    void initval(){
        for(int i=0;i<4;i++){
            AIinitStatus.push_back(1);
        }
    }
    void GenerateNorm(); //用于比较牌型的函数，游戏准备阶段
    void PrintJudgeNorm(); //用于输出所有牌型的函数，仅测试用
    void pointerdecide();//决定指针, 初始化时使用
    void GameStart(); //游戏开始
    void GameOver(); //游戏结束
    void Qcardinit(); //读入图片，游戏准备阶段
    void PrintinitCard(); //输出玩家的初始手牌，游戏准备阶段
    void PrintHoleCard(); //输出底牌，游戏出牌阶段
    void PrintPlayedCard(); //输出每位玩家打出的牌，游戏出牌阶段
    void ClearPlayedCard(); //用于更新手牌，游戏出牌阶段
    void AILandLordDecided(); //AI决定是否叫地主。游戏叫牌阶段
    void HumanLandLordDecided(int choice); //人类决定叫地主，游戏叫牌阶段
    void EndLandLordDecide(); //叫牌阶段结束处理，游戏叫牌阶段
    void HideUI(); //隐藏UI，游戏结束阶段
    void PrintinitHoleCard(); //输出背面朝上的底牌，游戏叫牌阶段
    void ShowLandLordRoundCurrentPlayer();//输出即将叫地主者当前的手牌
    void ClearCards();//清空显示, 为手牌显示更新做准备
    void ShowCurrentPlayerCards(); //输出当前玩家的手牌，游戏出牌阶段
    void RecoverLandLordButton(); //恢复叫分按钮，游戏叫牌阶段
    void DisableLandLordButton(); //使部分叫分按钮失效，游戏叫牌阶段
    void ChangeToSelected(int index); //点牌操作，游戏出牌阶段
    void ChangeToUnselected(int index); //点牌操作，游戏出牌阶段
    void RefreshCardStatus();//到下一位玩家出牌时，将所有手牌还原为未选中状态，游戏出牌阶段
    void AIPlayCard();//人类出牌算法，游戏出牌阶段
    void HumanPlayCard();//AI出牌算法，游戏出牌阶段
    void InitPlay();//每位玩家出牌阶段之前初始化，游戏出牌阶段
    void RoundEnd(int problem);//每位玩家出牌阶段结束的处理，游戏出牌阶段
    void JudegePlayedCard(); //判断出牌牌型是否正确，游戏出牌阶段
    void IndexCalculate(); //根据点击选择计算即将打出的牌的下标，游戏出牌阶段
    void pointerdelete();//清除所有卡牌显示，游戏结束阶段
    void PlayerTextShow();//显示玩家编号，游戏开始阶段
    //后面的全是小功能
    void ShowPlayerText1();
    void ShowPlayerText2();
    void HidePlayerText();
    void LandLordExhibit();
    void InTimePlayedCard();
    void InitInTimePlayedCard();
    void ClearInTimePlayedCard();
    void ButtonPosRecover();
    void ShowScoreText();
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
};

#endif // MAINWINDOW_H
