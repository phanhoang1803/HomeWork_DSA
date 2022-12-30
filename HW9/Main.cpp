#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
#include <unordered_map>
#include <sstream>
#include <bitset>

using namespace std;
#define BITS 9
#define CODE bitset<BITS>

// Convert input to list codes.
vector<CODE> convert(int argc, char* argv[]) {
	vector<CODE> res;
	for (int i = 2; i < argc; i++)
		res.push_back(stoi(argv[i]));
	return res;
}

// Compute compression ratio
double compressionRatio(string s, vector<CODE> codes) {
	// Number of bits before compression
	int N = s.size() * sizeof(char) * CHAR_BIT;
	// Number of bits after compression
	int n = codes.size() * BITS;

	return 100.0 * (N - n) / N;
}

vector<CODE> compress(string s) {
	unordered_map<string, CODE> table;

	// Initialize dic.
	for (int i = 0; i < 256; i++)
		table[string(1, i)] = i;

	string sPrev = "", sNext = "";
	sPrev += s[0];
	int code = 256;
	
	vector<CODE> codes;
	for (int i = 0; i < s.length(); i++) {
		if (i != s.length() - 1)
			sNext += s[i + 1];

		string newChar = sPrev + sNext;
		// If newChar exist in the dictionary,
		// set prev = newChar
		if (table.find(newChar) != table.end())
			sPrev = newChar;

		// If newChar doesn't exist in the dic,
		// add newChar into the dic,
		// and add prev into output_code.
		// set prev = next
		else {
			codes.push_back(table[sPrev]);
			table[newChar] = code++;
			sPrev = sNext;
		}

		// clear sNext
		sNext = "";
	}

	codes.push_back(table[sPrev]);

	return codes;
}
string decompress(vector<CODE> codes) {
	unordered_map<CODE, string> table;
	for (int i = 0; i <= 255; i++)
		table[i] = string(1, i);

	// Store decompression
	stringstream builder;

	CODE iPrev = codes[0];
	CODE iNext;

	string sPrev = table[iPrev];
	
	// c is always a first char of sPrev.
	string c = string(1, sPrev[0]);

	// Absolutely, a first code is always a char in ASCII.
	builder << sPrev;

	int code = 256;
	for (int i = 0; i < codes.size() - 1; i++) {	
		// Check the next code.
		iNext = codes[i + 1];

		// If the char of the next code exist in the dic,
		// push it to the res string.
		if (table.find(iNext) != table.end())
			sPrev = table[iNext];
		// otherwise,
		// lấy ký tự dòng tr, ghép với ký tự đầu tiên của dòng dưới.
		else {
			sPrev = table[iPrev];
			sPrev = sPrev + c;
		}
		// Push char to the res string.
		builder << sPrev;

		// Prepare for next loop.
		c = string(1, sPrev[0]);
		table[code] = table[iPrev] + c;
		code++;
		iPrev = iNext;
	}

	return builder.str();
}

void readCommandLine(int argc, char* argv[]) {
	if (argc < 3) {
		cerr << "Error: wrong input syntax!\n";
		exit(1);
	}

	// Compress
	if (strcmp(argv[1], "-c") == 0) {
		string s = argv[2];
		vector<CODE> codes = compress(s);

		// Print decimal codes.
		for (auto v : codes)
			cout << v.to_ulong() << " ";
		cout << endl;

		// Print binary codes.
		for (auto v : codes)
			cout << v << " ";

		cout << endl << compressionRatio(s, codes);
	}
	// Decompress
	else if (strcmp(argv[1], "-e") == 0) {
		vector<CODE> a = convert(argc, argv);
		string s = decompress(a);
		cout << s << endl;

		cout << compressionRatio(s, a);
	}
	else {
		cerr << "Error: wrong input syntax!\n";
		exit(1);
	}
}

int main(int argc, char* argv[]) {
	readCommandLine(argc, argv);

	return 0;
}