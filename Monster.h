#pragma once
#include "SpiritStones.h"
#include <sstream>

#define COMBAT_PRICE 1000 //战斗力

enum class MonsterLevel {
	ONE,
	TWO,
	THREE,
	FOUR,
	FIVE,
	SIX,
	SEVER,
	EIGHT,
	NINE,
	ALL_LEVEL
};

//妖兽类
class Monster{
public:
	Monster(int level = 1, string kind = "未知");
	string str()const;
	//妖兽换灵石函数
	SpiritStones getValue()const;
	//获取妖兽的战斗力
	int GetPower()const;
	//比较妖兽是否存在
	bool operator==(const Monster&other)const;
	//打印妖兽函数
	friend ostream& operator<<(ostream& os,const Monster& monster);

private:
	string kind;//种类
	int level;//等级1-9级
};