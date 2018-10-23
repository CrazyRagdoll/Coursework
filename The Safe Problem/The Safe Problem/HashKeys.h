#pragma once

#include <ostream>

using namespace std;

class HashKeys
{
public:
	HashKeys();
	HashKeys(int i);
	~HashKeys();

	void hashKey(int* key, int* tmp);

	void setKey(int a, int b, int c, int d);
	int* getKey();

	friend ostream& operator<<(ostream& ostr, const HashKeys& key);

protected:
	int hash_key[4];
	int hash(int x, int y);
};