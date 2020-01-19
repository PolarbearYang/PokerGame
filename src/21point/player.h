#ifndef PLAYER_H
#define PLAYER_H
#include <hand.h>

class Player : public hand{
public:
    Player();
    virtual ~Player();
    void Win();
    void Lose();
    void Push();
    void Bust();
    bool IsBusted() const;
    static int h_total;
    static int p1_total;
    static int p2_total;
    static int p3_total;
    static int p4_total;
    int m_money = 1000;
};
#endif // PLAYER_H

