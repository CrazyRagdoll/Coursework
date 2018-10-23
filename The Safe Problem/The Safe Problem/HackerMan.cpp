#include "stdafx.h"
#include "HackerMan.h"

#include <iostream>

HackerMan::HackerMan(vector<MultiLock> safes) {
	magic();
}

HackerMan::HackerMan(vector<int> val, vector<int> vals) {
	addRoot(val);
	addLNVals(vals);
	magic();
}

HackerMan::HackerMan(vector<int> val, vector<int> valsCN, vector<int> valsLN, vector<int> valsHN) {
	addRoot(val);
	addCNVals(valsCN);
	addLNVals(valsLN);
	addHNVals(valsHN);
	magic();
}

void HackerMan::magic() {
	findUHF();

	findLHF();

	findPHF();
}

void HackerMan::findUHF() {
	int CNtmp[4] = { root[0], root[1], root[2], root[3] };
	int CNcheck[4] = { CN[0], CN[1], CN[2], CN[3] };
	int iter = 0;
	bool equal = false;
	while (!equal) {
		iter++;
		CNtmp[0] = (root[0] + ((iter / 1000) % 10)) % 10;
		CNtmp[1] = (root[1] + ((iter / 100) % 10)) % 10;
		CNtmp[2] = (root[2] + ((iter / 10) % 10)) % 10;
		CNtmp[3] = (root[3] + ((iter / 1) % 10)) % 10;
		if ((CNtmp[0] == CNcheck[0]) && (CNtmp[1] == CNcheck[1]) && (CNtmp[2] == CNcheck[2]) && (CNtmp[3] == CNcheck[3])) {
			equal = true;
		}
	}
	UHF[0] = (iter / 1000) % 10; UHF[1] = (iter / 100) % 10;
	UHF[2] = (iter / 10) % 10;	 UHF[3] = (iter / 1) % 10;

	/*for (int i = 0; i < 4; i++) {
		while ((root[i] + UHF[i]) != CN[i]) {
			UHF[i]++;
		}
	}*/
}

void HackerMan::findLHF() {
	for (int i = 0; i < 4; i++)
	{
		LHF[i] = LN[i] - root[i] - UHF[i];
		fixVals(LHF[i]);
	}	
}

void HackerMan::findPHF() {
	//if we know two locked numbers we can find the PHF by:
	//LN1 = LN0 + UHF + LHF + PHF	==	LN1 - LN0 + (UHF + LHF) = PHF
	//Root + UHF + LHF = LN0		==	Root - LN0 = (UHF + LHF)
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
}

void HackerMan::fixVals(int& val) {
	while (val < 0) {
		val += 10;
	}
	while (val > 9) {
		val -= 10;
	}
}