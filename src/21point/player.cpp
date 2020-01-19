#include "player.h"
//int Player::m_money = 1000;
int Player::p1_total = 0;
int Player::p2_total = 0;
int Player::p3_total = 0;
int Player::p4_total = 0;
int Player::h_total = 0;
//bool Player::IsHitting = 0;
Player::Player()
{}
Player::~Player()
{}

void Player::Win(){
    m_money+=50;
}
void Player::Lose(){
    m_money-=50;
}
void Player::Push(){
    //m_money-=50;
}
void Player::Bust(){
    m_money-=50;
}
bool Player::IsBusted() const{
    return (GetTotal() > 21);
}
