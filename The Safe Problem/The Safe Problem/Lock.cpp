#include "stdafx.h"
#include "Lock.h"


Lock::Lock(int hNumber) :
	HN(hNumber),
	CN(0),
	LN(0)
{
}


Lock::~Lock()
{
}

void Lock::setNumber(char num, int val) {
	switch (num) {
	case 'C': CN = val;  break;
	case 'L': LN = val;  break;
	default: break;
	}
}

int Lock::getNumber(char num) {
	switch (num){
	case 'C': return CN;  break;
	case 'L': return LN;  break;
	case 'H': return HN;  break;
	default: return 0;
	}	
}

//Return true if OK
bool Lock::checkCN() {
	int a, b, c, d;
	a = (CN / 1000) % 10;
	b = (CN / 100) % 10;
	c = (CN / 10) % 10;
	d = (CN / 1) % 10;

	return (a != b && a != c && a != d && b != c && b != d && c != d);

}

bool Lock::checkLN() {
	return (LN != CN);
}