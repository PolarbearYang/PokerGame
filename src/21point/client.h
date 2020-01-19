#ifndef CLIENT_H
#define CLIENT_H
#include <QString>

class client
{
public:
    client();
    QString c_name = "Dallas";
    int c_ava = 1;
    void setname(QString n);
    void setava(int a);
};

#endif // CLIENT_H

