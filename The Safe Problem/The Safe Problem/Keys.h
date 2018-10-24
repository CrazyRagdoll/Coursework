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

protected:

	T a, b, c, d;

};
