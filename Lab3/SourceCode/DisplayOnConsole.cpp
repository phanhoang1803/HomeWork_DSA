#include "DisplayOnConsole.h"
#include <fstream>
#include <time.h>
#include "Enum.h"
#include "InputDataProcessing.h"
#include "SortFunctions.h"
#include "DataGenerator.h"
#include "SortFunctionsWithCmp.h"
#include "FuncsSupportSort.h"


#define FILE_WRITE_12 "output.txt"
#define FILE_WRITE_25 "input.txt"
string FILE_WRITE_3[] = { "input_1.txt","input_2.txt" ,"input_3.txt" ,"input_4.txt" };


//– Prototype : [Execution file] - a [Algorithm] [Given input] [Output parameter(s)]
//– Prototype : [Execution file] - a [Algorithm] [Input size] [Input order] [Output parameter(s)]
//– Prototype : [Execution file] - a [Algorithm] [Input size] [Output parameter(s)]
//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Given input]
//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Input size][Input order]

bool getInputFile(string fileName, int*& arr, int& sizeArr) {
	ifstream f;
	f.open(fileName);

	if (f.fail())
		return false;

	f >> sizeArr;
	arr = new int[sizeArr];

	for (int i = 0; i < sizeArr; i++)
		f >> arr[i];

	f.close();

	return true;
}

void writeOutputToFile(string fileName, int* arr, int  size) {
	ofstream f;
	f.open(fileName);

	if (f.fail()) {
		cerr << "Error write: Can't open file!\n";
		return;
	}

	f << size << endl;

	for (int i = 0; i < size; i++)
		f << arr[i] << " ";

	f.close();
}

unsigned long long  calNumberOfCmps(AlgorithmType at, int* arr, int  size) {
	int* arrTmp = copyArray(arr, size);
	unsigned long long nCmp = sortWithCompare(at, arrTmp, size);

	delete[]arrTmp;

	return nCmp;
}

double calDuration(AlgorithmType at, int* arr, int  size) {
	int* arrTmp = copyArray(arr, size);

	clock_t start = clock();
	sortWithoutCompare(at, arrTmp, size);
	clock_t end = clock();

	double duration = double(end - start) / CLOCKS_PER_SEC;

	delete[]arrTmp;

	return duration;
}

void displayOnConsole(CommandType cmdType, int  argc, string* argv) {
	switch (cmdType)
	{
	case Command1:
		displayCommand1(argc, argv);
		break;
	case Command2:
		displayCommand2(argc, argv);
		break;
	case Command3:
		displayCommand3(argc, argv);
		break;
	case Command4:
		displayCommand4(argc, argv);
		break;
	case Command5:
		displayCommand5(argc, argv);
		break;
	default:
		cerr << "Error: Invalid input.\n";
		break;
	}
}

// Algorithm mode
void displayOutputParameter(OutputParameterType opt, double duration, unsigned long long  nCompararisons) {
	switch (opt)
	{
	case Time:
		cout << "Running time: " << duration << " double\n";
		break;
	case Comp:
		cout << "Comparisons: " << nCompararisons << endl;
		break;
	case Both:
		cout << "Running time: " << duration << " double\n";
		cout << "Comparisons: " << nCompararisons << endl;
		break;
	default:
		break;
	};
}

// Comparison mode
void displayOutputParameter(double duration1, unsigned long long  nCompararisons1, double duration2, unsigned long long  nCompararisons2) {
	cout << "Running time: " << duration1 << " | " << duration2 << "\n";
	cout << "Comparisons: " << nCompararisons1 << " | " << nCompararisons2 << endl;
}

// Algorithm mode
void supportDisplayOutputPara(int* arr, int  size, AlgorithmType at, OutputParameterType opt) {
	unsigned long long  nCmp = calNumberOfCmps(at, arr, size);

	// Cal function runtime
	double duration = calDuration(at, arr, size);

	displayOutputParameter(opt, duration, nCmp);
}

// Comparison mode
void supportDisplayOutputPara(int* arr, int  size, AlgorithmType at1, AlgorithmType at2) {
	// Cal number of Comparisons
	unsigned long long nCmp1 = calNumberOfCmps(at1, arr, size), nCmp2 = calNumberOfCmps(at2, arr, size);

	// Cal function runtime
	double duration1 = calDuration(at1, arr, size), duration2 = calDuration(at2, arr, size);

	displayOutputParameter(duration1, nCmp1, duration2, nCmp2);
}


unsigned long long  sortWithCompare(AlgorithmType at, int* arr, int  size) {
	switch (at)
	{
	case SelectionSort:
		return selectionSortCmp(arr, size);
	case InsertionSort:
		return insertionSortCmp(arr, size);
	case BubbleSort:
		return bubbleSortCmp(arr, size);
	case ShakerSort:
		return shakerSortCmp(arr, size);
	case ShellSort:
		return shellSortCmp(arr, size);
	case HeapSort:
		return heapSortCmp(arr, size);
	case MergeSort:
		return mergeSortCmp(arr, 0, size - 1);
	case QuickSort:
		return quickSortCmp(arr, 0, size - 1);
	case CountingSort:
		return coutingSortCmp(arr, size);
	case RadixSort:
		return radixSortCmp(arr, size);
	case FlashSort:
		return flashSortCmp(arr, size);
	default:
		break;
	};
}

void sortWithoutCompare(AlgorithmType at, int* arr, int  size) {
	switch (at)
	{
	case SelectionSort:
		selectionSort(arr, size);
		break;
	case InsertionSort:
		insertionSort(arr, size);
		break;
	case BubbleSort:
		bubbleSort(arr, size);
		break;
	case ShakerSort:
		shakerSort(arr, size);
		break;
	case ShellSort:
		shellSort(arr, size);
		break;
	case HeapSort:
		heapSort(arr, size);
		break;
	case MergeSort:
		mergeSort(arr, 0, size - 1);
		break;
	case QuickSort:
		quickSort(arr, 0, size - 1);
		break;
	case CountingSort:
		coutingSort(arr, size);
		break;
	case RadixSort:
		radixSort(arr, size);
		break;
	case FlashSort:
		flashSort(arr, size);
		break;
	default:
		break;
	};
}

void displayCommand1(int  argc, string* argv) {
	int* arr;
	int  sizeArr = 0;
	unsigned long long  nCmp = 0;

	if (!getInputFile(argv[3], arr, sizeArr)) {
		cerr << "Error read: Can't open file!\n";
		return;
	}

	cout << "ALGORITHM MODE\n";
	cout << "Algorithm: " << argv[2] << endl;
	cout << "Input file: " << argv[3] << endl;
	cout << "Input size: " << sizeArr << endl;
	cout << "--------------------------\n";

	supportDisplayOutputPara(arr, sizeArr, getAlgorithmType(argv[2]), getOutputParameterType(argv[4]));

	writeOutputToFile(FILE_WRITE_12, arr, sizeArr);

	delete[]arr;
}

void displayCommand2(int  argc, string* argv) {
	int  sizeArr = stoi(argv[3]);
	int* arr = new int[sizeArr];

	GenerateData(arr, sizeArr, getInputOrderType(argv[4]));

	// Write down the generated input to the "input.txt" file
	writeOutputToFile(FILE_WRITE_25, arr, sizeArr);

	cout << "ALGORITHM MODE\n";
	cout << "Algorithm: " << argv[2] << endl;
	cout << "Input size: " << argv[3] << endl;
	cout << "Input order: " << argv[4] << endl;
	cout << "--------------------------\n";

	supportDisplayOutputPara(arr, sizeArr, getAlgorithmType(argv[2]), getOutputParameterType(argv[5]));

	// Write down the sorted array to the "ouput.txt" file
	sortWithoutCompare(getAlgorithmType(argv[2]), arr, sizeArr);
	writeOutputToFile(FILE_WRITE_12, arr, sizeArr);

	delete[]arr;
}

void displayCommand3(int  argc, string* argv) {
	int  sizeArr = stoi(argv[3]);

	cout << "ALGORITHM MODE\n";
	cout << "Algorithm: " << argv[2] << endl;
	cout << "Input size: " << argv[3] << endl;

	string inOrd[] = { "Randomize\n", "Nearly Sorted\n", "Sorted\n", "Reversed\n" };
	for (int i = Rand; i < (int)ErrorInputOrder; i++) {
		int* arr = new int[sizeArr];
		GenerateData(arr, sizeArr, InputOrderType(i));

		writeOutputToFile(FILE_WRITE_3[i], arr, sizeArr);

		cout << "\nInput order: " << inOrd[i];
		cout << "--------------------------\n";

		supportDisplayOutputPara(arr, sizeArr, getAlgorithmType(argv[2]), getOutputParameterType(argv[4]));

		delete[]arr;
	}
}

void displayCommand4(int  argc, string* argv) {
	int* arr;
	int  sizeArr = 0;
	unsigned long long nCmp = 0;

	if (!getInputFile(argv[4], arr, sizeArr)) {
		cerr << "Error: Can't open file!\n";
		return;
	}

	cout << "COMPARE MODE\n";
	cout << "Algorithm: " << argv[2] << " | " << argv[3] << endl;
	cout << "Input file: " << argv[4] << endl;
	cout << "Input size: " << sizeArr << endl;
	cout << "--------------------------\n";

	supportDisplayOutputPara(arr, sizeArr, getAlgorithmType(argv[2]), getAlgorithmType(argv[3]));

	delete[]arr;
}

void displayCommand5(int  argc, string* argv) {
	int  sizeArr = stoi(argv[4]);
	int* arr = new int[sizeArr];
	GenerateData(arr, sizeArr, getInputOrderType(argv[5]));

	// Write down the generated input to the "input.txt" file
	writeOutputToFile(FILE_WRITE_25, arr, sizeArr);

	cout << "COMPARE MODE\n";
	cout << "Algorithm: " << argv[2] << " | " << argv[3] << endl;
	cout << "Input size: " << sizeArr << endl;
	cout << "Input order: " << argv[5] << endl;
	cout << "--------------------------\n";

	supportDisplayOutputPara(arr, sizeArr, getAlgorithmType(argv[2]), getAlgorithmType(argv[3]));

	delete[]arr;
}