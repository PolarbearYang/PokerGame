#ifndef RFORM0_H
#define RFORM0_H
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
namespace Ui {
class rform0;
}

class rform0 : public QWidget
{
    Q_OBJECT

public:
    explicit rform0(QWidget *parent = nullptr);
    ~rform0();
    QUdpSocket *mSocket;
    static int num_player;
    static int pre_num;
    static int all_num;

private slots:
    void player4hit();
    void player4stay();
    void begin();
    void shuffle();
    void read_data();
    void on_pushButton_clicked();

signals:
    void rform0show();
private:
    Ui::rform0 *ui;
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
    void r1round();
    void r2round();
    void r3round();
    QList<QLabel*> c1_list;
    QList<QLabel*> c2_list;
    QList<QLabel*> c3_list;
    QList<QLabel*> c4_list;
    QList<QLabel*> h_list;
};

#endif
