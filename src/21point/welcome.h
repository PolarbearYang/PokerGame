#ifndef WELCOME_H
#define WELCOME_H

#include <QWidget>
#include <QLabel>
#include <form4.h>
#include <form3.h>
#include <form2.h>
#include <form1.h>
#include <form.h>
#include <rform0.h>
#include <rform1.h>
#include <rform2.h>
#include <host.h>
#include <mybutton.h>
#include <QLineEdit>
namespace Ui {
class welcome;
}

class welcome : public QWidget
{
    Q_OBJECT

public:
    explicit welcome(QWidget *parent = nullptr);
    ~welcome();
    static QString m_name;
    static int m_ava;


private:
    Ui::welcome *ui;
    mybutton *exit_btn;
    mybutton *this_begin_btn;
    mybutton *setself_btn;
    mybutton *help_btn;
    mybutton *host_btn;
    mybutton *guest_btn;
    mybutton *help_back_btn;
    mybutton *host_back_btn;
    mybutton *solo_btn;
    mybutton *bro_btn;
    mybutton *triple_btn;
    mybutton *group_btn;
    mybutton *self_back_btn;
    mybutton *self_ok_btn;
    QPushButton *setava1;
    QPushButton *setava2;
    QPushButton *setava3;
    QPushButton *setava4;
    QPushButton *setava5;
    QPushButton *setava6;
    QLabel *showname;
    QLabel *showava1;
    QLabel *showava2;
    QLabel *showok;
    QLabel *change1;
    QLabel *change2;
    form4 *this4man;
    Form *host4man;
    rform0 *host1man;
    rform1 *host2man;
    rform2 *host3man;
    host *findsever;
    QLabel *hhelp;
    QLineEdit *nameedt;


private slots:
    void newthis4man();
    void endgame();
    void helpshow();
    void helpback();
    void sethost();
    void solohost();
    void brohost();
    void triplehost();
    void grouphost();
    void findgame();
    void hostback();
    void setself();
    void selfback();
    void set1();
    void set2();
    void set3();
    void set4();
    void set5();
    void set6();
    void setname();
    void showwelcome();

};

#endif // WELCOME_H
