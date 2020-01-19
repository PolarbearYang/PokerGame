#ifndef WELCOMEWIN_H
#define WELCOMEWIN_H

#include<game.h>
#include<QLabel>
#include<QPushButton>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QWidget>
#include<QTimer>
#include<Drawbtnlab.h>
#include<QSlider>
#include<settingpanel.h>
#include "form1.h"
#include "form2.h"

class welcomewin : public QWidget
{
    Q_OBJECT

public slots:
    void onTimerout();
    void onsettingclick();
    void Launch21point();
    void LaunchLandlord();

public:
    welcomewin(QWidget *parent = 0);
    ~welcomewin();
    settingpanel *setting = new settingpanel();
private:
    QTimer *timer;
    QLabel *flowlab;
    QString strScrollCation;
public:
    Form2 *player1;
    Form1 *player2;
};



#endif // WELCOMEWIN_H
