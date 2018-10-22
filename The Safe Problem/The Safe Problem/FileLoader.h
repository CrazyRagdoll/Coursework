#pragma once
#pragma warning( disable : 4290 ) 

#include "stdafx.h"

class FileLoader
{
public:
	FileLoader() {};
	~FileLoader() {};

	void writeKeyFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	void writeMultiSafeFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF);
	void writeLockedSafeFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF);

	void readKeyFile(string file, vector<int>& roots, HashKeys& UHF, HashKeys& LHF, HashKeys& PHF);
	void FileLoader::readLockedSafeFile(string file, vector<int>& roots, vector<int>& LN) throw (invalid_argument);

protected:
	void populateHash(HashKeys& key, string line);
	void populateRoot(vector<int>& root, string line);
	void populateLN(vector<int>& LN, string line);

	ofstream myOutputFile; 
	ifstream myInputFile;

};

void FileLoader::writeKeyFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file, ios_base::app);

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	myOutputFile << "NS " << roots.size() / 4 << endl;
	for (int i = 0; i < (int)roots.size(); i += 4)
	{
		myOutputFile << "ROOT " << roots[i + 0] << roots[i + 1] << roots[i + 2] << roots[i + 3] << endl;
		myOutputFile << "UHF " << UHF << endl << "LHF " << LHF << endl << "PHF " << PHF << endl;
	}
	myOutputFile.close();
}

void FileLoader::writeMultiSafeFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument)  {
	myOutputFile.open(file, ios_base::app);
	int root[4];
	MultiLock lockCheck;

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	for (int i = 0; i < (int)roots.size(); i += 4)
	{
		root[0] = roots[i + 0]; root[1] = roots[i + 1]; root[2] = roots[i + 2]; root[3] = roots[i + 3];
		lockCheck = MultiLock(root, UHF, LHF, PHF);
		(lockCheck.checkMultiLock() ? myOutputFile << "NS" << i / 4 << " VALID\n" : myOutputFile << "NS" << i / 4 << " NOT VALID\n");
		myOutputFile << lockCheck;
	}
	myOutputFile.close();
}

void FileLoader::writeLockedSafeFile(string file, vector<int>& roots, HashKeys UHF, HashKeys LHF, HashKeys PHF) throw (invalid_argument) {
	myOutputFile.open(file, ios_base::app);
	int root[4], tempLN[4];
	MultiLock lockCheck;

	if (myOutputFile.fail()) throw invalid_argument("No file exists " + file);

	myOutputFile << "NL " << roots.size() / 4 << endl;
	for (int i = 0; i < (int)roots.size(); i += 4)
	{
		root[0] = roots[i + 0]; root[1] = roots[i + 1]; root[2] = roots[i + 2]; root[3] = roots[i + 3];
		lockCheck = MultiLock(root, UHF, LHF, PHF);
		myOutputFile << "ROOT " << root[0] << root[1] << root[2] << root[3] << "\n";

		for (int j = 0; j < lockCheck.getSize(); j++) {
			for (int z = 0; z < 4; z++) { tempLN[z] = lockCheck.getLock(z).getLN()[z]; }
			myOutputFile << "LN" << j << tempLN[0] <<  tempLN[1] <<  tempLN[2] << tempLN[3] << "\n";
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
		case 'R': populateRoot(roots, line); break;
		case 'U': populateHash(UHF, line); break;
		case 'L': populateHash(LHF, line); break;
		case 'P': populateHash(PHF, line); break;
		}
	}

	while (getline(myInputFile, line)) {
		if (line[0] == 'R') populateRoot(roots, line);
	}
	myInputFile.close();
}

void FileLoader::readLockedSafeFile(string file, vector<int>& roots, vector<int>& LN) throw (invalid_argument) {
	roots.clear();
	string line;
	myInputFile.open(file);

	if (myInputFile.fail())	throw invalid_argument("No file exists " + file);

	while (getline(myInputFile, line)) {
		if (line[0] == 'R') populateRoot(roots, line);
		if (line[0] == 'L') populateLN(LN, line);
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

void FileLoader::populateRoot(vector<int>& root, string line) {
	for (int i = 0; i < 4; i++) { root.push_back((int)line[i + 5] - 48); }
}

void FileLoader::populateLN(vector<int>& LN, string line) {
	for (int i = 0; i < 4; i++) { LN.push_back((int)line[i + 4] - 48); }
}