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

	void hack();
	void crackUHF();
	void crackLHF();
	void crackPHF();

	int* getUHF() { return UHF; }
	int* getLHF() { return LHF; }
	int* getPHF() { return PHF; }
	int getSize() const { return size; }

	MultiLock getLockedSafe(int i) { return lockedSafes[i]; }

	void populateHackerMan(MultiLock safe);
	void populateSolutions(MultiLock safe);
	
private:
	vector<MultiLock> lockedSafes, unlockedSafes;
	int size;
	int root[4];
	int UHF[4] = { 0,0,0,0 };
	int LHF[4] = { 0,0,0,0 };
	int PHF[4] = { 0,0,0,0 };
	vector<int> CN, LN, HN;
	vector<int> CN_sol, LN_sol, HN_sol;

	void fixVals(int& val);
	void incIter(int* iter);
	bool cracked(int* x, int* y);
};

