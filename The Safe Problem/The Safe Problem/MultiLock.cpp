#include "stdafx.h"
#include "MultiLock.h"

#include <iostream>

MultiLock::MultiLock(int* newRoot, HashKeys UHF, HashKeys LHF, HashKeys PHF)
{
	root[0] = newRoot[0];
	root[1] = newRoot[1];
	root[2] = newRoot[2];
	root[3] = newRoot[3];

	GenerateMultiLock(UHF, LHF, PHF);
}


MultiLock::~MultiLock()
{
}


void MultiLock::GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	locks.push_back(0);
	locks[0].setCN(UHF.hashKey(root));
	locks[0].setLN(LHF.hashKey(locks[0].getCN()));
	locks[0].setHN(PHF.hashKey(locks[0].getLN()));

	for (int i = 1; i < 5; i++) {
		locks.push_back(Lock(i));
		locks[i].setCN(UHF.hashKey(locks[i - 1].getHN()));
		locks[i].setLN(LHF.hashKey(locks[i].getCN()));
		locks[i].setHN(PHF.hashKey(locks[i].getLN()));
	}
}

bool MultiLock::checkMultiLock() {
	for (int i = 0; i < 5; i++) {
		if (locks[i].checkLock() == false) return false;
	}
	return true;
}

void MultiLock::printRoot() {
	cout << root[0] << root[1] << root[2] << root[3] << endl;
}

ostream& operator<<(ostream& ostr, const MultiLock& multiLock){
	for (int i = 0; i < 5; i++) {
		ostr << multiLock.locks[i] << std::endl;
	}
	return ostr;
}