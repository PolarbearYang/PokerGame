#ifndef FORM4_H
#define FORM4_H
#include <QWidget>
#include <player.h>
#include <house.h>
#include <deck.h>
#include <client.h>
#include <mybutton.h>
#include <QLabel>
#include <QTime>
#include <QMessageBox>

namespace Ui {
class form4;
}

class form4 : public QWidget
{
    Q_OBJECT

public:
    explicit form4(QWidget *parent = nullptr);
    ~form4();
private slots:
    void p1hit();
    void p1stay();
    void p2hit();
    void p2stay();
    void p3hit();
    void p3stay();
    void p4hit();
    void p4stay();
    void begin();
    void shuffle();
    void on_exitbtn_clicked();

signals:
    void form4show();
private:
    Ui::form4 *ui;
    bool tocontinue;
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
    void endgame();
    void play();
    bool m_Hit;
    bool m_Stand;
    Deck m_Deck;
    House m_House;
    Player p1Player;
    Player p2Player;
    Player p3Player;
    Player p4Player;
    mybutton *p1_hit_btn;
    mybutton *p1_stand_btn;
    mybutton *p2_hit_btn;
    mybutton *p2_stand_btn;
    mybutton *p3_hit_btn;
    mybutton *p3_stand_btn;
    mybutton *p4_hit_btn;
    mybutton *p4_stand_btn;
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

#endif // FORM_H

