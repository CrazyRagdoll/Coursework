#pragma once
class Lock
{
public:
	Lock(int hNumber);
	~Lock();

	void setNumber(char num, int val);
	int getNumber(char num);

	bool checkCN();
	bool checkLN();

protected:
	int CN, LN, HN;

};

