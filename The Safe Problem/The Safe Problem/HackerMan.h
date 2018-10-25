#pragma once
#include "MultiLock.h"

#include <vector>

using namespace std;

class HackerMan
{
public:
	HackerMan() {};
	HackerMan(vector<MultiLock> lSafes);
	HackerMan(vector<MultiLock> lSafes, vector<MultiLock> uSafes);
	~HackerMan() {};

	HashKeys getUHF(int i) { return UHF[i]; }
	HashKeys getLHF(int i) { return LHF[i]; }
	HashKeys getPHF(int i) { return PHF[i]; }
	int getSize() const { return size; }

	MultiLock getLockedSafe(int i) { return lockedSafes[i]; }
	
private:
	vector<MultiLock> lockedSafes, unlockedSafes;
	int size;
	int root[4];

	vector<HashKeys> UHF, LHF, PHF;
	vector<int> CN, LN, HN;
	vector<int> CN_sol, LN_sol, HN_sol;

	void fixVals(int& val);
	void incIter(int* iter);
	bool cracked(int* x, int* y);

	void populateHackerMan(MultiLock safe);
	void populateSolutions(MultiLock safe);

	void hack();
	void crackUHF(int safe);
	void crackLHF(int safe);
	void crackPHF(int safe);

	void cinematicHack();
	void sleep(int i);

};

