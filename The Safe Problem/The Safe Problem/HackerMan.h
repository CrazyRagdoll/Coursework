#pragma once

#include <vector>

#include "MultiLock.h"

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

	void populateHackerMan(MultiLock safe);
	void populateSolutions(MultiLock safe);
	
private:
	vector<MultiLock> lockedSafes, unlockedSafes;
	int root[4];
	int UHF[4] = { 0,0,0,0 };
	int LHF[4] = { 0,0,0,0 };
	int PHF[4] = { 0,0,0,0 };
	vector<int> CN, LN, HN;
	vector<int> CN_sol, LN_sol, HN_sol;

	void fixVals(int& val);
	void incIter(int* iter);
};

