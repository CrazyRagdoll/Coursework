// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

#include "HashKeys.h"
#include "MultiLock.h"
#include "FileLoader.h"

using namespace std;

void generateRoot(int* root, int i);

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF);

const string KeyFile = "key file.txt";
const string MultiSafeFile = "multi-safe file.txt";
const string LockedSafeFile = "locked safe file.txt";

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock(root, UHF, LHF, PHF);
	FileLoader myFiles;

	printHashKeys(UHF, LHF, PHF);

	int validSolutions = 0, bonusSolutions = 0, sols = 0, seed = 0;
	vector<int> validRoots;

	cout << "How many valid solutions do you require? ";
	cin >> sols;

	clock_t start;
	start = clock();

	while (validSolutions < sols) {
		generateRoot(root, seed++);
		multiLock = MultiLock(root, UHF, LHF, PHF);
		if (multiLock.checkMultiLock()) {
			for (int i = 0; i < 4; i++)	validRoots.push_back(root[i]);
			validSolutions++;
			if (multiLock.checkBONUSMultiLock()) bonusSolutions++;
		}
	}

	try {
		myFiles.writeKeyFile		(KeyFile, validRoots, UHF, LHF, PHF);
		myFiles.writeLockedSafeFile	(LockedSafeFile, validRoots, UHF, LHF, PHF);
		myFiles.readKeyFile			(KeyFile, validRoots, UHF, LHF, PHF);
		myFiles.writeMultiSafeFile	(MultiSafeFile, validRoots, UHF, LHF, PHF);
	}
	catch (const invalid_argument& iae) {
		cout << "Unable to read data: " << iae.what() << endl;
		exit(1);
	}

	cout << bonusSolutions << " bonus solutions!\n";
	cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.";

	//Coursework 2

	vector<int> lockedRoots, lockedLN;

	try {
		myFiles.readLockedSafeFile(LockedSafeFile, lockedRoots, lockedLN);
	}
	catch (const invalid_argument& iae) {
		cout << "Unable to read data: " << iae.what() << endl;
		exit(1);
	}











    return 0;
}

//Random Root Generation
void generateRoot(int* root, int i) {
	srand(i);
	for (int i = 0; i < 4; i++) { root[i] = rand() % 10; }
}

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	cout << "UHF " << UHF << endl;
	cout << "LHF " << LHF << endl;
	cout << "PHF " << PHF << endl;
}