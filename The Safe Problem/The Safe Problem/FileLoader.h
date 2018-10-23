#pragma once
#pragma warning( disable : 4290 ) 

#include "stdafx.h"

class FileLoader
{
public:
	FileLoader() {};
	~FileLoader() {};

	void writeKeyFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	void writeMultiSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	void writeLockedSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF);

	void readKeyFile(string file, vector<int>& roots, HashKeys& UHF, HashKeys& LHF, HashKeys& PHF);
	void readMultiSafeFile(string file, vector<int>& roots, vector<int>& CN, vector<int>& LN, vector<int>& HN);
	void readLockedSafeFile(string file, vector<int>& roots, vector<int>& LN);

	void readLockedSafeFile(string file, vector<MultiLock>& safes);

protected:
	void populateHash(HashKeys& key, string line);
	void populateNum(vector<int>& num, string line, int offSet);
	void populateNum(int* num, string line, int offSet);

	ofstream myOutputFile; 
	ifstream myInputFile;

};

void FileLoader::writeKeyFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	myOutputFile << "NS " << safes.size() << endl;
	for (int i = 0; i < (int)safes.size(); i++) {
		myOutputFile << "ROOT " << safes[i].getRoot()[0] << safes[i].getRoot()[1] << safes[i].getRoot()[2] << safes[i].getRoot()[3] << "\n";
		myOutputFile << "UHF " << UHF << "\n" << "LHF " << LHF << "\n" << "PHF " << PHF << "\n";
	}
	myOutputFile.close();
}

void FileLoader::writeMultiSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);
	MultiLock lockCheck;

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	for (int i = 0; i < (int)safes.size(); i ++)
	{
		lockCheck = safes[i];
		(lockCheck.checkMultiLock() ? myOutputFile << "NS" << i  << " VALID\n" : myOutputFile << "NS" << i / 4 << " NOT VALID\n");
		myOutputFile << lockCheck;
	}
	myOutputFile.close();
}

void FileLoader::writeLockedSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);
	MultiLock lockCheck;

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	myOutputFile << "NL " << safes.size() << endl;
	for (int i = 0; i < (int)safes.size(); i++)
	{
		lockCheck = safes[i];
		myOutputFile << "ROOT " << safes[i].getRoot()[0] << safes[i].getRoot()[1] << safes[i].getRoot()[2] << safes[i].getRoot()[3] << "\n";
		for (int j = 0; j < lockCheck.size; j++) {
			myOutputFile << "LN" << j << " " << lockCheck.getLock(j).getLN()[0] << lockCheck.getLock(j).getLN()[1] << lockCheck.getLock(j).getLN()[2] << lockCheck.getLock(j).getLN()[3] << "\n";
		}
		myOutputFile << "\n";
	}
	myOutputFile.close();
}

void FileLoader::readKeyFile(string file, vector<int>& roots, HashKeys& UHF, HashKeys& LHF, HashKeys& PHF) throw (invalid_argument) {
	roots.clear();
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	for (int i = 0; i < 5; i++) {
		getline(myInputFile, line);
		switch (line[0]) {
		case 'R': populateNum(roots, line, 5); break;
		case 'U': populateHash(UHF, line); break;
		case 'L': populateHash(LHF, line); break;
		case 'P': populateHash(PHF, line); break;
		}
	}

	while (getline(myInputFile, line)) {
		if (line[0] == 'R') populateNum(roots, line, 5);
	}
	myInputFile.close();
}

void FileLoader::readMultiSafeFile(string file, vector<int>& roots, vector<int>& CN, vector<int>& LN, vector<int>& HN) {
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	while (getline(myInputFile, line)) {
		if (line[0] == 'R') populateNum(roots, line, 5);
		if (line[0] == 'C') populateNum(CN, line, 4);
		if (line[0] == 'L') populateNum(LN, line, 14);
		if (line[0] == 'H') populateNum(HN, line, 24);
	}
	myInputFile.close();
}

void FileLoader::readLockedSafeFile(string file, vector<int>& roots, vector<int>& LN) throw (invalid_argument) {
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	while (getline(myInputFile, line)) {
		if (line[0] == 'R') populateNum(roots, line, 5);
		if (line[0] == 'L') populateNum(LN, line, 4);
	}
	myInputFile.close();
}

void FileLoader::readLockedSafeFile(string file, vector<MultiLock>& safes) throw (invalid_argument) {
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	int tmpRoot[4], tmpLN[4], count = 0;
	MultiLock tmpSafe;
	while (getline(myInputFile, line)) {
		if (line[0] == 'R') {
			populateNum(tmpRoot, line, 5);
			tmpSafe.setRoot(tmpRoot);
		}
		if (line[0] == 'L')
		{
			populateNum(tmpLN, line, 4);
			tmpSafe.addLock(tmpLN);
			count++;
		}
		if (line[0] == NULL) {
			safes.push_back(tmpSafe);
		}
	}
	myInputFile.close();
}

void FileLoader::populateHash(HashKeys& key, string line) {
	int temp[4];
	for (int i = 0; i < 4; i++) {
		if (line[4 + (i * 3)] == '-') { temp[i] = ((int)line[5 + (i * 3)] - 48)* -1; }
		else { temp[i] = ((int)line[5 + (i * 3)] - 48); }
	}
	key.setKey(temp[0], temp[1], temp[2], temp[3]);
}

void FileLoader::populateNum(vector<int>& num, string line, int offSet) {
	for (int i = 0; i < 4; i++) { num.push_back((int)line[i + offSet] - 48); }
}

void FileLoader::populateNum(int* num, string line, int offSet) {
	for (int i = 0; i < 4; i++) { num[i] = ((int)line[i + offSet] - 48); }
}