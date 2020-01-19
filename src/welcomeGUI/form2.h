#ifndef FORM2_H
#define FORM2_H

#include <QWidget>

namespace Ui {
class Form2;
}

class Form2 : public QWidget
{
    Q_OBJECT

public:
    explicit Form2(QWidget *parent = 0);
    ~Form2();

private slots:
    void on_Single_clicked();

    void on_Host_clicked();

    void on_Client_clicked();

private:
    Ui::Form2 *ui;
};

#endif // FORM2_H
