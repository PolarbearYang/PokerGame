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
        int index;//��ǰ�ť�±�
        void (MainWindow::*func)();
        //void (MainWindow::*func2)(int i);
        MainWindow* father;

        //int num;//ʵ��������
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
        void labelStatusChange();//�ı��Ƶ���ʾ״̬
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        //void setnum(int num){this->num=num;}
    };

    struct Card {
        bool pass=false;
        int count=0;
        std::vector<int> num;//����
        std::vector<int> color;//��ɫ
    };//ÿλ��ҳ�������, pass����

    MyGroupBox* labelbox;//���ƶ�Ӧ��ť
    QLabel* upperlabel;//�������(��ѡ��)
    QLabel* lowerlabel;//�������(δѡ��)
    QLabel* leftlabel;//�����ߵ�����(���泯��)
    QLabel* crosslabel;//������������(���泯��)
    QLabel* rightlabel;//����ұߵ�����
    QLabel* Holecard;//����
    QLabel* LastPlayerCard;//�ϼҳ�����
    int banker=0;//��ǰ��ׯ��
    int firstplayer=-1; //����һ����ҿ�ʼ
    int CurrentScore = 0; //����ƹ��ܹ���, ���ƽ׶ν�����Ϊ�����е���������
    int BackupChief = -1; //����ƹ��ܹ���, ���ƽ׶ν�����Ϊ������Ϊ��������
    int LandLordRoundCurrentPlayer=banker;
    int LandLordDecidecount=0;//�ѽзּ���?

    int pround = -1;
    int initround = 0;//���������ж��Ƿ������Ƿ��ǵ�һ�γ���, ��ȫԱPASS���һ�����Ƶ�
    int CurrentPlayer = -1; //��ǰ�ĳ�����
    int flag;

    std::vector<int> seat; //�ֱ��Ӧ��ǰ,�ұ�,����,���(��ʱ��˳��)ÿλ��Ҷ�Ӧ������
    std::vector<int> GoingtoPlay;//���ÿһ�����Ƿ�Ҫ���?��Ϊ1, ��Ϊ0, ����Ϊ�̶�����33
    std::vector<int> GoingtoPlayIndex;//���Ҫ������Ƶ��±�

    friend class MyGroupBox;
    struct Card PlayerPlayedCard[4];
    std::vector<int> temp;
    //��Ҫ���ⲿ����Pile

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

    //*���纯����ʼ
    void slot_connected();
    //void slot_sendmessage();
    void slot_recvmessage();
    void slot_disconnect();
    //���纯������

private:
    int tempint;//�������������ý��
    std::vector<int> AIinitStatus;//������������ý��
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> JudgeNorm;
    void initval(){
        for(int i=0;i<4;i++){
            AIinitStatus.push_back(0);
        }
    }
    void GenerateNorm();
    void PrintJudgeNorm();
    void pointerdecide();//����ָ��, ��ʼ��ʱʹ��
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
    void ShowLandLordRoundCurrentPlayer();//��������е����ߵ�ǰ������
    void ClearCards();//�����ʾ, Ϊ������ʾ������׼��
    void ShowCurrentPlayerCards();
    void RecoverLandLordButton();
    void DisableLandLordButton();
    void ChangeToSelected(int index);
    void ChangeToUnselected(int index);
    void RefreshCardStatus();//���������ƻ�ԭΪδѡ��״̬
    void AIPlayCard();//��������㷨
    void HumanPlayCard();//AI�����㷨
    void InitPlay();//���ƽ׶�֮ǰ��ʼ��
    void RoundEnd(int problem);//���ƽ׶ν����Ĵ���
    void JudegePlayedCard();
    void IndexCalculate();
    void pointerdelete();//������п�����ʾ
    void PlayerTextShow();//��ʾ��ұ��
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
    //bool CheckAvailable();//������Ƿ��ܴ��, �������������Ч
    //void PlayButtonSet();
    //void HumanPlayCardDelete();//�����õĺ���
    const QPixmap PrintCard(int Player, int j);//���ؿ���ֵ
    const QPixmap PrintCard(int num, int color, int flag);//��һ�ַ��ؿ���ֵ�ķ�ʽ
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
//���纯��
private:
    bool isconnetion; //�ж��Ƿ����ӵ��������ı�־λ
    QTcpSocket *TCP_sendMesSocket;
    QString recvMessage="0";
    //Player m_House;
    //Player p1Player;
    //Player p2Player;
    //Player p3Player;

};

#endif // MAINWINDOW_H
