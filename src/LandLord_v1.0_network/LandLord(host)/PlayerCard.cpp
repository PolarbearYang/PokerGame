//: PlayerCard.cpp
// ���ļ��洢AI�㷨
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
        struct CardGroupData tempGroup;//�������
        std::vector<int> Dictindex;//��¼ȡ������������
        for (int i = 0; i < (int)EffectiveDict.size(); i++) {
            if (EffectiveDict[i].point == 16)
                if (EffectiveDict[i].Val == 2)
                    Dictindex.push_back(i);
            if (EffectiveDict[i].point == 17)
                if (EffectiveDict[i].Val == 2)
                    Dictindex.push_back(i);
        }
        if ((int)Dictindex.size() == 2) {
            tempGroup.category = 0;//��ը, �����category����JudgeNorm�ı�׼(��Excel)
            for (int i = 0; i < (int)Dictindex.size(); i++) {
                for (int j = 0; j < (int)(EffectiveDict[Dictindex[i]].pos).size(); j++) {
                    tempGroup.index.push_back((EffectiveDict[Dictindex[i]].pos)[j]);
                }
            }
            tempGroup.MAXCard = INT_MAX;
            tempGroup.nCount = 4;
            tempGroup.nValue = 0; //����
            Group.push_back(tempGroup);
        }
        for (int j = (int)Dictindex.size() - 1; j >= 0; j--)
            EffectiveDict.erase(EffectiveDict.begin() + Dictindex[j]);//�����ѡ�е�Ԫ��
}

void DividedCard::CombinationStep2() {
    for (int i = 8; i >= 1; i--) {
        if ((int)EffectiveDict.size() > 0) {
            struct CardGroupData tempGroup;//�������
            std::vector<int> Dictindex;//��¼ȡ������������
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
                    tempGroup.nValue = 0; //����
                    EffectiveDict.erase(EffectiveDict.begin() + Dictindex[j]);
                    Group.push_back(tempGroup);
                }
            }
        }
    }
}

void DividedCard::WeightConfirm() {
    for (int i = 0; i < (int)Group.size(); i++) {
        //��ը��Ȩ
        if (Group[i].category == 0) {
            Group[i].nValue = INT_MAX;
            continue;
        }
        //ը����Ȩ
        if (Group[i].nCount >= 4) {
            Group[i].nValue = 1000 * (Group[i].nCount) + Group[i].MAXCard * 10;
            continue;
        }
        //������Ȩ
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
            Pindex.push_back(CurrentPointer2);//�����һ��Ԫ��

            //���ҵ�����Ԫ��, �������Pindex
            while (CurrentPointer2 < (int)Group.size() - 1) {
                if ((Group[CurrentPointer2].MAXCard - Group[CurrentPointer2 + 1].MAXCard == 1) && (Group[CurrentPointer2].category == Group[CurrentPointer2 + 1].category) && (Group[CurrentPointer2 + 1].MAXCard < 15) && (Group[CurrentPointer2].MAXCard < 15)) { //����, �Ҳ�����С2
                    Pindex.push_back(CurrentPointer2 + 1);
                }
                else
                    break;
                CurrentPointer2++;
            }
            if (Group[Pindex[0]].category == 6) { //��������˳
                if ((int)Pindex.size() >= 2) {
                    Compose(Pindex);
                    //CurrentPointer2 -= (int)Pindex.size();
                    //continue;
                }
            }
            if (Group[Pindex[0]].category == 7) { //���Ӳ�˫˳
                if ((int)Pindex.size() >= 3) {
                    Compose(Pindex);
                    //CurrentPointer2 -= (int)Pindex.size();
                    //continue;
                }
            }
            if (Group[Pindex[0]].category == 8) { //���Ʋ���˳
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
        if (TotalDualIndex.empty())//�����Ƿ��ѱ�ƥ����?
            break;
        if (Group[TotalTripleIndex[i]].category == 6) {
            if ((int)TotalDualIndex.size() != 0) {
                DualIndex.push_back(TotalDualIndex[(int)TotalDualIndex.size() - 1]);//ѡ��ĩβԪ��
                TripleWithDual(TotalTripleIndex[i], DualIndex);
                TotalDualIndex.erase(TotalDualIndex.begin() + (int)TotalDualIndex.size() - 1);//���ĩβԪ��
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
    //��ȷ�����
    if ((int)EffectiveDict.size() > 0)
        CombinationStep1();

    //��ȷ��ը��, ����, ����, ����
    CombinationStep2();

    //�����϶���ȷ��Ȩ��
    WeightConfirm();

    //���������кϲ�����:
    //�������ϲ�����˳
    //�Ѷ��Ӻϲ���˫˳
    //�ѵ��ƺϲ��ɵ�˳
    CombinationStep3();

    //�����������������(������˳������)
    //ͳ�����ԺͶ���
    CombinationStep4();
    //std::cout << "test end here..." << std::endl;
}

//�˺�������:
//��Group��Pindex�±���ƽ������, ��������洢��Group��Pindex[0]��, ��ɾ�������±��Ԫ��
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

//������ͬ���͵��Ƶ����, �������������
struct CardGroupData operator+=(struct CardGroupData& left, const struct CardGroupData& right) {
    if (left.category == 6)
        left.category += 21; //��˳���
    else
        if (left.category == 7)
            left.category += 9; //�������
        else
            if (left.category == 8) //�������
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
    //���ȴ����ֵ��С����
}

void DividedCard::ValueJudge() {
    Attribute.Value = 0; //��ʼ����ֵ����
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
    //ע: ��pcase������Ҫ����AI�㷨�Ĳ�ͬ���
    //0��ʾѡ����ʱ���ø��㷨�ж��Ƿ�Ҫ��Ϊ����
    //1��ʾ���ϼҵĳ����ж�
    //2��ʾ���ϼҵĳ����ж�
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
    //˾���BUG����
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
    //��ȷ�����
    CombinationStep1();

    //��ȷ��ը��, ����, ����, ����
    CombinationStep2();

    //�����϶���ȷ��Ȩ��
    WeightConfirm();

    //std::vector<int> available;//���Խ�ס�����͵��±�
    //���¸���������ѡ�������ܽ�ס�ϼҵ����͵����, Ȼ����ѡȨֵ��С�������ѹ��
    if (ch.category <= 8) {//���˴������ը������������, ֱ��ѹ
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
            //std::cout << (Group[i] > ch) << std::endl;//�����ô���
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
