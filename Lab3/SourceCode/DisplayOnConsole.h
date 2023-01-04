#pragma once
#include "Enum.h"
#include <iostream>

using namespace std;

//– Prototype : [Execution file] - a [Algorithm] [Given input] [Output parameter(s)]
//– Prototype : [Execution file] - a [Algorithm] [Input size] [Input order] [Output parameter(s)]
//– Prototype : [Execution file] - a [Algorithm] [Input size] [Output parameter(s)]
//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Given input]
//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Input size][Input order]

void displayOnConsole(CommandType cmdType, int  argc, string* argv);

bool getInputFile(string fileName, int*& arr, int& sizeArr);
void writeOutputToFile(string fileName, int* arr, int  size);

unsigned long long calNumberOfCmps(AlgorithmType at, int* arr, int  size);
double calDuration(AlgorithmType at, int* arr, int  size);

void displayOutputParameter(OutputParameterType opt, double duration, unsigned long long nCompararisons);
void displayOutputParameter(double duration1, unsigned long long  nCompararisons1, double duration2, unsigned long long nCompararisons2);

void supportDisplayOutputPara(int* arr, int  size, AlgorithmType at, OutputParameterType opt);
void supportDisplayOutputPara(int* arr, int  size, AlgorithmType at1, AlgorithmType at2);

unsigned long long  sortWithCompare(AlgorithmType at, int* arr, int  size);
void sortWithoutCompare(AlgorithmType at, int* arr, int  size);

void displayCommand1(int  argc, string* argv);
void displayCommand2(int  argc, string* argv);
void displayCommand3(int  argc, string* argv);
void displayCommand4(int  argc, string* argv);
void displayCommand5(int  argc, string* argv);

