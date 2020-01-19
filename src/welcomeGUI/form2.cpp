#include "form2.h"
#include "ui_form2.h"
#include <QProcess>

Form2::Form2(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Form2)
{
    ui->setupUi(this);
}

Form2::~Form2()
{
    delete ui;
}

void Form2::on_Single_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./LandLord_single.exe");
    this->close();
}

void Form2::on_Host_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./LandLord_host.exe");
    this->close();
}

void Form2::on_Client_clicked()
{
    QProcess* process;
    process=new QProcess();
    process->start("./LandLord_client.exe");
    this->close();
}
