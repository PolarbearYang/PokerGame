#ifndef FORM_H
#define FORM_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>
#include <player.h>
#include <deck.h>
#include <house.h>
#include <QTime>
#include <client.h>
#include <mybutton.h>
#include <QLabel>
#include <QUdpSocket>
//extern QList<QLabel*> c1_list;
//extern QList<QLabel*> c2_list;
//extern QList<QLabel*> c3_list;
//extern QList<QLabel*> c4_list;
//extern QList<QLabel*> h_list;
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
    static int pre_num;
    static int all_num;

private slots:
    void slot_newconnect();
    void slot_recvmessage();
    void slot_disconnect();
    void player4hit();
    void player4stay();
    void begin();
    void shuffle();
    void read_data();
    void on_pushButton_clicked();

signals:
    void Formshow();
private:
    Ui::Form *ui;
    QTcpServer *TCP_server;
    QTcpSocket *TCP_connectSocket1;
    QTcpSocket *TCP_connectSocket2;
    QTcpSocket *TCP_connectSocket3;
    Deck m_Deck;
    void showPlayer1cards(Player& aGenericPlayer);
    void showPlayer2cards(Player& aGenericPlayer);
    void showPlayer3cards(Player& aGenericPlayer);
    void showPlayer4cards(Player& aGenericPlayer);
    void showHousecards(House& aGenericPlayer);
    void cleanPlayer1cards();
    void cleanPlayer2cards();
    void cleanPlayer3cards();
    void cleanPlayer4cards();
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
    Player p4Player;
    Player p1Player;
    Player p2Player;
    Player p3Player;
    House m_House;
    mybutton *hit_btn;
    mybutton *stand_btn;
    QLabel *c1n;
    QLabel *c1m;
    QLabel *c1back;
    QLabel *c1a;
    QLabel *c2n;
    QLabel *c2m;
    QLabel *c2back;
    QLabel *c2a;
    QLabel *c3n;
    QLabel *c3m;
    QLabel *c3back;
    QLabel *c3a;
    QLabel *c4n;
    QLabel *c4m;
    QLabel *c4back;
    QLabel *c4a;
    client *c1;
    client *c2;
    client *c3;
    client *c4;
    void sleep(unsigned int msec);
    int leavenum = 0;
    QList<QLabel*> c1_list;
    QList<QLabel*> c2_list;
    QList<QLabel*> c3_list;
    QList<QLabel*> c4_list;
    QList<QLabel*> h_list;
};

#endif
