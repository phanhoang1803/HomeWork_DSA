#include "DisplayOnConsole.h"
#include "InputDataProcessing.h"
#include "ReadCommandLineArgument.h"

int main(int  argc, char* argv[]) {
	string* sargv = convertToString(argc, argv);

	CommandType cmdType = readCommandTypeInput(argc, sargv);

	displayOnConsole(cmdType, argc, sargv);

	delete[]sargv;

	return 0;
}