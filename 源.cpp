#include "SpiritStones.h"
#include "Monster.h"
#include "Immortal.h"

void testImmortal() {
	Immortal LH("恒少", "贱人派",ImmortalLevel::DA_CHENG);
	Immortal XY("星爷", "斧头帮", ImmortalLevel::DA_CHENG);
	Monster T1(1, "青龙");
	Monster T2(1, "白虎");
	cout << LH << endl;
	cout << XY << endl;
	LH.Close();
	cout << LH << endl;
	cout << "***************生死PK开始************\n" << endl;
	PK1(LH, XY);
	cout << LH << endl;
	cout << XY << endl;
}

void testSpiritStones() {
	SpiritStones stones(50, SpiritStonesRank::LOW_RANK);
	cout << stones << endl;
}

void testMonster() {
	Monster monster(6, "白虎");
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