#ifndef DECK_H
#define DECK_H
#include <algorithm>
#include <ctime>
#include <hand.h>
#include "player.h"
class Deck : public hand{
public:
    Deck();
    virtual ~Deck();
    void Populate();
    void Shuffle();
    void Deal(hand& aHand);
    //void AdditionalPlayerCards(Player& aPlayer);
    static int c_left;
};

#endif // DECK_H
