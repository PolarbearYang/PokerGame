#ifndef FORM1_H
#define FORM1_H

#include <QWidget>

namespace Ui {
class Form1;
}

class Form1 : public QWidget
{
    Q_OBJECT

public:
    explicit Form1(QWidget *parent = 0);
    ~Form1();

private slots:
    void on_Single_clicked();

    void on_Host_clicked();

    void on_Client_clicked();

private:
    Ui::Form1 *ui;
};

#endif // FORM1_H
