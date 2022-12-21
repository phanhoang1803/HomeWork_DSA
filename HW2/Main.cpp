#include "DataProcessing.h"

int main(int argc, char* argv[]) {
	DataProcessing dp;

	dp.readCommand(argc, argv);
	dp.displayOutput();

    return 0;
}