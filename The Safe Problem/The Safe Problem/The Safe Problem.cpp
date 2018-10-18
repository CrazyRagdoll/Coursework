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
void generateKeyFile(ofstream& myFile, int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF);
void readKeyFile(ifstream& myFile);

void populateRoot(int* root, string line);
void populateHash(HashKeys& key, string line);

const string KeyFile = "key file.txt";
const string MultiSafeFile = "multi-safe file.txt";

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock(root, UHF, LHF, PHF);
	ofstream myFile; ifstream myInputFile;

	printHashKeys(UHF, LHF, PHF);

	clock_t start;
	start = clock();

	myFile.open(KeyFile);
	myFile << "NS         " << endl;
	myFile.close();

	int validSolutions = 0, seed = 0;
	while (validSolutions < 5) {
		generateRoot(root, seed++);
		multiLock = MultiLock(root, UHF, LHF, PHF);
		//cout << "Lock " << i << ": "; multiLock.printRoot();
		if (multiLock.checkMultiLock()) {
			//cout << "Valid Lock!" << endl;
			validSolutions++;
			generateKeyFile(myFile, root, UHF, LHF, PHF);
			//multiLock.generateSafeFile(myFile, MultiSafeFile, validSolutions);
		}
	}

	myFile.open(KeyFile, ios_base::in);
	myFile << "NS " << validSolutions;
	myFile.close();

	readKeyFile(myInputFile);

	cout << seed << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.";

    return 0;
}

void generateKeyFile(ofstream& myFile, int* root, HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	myFile.open(KeyFile, ios_base::app);
	myFile << "ROOT " << root[0] << root[1] << root[2] << root[3] << endl;
	myFile << "UHF " << UHF << endl << "LHF " << LHF << endl << "PHF " << PHF << endl;
	myFile.close();
}

void readKeyFile(ifstream& myFile) {
	int root[4];
	HashKeys UHF, LHF, PHF;

	string line;
	myFile.open(KeyFile);
	for (int i = 0; i < 5; i++) {
		getline(myFile, line);
		switch (line[0]) {
		case 'R': populateRoot(root, line); break;
		case 'U': populateHash(UHF, line); break;
		case 'L': populateHash(LHF, line); break;
		case 'P': populateHash(PHF, line); break;
		}
	}

	int lineCounter = 0;
	while (getline(myFile, line)) {
		if (line[0] == 'R' ) populateRoot(root, line);
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

void populateRoot(int* root, string line) {
	root[0] = (int)line[5] - 48;
	root[1] = (int)line[6] - 48; 
	root[2] = (int)line[7] - 48; 
	root[3] = (int)line[8] - 48;
}

//Random Root Generation
void generateRoot(int* root, int i) {
	srand(i);
	root[0] = rand() % 10;
	root[1] = rand() % 10;
	root[2] = rand() % 10;
	root[3] = rand() % 10;
}

void printRoot(int* root) {
	cout << "ROOT " << root[0] << root[1] << root[2] << root[3] << endl;
}

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	cout << "UHF " << UHF << endl;
	cout << "LHF " << LHF << endl;
	cout << "PHF " << PHF << endl;
}