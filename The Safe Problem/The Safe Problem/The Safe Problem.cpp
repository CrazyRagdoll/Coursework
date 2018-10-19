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
void printRoot(int* root);

const string KeyFile = "key file.txt";
const string MultiSafeFile = "multi-safe file.txt";

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock(root, UHF, LHF, PHF);
	FileLoader myFiles;

	printHashKeys(UHF, LHF, PHF);

	clock_t start;
	start = clock();

	int validSolutions = 0, seed = 0;
	vector<int> validRoots;
	while (validSolutions < 10000) {
		generateRoot(root, seed++);
		multiLock = MultiLock(root, UHF, LHF, PHF);
		if (multiLock.checkMultiLock()) {
			for (int i = 0; i < 4; i++)	validRoots.push_back(root[i]);
			validSolutions++;
		}
	}

	myFiles.generateKeyFile(KeyFile, validRoots, UHF, LHF, PHF);
	myFiles.readKeyFile(KeyFile, validRoots, UHF, LHF, PHF);
	myFiles.generateMultiSafeFile(MultiSafeFile, validRoots, UHF, LHF, PHF);

	cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.";

    return 0;
}

//Random Root Generation
void generateRoot(int* root, int i) {
	srand(i);
	for (int i = 0; i < 4; i++) { root[i] = rand() % 10; }
}

void printRoot(int* root) {
	cout << "ROOT " << root[0] << root[1] << root[2] << root[3] << endl;
}

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	cout << "UHF " << UHF << endl;
	cout << "LHF " << LHF << endl;
	cout << "PHF " << PHF << endl;
}