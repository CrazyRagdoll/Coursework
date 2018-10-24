#include "stdafx.h"
#include "Lock.h"

//Return true if OK
bool Lock::checkLock() {
	if (CN[0] == CN[1] || CN[0] == CN[2] || CN[0] == CN[3] || CN[1] == CN[2] || CN[1] == CN[3] || CN[2] == CN[3]) {
		return false;
	}
	else return true;
}

//BONUS MULTI_SAFE left lock must be less than right lock
//Return true if lock is OK
bool Lock::checkNextLock(const Lock& nextLock) {
	int x = 0, y = 0;
	for (int i = 0; i < 4; i++) {
		x += this->CN[i]; 
		y += nextLock.CN[i];
	}
	return x < y;
}

//Return true if all locks add up to an even number
bool Lock::isEven() {
	int x = 0, y = 0, z = 0;
	for (int i = 0; i < 4; i++)
	{
		x += this->CN[i];
		y += this->LN[i];
		z += this->HN[i];
	}
	return ((x+y+z) % 2 ) == 0;
}

ostream& operator<<(ostream& ostr, const Lock& lock) {
	ostr << "CN" << lock.id << " " << lock.CN[0] << lock.CN[1] << lock.CN[2] << lock.CN[3]
		<< ", LN" << lock.id << " " << lock.LN[0] << lock.LN[1] << lock.LN[2] << lock.LN[3]
		<< ", HN" << lock.id << " " << lock.HN[0] << lock.HN[1] << lock.HN[2] << lock.HN[3];

	return ostr;
}