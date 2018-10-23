#pragma once

#include <vector>

#include "MultiLock.h"

using namespace std;

class HackerMan
{
public:
	HackerMan() {};
	HackerMan(vector<MultiLock> safes);
	HackerMan(vector<int> val, vector<int> vals);
	HackerMan(vector<int> val, vector<int> valsCN, vector<int> valsLN, vector<int> valsHN);
	~HackerMan() {};

	void addRoot(vector<int> val) { root[0] = val[0];  root[1] = val[1]; root[2] = val[2]; root[3] = val[3]; }

	void addCNVals(vector<int> vals) { for (int i = 0; i < (int)vals.size(); i++) { CN.push_back(vals[i]); } };
	void addLNVals(vector<int> vals) { for (int i = 0; i < (int)vals.size(); i++) { LN.push_back(vals[i]); } };
	void addHNVals(vector<int> vals) { for (int i = 0; i < (int)vals.size(); i++) { HN.push_back(vals[i]); } };

	void magic();

	void findUHF();
	void findLHF();
	void findPHF();

private:

	int root[4];
	int UHF[4] = { -9,-9,-9,-9 };
	int LHF[4] = { 0,0,0,0 };
	int PHF[4] = { 0,0,0,0 };
	vector<int> CN, LN, HN;

	void fixVals(int& val);

};

