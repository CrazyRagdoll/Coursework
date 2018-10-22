#pragma once

#include <ostream>

using namespace std;

class Lock
{
public:
	Lock() : id(0) {}
	Lock(int id) : id(id) { }
	~Lock();

	void setCN(int val[]) { CN[0] = val[0]; CN[1] = val[1]; CN[2] = val[2]; CN[3] = val[3]; }
	void setLN(int val[]) { LN[0] = val[0]; LN[1] = val[1]; LN[2] = val[2]; LN[3] = val[3]; }
	void setHN(int val[]) { HN[0] = val[0]; HN[1] = val[1]; HN[2] = val[2]; HN[3] = val[3]; }

	int* getCN() { return CN; }
	int* getLN() { return LN; }
	int* getHN() { return HN; }

	bool checkLock();
	bool checkNextLock(const Lock& rhs);
	bool isEven();

	friend ostream& operator<<(ostream& ostr, const Lock& lock);

protected:
	int CN[4];
	int LN[4];
	int HN[4];	
	int id;
};

