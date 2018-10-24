#include "stdafx.h"
#include "HackerMan.h"

#include <iostream>

HackerMan::HackerMan(vector<MultiLock> lSafes) {
	for (int i = 0; i < (int)lSafes.size(); i++)
	{
		lockedSafes.push_back(lSafes[i]);
	}
}

HackerMan::HackerMan(vector<MultiLock> lSafes, vector<MultiLock> uSafes) : size((int)lSafes.size()){
	for (int i = 0; i < (int)lSafes.size(); i++)
	{
		lockedSafes.push_back(lSafes[i]);
		unlockedSafes.push_back(uSafes[i]);
	}
	hack();
}

void HackerMan::hack() {
	populateHackerMan(lockedSafes[0]);
	populateSolutions(unlockedSafes[0]);
	crackUHF();
	crackLHF();
	crackPHF();
}

void HackerMan::crackUHF() {
	int UL_HF[4] = { LN[0] - root[0], LN[1] - root[1], LN[2] - root[2], LN[3] - root[3] };
	for (int i = 0; i < 4; i++) fixVals(UL_HF[i]);

	int iter[4] = { 0,0,0,0 };
	bool equal = false;

	while (!equal) {
		incIter(iter);
		UHF[0] = UL_HF[0] - iter[0];
		UHF[1] = UL_HF[1] - iter[1];
		UHF[2] = UL_HF[2] - iter[2];
		UHF[3] = UL_HF[3] - iter[3];

		int testCN[4] = { root[0] + UHF[0],  root[1] + UHF[1],  root[2] + UHF[2],  root[3] + UHF[3] };
		for (int i = 0; i < 4; i++) fixVals(testCN[i]);

		if ((testCN[0] == CN_sol[0]) && (testCN[1] == CN_sol[1]) && (testCN[2] == CN_sol[2]) && (testCN[3] == CN_sol[3])) equal = true;
	}

	//Quick way to figure out the CN by looping through each position of the root + newUHF
	/*for (int i = 0; i < 4; i++) {
	while ((root[i] + UHF[i]) != CN[i]) {
		UHF[i]++;
	}
	}*/
}

void HackerMan::crackLHF() {
	for (int i = 0; i < 4; i++)
	{
		LHF[i] = LN[i] - root[i] - UHF[i];
		fixVals(LHF[i]);
	}	
}

void HackerMan::crackPHF() {
	//if we know two locked numbers we can find the PHF by:
	//LN1 = LN0 + UHF + LHF + PHF	==	LN1 - LN0 + (UHF + LHF) = PHF
	//LN0 = Root + UHF + LHF		==	Root - LN0 = (UHF + LHF)
	//Therefore	we can sub them in  ==  PHF = LN1 - LN0 + Root - LN0	== PHF = LN1 - 2(LN0) + Root
	if (LN.size() >= 8) {
		for (int i = 0; i < 4; i++) {
			PHF[i] = root[i] + LN[i+4] - (2*(LN[i]));
		}
		for (int i = 0; i < 4; i++)
		{
			fixVals(PHF[i]);
		}
	}

	HN[0] = LN[0] + PHF[0]; HN[1] = LN[1] + PHF[1];
	HN[2] = LN[2] + PHF[2]; HN[3] = LN[3] + PHF[3];

}

void HackerMan::populateHackerMan(MultiLock safe) {
	for (int i = 0; i < 4; i++) { root[i] = safe.getRoot()[i]; }
	for (int i = 0; i < safe.getSize(); i++) {
		for (int j = 0; j < 4; j++) {
			CN.push_back(safe.getLock(i)->getCN()[j]);
			LN.push_back(safe.getLock(i)->getLN()[j]);
			HN.push_back(safe.getLock(i)->getHN()[j]);
		}
	}
}

void HackerMan::populateSolutions(MultiLock safe) {
	for (int i = 0; i < safe.getSize(); i++) {
		for (int j = 0; j < 4; j++) {
			CN_sol.push_back(safe.getLock(i)->getCN()[j]);
			LN_sol.push_back(safe.getLock(i)->getLN()[j]);
			HN_sol.push_back(safe.getLock(i)->getHN()[j]);
		}
	}
}

void HackerMan::fixVals(int& val) {
	while (val > 9) {
		val -= 10;
	}
	while (val < 0) {
		val += 10;
	}
}

void HackerMan::incIter(int* iter) {
	if (iter[0] == 9) {
		iter[0] = 0;
		if (iter[1] == 9) {
			iter[1] = 0;
			if (iter[2] == 9) {
				iter[2] = 0;
				if (iter[3] == 9) {
					iter[3] = 0;
				}
				else iter[3]++;
			}
			else iter[2]++;
		}
		else iter[1]++;
	}
	else iter[0]++;
}

bool HackerMan::cracked(int* x, int* y) {
	for (int i = 0; i < 4; i++) {
		if (x[i] != y[i]) return false;
	}
	return true;
}