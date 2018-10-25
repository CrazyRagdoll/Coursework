// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"
#include "HashKeys.h"
#include "MultiLock.h"
#include "FileLoader.h"
#include "HackerMan.h"
#include "Thread.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

using namespace std;

void generateRoot(int* root, int i);
void generateReadSafeFile(vector<MultiLock>& safes, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF, int size);

const string KeyFile = "key.txt";
const string MultiSafeFile = "multi-safe.txt";
const string LockedSafeFile = "locked-safe.txt";
const string HackedKeyFile = "hacked key.txt";
const string HackedSafeFile = "hacked safe.txt";

int main()


{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock;
	FileLoader myFiles;

	int validSols = 0, bonusSolutions = 0, sols = 0, seed = 0, size = 5, iter = 0;
	vector<int> validRoots;
	vector<MultiLock> validSafes;

	char gen = ' ';
	cout << "Generate new Safes? y/n ";
	cin >> gen;

	while (gen != 'y' && gen != 'n' && gen != 'Y' && gen != 'N') {
		cout << "Please enter Y or N! ";
		cin >> gen;
	}
	
	if (gen == 'Y' || gen == 'y') {
		cout << "How many valid solutions do you require? ";
		cin >> sols;
		cout << "How large are the MultiLocks? ";
		cin >> size;

		clock_t start;
		start = clock();

		while (validSols < sols) {
			generateRoot(root, seed++);
			multiLock = MultiLock(root, UHF, LHF, PHF, size);
			if (multiLock.checkMultiLock()) {
				validSafes.push_back(multiLock);
				validSols++;
				if (multiLock.checkBONUSMultiLock()) bonusSolutions++;
			}
			iter++;
			if (iter > 15000) {
				cout << "15000 Iterations; changing hash values.\n";
				UHF = HashKeys(seed); LHF = HashKeys(seed); PHF = HashKeys(seed);
				iter = 0;
			}
		}

		try {
			myFiles.writeKeyFile(KeyFile, validSafes, UHF, LHF, PHF);
			myFiles.writeLockedSafeFile(LockedSafeFile, validSafes, UHF, LHF, PHF);
			myFiles.readKeyFile(KeyFile, validRoots, UHF, LHF, PHF);
			vector<MultiLock> readSafes;
			generateReadSafeFile(readSafes, validRoots, UHF, LHF, PHF, size);
			myFiles.writeMultiSafeFile(MultiSafeFile, readSafes);
		}
		catch (const invalid_argument& iae) {
			cout << "Unable to read data: " << iae.what() << endl;
			//exit(1);
		}

		cout << bonusSolutions << " bonus solutions!\n";
		cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.\n";
	}


	//Coursework 2

	char hack = ' ';
	cout << "Hack Safes? y/n ";
	cin >> hack;

	while (hack != 'y' && hack != 'n' && hack != 'Y' && hack != 'N') {
		cout << "Please enter Y or N! "; 
		cin >> hack;
	} 
	
	if (hack == 'y' || hack == 'Y') {
		clock_t start;
		start = clock();

		vector<MultiLock> lockedSafes, unlockedSafes;

		try {
			myFiles.readMultiSafeFile(MultiSafeFile, unlockedSafes);
			myFiles.readLockedSafeFile(LockedSafeFile, lockedSafes);
		}
		catch (const invalid_argument& iae) {
			cout << "Unable to read data: " << iae.what() << endl;
			//exit(1);
		}

		HackerMan hackSafe(lockedSafes, unlockedSafes);
		vector<MultiLock> hackedSafes;
		vector<HashKeys> hackedUHF, hackedLHF, hackedPHF;

		for(int i = 0; i < hackSafe.getSize(); i++) {
			hackedUHF.push_back(hackSafe.getUHF(i));
			hackedLHF.push_back(hackSafe.getLHF(i)); 
			hackedPHF.push_back(hackSafe.getPHF(i));

			hackedSafes.push_back(MultiLock(hackSafe.getLockedSafe(i).getRoot(), hackedUHF[i], hackedLHF[i], hackedPHF[i], hackSafe.getLockedSafe(i).getSize()));
		}

		try {
			myFiles.writeKeyFile(HackedKeyFile, hackedSafes, hackedUHF, hackedLHF, hackedPHF);
			myFiles.writeMultiSafeFile(HackedSafeFile, hackedSafes);
		}
		catch (const invalid_argument& iae) {
			cout << "Unable to read data: " << iae.what() << endl;
			//exit(1);
		}

		cout << "Safes Hacked in " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.\n";
	}

    return 0;
}

//Random Root Generation
void generateRoot(int* root, int i) {
	srand(i);
	for (int i = 0; i < 4; i++) { root[i] = rand() % 10; }
}

void generateReadSafeFile(vector<MultiLock>& safes, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF, int size) {
	int root[4];
	for (int i = 0; i < (int)roots.size(); i += 4) {
		root[0] = roots[i + 0]; root[1] = roots[i + 1]; root[2] = roots[i + 2]; root[3] = roots[i + 3];
		MultiLock tmpSafe(root, UHF, LHF, PHF, size);
		safes.push_back(tmpSafe);
	}
}