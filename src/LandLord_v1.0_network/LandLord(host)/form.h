#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>
//#include <player.h>
//#include <deck.h>
//#include <mybutton.h>
#include <QLabel>
#include <QUdpSocket>
extern QList<QLabel*> c1_list;
extern QList<QLabel*> c2_list;
extern QList<QLabel*> c3_list;
extern QList<QLabel*> h_list;
namespace Ui {
class Form;
}

class Form : public QWidget
{
    Q_OBJECT

public:
    explicit Form(QWidget *parent = nullptr);
    ~Form();
    QUdpSocket *mSocket;
    static int num_player;

private slots:
    void slot_newconnect();
    void slot_sendmessage();
    void slot_recvmessage();
    void slot_disconnect();
    void househit();
    void housestay();
    void begin();
    void shuffle();
    void read_data();

private:
    Ui::Form *ui;
    QTcpServer *TCP_server; //QTcpServer服务器
    QTcpSocket *TCP_connectSocket1; //与客户端连接套接字
    QTcpSocket *TCP_connectSocket2;
    QTcpSocket *TCP_connectSocket3;
    Deck m_Deck;
    void showPlayer1cards(Player& aGenericPlayer);
    void showPlayer2cards(Player& aGenericPlayer);
    void showPlayer3cards(Player& aGenericPlayer);
    void showHousecards(Player& aGenericPlayer);
    void cleanPlayer1cards();
    void cleanPlayer2cards();
    void cleanPlayer3cards();
    void cleanHousecards();
    void play();
    void endgame();
    void player1hit();
    void player1stay();
    void player2hit();
    void player2stay();
    void player3hit();
    void player3stay();
    bool m_Hit;
    bool m_Stand;
    Player m_House;
    Player p1Player;
    Player p2Player;
    Player p3Player;
    mybutton *hit_btn; //对应按钮
    mybutton *stand_btn;
};
#endif // FORM_H
