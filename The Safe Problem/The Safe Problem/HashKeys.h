#pragma once
class HashKeys
{
public:
	HashKeys();
	~HashKeys();

	int hashKey(int key);

	void setKey(int a, int b, int c, int d);

protected:
	int hashVal(int val, int hashVal);
	int  getKey(char x);

	int a, b, c, d;

};

