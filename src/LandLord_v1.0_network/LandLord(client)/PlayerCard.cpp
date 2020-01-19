//: PlayerCard.cpp
// 本文件存储AI算法
#pragma warning(disable:4267)
#include "PlayerCard.h"
#include<vector>
#include<iostream>

DividedCard::DividedCard() {
    Attribute.NeedRound = INT_MAX;
    Attribute.Value = 0;
    //divideGroup();
}

DividedCard::~DividedCard() {
    //std::vector<struct CardGroupData>.swap(Group);
}

void DividedCard::CombinationStep1() {
        struct CardGroupData tempGroup;//存放牌型
        std::vector<int> Dictindex;//记录取出的手牌坐标
        for (int i = 0; i < (int)EffectiveDict.size(); i++) {
            if (EffectiveDict[i].point == 16)
                if (EffectiveDict[i].Val == 2)
                    Dictindex.push_back(i);
            if (EffectiveDict[i].point == 17)
                if (EffectiveDict[i].Val == 2)
                    Dictindex.push_back(i);
        }
        if ((int)Dictindex.size() == 2) {
            tempGroup.category = 0;//王炸, 这里的category延用JudgeNorm的标准(见Excel)
            for (int i = 0; i < (int)Dictindex.size(); i++) {
                for (int j = 0; j < (int)(EffectiveDict[Dictindex[i]].pos).size(); j++) {
                    tempGroup.index.push_back((EffectiveDict[Dictindex[i]].pos)[j]);
                }
            }
            tempGroup.MAXCard = INT_MAX;
            tempGroup.nCount = 4;
            tempGroup.nValue = 0; //待定
            Group.push_back(tempGroup);
        }
        for (int j = (int)Dictindex.size() - 1; j >= 0; j--)
            EffectiveDict.erase(EffectiveDict.begin() + Dictindex[j]);//清楚已选中的元素
}

void DividedCard::CombinationStep2() {
    for (int i = 8; i >= 1; i--) {
        if ((int)EffectiveDict.size() > 0) {
            struct CardGroupData tempGroup;//存放牌型
            std::vector<int> Dictindex;//记录取出的手牌坐标
            for (int j = 0; j < (int)EffectiveDict.size(); j++) {
                if (EffectiveDict[j].Val == i) {
                    Dictindex.push_back(j);
                }
            }
            if ((int)Dictindex.size() >= 1) {
                for (int j = (int)Dictindex.size() - 1; j >= 0; j--) {
                    tempGroup.index.clear();
                    tempGroup.category = 9 - i;
                    tempGroup.MAXCard = EffectiveDict[Dictindex[j]].point;
                    for (int k = 0; k < (int)(EffectiveDict[Dictindex[j]].pos).size(); k++) {
                        tempGroup.index.push_back((EffectiveDict[Dictindex[j]].pos)[k]);
                    }
                    tempGroup.nCount = i;
                    tempGroup.nValue = 0; //待定
                    EffectiveDict.erase(EffectiveDict.begin() + Dictindex[j]);
                    Group.push_back(tempGroup);
                }
            }
        }
    }
}

void DividedCard::WeightConfirm() {
    for (int i = 0; i < (int)Group.size(); i++) {
        //王炸赋权
        if (Group[i].category == 0) {
            Group[i].nValue = INT_MAX;
            continue;
        }
        //炸弹赋权
        if (Group[i].nCount >= 4) {
            Group[i].nValue = 1000 * (Group[i].nCount) + Group[i].MAXCard * 10;
            continue;
        }
        //三条赋权
        if (Group[i].nCount >= 3) {
            Group[i].nValue = Group[i].MAXCard * 10 + 10 * ((Group[i].MAXCard >= 14) ? Group[i].MAXCard : 0) + 5;
            continue;
        }
        if (Group[i].nCount <= 2) {
            Group[i].nValue = Group[i].MAXCard * 10 + 10 * ((Group[i].MAXCard >= 14) ? Group[i].MAXCard : 0) + Group[i].nCount;
            continue;
        }
    }
}

void DividedCard::CombinationStep3() {
    int CurrentPointer = 0;
    while (CurrentPointer < (int)Group.size()) {
        int CurrentPointer2 = CurrentPointer;
        if (Group[CurrentPointer2].category > 5) {
            std::vector<int> Pindex;
            Pindex.push_back(CurrentPointer2);//插入第一个元素

            //若找到连续元素, 则将其插入Pindex
            while (CurrentPointer2 < (int)Group.size() - 1) {
                if ((Group[CurrentPointer2].MAXCard - Group[CurrentPointer2 + 1].MAXCard == 1) && (Group[CurrentPointer2].category == Group[CurrentPointer2 + 1].category) && (Group[CurrentPointer2 + 1].MAXCard < 15) && (Group[CurrentPointer2].MAXCard < 15)) { //连续, 且不包括小2
                    Pindex.push_back(CurrentPointer2 + 1);
                }
                else
                    break;
                CurrentPointer2++;
            }
            if (Group[Pindex[0]].category == 6) { //三条并三顺
                if ((int)Pindex.size() >= 2) {
                    Compose(Pindex);
                    //CurrentPointer2 -= (int)Pindex.size();
                    //continue;
                }
            }
            if (Group[Pindex[0]].category == 7) { //对子并双顺
                if ((int)Pindex.size() >= 3) {
                    Compose(Pindex);
                    //CurrentPointer2 -= (int)Pindex.size();
                    //continue;
                }
            }
            if (Group[Pindex[0]].category == 8) { //单牌并单顺
                if ((int)Pindex.size() >= 5) {
                    Compose(Pindex);
                    //CurrentPointer2 -= (int)Pindex.size();
                    //continue;
                }
            }
        }
        CurrentPointer++;
    }
}

void DividedCard::CombinationStep4() {
    std::vector<int> TotalTripleIndex;
    std::vector<int> TotalDualIndex;
    for (int i = 0; i < (int)Group.size(); i++) {
        if (Group[i].category == 7)
            TotalDualIndex.push_back(i);
        if (Group[i].category == 6 || (Group[i].category >= 27 && Group[i].category <= 37))
            TotalTripleIndex.push_back(i);
    }
    for (int i = (int)TotalTripleIndex.size() - 1; i >= 0; i--) {
        std::vector<int> DualIndex;
        if (TotalDualIndex.empty())//对子是否已被匹配完?
            break;
        if (Group[TotalTripleIndex[i]].category == 6) {
            if ((int)TotalDualIndex.size() != 0) {
                DualIndex.push_back(TotalDualIndex[(int)TotalDualIndex.size() - 1]);//选择末尾元素
                TripleWithDual(TotalTripleIndex[i], DualIndex);
                TotalDualIndex.erase(TotalDualIndex.begin() + (int)TotalDualIndex.size() - 1);//清除末尾元素
                continue;
            }
        }
        if (Group[TotalTripleIndex[i]].category >= 27 && Group[TotalTripleIndex[i]].category <= 37) {
            if ((int)TotalDualIndex.size() >= Group[TotalTripleIndex[i]].category - 25) {
                for (int j = 0; j < (int)Group[TotalTripleIndex[i]].category - 25; j++) {
                    DualIndex.push_back(TotalDualIndex[(int)TotalDualIndex.size() - 1]);
                    TotalDualIndex.erase(TotalDualIndex.begin() + (int)TotalDualIndex.size() - 1);
                }
                TripleWithDual(TotalTripleIndex[i], DualIndex);
                continue;
            }
        }
    }
}

void DividedCard::divideGroup() {
    //先确定火箭
    if ((int)EffectiveDict.size() > 0)
        CombinationStep1();

    //再确定炸弹, 三条, 对子, 单牌
    CombinationStep2();

    //对以上对象确定权重
    WeightConfirm();

    //接下来进行合并操作:
    //把三条合并成三顺
    //把对子合并成双顺
    //把单牌合并成单顺
    CombinationStep3();

    //最后进行三带二的组合(或者三顺带对子)
    //统计连对和对子
    CombinationStep4();
    //std::cout << "test end here..." << std::endl;
}

//此函数用于:
//将Group中Pindex下标的牌进行组合, 并将结果存储于Group的Pindex[0]中, 并删除其他下标的元素
void DividedCard::Compose(std::vector<int>& Pindex) {
    for (int i = 0; i < (int)Pindex.size() - 1; i++) {
        Group[Pindex[0]] += Group[Pindex[i + 1]];
    }
    for (int i = (int)Pindex.size() - 1; i >= 1; i--)
        Group.erase(Group.begin() + Pindex[i]);
}

void DividedCard::TripleWithDual(int Tripleindex, std::vector<int>& DualIndex) {
    for (int i = 0; i < (int)DualIndex.size(); i++) {
        Group[Tripleindex].nCount += Group[DualIndex[i]].nCount;
        for (int j = 0; j < (int)Group[DualIndex[i]].index.size(); j++) {
            Group[Tripleindex].index.push_back(Group[DualIndex[i]].index[j]);
        }
    }
    if (Group[Tripleindex].category == 6)
        Group[Tripleindex].category = 38;
    else
        Group[Tripleindex].category += 12;
    for (int i = 0; i < (int)DualIndex.size(); i++) {
        Group.erase(Group.begin() + DualIndex[i]);
    }
}

//仅用于同类型的牌的组合, 三带对另外计算
struct CardGroupData operator+=(struct CardGroupData& left, const struct CardGroupData& right) {
    if (left.category == 6)
        left.category += 21; //三顺组合
    else
        if (left.category == 7)
            left.category += 9; //对子组合
        else
            if (left.category == 8) //单牌组合
                left.category = left.category - 4 + 1;
            else
                left.category++;

    left.nCount += right.nCount;
    for (int i = 0; i < (int)right.index.size(); i++) {
        left.index.push_back(right.index[i]);
    }
    return left;
};

void DividedCard::DetermineChoice() {
    int Minvalue = INT_MAX, Minindex = 0;
    for (int i = 0; i < (int)Group.size(); i++) {
        if (Group[i].nValue < Minvalue) {
            Minindex = i;
            Minvalue = Group[i].nValue;
        }
    }
    if (Group.empty()) {
        choice.push_back(0);
        choice.push_back(1);
        return;
    }
    for (int i = 0; i < (int)Group[Minindex].index.size(); i++) {
        choice.push_back(Group[Minindex].index[i]);
    }
    //优先打出价值最小的牌
}

void DividedCard::ValueJudge() {
    Attribute.Value = 0; //初始化价值清零
    Attribute.NeedRound = (int)Group.size();
    for (int i = 0; i < Attribute.NeedRound; i++)
        Attribute.Value += Group[i].nValue;
}

void DividedCard::LandLordJudge() {
    double Score = (double)Attribute.Value / ((double)Attribute.NeedRound) / ((double)(Attribute.NeedRound));
    if (Score >= 90) {
        Landlord = 3;
    }
    else
        if (Score >= 60) {
            Landlord = 2;
        }
        else
            if (Score >= 30) {
                Landlord = 1;
            }
            else
                Landlord = 0;
}

void DividedCard::Interface(int pcase) {
    //注: 用pcase代表需要调用AI算法的不同情况
    //0表示选地主时调用该算法判定是否要成为地主
    //1表示无上家的出牌判定
    //2表示有上家的出牌判定
    if (pcase == 0) {
        divideGroup();
        ValueJudge();
        LandLordJudge();
    }
    if (pcase == 1) {
        divideGroup();
        ValueJudge();
        DetermineChoice();
    }
    if (pcase == 2) {
        divideGroup2();
        ValueJudge();
        DetermineChoice2();
    }
    //std::cout << "test end here..." << std::endl;
    //system("pause");
}

void DividedCard::DetermineChoice2() {
    //司令对BUG修正
    if (Group.empty()) {
        if (ch.category == 7 && ch.MAXCard <= 16) {
            choice.push_back(0);
            choice.push_back(1);
        }
        return;
    }

    if (available.empty()) {
        choice.push_back(-1);
        return;
    }
    int Minvalue = INT_MAX, Minindex = 0;
    for (int i = 0; i < (int)available.size(); i++) {
        if (Group[available[i]].nValue < Minvalue) {
            Minindex = i;
            Minvalue = Group[available[i]].nValue;
        }
    }
    for (int i = 0; i < (int)Group[available[Minindex]].index.size(); i++) {
        choice.push_back(Group[available[Minindex]].index[i]);
    }
}


void DividedCard::divideGroup2() {
    //先确定火箭
    CombinationStep1();

    //再确定炸弹, 三条, 对子, 单牌
    CombinationStep2();

    //对以上对象确定权重
    WeightConfirm();

    //std::vector<int> available;//可以接住的牌型的下标
    //以下根据牌型挑选出所有能接住上家的牌型的组合, 然后挑选权值最小的项进行压牌
    if (ch.category <= 8) {//别人打出的是炸弹或三条类型, 直接压
        for(int i=0;i<(int)Group.size();i++)
            if (Group[i] > ch) {
                available.push_back(i);
            }
    }
    std::cout << 1 << std::endl;
    if (ch.category >= 9 && ch.category <= 37) {
        CombinationStep3();
        for (int i = 0; i < (int)Group.size(); i++)
            if (Group[i] > ch) {
                available.push_back(i);
            }
    }

    if (ch.category >= 38) {
        CombinationStep3();
        CombinationStep4();
        for (int i = 0; i < (int)Group.size(); i++) {
            //std::cout << (Group[i] > ch) << std::endl;//测试用代码
            if (Group[i] > ch) {
                available.push_back(i);
            }
        }
    }

    //std::cout << "test end here..." << std::endl;

}

bool operator>(const struct CardGroupData& left, const struct CardGroupData& right) {
    if (left.category <= 5 && right.category >= 6)
        return 1;
    else
        if (left.category <= 5 && right.category <= 5) {
            if (left.category < right.category) {
                return 1;
            }
            else
                if ((left.category == right.category)) {
                    if ((left.MAXCard) > (right.MAXCard)){
                        return 1;
                    }
                }
        }
        else
            if ((left.category >= 6) && (right.category >= 6)) {
                if (left.category == right.category) {
                    if (left.MAXCard > right.MAXCard) {
                        return 1;
                    }
                }
            }
    return 0;
}
///:~
