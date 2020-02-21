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
	//������ʯ�ʲ�����
	stones.push_back(sun);
	//�������ʲ����
	monsters.erase(monsters.begin(), monsters.end());
	return true;
}

bool Immortal::Trade(const Monster& monster){
	if (!state) {
		return false;
	}
	if (!HaveMonster(monster)) {
		cout << name << "û��" << monster;
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
		cout << "[������]:" << other.name << "û��" << monster;
		return false;
	}
	//������ʯ�����Ƿ���Թ�������
	SpiritStones sun;
	for (int i = 0; i < stones.size(); i++) {
		sun = sun + stones[i];
	}
	if (sun >= monster.getValue()) {
		sun = sun - monster.getValue();
		stones.clear();//�����ԭ������ʯ
		stones.push_back(sun);//ʣ�µ���ʯ
		monsters.push_back(monster);//�򵽵�����
		other.RemoveMonster(monster);//���Ҽ�������
		other.stones.push_back(monster.getValue());//���һ�ȡ��ʯ
		return true;
	}
	else {
		cout << name << "��ʯ����,����" << monster << endl;
		return false;
	}

}

bool Immortal::Trade(const Monster& monster1, Immortal& other, const Monster& monster2){
	if (!state || !other.state) {
		return false;
	}
	if (monster1==monster2 || !HaveMonster(monster1) || !other.HaveMonster(monster2)) {
		cout << name << "û��" << monster1 << "����" << other.name << "û��" << monster2;
		return false;
	}
	//��������
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
		cout << "[������]:" << name << "û��" << monster << endl;
		return false;
	}
	//������ʯ�����Ƿ���Թ�������
	SpiritStones sun;
	for (int i = 0; i <other.stones.size(); i++) {
		sun = sun + other.stones[i];
	}
	if (!(sun >= monster.getValue())) {
		cout << other.name << "Ǯ������" << monster << endl;
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
	//����ȼ���ս����
	int ret = ((int)level) * COMBAT_PRICE;
	//��ʯ�ӳ�ս����
	SpiritStones stone;
	for (int i = 0; i < stones.size(); i++) {
		stone = stone + stones[i];
	}
	ret += stone.GetCount() * MARK_UP;
	//���޼ӳ�ս����
	for (int k = 0; k < monsters.size(); ++k) {
		ret += monsters[k].GetPower() * MARK_UP;
	}
	return ret;//�����ۺ�ս����
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
	//�����ֵ�ж��Ƿ�ɹ�
	srand((int)time(NULL));
	int number = rand() %3;
	if (number==1){
		cout << name << "�չسɹ�" << endl;
		level = (ImmortalLevel)((int)level+1);
	}
	else {
		cout << name << "�չ�ʧ��" << endl;
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
	os << "[������]����:" << immortal.name << "; ����:" << immortal.school
		<< "; ״̬:" << (immortal.state ? "����" : "����")
		<< "; �ȼ�:" << immortal.level
		<< ";ս����" << immortal.Getpower();
	//��ʯ���ʲ�����
	SpiritStones sun;
	for (int i = 0; i < immortal.stones.size(); ++i) {
		sun = sun + immortal.stones[i];
	}
	os << "; ��ʯ����:" << sun;
	//���������ʲ�
	os << "; ����:";
	if (!immortal.monsters.size()) {
		os << "��";
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
		os << "������";
		break;
	case ImmortalLevel::ZHU_JI:
		os << "������";
		break;
	case ImmortalLevel::JIE_DAN:
		os << "�ᵤ��";
		break;
	case ImmortalLevel::YUAN_YING:
		os << "ԪӤ��";
		break;
	case ImmortalLevel::HUA_SHEN:
		os << "������";
		break;
	case ImmortalLevel::LIAN_XU:
		os << "������";
		break;
	case ImmortalLevel::HE_TI:
		os << "������";
		break;
	case ImmortalLevel::DA_CHENG:
		os << "�����";
		break;
	case ImmortalLevel::DU_JIE:
		os << "�ɽ���";
		break;
	default:
		os << "δ֪�ȼ�";
		break;
	}
	return os;
}

bool PK(Immortal& one, Immortal& two){
	if (!one.state || !two.state) {
		return false;
	}
	if (one.Getpower() > two.Getpower()) {
		cout << one.name << "\tʤ��" << endl;
		two.state = false;
		return true;
	}
	else {
		cout << one.name << "\tʧ��" << endl;
		one.state = false;
		return false;
	}
}

bool PK1(Immortal& one, Immortal& two){
	SpiritStones sun1, sun2;
	if (!one.state || !two.state) {
		return false;
	}
	//����one���ʲ�,
	for (int i = 0; i < one.stones.size(); ++i) {
		sun1 = sun1 + one.stones[i];
	}
	//����two���ʲ�,
	for (int i = 0; i < two.stones.size(); ++i) {
		sun2 = sun2 + two.stones[i];
	}
	if (one.Getpower() > two.Getpower()) {
		cout << one.name << "ʤ��,���" << two.name << "�������ʲ�" << endl;
		one.stones.push_back(sun2);
		//��ȡ�����ʲ�
		for (int i = 0; i < two.monsters.size(); i++) {
			one.monsters.push_back(two.monsters[i]);
		}
		two.Die();
		return true;
	}
	else {
		cout << two.name << "ʤ��,���" << one.name << "�������ʲ�" << endl;
		two.stones.push_back(sun1);
		//��ȡ�����ʲ�
		for (int i = 0; i < one.monsters.size(); i++) {
			two.monsters.push_back(two.monsters[i]);
		}
		one.Die();
		return true;
	}
	return false;
}
