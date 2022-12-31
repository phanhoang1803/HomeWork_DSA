#include "ReadCommand.h"

void readCommand(int argc, char* argv[]) {
	if (argc < 5) {
		cerr << "Error: invalid syntax.\n";
		return;
	}

	DataProcessing dp;
	string request;
	string tableName;
	string tableType;
	int L, R;
	vector<int> numberList;

	//Tham số dòng lệnh : filethựcthi make Tênbảng Loạibảng Dãysố
	//Tham số dòng lệnh : filethựcthi query Tênbảng Chặndưới Chặntrên
	
	// Convert char* list to string list
	vector<string> sargv(argc);
	for (int i = 0; i < argc; i++)
		sargv[i] = argv[i];
	

	request = sargv[1];
	tableName = sargv[2];
	tableType = sargv[3];

	// Make table
	if (request == "make") {
		for (int i = 4; i < argc; i++)
			numberList.push_back(stoi(sargv[i]));
		dp.makeSparseTable(tableName, tableType, numberList);
		dp.printTable(tableName);
	}
	// Query table
	else if (request == "query") {
		L = stoi(sargv[3]);
		R = stoi(sargv[4]);

		cout << dp.querySparseTable(tableName, L, R) << endl;
	}
	else {
		cerr << "Error: invalid syntax.\n";
		return;
	}
}