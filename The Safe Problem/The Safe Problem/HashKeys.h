#pragma once

#include <ostream>

using namespace std;

class HashKeys
{
public:
	HashKeys();
	~HashKeys();

	int* hashKey(int* key);

	void setKey(int a, int b, int c, int d);
	int* getKey();

	friend ostream& operator<<(ostream& ostr, const HashKeys& key);

protected:

	int hash(int x, int y);

	int hash_key[4];

};

