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
        void setindex(int i){index=i;}
        //void setfuncptr(void (MainWindow::*fun1)(int), void (MainWindow::*fun2)(int)){func1=fun1;func2=fun2;}
        void setfuncptr(void (MainWindow::*fun)()){func=fun;}
        void setfather(MainWindow* father){this->father=father;}
        int Getindex(){return index;}
        void labelStatusChange();//�ı��Ƶ���ʾ״̬
        void mousePressEvent(QMouseEvent *e);
        void mouseReleaseEvent(QMouseEvent *e);
        //void setnum(int num){this->num=num;}
    };//Ϊʵ�����������ư�ť�������ɵ���

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

    void on_ButtonConfirm_clicked(); //��Ϸ��ʼ����ȷ����Ϸ��ʼ

    void on_Chief3Score_clicked(); //���ƽ׶ε����3��

    void on_Play_clicked(); //���ư�ť

    void on_Chief2Score_clicked(); //���ƽ׶ε����2��

    void on_Chief1Score_clicked(); //���ƽ׶ε����1��

    void on_DoNotPlay_clicked(); //���ƽ׶�ѡ�񲻳�

    void on_Chief0Score_clicked(); //���ƽ׶�ѡ�񲻽�

private:
    int tempint;//�������������ý��
    std::vector<int> AIinitStatus;//������������ý��
    Ui::MainWindow *ui;
    std::vector<std::vector<int>> JudgeNorm;
    void initval(){
        for(int i=0;i<4;i++){
            AIinitStatus.push_back(1);
        }
    }
    void GenerateNorm(); //���ڱȽ����͵ĺ�������Ϸ׼���׶�
    void PrintJudgeNorm(); //��������������͵ĺ�������������
    void pointerdecide();//����ָ��, ��ʼ��ʱʹ��
    void GameStart(); //��Ϸ��ʼ
    void GameOver(); //��Ϸ����
    void Qcardinit(); //����ͼƬ����Ϸ׼���׶�
    void PrintinitCard(); //�����ҵĳ�ʼ���ƣ���Ϸ׼���׶�
    void PrintHoleCard(); //������ƣ���Ϸ���ƽ׶�
    void PrintPlayedCard(); //���ÿλ��Ҵ�����ƣ���Ϸ���ƽ׶�
    void ClearPlayedCard(); //���ڸ������ƣ���Ϸ���ƽ׶�
    void AILandLordDecided(); //AI�����Ƿ�е�������Ϸ���ƽ׶�
    void HumanLandLordDecided(int choice); //��������е�������Ϸ���ƽ׶�
    void EndLandLordDecide(); //���ƽ׶ν���������Ϸ���ƽ׶�
    void HideUI(); //����UI����Ϸ�����׶�
    void PrintinitHoleCard(); //������泯�ϵĵ��ƣ���Ϸ���ƽ׶�
    void ShowLandLordRoundCurrentPlayer();//��������е����ߵ�ǰ������
    void ClearCards();//�����ʾ, Ϊ������ʾ������׼��
    void ShowCurrentPlayerCards(); //�����ǰ��ҵ����ƣ���Ϸ���ƽ׶�
    void RecoverLandLordButton(); //�ָ��зְ�ť����Ϸ���ƽ׶�
    void DisableLandLordButton(); //ʹ���ֽзְ�ťʧЧ����Ϸ���ƽ׶�
    void ChangeToSelected(int index); //���Ʋ�������Ϸ���ƽ׶�
    void ChangeToUnselected(int index); //���Ʋ�������Ϸ���ƽ׶�
    void RefreshCardStatus();//����һλ��ҳ���ʱ�����������ƻ�ԭΪδѡ��״̬����Ϸ���ƽ׶�
    void AIPlayCard();//��������㷨����Ϸ���ƽ׶�
    void HumanPlayCard();//AI�����㷨����Ϸ���ƽ׶�
    void InitPlay();//ÿλ��ҳ��ƽ׶�֮ǰ��ʼ������Ϸ���ƽ׶�
    void RoundEnd(int problem);//ÿλ��ҳ��ƽ׶ν����Ĵ�����Ϸ���ƽ׶�
    void JudegePlayedCard(); //�жϳ��������Ƿ���ȷ����Ϸ���ƽ׶�
    void IndexCalculate(); //���ݵ��ѡ����㼴��������Ƶ��±꣬��Ϸ���ƽ׶�
    void pointerdelete();//������п�����ʾ����Ϸ�����׶�
    void PlayerTextShow();//��ʾ��ұ�ţ���Ϸ��ʼ�׶�
    //�����ȫ��С����
    void ShowPlayerText1();
    void ShowPlayerText2();
    void HidePlayerText();
    void LandLordExhibit();
    void InTimePlayedCard();
    void InitInTimePlayedCard();
    void ClearInTimePlayedCard();
    void ButtonPosRecover();
    void ShowScoreText();
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
};

#endif // MAINWINDOW_H
