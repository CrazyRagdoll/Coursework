// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>

#include "HashKeys.h"

using namespace std;

int main()
{

	int root;
	root = rand() % 10000;

	HashKeys UHF, LHF, PHF;

	int CN, LN, HN;

	cout << "Root " << root << endl;

	CN = UHF.hashKey(root);

	cout << "CN " << CN << endl;

	LN = LHF.hashKey(CN);

	cout << "LN " << LN << endl;

	HN = PHF.hashKey(LN);

	cout << "HN " << HN << endl;




















	int poop;
	cin >> poop;


    return 0;
}