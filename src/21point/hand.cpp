#include "hand.h"

hand::hand(){
    m_cards.reserve(7);
}
hand::~hand(){
    Clear();
}
void hand::Add(card* pcard){
    m_cards.push_back(pcard);
}
void hand::Clear(){
    vector<card*>::iterator iter = m_cards.begin();
    for (iter = m_cards.begin(); iter != m_cards.end(); ++iter){
        delete *iter;
        *iter = 0;
    }
    m_cards.clear(); //回合结束后，清空手牌
}
int hand::GetTotal() const{
    if (m_cards.empty()){
        return 0;
    }
    if (m_cards[0]->GetValue() == 0){
        return m_cards[1]->GetValue();
    }
    int total = 0;
    vector<card*>::const_iterator iter;
    for (iter = m_cards.begin(); iter != m_cards.end(); ++iter){
        total += (*iter)->GetValue();
    }
    bool containAce = false;
    for (iter = m_cards.begin(); iter != m_cards.end(); ++iter){
        if ((*iter)->GetValue() == card::ACE){
            containAce = true;
        }
    }
    if (containAce && total <= 11){
        total += 10; //21点中A可算11可算1
    }
    return total;
}
int hand::GetNum() const{
    if (m_cards.empty()){
        return 0;
    }
    if (m_cards[0]->GetValue() == 0){
        return 0;
    }
    int total = 0;
    vector<card*>::const_iterator iter;
    for (iter = m_cards.begin(); iter != m_cards.end(); ++iter){
        total += 1;
    }
    return total;
}
