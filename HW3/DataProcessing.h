#pragma once
#include "SparseTable.h"
#include <fstream>
#include <iostream>
#include "QueryType.h"

using namespace std;

class DataProcessing
{
private:
	string _fileName = "sparsetables.txt"; // Saved sparse table

private:
	vector<string> _tableNames;
	vector<string> _tableTypes;
	vector<SparseTable> _stl;

public:
	void writeTables();
	bool readTables();
	void printTable(string tableName);

	void makeSparseTable(string tableName, string tableType, vector<int> numberList);
	int querySparseTable(string tableName, int L, int R);
};

