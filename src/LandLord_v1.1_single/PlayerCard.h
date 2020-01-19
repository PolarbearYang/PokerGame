#pragma once
#ifndef PLAYERCARD_H
#define PLAYERCARD_H
#include <vector>
#include "Card.h"
typedef int CardGroup;
enum PColor { PNone, PSpade, PHearts, PClub, PDiamonds };
class PCard {
public:
	int num;//实际大小
	int color;//花色
    PCard(int i, int a):num(i),color(a) {}
};//简化的PCard, 仅用于判断相对位置
struct ExpandedKey {
	int point;
	int Val;
	std::vector<int> pos;
    ExpandedKey(int i, int j = 0) :point(i), Val(j) {}
};
struct HandCardValue{
	int Value;//价值权重
	int NeedRound;//几回合能出完牌
};//用于计算当前手牌的价值, 判断能否叫地主
struct CardGroupData {
	std::vector<int> index;//该牌型对应原手牌的下标
	CardGroup category = -1;//牌型
	int nValue = 0;//含牌价值, 用于赋权
	int nCount = 0;//含牌数量
	int MAXCard = 0;//用于决定牌的大小的牌值
	friend struct CardGroupData operator+=(struct CardGroupData& left, const struct CardGroupData& right);
	friend bool operator>(const struct CardGroupData& left, const struct CardGroupData& right);
};
class DividedCard {
	void CombinationStep1();//这一步确定是否有王炸
	void CombinationStep2();//这一步组合出所有的炸弹,三条,对子,单牌
	void CombinationStep3();//这一步组合出所有的三顺,连对,单顺
	void CombinationStep4();//这一步组合出所有的三带二组合
	void WeightConfirm();//这一步确定权重
    //void SplitCard(int index, int i);拆牌专用
public:
	std::vector<int> choice;//需要打出的牌的下标
	struct HandCardValue Attribute;// 当前牌的固有属性, 用于判断方案的优先级
	std::vector<PCard> CardSequence;//存放简化的Card序列, 仅用于返回坐标用
	std::vector<struct CardGroupData> Group; //存放已经分组的手牌
	std::vector<ExpandedKey> EffectiveDict;//在dict基础上除去所有数量为0的项
	void divideGroup();//在没有上家的情况下进行的分类
	void divideGroup2();//在有上家的情况下进行的分类
	struct CardGroupData ch;//上家的牌型, 仅在存在上家牌型时调用
public:
	int Landlord = 0;//0分不叫地主, 其他对应要叫的分
	DividedCard();
	~DividedCard();
	void Compose(std::vector<int>&);
	void TripleWithDual(int, std::vector<int>&);
	void DetermineChoice();//决定要打出什么牌(没有上家)
	void DetermineChoice2();//决定要打出什么牌(有上家)
	void ValueJudge();//手牌价值计算
	void LandLordJudge();//判断要叫几分
	void Interface(int pcase);//与外部函数对接的接口函数, 专门用于被外部函数调用
	std::vector<int> available;//可以接住的牌型的下标, 仅用于有上家的情况
};
#endif // !PLAYERCARD_H
