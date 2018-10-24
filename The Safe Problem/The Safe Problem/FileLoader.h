#pragma once
#pragma warning( disable : 4290 ) 

#include <cmath>

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
	void readMultiSafeFile(string file, vector<MultiLock>& safes);
	void readLockedSafeFile(string file, vector<MultiLock>& safes);

protected:
	void populateHash(HashKeys& key, string line);
	void populateNum(vector<int>& num, string line, int offSet);
	void populateNum(int* num, string line, int offSet);
	void populateNumSols(int& num, string line, int offSet);

	ofstream myOutputFile; 
	ifstream myInputFile;

};

void FileLoader::writeKeyFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);

	if (myOutputFile.fail()) throw invalid_argument("Failed to create " + file);

	myOutputFile << "NS " << safes.size() << endl;
	for (int i = 0; i < (int)safes.size(); i++) {
		myOutputFile << "ROOT " << safes[i].getRoot()[0] << safes[i].getRoot()[1] << safes[i].getRoot()[2] << safes[i].getRoot()[3] << "\n";
		myOutputFile << "UHF " << UHF << "\n" << "LHF " << LHF << "\n" << "PHF " << PHF << "\n";
	}
	myOutputFile.close();
}

void FileLoader::writeMultiSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);

	if (myOutputFile.fail()) throw invalid_argument("Failed to create " + file);

	myOutputFile << "NS" << (int)safes.size() << " ";
	for (int i = 0; i < (int)safes.size(); i ++)
	{
		(safes[i].checkMultiLock() ? myOutputFile << "VALID\n" : myOutputFile << "NOT VALID\n");
		myOutputFile << safes[i];
	}
	myOutputFile.close();
}

void FileLoader::writeLockedSafeFile(string file, vector<MultiLock> safes, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file);

	if (myOutputFile.fail()) throw invalid_argument("Failed to create " + file);

	myOutputFile << "NL " << safes.size() << endl;
	for (int i = 0; i < (int)safes.size(); i++)
	{
		myOutputFile << "ROOT " << safes[i].getRoot()[0] << safes[i].getRoot()[1] << safes[i].getRoot()[2] << safes[i].getRoot()[3] << "\n";
		for (int j = 0; j < safes[i].getSize(); j++) {
			myOutputFile << "LN" << j << " " << safes[i].getLock(j)->getLN()[0] << safes[i].getLock(j)->getLN()[1] << safes[i].getLock(j)->getLN()[2] << safes[i].getLock(j)->getLN()[3] << "\n";
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

	int sols = 0;
	for (int i = 0; i < 5; i++) {
		getline(myInputFile, line);
		switch (line[0]) {
		case 'N': populateNumSols(sols, line, 3); break;
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

void FileLoader::readMultiSafeFile(string file, vector<MultiLock>& safes) throw (invalid_argument) {
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	int sols = 0;
	getline(myInputFile, line);
	populateNumSols(sols, line, 2);
	for (int i = 0; i < sols; i++) {
		int tmpCN[4], tmpLN[4], tmpHN[4], count = 0;
		MultiLock tmpSafe;

		while (getline(myInputFile, line)) {
			if (line[0] == 'C') {
				populateNum(tmpCN, line, 4);
				populateNum(tmpLN, line, 14);
				populateNum(tmpHN, line, 24);
				tmpSafe.addLock();
				tmpSafe.getLock(count)->setCN(tmpCN);
				tmpSafe.getLock(count)->setLN(tmpLN);
				tmpSafe.getLock(count)->setHN(tmpHN);
				count++;
			}
			else {
				break;
			}
		}
		safes.push_back(tmpSafe);
	}
	myInputFile.close();
}

void FileLoader::readLockedSafeFile(string file, vector<MultiLock>& safes) throw (invalid_argument) {
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	int sols = 0;
	getline(myInputFile, line);
	populateNumSols(sols, line, 3);
	for (int i = 0; i < sols; i++) {
		int tmpRoot[4], tmpLN[4], count = 0;
		MultiLock tmpSafe;

		while (getline(myInputFile, line)) {
			if (line[0] == 'R') {
				populateNum(tmpRoot, line, 5);
				tmpSafe.setRoot(tmpRoot);
			}
			else if (line[0] == 'L')
			{
				populateNum(tmpLN, line, 4);
				tmpSafe.addLock();
				tmpSafe.getLock(count)->setLN(tmpLN);
				count++;
			}
			else break;
		}
		safes.push_back(tmpSafe);
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

void FileLoader::populateNumSols(int& num, string line, int offSet) {
	int count = 0, tmp[6], power = 0;
	while (line[count + offSet] != '\n' && line[count + offSet] != ' ' && line[count + offSet] != '\0') {
		tmp[count] = (line[count + offSet] - 48);
		count++;
	}
	for (int i = count; i > 0; i--) {
		num += tmp[i-1] * (int)(pow(10, power++));
	}
}