#include "Monster.h"

Monster::Monster(int level, string kind){
	this->level = level;
	this->kind = kind;
}

string Monster::str()const{
	stringstream ret;
	ret << level << "��" << kind << "����";
	return ret.str();
}

SpiritStones Monster::getValue()const{
	//���������Ǯ
	int count[] = {100,200,500,1000,2000,5000,10000,20000,100000 };
	//���ݵȼ���ȡ��ʯ
	int sun = count[level-1];
	return SpiritStones(sun,SpiritStonesRank::LOW_RANK);
}

int Monster::GetPower() const{
	return level * COMBAT_PRICE;
}

bool Monster::operator==(const Monster& other)const{
	if ((this->kind == other.kind)&&(this->level==other.level)) {
		return true;
	}
	else {
		return false;
	}
}

ostream& operator<<(ostream& os,const Monster& monster) {
	os << monster.str();
	return os;
}
