#include "card.h"

card::card(rank r, suit s, bool ifu): m_Rank(r), m_Suit(s), m_IsFaceUp(ifu){
}
int card::GetValue() const{
    int value = 0;
    if (m_IsFaceUp){
        value = m_Rank;
        if (value > 10){
            value = 10; //J,Q,K算10
        }
    }
    return value;
}
void card::Flip(){
    m_IsFaceUp = !(m_IsFaceUp);
}
