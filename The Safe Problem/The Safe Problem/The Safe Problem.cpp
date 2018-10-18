// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>
#include <time.h>

#include "HashKeys.h"
#include "MultiLock.h"

using namespace std;

void generateRoot(int* root, int i);

void printHashKeys(HashKeys UHF, HashKeys LHF, HashKeys PHF);
void printRoot(int* root);

int main()
{
	int root[4];
	HashKeys UHF, LHF, PHF;
	MultiLock multiLock(root, UHF, LHF, PHF);

	printHashKeys(UHF, LHF, PHF);

	int x; cout << "How many iterations? "; cin >> x;

	clock_t start;
	start = clock();

	for (int i = 0; i < x; i++) {
		generateRoot(root, i);
		multiLock = MultiLock(root, UHF, LHF, PHF);
		cout << "Lock " << i << ": "; multiLock.printRoot();
		if (multiLock.checkMultiLock()) {
			cout << "Valid Lock!" << endl;
		}
	}

	cout << x << " iterations took " << (clock() - start) / (double)(CLOCKS_PER_SEC / 1000) << " ms.";

    return 0;
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