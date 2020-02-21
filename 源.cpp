#include "SpiritStones.h"
#include "Monster.h"
#include "Immortal.h"

void testImmortal() {
	Immortal LH("����", "������",ImmortalLevel::DA_CHENG);
	Immortal XY("��ү", "��ͷ��", ImmortalLevel::DA_CHENG);
	Monster T1(1, "����");
	Monster T2(1, "�׻�");
	cout << LH << endl;
	cout << XY << endl;
	LH.Close();
	cout << LH << endl;
	cout << "***************����PK��ʼ************\n" << endl;
	PK1(LH, XY);
	cout << LH << endl;
	cout << XY << endl;
}

void testSpiritStones() {
	SpiritStones stones(50, SpiritStonesRank::LOW_RANK);
	cout << stones << endl;
}

void testMonster() {
	Monster monster(6, "�׻�");
	cout << monster << endl;
}

int main(void) {
	testSpiritStones();
	cout << endl;
	testMonster();
	cout << endl;
	testImmortal();

	system("pause");
	return 0;
}