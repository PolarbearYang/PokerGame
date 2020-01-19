#pragma once
#ifndef PLAYERCARD_H
#define PLAYERCARD_H
#include <vector>
#include "Card.h"
typedef int CardGroup;
enum PColor { PNone, PSpade, PHearts, PClub, PDiamonds };
class PCard {
public:
	int num;//ʵ�ʴ�С
	int color;//��ɫ
    PCard(int i, int a):num(i),color(a) {}
};//�򻯵�PCard, �������ж����λ��
struct ExpandedKey {
	int point;
	int Val;
	std::vector<int> pos;
    ExpandedKey(int i, int j = 0) :point(i), Val(j) {}
};
struct HandCardValue{
	int Value;//��ֵȨ��
	int NeedRound;//���غ��ܳ�����
};//���ڼ��㵱ǰ���Ƶļ�ֵ, �ж��ܷ�е���
struct CardGroupData {
	std::vector<int> index;//�����Ͷ�Ӧԭ���Ƶ��±�
	CardGroup category = -1;//����
	int nValue = 0;//���Ƽ�ֵ, ���ڸ�Ȩ
	int nCount = 0;//��������
	int MAXCard = 0;//���ھ����ƵĴ�С����ֵ
	friend struct CardGroupData operator+=(struct CardGroupData& left, const struct CardGroupData& right);
	friend bool operator>(const struct CardGroupData& left, const struct CardGroupData& right);
};
class DividedCard {
	void CombinationStep1();//��һ��ȷ���Ƿ�����ը
	void CombinationStep2();//��һ����ϳ����е�ը��,����,����,����
	void CombinationStep3();//��һ����ϳ����е���˳,����,��˳
	void CombinationStep4();//��һ����ϳ����е����������
	void WeightConfirm();//��һ��ȷ��Ȩ��
    //void SplitCard(int index, int i);����ר��
public:
	std::vector<int> choice;//��Ҫ������Ƶ��±�
	struct HandCardValue Attribute;// ��ǰ�ƵĹ�������, �����жϷ��������ȼ�
	std::vector<PCard> CardSequence;//��ż򻯵�Card����, �����ڷ���������
	std::vector<struct CardGroupData> Group; //����Ѿ����������
	std::vector<ExpandedKey> EffectiveDict;//��dict�����ϳ�ȥ��������Ϊ0����
	void divideGroup();//��û���ϼҵ�����½��еķ���
	void divideGroup2();//�����ϼҵ�����½��еķ���
	struct CardGroupData ch;//�ϼҵ�����, ���ڴ����ϼ�����ʱ����
public:
	int Landlord = 0;//0�ֲ��е���, ������ӦҪ�еķ�
	DividedCard();
	~DividedCard();
	void Compose(std::vector<int>&);
	void TripleWithDual(int, std::vector<int>&);
	void DetermineChoice();//����Ҫ���ʲô��(û���ϼ�)
	void DetermineChoice2();//����Ҫ���ʲô��(���ϼ�)
	void ValueJudge();//���Ƽ�ֵ����
	void LandLordJudge();//�ж�Ҫ�м���
	void Interface(int pcase);//���ⲿ�����ԽӵĽӿں���, ר�����ڱ��ⲿ��������
	std::vector<int> available;//���Խ�ס�����͵��±�, ���������ϼҵ����
};
#endif // !PLAYERCARD_H
