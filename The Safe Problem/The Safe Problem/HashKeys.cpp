#include "stdafx.h"
#include "HashKeys.h"

#include <cstdlib>
#include <iostream>

HashKeys::HashKeys() {
	while (!OK_key) {
		for (int i = 0; i < 4; i++) {
			hash_key[i] = rand() % 19 - 9;
		}
		OK_key = check_key(hash_key);
	}
}

HashKeys::HashKeys(int i) {
	srand(i);
	while (!OK_key) {
		for (int i = 0; i < 4; i++) {
			hash_key[i] = rand() % 19 - 9;
		}
		OK_key = check_key(hash_key);
	}
}

bool HashKeys::check_key(int key[]) {
	if (key[0] == 0 && key[1] == 0 && key[2] == 0 && key[3] == 0) return false; 
	else return true;
}

void HashKeys::hashKey(int* key, int* tmp) {
	for (int i = 0; i < 4; i++) tmp[i] = hash(key[i], hash_key[i]);
}

int HashKeys::hash(int x, int y) {
	int res = x + y;
	while (res > 9) {
		res -= 10;
	}
	while (res < 0) {
		res += 10;
	}
	return res;
}


void HashKeys::setKey(int a, int b, int c, int d) {
	hash_key[0] = a;
	hash_key[1] = b;
	hash_key[2] = c;
	hash_key[3] = d;
}

ostream& operator<<(ostream& ostr, const HashKeys& key) {
	
	ostr << (key.hash_key[0] >= 0 ? "+" : "") << key.hash_key[0] << "," 
		 << (key.hash_key[1] >= 0 ? "+" : "") << key.hash_key[1] << ","
		 << (key.hash_key[2] >= 0 ? "+" : "") << key.hash_key[2] << ","
		 << (key.hash_key[3] >= 0 ? "+" : "") << key.hash_key[3];
	
	return ostr;
}

int& HashKeys::operator[](int i) {
	if (i > 3) {
		std::cout << "Out of bounds...\n"; 
		return hash_key[0];
	}
	return hash_key[i];
}

HashKeys& HashKeys::operator=(const HashKeys& rhs) {
	if (this == &rhs) return (*this);

	for (int i = 0; i < 4; i++) {
		hash_key[i] = rhs.hash_key[i];
	}

	return *this;
}
