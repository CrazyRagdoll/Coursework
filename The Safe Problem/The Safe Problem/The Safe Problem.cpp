// The Safe Problem.cpp : Defines the entry point for the console application.

#include "stdafx.h"

#include <cstdlib>
#include <iostream>

#include "HashKeys.h"
#include "Lock.h"

using namespace std;

int main()
{

	int root;
	srand(2);// % 10000;
	root = rand() % 10000;

	HashKeys UHF, LHF, PHF;

	Lock lock0(root);

	lock0.setNumber('C', UHF.hashKey(lock0.getNumber('H')));
	lock0.setNumber('L', LHF.hashKey(lock0.getNumber('C')));

	cout << (lock0.checkCN() ? "CN is valid!" : "CN is invalid!");

	Lock lock1(lock0.getNumber('H'));

	lock1.setNumber('C', UHF.hashKey(lock1.getNumber('H')));
	lock1.setNumber('L', LHF.hashKey(lock1.getNumber('C')));

	cout << (lock1.checkCN() ? "CN is valid!" : "CN is invalid!");

	int poop;
	cin >> poop;


    return 0;
}