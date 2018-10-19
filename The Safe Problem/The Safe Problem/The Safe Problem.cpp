// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <time.h>
#include <string>

#include "HashKeys.h"
#include "MultiLock.h"

using namespace std;

void generateRoot(int* root, int i);

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF);
void printRoot(int* root);

void generateKeyFile(ofstream& myFile, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF);
void generateMultiSafeFile(ofstream& myFile, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF);

void readKeyFile(ifstream& myFile, vector<int>& roots, HashKeys& UHF, HashKeys& LHF, HashKeys& PHF);

void populateRoot(vector<int>& root, string line);
void populateHash(HashKeys& key, string line);

const string KeyFile = "key file.txt";
const string MultiSafeFile = "multi-safe file.txt";

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock(root, UHF, LHF, PHF);
	ofstream myOutputFile; ifstream myInputFile;

	printHashKeys(UHF, LHF, PHF);

	clock_t start;
	start = clock();

	int validSolutions = 0, seed = 0;
	vector<int> validRoots;
	while (validSolutions < 5) {
		generateRoot(root, seed++);
		multiLock = MultiLock(root, UHF, LHF, PHF);
		if (multiLock.checkMultiLock()) {
			for (int i = 0; i < 4; i++)	validRoots.push_back(root[i]);
			validSolutions++;
		}
	}

	generateKeyFile(myOutputFile, validRoots, UHF, LHF, PHF);

	readKeyFile(myInputFile, validRoots, UHF, LHF, PHF);

	generateMultiSafeFile(myOutputFile, validRoots, UHF, LHF, PHF);

	cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.";

    return 0;
}

void generateKeyFile(ofstream& myFile, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	myFile.open(KeyFile, ios_base::app);
	myFile << "NS " << roots.size()/4 << endl;
	for (int i = 0; i < (int)roots.size(); i+=4)
	{
		myFile << "ROOT " << roots[i] << roots[i + 1] << roots[i + 2] << roots[i + 3] << endl;
		myFile << "UHF " << UHF << endl << "LHF " << LHF << endl << "PHF " << PHF << endl;
	}
	myFile.close();
}

void generateMultiSafeFile(ofstream& myFile, vector<int> roots, HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	myFile.open(MultiSafeFile, ios_base::app);
	for (int i = 0; i < (int)roots.size(); i+=4)
	{
		int root[4] = { roots[i], roots[i + 1], roots[i + 2], roots[i + 3] };
		MultiLock lockCheck(root, UHF, LHF, PHF);
		(lockCheck.checkMultiLock() ? myFile << "NS" << i/4 << " VALID\n" : myFile << "NS" << i / 4 << " NOT VALID\n");
		myFile << lockCheck;
	}
	myFile.close();
}

void readKeyFile(ifstream& myFile, vector<int>& roots, HashKeys& UHF, HashKeys& LHF, HashKeys& PHF) {
	roots.clear();
	string line;
	myFile.open(KeyFile);
	for (int i = 0; i < 5; i++) {
		getline(myFile, line);
		switch (line[0]) {
		case 'R': populateRoot(roots, line); break;
		case 'U': populateHash(UHF, line); break;
		case 'L': populateHash(LHF, line); break;
		case 'P': populateHash(PHF, line); break;
		}
	}

	int lineCounter = 0;
	while (getline(myFile, line)) {
		if (line[0] == 'R' ) populateRoot(roots, line);
		lineCounter++;
	}
	myFile.close();
}

void populateHash(HashKeys& key, string line) {
	int temp[4];
	for (int i = 0; i < 4; i++) {
		if (line[4+(i*3)] == '-') { temp[i] = ((int)line[5+(i*3)] - 48)* -1; }
		else { temp[i] = ((int)line[5+(i*3)] - 48); }
	}
	key.setKey(temp[0], temp[1], temp[2], temp[3]);
}

void populateRoot(vector<int>& root, string line) {
	for (int i = 0; i < 4; i++) { root.push_back((int)line[i+5] - 48); }
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