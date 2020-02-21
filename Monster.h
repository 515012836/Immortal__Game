#pragma once
#include "SpiritStones.h"
#include <sstream>

#define COMBAT_PRICE 1000 //ս����

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

//������
class Monster{
public:
	Monster(int level = 1, string kind = "δ֪");
	string str()const;
	//���޻���ʯ����
	SpiritStones getValue()const;
	//��ȡ���޵�ս����
	int GetPower()const;
	//�Ƚ������Ƿ����
	bool operator==(const Monster&other)const;
	//��ӡ���޺���
	friend ostream& operator<<(ostream& os,const Monster& monster);

private:
	string kind;//����
	int level;//�ȼ�1-9��
};