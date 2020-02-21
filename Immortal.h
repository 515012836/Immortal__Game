#pragma once
#include "Monster.h"
#include "SpiritStones.h"
#include <vector>

enum class ImmortalLevel {
	LIAN_QI,//������
	ZHU_JI,//������
	JIE_DAN,//�ᵤ��
	YUAN_YING,//ԪӤ��
	HUA_SHEN,//������
	LIAN_XU,//������
	HE_TI,//������
	DA_CHENG,//�����
	DU_JIE,//�ɽ���
	ALL_LEVEL//ȫ���ȼ�
};

//��������
class Immortal{
public:
	Immortal(string name, string school, ImmortalLevel level = ImmortalLevel::LIAN_QI);

	//�ɿ�
	void Mining();
	//��������
	bool Capture(const Monster& monster);
	//���г�������������
	bool Trade();
	//���г�����ָ������
	bool Trade(const Monster& monster);
	//���Լ�����ʯ�������������ߵ�����
	bool Trade(Immortal& other, const Monster& monster);
	//���Լ������޻�ȡ���������ߵ�����
	bool Trade(const Monster& monster1, Immortal& other, const Monster& monster2);
	//���Լ�������������������߻�ȡ��ʯ
	bool Trade(const Monster& monster, Immortal& other);
	//PK����
	int Getpower()const;
	//������������Ĵ�����
	void Die();
	//��ӡ�����ĺ���(�����������һ����ʱ��,������Ϊ��Ԫ��ֻ��һ���Ϳ�����)
	friend ostream& operator<<(ostream& os,Immortal& immortal);
	//������֮�����
	bool operator>(Immortal& other);
	bool operator<(Immortal& other);
	//��ͨPK
	friend bool PK(Immortal& one, Immortal& two);
	//��������
	friend bool PK1(Immortal& one, Immortal& two);
	//�չ�����
	bool Close();
	//�ȼ�����
	ImmortalLevel operator+(ImmortalLevel& level);


private:
	string name;//����
	string school;//����
	ImmortalLevel level;//�ȼ�
	vector<SpiritStones>stones;//��ʯ�ʲ�
	vector<Monster>monsters;//�����ʲ�
	bool state;//״̬

	//�ж��Ƿ���ָ��������
	bool HaveMonster(const Monster&monster);
	//�Ƴ�ָ��������
	bool RemoveMonster(const Monster& monster);
};
//��ӡ�ȼ��ĺ���
ostream& operator<<(ostream& os,ImmortalLevel& level);
bool PK(Immortal& one, Immortal& two);
bool PK1(Immortal& one, Immortal& two);
