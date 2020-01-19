#ifndef TCP_HOST_H
#define TCP_HOST_H

#include <QWidget>
#include <QTcpServer>
#include <QTcpSocket>

namespace Ui {
class TCP_host;
}

class TCP_host : public QWidget
{
    Q_OBJECT

public:
    explicit TCP_host(QWidget *parent = nullptr);
    ~TCP_host();

private slots:
    void slot_newconnect(); //建立新连接的槽
    void slot_sendmessage(); //发送消息的槽
    void slot_recvmessage(); //接收消息的槽
    void slot_disconnect(); //取消连接的槽

private:
    Ui::TCP_host *ui;

    QTcpServer *TCP_server; //QTcpServer服务器
    QTcpSocket *TCP_connectSocket; //与客户端连接套接字
};

#endif // TCP_SERVER_H
