#include "stdafx.h"
#include "HashKeys.h"

#include <cstdlib>

HashKeys::HashKeys() : 
	a(rand() % 19 - 9),
	b(rand() % 19 - 9),
	c(rand() % 19 - 9),
	d(rand() % 19 - 9)
{
}


HashKeys::~HashKeys()
{
}

int HashKeys::hashKey(int key) {
	int newKey = 0;

	newKey += (hashVal((key / 1000) % 10, a)) * 1000;
	newKey += (hashVal((key / 100) % 10, b)) * 100;
	newKey += (hashVal((key / 10) % 10, c)) * 10;
	newKey += (hashVal((key / 1) % 10, d)) * 1;

	return newKey;
}

void HashKeys::setKey(int a, int b, int c, int d) {
	a = a; b = b; c = c; d = d; 
}

int HashKeys::getKey(char x) {
	switch(x) {
		case 'a': return a;  break;
		case 'b': return b;  break;
		case 'c': return c;  break;
		case 'd': return d;  break;
		default: return 0;
	}
}

int HashKeys::hashVal(int val, int hashVal) {
	int newVal = val + hashVal;
	if (newVal < 0) newVal += 10;
	else if (newVal > 9) newVal %= 10;
	return newVal;
}