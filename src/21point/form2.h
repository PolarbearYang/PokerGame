#ifndef FORM2_H
#define FORM2_H
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>
#include <player.h>
#include <deck.h>
#include <mybutton.h>
#include <QLabel>
#include <QUdpSocket>
#include <QtNetwork>
#include <client.h>
#include <house.h>
namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT

public:
    explicit Form2(QWidget *parent = nullptr);
    ~Form2();
    static int num_player;

private slots:
    void slot_connected();
    //void slot_sendmessage();
    void slot_recvmessage();
    void slot_disconnect();
    void begin();
    void shuffle();
    void player2hit();
    void player2stay();
    //void read_data();

    void on_pushButton_clicked();
signals:
    void Form2show();
private:
    Ui::Form2 *ui;
    bool isconnetion; //判断是否连接到服务器的标志位
    QTcpSocket *TCP_sendMesSocket;
    Deck m_Deck;
    void showPlayer1cards(Player& aGenericPlayer);
    void showPlayer2cards(Player& aGenericPlayer);
    void showPlayer3cards(Player& aGenericPlayer);
    void showPlayer4cards(Player& aGenericPlayer);
    void showHousecards(House& aGenericPlayer);
    void cleanPlayer4cards();
    void cleanPlayer1cards();
    void cleanPlayer2cards();
    void cleanPlayer3cards();
    void cleanHousecards();
    void play();
    void endgame();
    void player1hit();
    void player1stay();
    void player3hit();
    void player3stay();
    void player4hit();
    void player4stay();
    bool m_Hit;
    bool m_Stand;
    House m_House;
    Player p1Player;
    Player p2Player;
    Player p3Player;
    Player p4Player;
    mybutton *hit_btn; //对应按钮
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
    QList<QLabel*> c1_list;
    QList<QLabel*> c2_list;
    QList<QLabel*> c3_list;
    QList<QLabel*> c4_list;
    QList<QLabel*> h_list;
};

#endif
