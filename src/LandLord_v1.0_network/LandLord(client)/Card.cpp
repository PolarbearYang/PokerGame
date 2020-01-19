// Card.cpp: 与预编译标头对应的源文件；编译成功所必需的
#pragma warning(disable:4267)
#include "Card.h"
#include <iostream>
#include "RandArray.h"
#include <vector>
#include <algorithm>
#include "PlayerCard.h"

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include <QDialog>
#include <QtWidgets>
#include "MyQGroupBox.h"
#include <QString>
#include <QLabel>
#include <QPicture>
#include <QPixmap>
#include <QApplication>
#include <QTime>
#include <QSound>
#include <math.h>

Card::Card(int tempnum, Color color) {
    this->color = color;
    if (tempnum >= 3 && tempnum <= 9) {
        this->num = tempnum;
        this->Point[0] = '0' + tempnum;
        this->Point[1] = '\0';
        this->Point[2] = '\0';
    }
    if (tempnum == 10) {
        this->num = tempnum;
        this->Point[0] = '1';
        this->Point[1] = '0';
        this->Point[2] = '\0';
    }
    if (tempnum >= 11 && tempnum <= 13) {
        this->num = tempnum;
        this->Point[0] = 'J' + tempnum - 11;
        this->Point[1] = '0';
        this->Point[2] = '\0';
    }
    if (tempnum == 1) {
        this->num = tempnum + 13;
        this->Point[0] = 'A';
        this->Point[1] = '0';
        this->Point[2] = '\0';
    }
    if (tempnum == 2) {
        this->num = tempnum + 13;
        this->Point[0] = '2';
        this->Point[1] = '0';
        this->Point[2] = '\0';
    }
    if (tempnum == LJOKER) {
        this->num = 16;
        this->Point[0] = 'L';
        this->Point[1] = 'J';
        this->Point[2] = '\0';
    }
    if (tempnum == JOKER) {
        this->num = 17;
        this->Point[0] = 'J';
        this->Point[1] = 'O';
        this->Point[2] = '\0';
    }
}

bool operator>(const Card& left, const Card& right) {
    return left.num > right.num;
}

bool operator<(const Card& left, const Card& right) {
    return left.num < right.num;

}

bool operator>=(const Card& left, const Card& right) {
    if (left.num > right.num)
        return 1;
    else
        if (left.num == right.num && left.color >= right.color)
            return 1;
    return 0;
} //用于给手牌排序

bool operator<=(const Card& left, const Card& right) {
    if (left.num < right.num)
        return 1;
    else
        if (left.num == right.num && left.color <= right.color)
            return 1;
    return 0;
}

Pile::Pile(int pack):pack(pack) {
    card=new Card[pack * 54];
    for(int i=0;i<pack*54;i++){
        perm.push_back(0);
    }
    int temp = 0;
    for (int i = 3; i <= 9; i++) {
        for (int j = 0; j < pack; j++) {
            card[temp].num = i;
            card[temp].Point[0] = '0' + i;
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Spade;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = i;
            card[temp].Point[0] = '0' + i;
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Hearts;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = i;
            card[temp].Point[0] = '0' + i;
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Club;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = i;
            card[temp].Point[0] = '0' + i;
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Diamonds;
            temp++;
        }
    }

    for (int j = 0; j < pack; j++) {
        card[temp].num = 10;
        card[temp].Point[0] = '1';
        card[temp].Point[1] = '0';
        card[temp].Point[2] = '\0';
        card[temp].color = Spade;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 10;
        card[temp].Point[0] = '1';
        card[temp].Point[1] = '0';
        card[temp].Point[2] = '\0';
        card[temp].color = Hearts;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 10;
        card[temp].Point[0] = '1';
        card[temp].Point[1] = '0';
        card[temp].Point[2] = '\0';
        card[temp].color = Club;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 10;
        card[temp].Point[0] = '1';
        card[temp].Point[1] = '0';
        card[temp].Point[2] = '\0';
        card[temp].color = Diamonds;
        temp++;
    }

        for (int j = 0; j < pack; j++) {
            card[temp].num = 11;
            card[temp].Point[0] = 'J';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Spade;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 11;
            card[temp].Point[0] = 'J';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Hearts;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 11;
            card[temp].Point[0] = 'J';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Club;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 11;
            card[temp].Point[0] = 'J';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Diamonds;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 12;
            card[temp].Point[0] = 'Q';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Spade;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 12;
            card[temp].Point[0] = 'Q';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Hearts;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 12;
            card[temp].Point[0] = 'Q';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Club;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 12;
            card[temp].Point[0] = 'Q';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Diamonds;
            temp++;
        }

        for (int j = 0; j < pack; j++) {
            card[temp].num = 13;
            card[temp].Point[0] = 'K';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Spade;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 13;
            card[temp].Point[0] = 'K';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Hearts;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 13;
            card[temp].Point[0] = 'K';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Club;
            temp++;
        }
        for (int j = 0; j < pack; j++) {
            card[temp].num = 13;
            card[temp].Point[0] = 'K';
            card[temp].Point[1] = '\0';
            card[temp].Point[2] = '\0';
            card[temp].color = Diamonds;
            temp++;
        }
    //Ace
    for (int j = 0; j < pack; j++) {
        card[temp].num = 14;
        card[temp].Point[0] = 'A';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Spade;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 14;
        card[temp].Point[0] = 'A';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Hearts;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 14;
        card[temp].Point[0] = 'A';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Club;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 14;
        card[temp].Point[0] = 'A';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Diamonds;
        temp++;
    }
    //小2
    for (int j = 0; j < pack; j++) {
        card[temp].num = 15;
        card[temp].Point[0] = '2';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Spade;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 15;
        card[temp].Point[0] = '2';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Hearts;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 15;
        card[temp].Point[0] = '2';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Club;
        temp++;
    }
    for (int j = 0; j < pack; j++) {
        card[temp].num = 15;
        card[temp].Point[0] = '2';
        card[temp].Point[1] = '\0';
        card[temp].Point[2] = '\0';
        card[temp].color = Diamonds;
        temp++;
    }
    //小王
    for (int j = 0; j < pack; j++) {
        card[temp].num = LJOKER;
        card[temp].Point[0] = 'L';
        card[temp].Point[1] = 'J';
        card[temp].Point[2] = '\0';
        card[temp].color = None;
        temp++;
    }
    //大王
    for (int j = 0; j < pack; j++) {
        card[temp].num = JOKER;
        card[temp].Point[0] = 'J';
        card[temp].Point[1] = 'O';
        card[temp].Point[2] = '\0';
        card[temp].color = None;
        temp++;
    }
}

void Card::PrintCard() {
    switch (color)
    {
    case None:
        break;
    case Spade:
        std::cout << char(6);
        break;
    case Hearts:
        std::cout << char(3);
        break;
    case Club:
        std::cout << char(5);
        break;
    case Diamonds:
        std::cout << char(4);
        break;
    default:
        break;
    }
    std::cout << Point << " ";
}

void Pile::PrintPile() {
    for (int i = 0; i < pack * 54; i++) {
        card[i].PrintCard();
    }
    std::cout << std::endl;
}

void Pile::Shuffle() {
    std::vector<int> Array;
    for (int i = 0; i < pack * 54; i++)
        Array.push_back(i);
    RandArray(Array, perm);
}

void Pile::PrintCurrentPile() {
    for (int i = 0; i < pack * 54; i++) {
        card[perm[i]].PrintCard();
    }
    std::cout << std::endl;
}

void Pile::Allocation() {
    int temp = 0;
    qDebug()<<"flag1";
    for (int i = 0; i < 4; i++) {
        Player[i].num = (54 * pack) / 4 - 2;
        for (int j = 0; j < Player[i].num; j++) {
            qDebug()<<"perm[temp]: "<<perm[temp];
            (Player[i].card).push_back(card[perm[temp]]);
            qDebug()<<"card_push_back error? "<<j;
            temp++;
        }
        qDebug()<<"flag2 "<<i;
        Player[i].SortCard();
        qDebug()<<"flag3 "<<i;
    }
    HoleCard.num = pack * 4;
    for (int i = 0; i < pack * 4; i++) {
        (HoleCard.card).push_back(card[perm[temp]]);
        temp++;
    }
}

void PlayerCard::PrintHandCard() {
    for (int i = 0; i < num; i++)
        card[i].PrintCard();
    std::cout << std::endl;
}

void Pile::PrintPlayerCard() {
    for (int i = 0; i < 4; i++) {
        std::cout << "Player " << i + 1 << ": ";
        Player[i].PrintHandCard();
    }
}

void Pile::PrintHoleCard() {
    std::cout << "Hole card: ";
    HoleCard.PrintHandCard();
}

void PlayerCard::SortCard() {
    for (int i = 0; i < num; i++)
        for (int j = num - 1; j > i; j--)
            if (card[j] <= card[j - 1]) {
                Card tempcard;
                tempcard = card[j];
                card[j] = card[j - 1];
                card[j - 1] = tempcard;
            }
}

void choose::getarray(std::vector<int> &Array) {
    int a;
    char c;
    std::cin >> a;
    fflush(stdin);
    Array.push_back(a);
    while ((c = getchar()) != '\n') {
        std::cin >> a;
        fflush(stdin);
        Array.push_back(a);
    }
}

int choose::choice(std::vector<int>& Humanindex, bool human) {
    //执行之前做一次清空
    num=0;
    if(!card.empty()){card.clear();}
    if(human){
        std::cout << "输入玩家" << PlayerNum + 1 << "所要出的牌的下标：" << std::endl;
        num = (int)Humanindex.size();
        //如果想要PASS, 就输入首项为负数的数组
    if(Humanindex.size()==0){
        return -1;
    }
    if (Humanindex[0] < 0)
        return 0;
    for (int i = 0; i < num; i++)
        if (Humanindex[i]<0 || Humanindex[i]>((int)Player[PlayerNum].num-1))
            return -1;
    for (int i = 0; i < (int)Humanindex.size(); i++)
        card.push_back((Player[PlayerNum].card)[Humanindex[i]]);
    std::cout << "你即将打出：" << std::endl;
    SortCard();
    PrintHandCard();
    return 1;
    //1表示正常出牌, 0表示PASS, -1表示输入异常
    }
    else
        return 0;
}

int choose::choice(std::vector<int>& AIindex) {
    std::cout << "现在是AI玩家" << PlayerNum + 1 << "的轮次!" << std::endl;
    num = (int)AIindex.size();
    //如果想要PASS, 就输入首项为负数的数组
    /*
    if (num == 0) {
        index.push_back(0);
        index.push_back(1);
        return 1;
    }
    */
    if (num == 0) {
        return 0;
    }
    if (AIindex[0] < 0)
        return 0;
    for (int i = 0; i < num; i++)
        if (AIindex[i]<0 || AIindex[i]>((int)Player[PlayerNum].num - 1))
            return -1;
    for (int i = 0; i < (int)AIindex.size(); i++) {
        card.push_back((Player[PlayerNum].card)[AIindex[i]]);
        index.push_back(AIindex[i]);
    }
    std::cout << "你即将打出：" << std::endl;
    SortCard();
    PrintHandCard();
    return 1;
    //1表示正常出牌, 0表示PASS, -1表示输入异常
}

void PlayerCard::Frequency() {
    for (int i = 0; i < 15; i++)
        dict[i].Val = 0; //重新统计, 将值归零
    EffectiveDict.clear(); //清空, 初始化
    for (int i = 0; i < (int)card.size(); i++) {
        dict[card[i].num - 3].Val++; //统计牌面
    }
    //选择有效牌面(数量不为0的点数统计)
    for (int i = 0; i < 15; i++)
        if (dict[i].Val != 0)
            EffectiveDict.push_back(dict[i]);
    //进行排序
    for (int i = 0; i < (int)EffectiveDict.size(); i++)
        for (int j = EffectiveDict.size() - 1; j > i; j--)
            if ((EffectiveDict[j].Val > EffectiveDict[j - 1].Val) || (EffectiveDict[j].Val == EffectiveDict[j - 1].Val && EffectiveDict[j].point <= EffectiveDict[j - 1].point)) {
                Key tempkey(0,0);
                tempkey = EffectiveDict[j];
                EffectiveDict[j] = EffectiveDict[j - 1];
                EffectiveDict[j - 1] = tempkey;
            }
}



bool operator>(const choose& left, const choose& right) {
    if (left.Category <= 5 && right.Category >= 6)
        return 1;
    else
        if (left.Category <= 5 && right.Category <= 5) {
            if (left.Category < right.Category)
                return 1;
            else
                if ((left.Category == right.Category) && ((left.EffectiveDict[0].point) > (right.EffectiveDict[0].point)))
                    return 1;
        }
        else
            if ((left.Category >= 6) && (right.Category >= 6)) {
                if (left.Category == right.Category) {
                    if (left.EffectiveDict[0].point > right.EffectiveDict[0].point)
                        return 1;
                }
            }
    return 0;
}

bool choose::LegalJudge() {
    std::vector<int> character;
    for (int i = 0; i < (int)EffectiveDict.size(); i++)
        character.push_back(EffectiveDict[i].Val);
    int i;
    for (i = 0; i < (int)JudgeNorm.size(); i++)
        if (character == JudgeNorm[i]) {
            Category = i;
            break;
        }
    if (i >= (int)JudgeNorm.size())
        return 0;
    if (i == 0) {
        if (!(EffectiveDict[0].point == LJOKER))
            return 0;
        if (!(EffectiveDict[1].point == JOKER))
            return 0;
    }
    if (i >= 9 && i <= 16) {
        if (EffectiveDict[i - 5].point >= 15)
            return 0;
        for (int j = 0; j < i - 5; j++)
            if ((EffectiveDict[j + 1].point - EffectiveDict[j].point) != 1)
                return 0;
    }
    if (i >= 17 && i <= 26) {
        if (EffectiveDict[i - 15].point >= 15)
            return 0;
        for (int j = 0; j < i - 15; j++)
            if ((EffectiveDict[j + 1].point - EffectiveDict[j].point) != 1)
                return 0;
    }
    if (i >= 27 && i <= 37) {
        if (EffectiveDict[i - 26].point >= 15)
            return 0;
        for (int j = 0; j < i - 26; j++)
            if ((EffectiveDict[j + 1].point - EffectiveDict[j].point) != 1)
                return 0;
    }
    if (i >= 39 && i <= 48) {
        if (EffectiveDict[i - 38].point >= 15)
            return 0;
        for (int j = 0; j < i - 38; j++)
            if ((EffectiveDict[j + 1].point - EffectiveDict[j].point) != 1)
                return 0;
    }
    /*
    if (i >= 50 && i <= 59) {
        if (EffectiveDict[i - 49].point >= 15)
            return 0;
        for (int j = 0; j < i - 49; j++)
            if ((EffectiveDict[j + 1].point - EffectiveDict[j].point) != 1)
                return 0;
    }
    */
    return 1;
}

choose::choose(const choose& c) {
    this->PlayerNum = c.PlayerNum;
    this->Player = c.Player;
    for (int i = 0; i < (int)c.index.size(); i++)
        index.push_back(c.index[i]);
    for (int i = 0; i < (int)c.dict.size(); i++)
        dict.push_back(c.dict[i]);
    for (int i = 0; i < (int)c.EffectiveDict.size(); i++)
        EffectiveDict.push_back(c.EffectiveDict[i]);
    JudgeNorm = c.JudgeNorm;
    Category = c.Category;
}//拷贝构造函数

PlayerCard& operator+=(PlayerCard& left, const PlayerCard& right) {
    left.num += right.num;
    for (int i = 0; i < (int)right.card.size(); i++)
        left.card.push_back(right.card[i]);
    left.chief = 1;
    left.SortCard();
    return left;
}

PlayerCard& operator-=(PlayerCard& left, choose& right) {
    left.num -= right.num;//必须先对right进行升序排列!
    for (int i = 0; i < (int)right.index.size(); i++) {
        for (int j = (int)right.index.size() - 1; j > i; j--) {
            if ((right.index[j] < right.index[j - 1])) {
                int tempkey;
                tempkey = right.index[j];
                right.index[j] = right.index[j - 1];
                right.index[j - 1] = tempkey;
            }
        }
    }
    for (int i = ((right.index).size() - 1); i >= 0; i--) {
        left.card.erase(left.card.begin() + right.index[i]);
    }
    return left;
}

//该函数用于出无上家的牌
void PlayerCard::AICard(std::vector<int>& temp) {
    Frequency();//重新统计当前手牌

    //以下过程均为把参数传入AIpcard, 以独立处理的过程
    DividedCard AIpcard;
    for (int i = 0; i < (int)EffectiveDict.size(); i++) {
        ExpandedKey temp2(EffectiveDict[i].point, EffectiveDict[i].Val);
        AIpcard.EffectiveDict.push_back(temp2);
    }//EffectiveDict的初始化, 尚未考虑其包含的下标
    for (int i = 0; i < (int)card.size(); i++) {
        PCard temp2(card[i].num, card[i].color);
        AIpcard.CardSequence.push_back(temp2);
    }//PCard赋值
    //接下来补充EffectiveDict对应的下标
    for (int j = 0; j < (int)AIpcard.EffectiveDict.size(); j++) {
        for (int i = 0; i < (int)AIpcard.CardSequence.size(); i++) {
            if (AIpcard.EffectiveDict[j].point == AIpcard.CardSequence[i].num)
                AIpcard.EffectiveDict[j].pos.push_back(i);
        }
    }
    //至此传输完毕
    AIpcard.Interface(1);
    for (int i = 0; i < (int)AIpcard.choice.size(); i++)
        temp.push_back(AIpcard.choice[i]);
}


//该函数仅用于判断是否当地主
void PlayerCard::AICard() {
    Frequency();//重新统计当前手牌

//以下过程均为把参数传入AIpcard, 以独立处理的过程
    DividedCard AIpcard;
    for (int i = 0; i < (int)EffectiveDict.size(); i++) {
        ExpandedKey temp2(EffectiveDict[i].point, EffectiveDict[i].Val);
        AIpcard.EffectiveDict.push_back(temp2);
    }//EffectiveDict的初始化, 尚未考虑其包含的下标
    for (int i = 0; i < (int)card.size(); i++) {
        PCard temp2(card[i].num, card[i].color);
        AIpcard.CardSequence.push_back(temp2);
    }//PCard赋值
    //接下来补充EffectiveDict对应的下标
    for (int j = 0; j < (int)AIpcard.EffectiveDict.size(); j++) {
        for (int i = 0; i < (int)AIpcard.CardSequence.size(); i++) {
            if (AIpcard.EffectiveDict[j].point == AIpcard.CardSequence[i].num)
                AIpcard.EffectiveDict[j].pos.push_back(i);
        }
    }
    //至此传输完毕
    AIpcard.Interface(0);
    chief = AIpcard.Landlord;
    //if (chief == 0)chief = 4;
}


//该函数用于出比上家大的牌
void PlayerCard::AICard(std::vector<int>& temp, PlayerCard& ch, int category) {
    Frequency();//重新统计当前手牌

    //以下过程均为把参数传入AIpcard, 以独立处理的过程
    DividedCard AIpcard;
    for (int i = 0; i < (int)EffectiveDict.size(); i++) {
        ExpandedKey temp(EffectiveDict[i].point, EffectiveDict[i].Val);
        AIpcard.EffectiveDict.push_back(temp);
    }//EffectiveDict的初始化, 尚未考虑其包含的下标
    for (int i = 0; i < (int)card.size(); i++) {
        PCard temp(card[i].num, card[i].color);
        AIpcard.CardSequence.push_back(temp);
    }//PCard赋值
    //接下来补充EffectiveDict对应的下标
    for (int j = 0; j < (int)AIpcard.EffectiveDict.size(); j++)
        for (int i = 0; i < (int)AIpcard.CardSequence.size(); i++)
            if (AIpcard.EffectiveDict[j].point == AIpcard.CardSequence[i].num)
                AIpcard.EffectiveDict[j].pos.push_back(i);
    //至此传输完毕

    //接下来要传入ch以作比较

    for (int i = 0; i < (int)ch.EffectiveDict.size(); i++)
        for (int j = ch.EffectiveDict.size() - 1; j > i; j--)
            if ((ch.EffectiveDict[j].Val > ch.EffectiveDict[j - 1].Val) || (ch.EffectiveDict[j].Val == ch.EffectiveDict[j - 1].Val && ch.EffectiveDict[j].point <= ch.EffectiveDict[j - 1].point)) {
                Key tempkey(0, 0);
                tempkey = ch.EffectiveDict[j];
                ch.EffectiveDict[j] = ch.EffectiveDict[j - 1];
                ch.EffectiveDict[j - 1] = tempkey;
            }
    AIpcard.ch.category = category;
    AIpcard.ch.MAXCard = ch.EffectiveDict[0].point;
    for (int i = 0; i < (int)ch.EffectiveDict.size(); i++) {
        AIpcard.ch.nCount += (int)ch.EffectiveDict[i].Val;
    }
    //MAXCARD对应数量最多的手牌的最大值
    //AIpcard.divideGroup();
    //std::cout << ch.chief << std::endl;
    AIpcard.Interface(2);
    for (int i = 0; i < (int)AIpcard.choice.size(); i++)
        temp.push_back(AIpcard.choice[i]);
}
// 一般情况下，忽略此文件，但如果你使用的是预编译标头，请保留它。

