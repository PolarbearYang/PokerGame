#ifndef Form_H
#define Form_H
#include "mainwindow.h"
#include <QUdpSocket>
#include <QWidget>
#include <QLabel>
#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDateTime>
#include <QMessageBox>

extern QList<QLabel*> c1_list;
extern QList<QLabel*> c3_list;
extern QList<QLabel*> c2_list;
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
    static int m_order;
    static QString ip;//зЂвт
    MainWindow *player;

    //Form2 *player2;
    //Form3 *player3;

private slots:
    void on_pushButton_clicked();
    void read_data();
    void on_freshbtn_clicked();

private:
    Ui::Form *ui;
};

#endif // Form_H
