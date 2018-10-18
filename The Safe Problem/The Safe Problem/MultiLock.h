#pragma once
#include "Lock.h"
#include "HashKeys.h"

#include <vector>

class MultiLock :
	public Lock
{
public:
	MultiLock(int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	~MultiLock();

	void GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF);

	bool checkMultiLock();

	void printRoot();

	friend ostream& operator<<(ostream& ostr, const MultiLock& multiLock);

protected:
	int root[4];
	vector<Lock> locks;
};

