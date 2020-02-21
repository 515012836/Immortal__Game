#include "Immortal.h"
#include <ctime>

#define MARK_UP 0.05

Immortal::Immortal(string name, string school, ImmortalLevel level){
	this->name = name;
	this->school = school;
	this->level = level;
	this->state = true;
}

void Immortal::Mining(){
	stones.push_back( SpiritStones(100, SpiritStonesRank::LOW_RANK));
}

bool Immortal::Capture(const Monster& monster) {
	if (Getpower() > monster.GetPower()) {
		monsters.push_back(monster);
		return true;
	}
	else if(Getpower()<monster.GetPower()){
		Die();
		return false;
	}
}

bool Immortal::Trade(){
	if (!state) {
		return false;
	}
	SpiritStones sun;
	for (int i = 0; i < monsters.size(); ++i) {
		sun = sun + monsters[i].getValue();
	}
	//计算灵石资产总量
	stones.push_back(sun);
	//把妖兽资产清空
	monsters.erase(monsters.begin(), monsters.end());
	return true;
}

bool Immortal::Trade(const Monster& monster){
	if (!state) {
		return false;
	}
	if (!HaveMonster(monster)) {
		cout << name << "没有" << monster;
		return false;
	}
	SpiritStones stone = monster.getValue();
	stones.push_back(stone);
	RemoveMonster(monster);

	return true;
}

bool Immortal::Trade(Immortal& other, const Monster& monster){
	if (state == false || other.state == false) {
		return false;
	}
	if (!other.HaveMonster(monster)) {
		cout << "[修仙者]:" << other.name << "没有" << monster;
		return false;
	}
	//计算灵石总量是否可以购买妖兽
	SpiritStones sun;
	for (int i = 0; i < stones.size(); i++) {
		sun = sun + stones[i];
	}
	if (sun >= monster.getValue()) {
		sun = sun - monster.getValue();
		stones.clear();//先清空原来的灵石
		stones.push_back(sun);//剩下的灵石
		monsters.push_back(monster);//买到的妖兽
		other.RemoveMonster(monster);//卖家减掉妖兽
		other.stones.push_back(monster.getValue());//卖家获取灵石
		return true;
	}
	else {
		cout << name << "灵石不够,买不起" << monster << endl;
		return false;
	}

}

bool Immortal::Trade(const Monster& monster1, Immortal& other, const Monster& monster2){
	if (!state || !other.state) {
		return false;
	}
	if (monster1==monster2 || !HaveMonster(monster1) || !other.HaveMonster(monster2)) {
		cout << name << "没有" << monster1 << "或者" << other.name << "没有" << monster2;
		return false;
	}
	//交换妖兽
	RemoveMonster(monster1);
	other.monsters.push_back(monster1);
	other.RemoveMonster(monster2);
	monsters.push_back(monster2);

	return true;
}

bool Immortal::Trade(const Monster& monster, Immortal& other){
	if (state == false || other.state == false) {
		return false;
	}
	if (!HaveMonster(monster)) {
		cout << "[修仙者]:" << name << "没有" << monster << endl;
		return false;
	}
	//计算灵石总量是否可以购买妖兽
	SpiritStones sun;
	for (int i = 0; i <other.stones.size(); i++) {
		sun = sun + other.stones[i];
	}
	if (!(sun >= monster.getValue())) {
		cout << other.name << "钱不够买" << monster << endl;
		return false;
	}
	other.stones.clear();
	other.stones.push_back(sun - monster.getValue());
	other.monsters.push_back(monster);
	RemoveMonster(monster);
	stones.push_back(monster.getValue());
	return true;
}

int Immortal::Getpower() const{
	//自身等级的战斗力
	int ret = ((int)level) * COMBAT_PRICE;
	//灵石加成战斗力
	SpiritStones stone;
	for (int i = 0; i < stones.size(); i++) {
		stone = stone + stones[i];
	}
	ret += stone.GetCount() * MARK_UP;
	//妖兽加成战斗力
	for (int k = 0; k < monsters.size(); ++k) {
		ret += monsters[k].GetPower() * MARK_UP;
	}
	return ret;//返回综合战斗力
}

void Immortal::Die(){
	state = false;
	stones.erase(stones.begin(), stones.end());
	monsters.erase(monsters.begin(), monsters.end());
}

bool Immortal::operator>(Immortal& other){
	return this->Getpower() > other.Getpower();
}

bool Immortal::operator<(Immortal& other){
	return Getpower() < other.Getpower();
}

bool Immortal::Close(){
	if (!state) {
		return false;
	}
	int power = Getpower();
	//用随机值判断是否成功
	srand((int)time(NULL));
	int number = rand() %3;
	if (number==1){
		cout << name << "闭关成功" << endl;
		level = (ImmortalLevel)((int)level+1);
	}
	else {
		cout << name << "闭关失败" << endl;
		level = (ImmortalLevel)((int)level -1);
	}
}

bool Immortal::HaveMonster(const Monster& monster){
	for (int i = 0; i < monsters.size(); i++) {
		if (monster == monsters[i]) {
			return true;
		}
		else {
			return false;
		}
	}
}

bool Immortal::RemoveMonster(const Monster& monster){
	for (vector<Monster>::iterator it = monsters.begin(); it != monsters.end();) {
		if (*it == monster) {
			it=monsters.erase(it);
			return true;
		}
		else {
			it++;
		}
	}
	return false;
}

ostream& operator<<(ostream& os, Immortal& immortal){
	os << "[修仙者]名字:" << immortal.name << "; 门派:" << immortal.school
		<< "; 状态:" << (immortal.state ? "生存" : "死亡")
		<< "; 等级:" << immortal.level
		<< ";战斗力" << immortal.Getpower();
	//灵石总资产计算
	SpiritStones sun;
	for (int i = 0; i < immortal.stones.size(); ++i) {
		sun = sun + immortal.stones[i];
	}
	os << "; 灵石总量:" << sun;
	//计算妖兽资产
	os << "; 妖兽:";
	if (!immortal.monsters.size()) {
		os << "无";
	}
	else {
		for (int n = 0; n < immortal.monsters.size(); n++) {
			os << immortal.monsters[n] << "; ";
		}
	}
	return os;
}

ostream& operator<<(ostream& os, ImmortalLevel& level){
	switch (level) {
	case ImmortalLevel::LIAN_QI:
		os << "练气期";
		break;
	case ImmortalLevel::ZHU_JI:
		os << "筑基期";
		break;
	case ImmortalLevel::JIE_DAN:
		os << "结丹期";
		break;
	case ImmortalLevel::YUAN_YING:
		os << "元婴期";
		break;
	case ImmortalLevel::HUA_SHEN:
		os << "化神期";
		break;
	case ImmortalLevel::LIAN_XU:
		os << "练虚期";
		break;
	case ImmortalLevel::HE_TI:
		os << "合体期";
		break;
	case ImmortalLevel::DA_CHENG:
		os << "大乘期";
		break;
	case ImmortalLevel::DU_JIE:
		os << "渡劫期";
		break;
	default:
		os << "未知等级";
		break;
	}
	return os;
}

bool PK(Immortal& one, Immortal& two){
	if (!one.state || !two.state) {
		return false;
	}
	if (one.Getpower() > two.Getpower()) {
		cout << one.name << "\t胜利" << endl;
		two.state = false;
		return true;
	}
	else {
		cout << one.name << "\t失败" << endl;
		one.state = false;
		return false;
	}
}

bool PK1(Immortal& one, Immortal& two){
	SpiritStones sun1, sun2;
	if (!one.state || !two.state) {
		return false;
	}
	//计算one的资产,
	for (int i = 0; i < one.stones.size(); ++i) {
		sun1 = sun1 + one.stones[i];
	}
	//计算two的资产,
	for (int i = 0; i < two.stones.size(); ++i) {
		sun2 = sun2 + two.stones[i];
	}
	if (one.Getpower() > two.Getpower()) {
		cout << one.name << "胜利,获得" << two.name << "的所有资产" << endl;
		one.stones.push_back(sun2);
		//获取妖兽资产
		for (int i = 0; i < two.monsters.size(); i++) {
			one.monsters.push_back(two.monsters[i]);
		}
		two.Die();
		return true;
	}
	else {
		cout << two.name << "胜利,获得" << one.name << "的所有资产" << endl;
		two.stones.push_back(sun1);
		//获取妖兽资产
		for (int i = 0; i < one.monsters.size(); i++) {
			two.monsters.push_back(two.monsters[i]);
		}
		one.Die();
		return true;
	}
	return false;
}
