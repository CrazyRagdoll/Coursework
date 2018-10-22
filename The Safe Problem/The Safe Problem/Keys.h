#pragma once
#include <stdint.h>
#include <cstdlib>

class Keys
{
public:

	Keys()
	{
	}

	~Keys()
	{
	}

	void randomKey(int i) {
		srand(i);
		a = rand() % 19 - 9;
		b = rand() % 19 - 9;
		c = rand() % 19 - 9;
		d = rand() % 19 - 9;
	}

protected:

	int8_t a, b, c, d;

};

