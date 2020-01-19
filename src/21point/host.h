#ifndef HOST_H
#define HOST_H
#include <QUdpSocket>
#include <QWidget>
#include <QMessageBox>
#include <form1.h>
#include <form2.h>
#include <form3.h>
#include <QLabel>
#include <QTime>
#include <QListWidget>
namespace Ui {
class host;
}

class host : public QWidget
{
    Q_OBJECT

public:
    explicit host(QWidget *parent = nullptr);
    ~host();
    QUdpSocket *mSocket;
    static int m_order;
    static QString ip;
    QStringList iplist;
    Form1 *player1;
    Form2 *player2;
    Form3 *player3;

private slots:
    void on_pushButton_clicked();
    void read_data();
    void on_freshbtn_clicked();
    void cconnected();
    void showhost();
    void on_Exit_btn_clicked();
    void on_listWidget_itemClicked(QListWidgetItem *item);
    void on_listWidget_itemDoubleClicked(QListWidgetItem *item);

signals:
    void Hostshow();
private:
    Ui::host *ui;
    void sleep(unsigned int msec);
    int max_player;
    bool isfound;
    bool getone;
};

#endif // HOST_H
