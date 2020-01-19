#ifndef GAME_H
#define GAME_H
#include<QMouseEvent>

//整体框架，交互各个功能模块


class Game
{
public:
    Game();
    ~Game();

    //鼠标点击后信息传递处理
    void clickevent();
    bool chosen_sta();
    bool chosen_con();

    void doudizhu();//打开斗地主游戏
    void blackjack();//打开21点
};

#endif // GAME_H
