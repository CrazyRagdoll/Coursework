#include "stdafx.h"
#include "MultiLock.h"

#include <iostream>

MultiLock::MultiLock() : size(0){

}

MultiLock::MultiLock(int* newRoot, HashKeys UHF, HashKeys LHF, HashKeys PHF) :size(5) {
	setRoot(newRoot);

	GenerateMultiLock(UHF, LHF, PHF);
}

MultiLock::MultiLock(int* newRoot, HashKeys UHF, HashKeys LHF, HashKeys PHF, int size) : size(size) {
	setRoot(newRoot);

	GenerateMultiLock(UHF, LHF, PHF);
}

void MultiLock::GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	Lock tmp(0);
	int val[4];
	UHF.hashKey(root, val);
	tmp.setCN(val);
	LHF.hashKey(tmp.getCN(), val);
	tmp.setLN(val);
	PHF.hashKey(tmp.getLN(), val);
	tmp.setHN(val);
	locks.push_back(tmp);

	for (int i = 1; i < size; i++) {
		tmp = Lock(i);
		UHF.hashKey(locks[i - 1].getHN(), val);
		tmp.setCN(val);
		LHF.hashKey(tmp.getCN(), val);
		tmp.setLN(val);
		PHF.hashKey(tmp.getLN(), val);
		tmp.setHN(val);
		locks.push_back(tmp);
	}
}

bool MultiLock::checkMultiLock() {
	for (int i = 0; i < size; i++) {
		if (locks[i].checkLock() == false) return false;
	}
	return true;
}

//BONUS POINTS
bool MultiLock::checkBONUSMultiLock() {
	for (int i = 0; i < size; i++) {
		if (locks[i].checkLock() == false) return false;
	}
	//BONUS MULTI SAFE
	for (int i = 0; i < size-1; i++) {
		if (locks[i].checkNextLock(locks[i+1]) == false) return false;
	}
	//BONUS MULTI SAFE
	for (int i = 0; i < size; i++) {
		if (locks[i].isEven() == false) return false;
	}
	return true;
}

ostream& operator<<(ostream& ostr, const MultiLock& multiLock){
	for (int i = 0; i < multiLock.getSize(); i++) {
		ostr << multiLock.locks[i] << "\n";
	}
	return ostr;
}