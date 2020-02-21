#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//C++11标准的枚举定义:
enum class SpiritStonesRank {
	LOW_RANK,//初级
	SECONDARY_RANK,//中级
	EXPERT_RANK,//高级
	ALL_RANK//方便以后做循环使用的量
};

//灵石类
class SpiritStones{
public:
	SpiritStones(int count = 0, SpiritStonesRank rank = SpiritStonesRank::LOW_RANK);
	~SpiritStones(){}
	int GetCount();
	//输入灵石数据
	string str()const;
	//灵石相加:
	SpiritStones operator+(const SpiritStones& stone);
	//灵石相减
	SpiritStones operator-(const SpiritStones& stone);
	//灵石比较
	bool operator>=(const SpiritStones& stone);
	//打印这个类
	friend ostream& operator<<(ostream& os, SpiritStones& stones);

private:
	int count;//数量:单位块
	SpiritStonesRank rank;//灵石等级
};

