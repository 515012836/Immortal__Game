#include "SpiritStones.h"

SpiritStones::SpiritStones(int count, SpiritStonesRank rank) {
	this->count = count;
	this->rank = rank;
}

int SpiritStones::GetCount(){
	return count;
}

string SpiritStones::str()const{
	stringstream ret;
	cout << count << "��";
	switch (rank){
	case SpiritStonesRank::LOW_RANK:
		ret << "������ʯ";
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		ret << "�м���ʯ";
		break;
	case SpiritStonesRank::EXPERT_RANK:
		ret << "�߼���ʯ";
		break;
	default:
		ret << "δ֪�ȼ�";
		break;
	}

	return ret.str();
}

//��ʯ��Ӻ���
SpiritStones SpiritStones::operator+(const SpiritStones& stone){
	int sun = 0;
	switch (stone.rank) {
	case SpiritStonesRank::LOW_RANK:
		sun += stone.count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun += stone.count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun += stone.count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	switch (rank) {
	case SpiritStonesRank::LOW_RANK:
		sun += count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun += count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun += count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	return SpiritStones(sun, SpiritStonesRank::LOW_RANK);
}

SpiritStones SpiritStones::operator-(const SpiritStones& stone){
	int sun = 0;
	switch (stone.rank) {
	case SpiritStonesRank::LOW_RANK:
		sun = stone.count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun = stone.count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun = stone.count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	int sun2 = 0;
	switch (rank) {
	case SpiritStonesRank::LOW_RANK:
		sun2 = count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun2 = count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun2 = count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	return SpiritStones(sun2-sun, SpiritStonesRank::LOW_RANK);
}

bool SpiritStones::operator>=(const SpiritStones& stone){
	int sun = 0;
	switch (stone.rank) {
	case SpiritStonesRank::LOW_RANK:
		sun = stone.count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun = stone.count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun = stone.count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	int sun2 = 0;
	switch (rank) {
	case SpiritStonesRank::LOW_RANK:
		sun2 = count;
		break;
	case SpiritStonesRank::SECONDARY_RANK:
		sun2 = count * 10;
		break;
	case SpiritStonesRank::EXPERT_RANK:
		sun2 = count * 100;
		break;
	default:
		cout << "δ֪�ȼ�!\n";
		break;
	}
	return sun2 >= sun;
}

ostream& operator<<(ostream& os, SpiritStones& stones) {
	os << stones.str();
	return os;
}
