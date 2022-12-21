#pragma once
#include "Libraries.h"

// ST[i][j]; i = start index. 2^j = length

class SparseTable
{
public:
	vector<vector<int>> _ST;
	int _rows; // Rows
	int _cols; // Cols

	SparseTable() {};
	SparseTable(int rows, int cols);

	void makeSparseTable(vector<int> data, int (*p)(int, int));
	int query(int L, int R, int (*p)(int, int));
};

