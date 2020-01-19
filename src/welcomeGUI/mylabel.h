#ifndef MYLABEL_H
#define MYLABEL_H

#include <QObject>
#include <QLabel>

class mybutton : public QLabel
{
    Q_OBJECT

public:
    explicit mylabel(QLabel *parent = 0);

signals:

public slots:
};

#endif // MYLABEL_H
