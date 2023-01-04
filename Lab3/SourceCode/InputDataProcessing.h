#pragma once
#include "Enum.h"
#include <iostream>
#include <string>

using namespace std;

ModeType getModeType(string s);
AlgorithmType getAlgorithmType(string s);
InputType getInputType(string s);
InputOrderType getInputOrderType(string s);
OutputParameterType getOutputParameterType(string s);
string* convertToString(int  argc, char* argv[]);
