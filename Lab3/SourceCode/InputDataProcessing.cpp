#include "InputDataProcessing.h"

ModeType getModeType(string s) {
	if (s == "-a")
		return AlgorithmMode;
	if (s == "-c")
		return ComparisonMode;
	return ErrorMode;
}

AlgorithmType getAlgorithmType(string s) {
	string sortedList[] = { "selection-sort", "insertion-sort", "bubble-sort", "shaker-sort", "shell-sort",
	"heap-sort", "merge-sort", "quick-sort", "counting-sort","radix-sort", "flash-sort" };

	for (int i = 0; i < 11; i++) {
		if (s == sortedList[i])
			return AlgorithmType(i);
	}

	return ErrorAlgorithm;
}

InputType getInputType(string s) {
	if (s.find(".txt") != -1)
		return GivenInput;

	for (int i = 0; i < s.size(); i++) {
		if (s[i] < '0' || s[i] > '9')
			return ErrorInput;
	}

	int  size = stoi(s);

	return size > 0 ? InputSize : ErrorInput;
}

InputOrderType getInputOrderType(string s) {
	if (s == "-rand")
		return Rand;
	if (s == "-nsorted")
		return Nsorted;
	if (s == "-sorted")
		return Sorted;
	if (s == "-rev")
		return Rev;
	return ErrorInputOrder;
}

OutputParameterType getOutputParameterType(string s) {
	if (s == "-time")
		return Time;
	if (s == "-comp")
		return Comp;
	if (s == "-both")
		return Both;
	return ErrorOutputParameter;
}

string* convertToString(int  argc, char* argv[]) {
	string* sargv = new string[argc];

	for (int i = 0; i < argc; i++) {
		sargv[i] = argv[i];
	}

	return sargv;
}