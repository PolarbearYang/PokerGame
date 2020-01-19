#ifndef HOUSE_H
#define HOUSE_H
#include <hand.h>

class House : public hand{
public:
    House();
    virtual ~House();
    virtual bool IsHitting() const;
    void FlipFirstCard();
    static int h_total;
    void Bust() const;
    bool IsBusted() const;
};
#endif // HOUSE_H

