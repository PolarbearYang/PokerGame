#include "deck.h"
int Deck::c_left = 52;
Deck::Deck(){
    m_cards.reserve(52);
    Populate();
}
Deck::~Deck()
{}
void Deck::Populate(){
    Clear();
    for (int s = card::CLUBS; s <= card::SPADES; ++s){
        for (int r = card::ACE; r <= card::KING; ++r){
            Add(new card(static_cast<card::rank>(r), static_cast<card::suit>(s)));
        }
    }
}
void Deck::Shuffle(){
    random_shuffle(m_cards.begin(), m_cards.end());
}
void Deck::Deal(hand& ahand){
    if (!m_cards.empty()){
        ahand.Add(m_cards.back());
        m_cards.pop_back();
    } else {
        //cout << "Out of cards. Unable to deal.";
        //暂时没想好怎么处理牌堆为空的情况
    }
}
