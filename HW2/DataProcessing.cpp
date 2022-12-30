#include "DataProcessing.h"
#include "StringSearchAlgorithm.h"

//Input:
//• Tham số dòng lệnh : file_thực_thi File_text Chuỗi_cần_tìm Thuật_toán
//(cách nhau bở khoảng trắng).
//Các thuật toán bao gồm : BF(brute - force), RK(Rabin - Karp), KMP(Knuth - MorrisPatt), BM(Boyer - Moore)
//• VD : a.exe input.txt AABA BM
//• input.txt : AABAACAADAABAABA
//Output :
//• Số lần xuất hiện của chuỗi cần tìm kiếm và thời gian thực thi(ms).
//• VD : 3 - 0.69


void DataProcessing::readCommand(int argc, char* argv[]) {
	if (argc != 4) {
		cerr << "Error: wrong command line parameter syntax.\nExit program\n";
		exit(1);
	}

	// Read some information.
	_fileName		= argv[1];
	_pattern		= argv[2];
	_algorithmType	= argv[3];

	// Read text from file.
	ifstream is;
	is.open(_fileName);

	// If can't open the file or the file doesn't exist,
	// exit the program
	if (is.fail()) {
		cerr << "Error: can't open this text file.\nExit program\n";
		exit(1);
	}

	is >> _text;

	is.close();
}

void DataProcessing::displayOutput() {
	vector<string> algorithmSyntax = { "BF", "RK", "KMP", "BM" };
	int i = 0;
	
	// Find the algorithm is requested.
	for (; i < algorithmSyntax.size(); i++)
		if (algorithmSyntax[i] == _algorithmType)
			break;

	// Display output.
	switch (i)
	{
	case 0: 
		cout << calculateNumSubsAndTime(_text, _pattern, StringSearchAlgorithm::BruteForce);
		break;
	case 1:
		cout << calculateNumSubsAndTime(_text, _pattern, StringSearchAlgorithm::RabinKarp);
		break;
	case 2:
		cout << calculateNumSubsAndTime(_text, _pattern, StringSearchAlgorithm::KnuthMorrisPatt);
		break;
	case 3:
		cout << calculateNumSubsAndTime(_text, _pattern, StringSearchAlgorithm::BoyerMoore);
		break;
	default:
		cerr << "Error: the algorithm syntax is wrong.\nExit program.\n";
		exit(1);
	}
}

string DataProcessing::calculateNumSubsAndTime(string text, string pattern, int(*p)(string, string)) {
	stringstream builder;

	// Calculate the running time of the algorithm.
	clock_t start = clock();
	builder << p(text, pattern);
	clock_t end = clock();

	double duration = double(end - start) / CLOCKS_PER_SEC;

	builder << " - " << duration;

	// Return the res string will be printed on the console.
	return builder.str();
}
