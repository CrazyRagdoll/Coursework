// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

#include "HashKeys.h"
#include "MultiLock.h"
#include "FileLoader.h"
#include "HackerMan.h"

using namespace std;

void generateRoot(int* root, int i);

const string KeyFile = "key file.txt";
const string MultiSafeFile = "multi-safe file.txt";
const string LockedSafeFile = "locked safe file.txt";

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock;
	FileLoader myFiles;

	int validSolutions = 0, bonusSolutions = 0, sols = 0, seed = 0, size = 5, iter = 0;
	vector<int> validRoots;
	vector<MultiLock> validSafes;

	cout << "How many valid solutions do you require? ";
	cin >> sols;
	cout << "How large are the MultiLocks? ";
	cin >> size;

	clock_t start;
	start = clock();

	while (validSolutions < sols) {
		generateRoot(root, seed++);
		multiLock = MultiLock(root, UHF, LHF, PHF, size);
		if (multiLock.checkMultiLock()) {
			validSafes.push_back(multiLock);
			validSolutions++;
			if (multiLock.checkBONUSMultiLock()) bonusSolutions++;
		}
		iter++;
		if (iter > 15000) {
			cout << "15000 Iterations & no solution; changing hash values.\n";
			UHF = HashKeys(seed); LHF = HashKeys(seed); PHF = HashKeys(seed);
			iter = 0;
		}
	}

	try {
		myFiles.writeKeyFile		(KeyFile, validSafes, UHF, LHF, PHF);
		myFiles.writeLockedSafeFile	(LockedSafeFile, validSafes, UHF, LHF, PHF);
		myFiles.readKeyFile			(KeyFile, validRoots, UHF, LHF, PHF);
		myFiles.writeMultiSafeFile	(MultiSafeFile, validSafes, UHF, LHF, PHF);
	}
	catch (const invalid_argument& iae) {
		cout << "Unable to read data: " << iae.what() << endl;
		exit(1);
	}

	cout << bonusSolutions << " bonus solutions!\n";
	cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.\n";

	//Coursework 2

	int x;
	cout << "Hack Safe? ";
	cin >> x;
	
	if (x != 0) {
		start = clock();

		vector<MultiLock> lockedSafes;
		vector<int> lockedRoots, lockedLN;
		vector<int> unlRoots, unlCN, unlLN, unlHN;

		try {
			//myFiles.readLockedSafeFile(LockedSafeFile, lockedRoots, lockedLN);
			myFiles.readMultiSafeFile(MultiSafeFile, unlRoots, unlCN, unlLN, unlHN);
			myFiles.readLockedSafeFile(LockedSafeFile, lockedSafes);
		}
		catch (const invalid_argument& iae) {
			cout << "Unable to read data: " << iae.what() << endl;
			exit(1);
		}

		HackerMan getHacked(lockedRoots, unlCN, lockedLN, unlHN);

		HackerMan getHackedV2(lockedSafes);

		cout << "Safe Hacked in " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.\n";

	}

    return 0;
}

//Random Root Generation
void generateRoot(int* root, int i) {
	srand(i);
	for (int i = 0; i < 4; i++) { root[i] = rand() % 10; }
}