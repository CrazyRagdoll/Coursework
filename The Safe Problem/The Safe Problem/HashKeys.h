#pragma once

#include <ostream>
#include <iostream>

using namespace std;

class HashKeys
{
public:
	HashKeys();
	HashKeys(int i);
	~HashKeys() {};

	void hashKey(int* key, int* tmp);

	void setKey(int a, int b, int c, int d);
	int* getKey() {	return hash_key; }

	friend ostream& operator<<(ostream& ostr, const HashKeys& key);

	int & operator[](int i);

	HashKeys& operator=(const HashKeys& rhs);

protected:
	int hash_key[4];
	int hash(int x, int y);
	bool OK_key = false;	//A hash key cannot be 0,0,0,0 otherwise it may produce a CN to be equal to an LN
	bool check_key(int key[]);
};