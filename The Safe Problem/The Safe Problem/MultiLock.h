#pragma once
#include "Lock.h"
#include "HashKeys.h"

#include <vector>
#include <fstream>

class MultiLock
{
public:
	MultiLock() {};
	MultiLock(int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	~MultiLock();

	void GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF);

	bool checkMultiLock();
	bool checkBONUSMultiLock();

	void printRoot();

	friend ostream& operator<<(ostream& ostr, const MultiLock& multiLock);

protected:
	Lock locks[5];
	int root[4];
};

