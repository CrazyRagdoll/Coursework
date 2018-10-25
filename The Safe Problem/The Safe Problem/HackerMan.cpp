#include "stdafx.h"
#include "HackerMan.h"

#include <iostream>
#include <chrono>
#include <thread>

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
	//cinematicHack();
}

void HackerMan::hack() {
	for (int i = 0; i < lockedSafes.size(); i++) {
		populateHackerMan(lockedSafes[i]);
		populateSolutions(unlockedSafes[i]);
		crackUHF(i);
		crackLHF(i);
		crackPHF(i);
	}
}

void HackerMan::crackUHF(int safe) {
	int UL_HF[4] = { LN[0] - root[0], LN[1] - root[1], LN[2] - root[2], LN[3] - root[3] };
	for (int i = 0; i < 4; i++) fixVals(UL_HF[i]);

	int iter[4] = { 0,0,0,0 };
	int testCN[4];
	bool equal = false;

	HashKeys UHFtmp;
	while (!equal) {
		incIter(iter);

		UHFtmp.setKey(UL_HF[0] - iter[0], UL_HF[1] - iter[1], UL_HF[2] - iter[2], UL_HF[3] - iter[3]);

		testCN[0] = root[0] + UHFtmp[0];
		testCN[1] = root[1] + UHFtmp[1];
		testCN[2] = root[2] + UHFtmp[2];
		testCN[3] = root[3] + UHFtmp[3];

		for (int i = 0; i < 4; i++) fixVals(testCN[i]);

		if ((testCN[0] == CN_sol[0]) && (testCN[1] == CN_sol[1]) && (testCN[2] == CN_sol[2]) && (testCN[3] == CN_sol[3])) equal = true;
	}

	UHF.push_back(UHFtmp);

}


void HackerMan::crackLHF(int safe) {
	HashKeys LHFtmp;
	for (int i = 0; i < 4; i++)
	{
		LHFtmp[i] = LN[i] - root[i] - UHF[safe][i];
		fixVals(LHFtmp[i]);
	}
	LHF.push_back(LHFtmp);
}

void HackerMan::crackPHF(int safe) {
	//if we know two locked numbers we can find the PHF by:
	//LN1 = LN0 + UHF + LHF + PHF	==	LN1 - LN0 + (UHF + LHF) = PHF
	//LN0 = Root + UHF + LHF		==	Root - LN0 = (UHF + LHF)
	//Therefore	we can sub them in  ==  PHF = LN1 - LN0 + Root - LN0	== PHF = LN1 - 2(LN0) + Root
	HashKeys PHFtmp;
	if (LN.size() >= 8) {
		for (int i = 0; i < 4; i++) {
			PHFtmp[i] = root[i] + LN[i + 4] - (2 * (LN[i]));
		}
		for (int i = 0; i < 4; i++)
		{
			fixVals(PHFtmp[i]);
		}
	}

	HN[0] = LN[0] + PHFtmp[0]; HN[1] = LN[1] + PHFtmp[1];
	HN[2] = LN[2] + PHFtmp[2]; HN[3] = LN[3] + PHFtmp[3];

	PHF.push_back(PHFtmp);
}

void HackerMan::populateHackerMan(MultiLock safe) {
	CN.clear();
	LN.clear();
	HN.clear();
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
	CN_sol.clear();
	LN_sol.clear();
	HN_sol.clear();
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

void HackerMan::cinematicHack() {

	cout << "Loading HackerMan 3000........."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << ".\n";
	cout << "[                                   ]\r[";
	for (int i = 0; i < 35; i++) { cout << "#"; sleep(50); } cout << "] LOADED\n";

	cout << "\nHackerMan 3000: Populating....."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << ".\n";
	cout << "[                                   ]\r[";
	for (int i = 0; i < 35; i++) { cout << "#"; sleep(50); } cout << "] POPULATED\n";

	cout << "\nHackerMan 3000: Cracking UHF..."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << ".\n";
	cout << "[                                   ]\r[";
	for (int i = 0; i < 35; i++) { cout << "#"; sleep(50); } cout << "] CRACKED\n";

	cout << "\nHackerMan 3000: Cracking LHF..."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << ".\n";
	cout << "[                                   ]\r[";
	for (int i = 0; i < 35; i++) { cout << "#"; sleep(50); } cout << "] CRACKED\n";

	cout << "\nHackerMan 3000: Cracking PHF..."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << "."; sleep(250); cout << ".\n";
	cout << "[                                   ]\r[";
	for (int i = 0; i < 35; i++) { cout << "#"; } cout << "] CRACKED\n";

	cout << "\n~~~~~~~~~~~SAFE HACKED~~~~~~~~~~~\n";


	sleep(2500);
}


void HackerMan::sleep(int i) {
	std::this_thread::sleep_for(std::chrono::milliseconds(i));
}