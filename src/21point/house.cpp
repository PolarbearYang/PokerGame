#include "house.h"
int House::h_total = 0;
House::House():
    hand()
{}
House::~House()
{}
bool House::IsHitting() const{
    return (GetTotal() <= 16);
}
void House::FlipFirstCard(){
    if (!(m_cards.empty())){
        m_cards[0]->Flip();
    } else {
        //cout << "No card to flip!\n";
    }
}
void House::Bust() const{

}
bool House::IsBusted() const{
    return (GetTotal() > 21);
}
