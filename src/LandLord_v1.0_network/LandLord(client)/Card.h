// 入门提示: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

#pragma once
#ifndef CARD_H
#define CARD_H
#include <vector>
#include "PlayerCard.h"
enum Color { None, Spade, Hearts, Club, Diamonds }; //None用于标记大小王, 其余对应真实花色
const int JOKER = 17;
const int LJOKER = 16;
class Card;
class Pile;
class PlayerCard;
class HoleCards;

struct Key {
	int point;
	int Val;
	Key(int i, int j = 0) :point(i), Val(j) {};
};

class Card {
public:
	char Point[3];//点数
	int num;//实际大小
	Color color;//花色
public:
	Card(int tempnum = 0, Color color = Spade);
	~Card() {};
	friend bool operator>(const Card& left, const Card& right);
	friend bool operator<(const Card& left, const Card& right);
	friend bool operator>=(const Card& left, const Card& right); //用于给手牌排序
	friend bool operator<=(const Card& left, const Card& right);
	friend class Pile;
	friend class PlayerCard;
	void PrintCard();//控制台上使用的检查函数
};

class PlayerCard {
	//玩家的手牌情况
public:
	std::vector<Card> card;//手牌
	int num;//当前手牌数
	std::vector<Key> dict;//存储各种要出的牌所占的数量
	std::vector<Key> EffectiveDict;//在dict基础上除去所有数量为0的项
	bool AIcontrol = 0;//是否由机器控制?是为True, 否为False
public:
	int chief = 0;//是否是地主?是为所要叫的分数, 否为0
	void PrintHandCard();//控制台上使用的检查函数
	void SortCard();//给手牌排序
	PlayerCard():chief(0),num(0){
		for (int i = 3; i <= 17; i++) {

			if (i == 16)
				num = LJOKER;
			else
				if (i == 17)
					num = JOKER;
				else
					num = i;
			Key temp(num, 0);
			dict.push_back(temp);

			num = 0;
		}
    }
	void Frequency();//牌面数字统计, 生成dict
	friend class Pile;
	friend class choose;
	friend PlayerCard& operator+=(PlayerCard& left, const PlayerCard& right);//用于将底牌收入手牌
	friend PlayerCard& operator-=(PlayerCard& left, const choose& right);//出牌专用
	void AICard();//智能决定是否做地主
	void AICard(std::vector<int>&);//智能出牌, 自动模式时调用, 用于处理第一个出牌的情况(没有上家)
	void AICard(std::vector<int>&, PlayerCard& ch, int category);//智能出牌, 自动模式时调用, 用于处理有上家的情况
};

class HoleCards :public PlayerCard {
};

class choose :public PlayerCard {
	int PlayerNum;//玩家编号
	PlayerCard* Player;//玩家数据存储地址
	std::vector<int> index;//手牌位置

	std::vector<std::vector<int>> JudgeNorm;//用于判断牌型是否正确
	void getarray(std::vector<int> &);//读入index的函数

public:
	int Category;//牌型编号
	choose(int i, PlayerCard* Player, std::vector<std::vector<int>>& JudgeNorm):JudgeNorm(JudgeNorm) {
		PlayerNum = i; 
		this->Player = Player;
		for (int i = 3; i <= 17; i++) {

			if (i == 16)
				num = LJOKER;
			else
				if (i == 17)
					num = JOKER;
				else
					num = i;
			Key temp(num, 0);
			dict.push_back(temp);
		}
		num = index.size();
    }//默认输入量为玩家编号
    ~choose() {}
	choose(const choose& c);

    int choice(std::vector<int>& Humanindex, bool human);//读入下标, 确定要出的牌, 存在index中, 它调用了getarray
	int choice(std::vector<int>& AIindex);
	bool LegalJudge();//判断出牌选择的组合是否合法的函数, 该函数不比较大小, 只看牌面是否合法
	friend bool operator>(const choose& left, const choose& right);
	friend PlayerCard& operator-=(PlayerCard& left, choose& right);
	choose& operator=(const choose& ch) {
		if (&ch != this) {
            this->num=ch.num;
			this->PlayerNum = ch.PlayerNum;
			this->Player = ch.Player;
			this->index.clear();
			this->dict.clear();
            this->card.clear();
			this->EffectiveDict.clear();
			for (int i = 0; i < (int)ch.index.size(); i++)
				index.push_back(ch.index[i]);
			for (int i = 0; i < (int)ch.dict.size(); i++)
				dict.push_back(ch.dict[i]);
			for (int i = 0; i < (int)ch.EffectiveDict.size(); i++)
				EffectiveDict.push_back(ch.EffectiveDict[i]);
            for(int i=0;i<(int)ch.card.size();i++)
                card.push_back(ch.card[i]);
			JudgeNorm = ch.JudgeNorm;
			Category = ch.Category;
		}
		return *this;
	}
    void HumanPlayCardDelete(PlayerCard& Player, std::vector<int>& GoingtoPlayIndex){
        //由于人类出牌出现的不明问题,重写-=函数
        for(int j=(int)GoingtoPlayIndex.size()-1;j>=0;j--){
            Player.card.erase(Player.card.begin()+GoingtoPlayIndex[j]);
        }
        Player.Frequency();
        Player.num-=((int)GoingtoPlayIndex.size());
    }
	//friend bool operator<(const choose& left, const choose& right);
};

class Pile {
	int pack;//牌的副数
	Card* card; //对应卡牌
public:
	std::vector<int> perm; //通过下标排列记录当前排序
public:
	Pile(int pack = 2);
	void PrintPile();//输出按顺序排列的牌堆
	void PrintCurrentPile();//输出洗牌之后的牌堆
	void Shuffle();//洗牌
	void Allocation();//发牌函数
	void PrintPlayerCard();//控制台上使用的检查函数
	void PrintHoleCard();//控制台上使用的检查函数
	PlayerCard Player[4];//四名玩家
	HoleCards HoleCard;//底牌
}; //牌库

#endif //CARD_H
