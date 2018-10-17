// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <vector>
#include <chrono>

#include "HashKeys.h"
#include "Lock.h"

using namespace std;

void generateRoot(int* root);

void generateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF);

int main()
{
	int root[4];

	generateRoot(root);

	HashKeys UHF, LHF, PHF;

	cout << "ROOT " << root[0] << root[1] << root[2] << root[3] << endl;
	cout << "UHF " << UHF << endl;
	cout << "LHF " << LHF << endl;
	cout << "PHF " << PHF << endl;

	int x;
	cout << "How many iterations? ";
	cin >> x;

	auto start = chrono::steady_clock::now();

	for (int i = 1; i < x; i++) {
		generateMultiLock(UHF, LHF, PHF);
	}

	auto end = chrono::steady_clock::now();
	cout << "done in " << chrono::duration_cast<chrono::milliseconds> (end - start).count();

	int poop;
	cin >> poop;

    return 0;
}

void generateMultiLock(HashKeys UHF, HashKeys LHF, HashKeys PHF) {
	vector<Lock> multiLock;

	int root[4];
	generateRoot(root);
	multiLock.push_back(0);
	multiLock[0].setCN(UHF.hashKey(root));
	multiLock[0].setLN(LHF.hashKey(multiLock[0].getCN()));
	multiLock[0].setHN(PHF.hashKey(multiLock[0].getLN()));

	for (int i = 1; i < 5; i++) {
		multiLock.push_back(Lock(i));
		multiLock[i].setCN(UHF.hashKey(multiLock[i - 1].getHN()));
		multiLock[i].setLN(LHF.hashKey(multiLock[i].getCN()));
		multiLock[i].setHN(PHF.hashKey(multiLock[i].getLN()));
	}

}

//Random Root Generation
void generateRoot(int* root) {

	srand(0);
	int randy = rand() % 10000;
	root[0] = randy / 1000 % 10;
	root[1] = randy / 100 % 10;
	root[2] = randy / 10 % 10;
	root[3] = randy / 1 % 10;

}