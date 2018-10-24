#pragma once
#include "Lock.h"
#include "HashKeys.h"

#include <vector>
#include <fstream>

class MultiLock
{
public:
	MultiLock();
	MultiLock(int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	MultiLock(int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF, int size);
	~MultiLock() {};

	void GenerateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF);

	bool checkMultiLock();
	bool checkBONUSMultiLock();

	int getSize() const { return size; }

	void addLock() { Lock lock(size); size++; locks.push_back(lock); }
	Lock* getLock(int i) { return &locks[i]; }

	void setRoot(int val[]) { root[0] = val[0]; root[1] = val[1]; root[2] = val[2]; root[3] = val[3]; }
	int* getRoot() { return root; }

	friend ostream& operator<<(ostream& ostr, const MultiLock& multiLock);

protected:
	vector<Lock> locks;
	int root[4]; 
	int size;
};

