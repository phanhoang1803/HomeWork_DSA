#include "DataProcessing.h"
#include "Libraries.h"

void DataProcessing::writeTables() {
	ofstream writer(_fileName);

	writer << _tableNames.size() << "\n";

	for (int i = 0; i < _tableNames.size(); i++) {
		// A MIN rows cols
		// data
		int rows = _stl[i]._rows, cols = _stl[i]._cols;

		writer << _tableNames[i] << " " << _tableTypes[i] << " " << rows << " " << cols << "\n";
		int j = 0;
		for (; j < rows * cols - 1; j++)
			writer << _stl[i]._ST[j / cols][j % cols] << " ";

		writer << _stl[i]._ST[j / cols][j % cols] << "\n";
	}

	writer.close();
}
bool DataProcessing::readTables() {
	ifstream reader(_fileName);

	if (reader.fail())
		return false;

	_tableNames.resize(0);
	_tableTypes.resize(0);
	_stl.resize(0);

	int numTables;
	reader >> numTables;

	for(int i = 0; i < numTables; i++){
		string tableName, tableType;
		int rows, cols;

		// A MIN rows cols
		// data
		reader >> tableName >> tableType >> rows >> cols;

		_tableNames.push_back(tableName);
		_tableTypes.push_back(tableType);

		SparseTable st(rows, cols);
	
		for (int j = 0; j < rows * cols; j++)
			reader >> st._ST[j / cols][j % cols];

		_stl.push_back(st);
	}

	reader.close();
}

void DataProcessing::printTable(string tableName) {
	for (int i = 0; i < _tableNames.size(); i++) {
		if (_tableNames[i] == tableName) {
			_stl[i].print();
			break;
		}
	}
}

void DataProcessing::makeSparseTable(string tableName, string tableType, vector<int> numberList) {
	readTables();

	// If the table name is the same, we replace the old table with the new one
	int i = 0; 
	for (; i < _tableNames.size(); i++)
		if (_tableNames[i] == tableName)
			break;

	if (i == 5) {
		cout << "Error: can't add table because there are already 5 tables.\n";
		return;
	}

	SparseTable st;
	int(*p)(int, int) = NULL;
	if (tableType == "MIN")
		p = min;
	else if (tableType == "MAX")
		p = max;
	else if (tableType == "GCD")
		p = gcd;
	st.makeSparseTable(numberList, p);

	// If the number of tables is less than 5 and don't have the same name.
	if (i == _tableNames.size()) {
		_tableNames.push_back(tableName);
		_tableTypes.push_back(tableType);
		_stl.push_back(st);
	}
	// If same table name.
	else {
		_tableNames[i] = tableName;
		_tableTypes[i] = tableType;
		_stl[i] = st;
	}

	// Save the table.
	writeTables();
}

int DataProcessing::querySparseTable(string tableName, int L, int R) {
	readTables();
	
	for (int i = 0; i < _tableNames.size(); i++)
		if (_tableNames[i] == tableName) {
			if (_tableTypes[i] == "MIN")
				return _stl[i].query(L, R, min);

			if (_tableTypes[i] == "MAX")
				return _stl[i].query(L, R, max);

			if (_tableTypes[i] == "GCD")
				return _stl[i].query(L, R, gcd);

			cerr << "Error: Invalid table type.\n";
			exit(1);
		}

	cerr << "Error: Invalid table name.\n";
	exit(1);
}