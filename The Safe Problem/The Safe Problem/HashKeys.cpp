#include "stdafx.h"
#include "HashKeys.h"

#include <cstdlib>
#include <iostream>

HashKeys::HashKeys() {
	for (int i = 0; i < 4; i++) {
		hash_key[i] = rand() % 19 - 9;
	}
}

HashKeys::~HashKeys()
{
}

int* HashKeys::hashKey(int* key) {
	int *tmp = new int[4];

	for (int i = 0; i < 4; i++) tmp[i] = hash(key[i], hash_key[i]);

	return tmp;
	delete[] tmp;
}

int HashKeys::hash(int x, int y) {
	if (x + y > 9) {
		return x + y - 10;
	}
	else if (x + y < 0) {
		return x + y + 10;
	}
	else {
		return x + y;
	}
}


void HashKeys::setKey(int a, int b, int c, int d) {
	hash_key[0] = a;
	hash_key[1] = b;
	hash_key[2] = c;
	hash_key[3] = d;
}

int* HashKeys::getKey() {
	return hash_key;
}

ostream& operator<<(ostream& ostr, const HashKeys& key) {
	
	ostr << (key.hash_key[0] > 0 ? "+" : "") << key.hash_key[0] <<"," 
		 << (key.hash_key[1] > 0 ? "+" : "") << key.hash_key[1] << ","
		 << (key.hash_key[2] > 0 ? "+" : "") << key.hash_key[2] << ","
		 << (key.hash_key[3] > 0 ? "+" : "") << key.hash_key[3];
	
	return ostr;
}