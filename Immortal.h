#pragma once
#include "Monster.h"
#include "SpiritStones.h"
#include <vector>

enum class ImmortalLevel {
	LIAN_QI,//练气期
	ZHU_JI,//筑基期
	JIE_DAN,//结丹期
	YUAN_YING,//元婴期
	HUA_SHEN,//化神期
	LIAN_XU,//练虚期
	HE_TI,//合体期
	DA_CHENG,//大乘期
	DU_JIE,//渡劫期
	ALL_LEVEL//全部等级
};

//修仙者类
class Immortal{
public:
	Immortal(string name, string school, ImmortalLevel level = ImmortalLevel::LIAN_QI);

	//采矿
	void Mining();
	//捕获妖兽
	bool Capture(const Monster& monster);
	//到市场售卖所有妖兽
	bool Trade();
	//到市场售卖指定妖兽
	bool Trade(const Monster& monster);
	//用自己的灵石购买其他修仙者的妖兽
	bool Trade(Immortal& other, const Monster& monster);
	//用自己的妖兽换取其他修仙者的妖兽
	bool Trade(const Monster& monster1, Immortal& other, const Monster& monster2);
	//把自己的妖兽买给其他修仙者换取灵石
	bool Trade(const Monster& monster, Immortal& other);
	//PK函数
	int Getpower()const;
	//修仙者死亡后的处理函数
	void Die();
	//打印这个类的函数(当重载运算符一样的时候,类内作为友元的只放一个就可以了)
	friend ostream& operator<<(ostream& os,Immortal& immortal);
	//修仙者之间比武
	bool operator>(Immortal& other);
	bool operator<(Immortal& other);
	//普通PK
	friend bool PK(Immortal& one, Immortal& two);
	//生死决斗
	friend bool PK1(Immortal& one, Immortal& two);
	//闭关修炼
	bool Close();
	//等级上升
	ImmortalLevel operator+(ImmortalLevel& level);


private:
	string name;//名字
	string school;//门派
	ImmortalLevel level;//等级
	vector<SpiritStones>stones;//灵石资产
	vector<Monster>monsters;//妖兽资产
	bool state;//状态

	//判断是否有指定的妖兽
	bool HaveMonster(const Monster&monster);
	//移除指定的妖兽
	bool RemoveMonster(const Monster& monster);
};
//打印等级的函数
ostream& operator<<(ostream& os,ImmortalLevel& level);
bool PK(Immortal& one, Immortal& two);
bool PK1(Immortal& one, Immortal& two);
