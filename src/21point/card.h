#ifndef CARD_H
#define CARD_H
#include <iostream>
using namespace std;
class card
{
public:
    enum rank {ACE = 1, TWO, THREE, FOUR, FIVE, SIX, SEVEN, EIGHT, NINE, TEN, JACK, QUEEN, KING
    };
    enum suit {CLUBS, DIAMONDS, HEARTS, SPADES
    };
    card(rank r = ACE, suit s = SPADES, bool ifu = true);
    int GetValue() const;
    void Flip();
    rank m_Rank;
    suit m_Suit;
    bool m_IsFaceUp;
};

#endif // CARD_H
