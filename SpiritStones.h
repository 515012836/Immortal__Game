#pragma once
#include <iostream>
#include <sstream>
#include <fstream>

using namespace std;

//C++11��׼��ö�ٶ���:
enum class SpiritStonesRank {
	LOW_RANK,//����
	SECONDARY_RANK,//�м�
	EXPERT_RANK,//�߼�
	ALL_RANK//�����Ժ���ѭ��ʹ�õ���
};

//��ʯ��
class SpiritStones{
public:
	SpiritStones(int count = 0, SpiritStonesRank rank = SpiritStonesRank::LOW_RANK);
	~SpiritStones(){}
	int GetCount();
	//������ʯ����
	string str()const;
	//��ʯ���:
	SpiritStones operator+(const SpiritStones& stone);
	//��ʯ���
	SpiritStones operator-(const SpiritStones& stone);
	//��ʯ�Ƚ�
	bool operator>=(const SpiritStones& stone);
	//��ӡ�����
	friend ostream& operator<<(ostream& os, SpiritStones& stones);

private:
	int count;//����:��λ��
	SpiritStonesRank rank;//��ʯ�ȼ�
};

