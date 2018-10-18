#pragma once
#include "Lock.h"
#include "HashKeys.h"

#include <vector>
#include <fstream>

class MultiLock :
	public Lock
{
public:
	MultiLock(int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	~MultiLock();

	void GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF);

	bool checkMultiLock();

	void generateSafeFile(ofstream& myFile, string file, int solution);

	void printRoot();

	friend ostream& operator<<(ostream& ostr, const MultiLock& multiLock);

protected:
	int root[4];
	vector<Lock> locks;
};

