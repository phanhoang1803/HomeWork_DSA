#include "SparseTable.h"

SparseTable::SparseTable(int rows, int cols) {
	_rows = rows;
	_cols = cols;
	_ST = vector<vector<int>>(_rows);
	for (int i = 0; i < _rows; i++)
		_ST[i].resize(_cols);
}

void SparseTable::makeSparseTable(vector<int> data, int (*p)(int, int)) {
	_rows = data.size();
	_cols = log2(_rows) + 1;
	_ST = vector<vector<int>>(_rows);

	// Set size of table
	for (int i = 0; i < _rows; i++) {
		_ST[i].resize(_cols);
		// Of course, p(data[i,..., i + 2^0 - 1]) = p(data[i,...,i]) = data[i];
		_ST[i][0] = data[i];	
	}
	
	// We conduct set data for each interval 2 4 8 16 ... 2^n
	for (int j = 1; j < _cols; j++) {
		int interval = pow(2, j);
		
		for (int i = 0; i + interval - 1 < _rows; i++)
			// interval = 2^j
			// ST[i][j] = p(data[i,..., i + interval - 1])
			//			= p(data[i			   ,..., i + interval/2 - 1], 
			//				data[i + interval/2,..., i + interval - 1])
			_ST[i][j] = p(_ST[i][j - 1], _ST[i + interval / 2][j - 1]);
	}
}

int SparseTable::query(int L, int R, int (*p)(int, int)) {
	int res = 0;

	if (L < 0 || R >= _rows || L > R) {
		cerr << "Error: invalid range of query.\n";
		return -1;
	}

	int length = R - L + 1;
	int k = log2(length);

	res = p(_ST[L][k], _ST[R - pow(2, k) + 1][k]);

	return res;
}