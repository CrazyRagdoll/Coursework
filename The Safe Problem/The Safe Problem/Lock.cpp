#include "stdafx.h"
#include "Lock.h"

Lock::~Lock()
{
}

//Return true if OK
bool Lock::checkCN() {
	int a, b, c, d;
	a = CN[0];
	b = CN[1];
	c = CN[2];
	d = CN[3];

	return (a != b && a != c && a != d && b != c && b != d && c != d);
}

bool Lock::checkLN() {
	return (LN != CN);
}

ostream& operator<<(ostream& ostr, const Lock& lock) {
	ostr << "CN" << lock.id << " " << lock.CN[0] << lock.CN[1] << lock.CN[2] << lock.CN[3]
		<< ", LN" << lock.id << " " << lock.LN[0] << lock.LN[1] << lock.LN[2] << lock.LN[3]
		<< ", HN" << lock.id << " " << lock.HN[0] << lock.HN[1] << lock.HN[2] << lock.HN[3];

	return ostr;
}