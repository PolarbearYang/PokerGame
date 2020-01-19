#include "form1.h"
#include "ui_form1.h"
#include <QProcess>

Form1::Form1(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form1)
{
    ui->setupUi(this);
}

Form1::~Form1()
{
    delete ui;
}

void Form1::on_Single_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./4BJ.exe");
    this->close();
}

void Form1::on_Host_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./housework.exe");
    this->close();
}

void Form1::on_Client_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./playerwork.exe");
    this->close();
}
