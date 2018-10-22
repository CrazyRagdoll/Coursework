#pragma once

#include <ostream>

using namespace std;

template <Typename T>
class Keys
{
public:

	Keys()
	{
	}

	Keys(int a, int b, int c, int d) :
		a(a), b(b), c(c), d(d)
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

	T a, b, c, d;

};
