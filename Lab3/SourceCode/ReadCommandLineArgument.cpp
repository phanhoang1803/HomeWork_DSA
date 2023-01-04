#include "ReadCommandLineArgument.h"

CommandType readCommandTypeInput(int  argc, string* argv) {
	if (argc > 6 || argc < 5)
		return ErrorCommandType;

	// Command 1,2,3
	if (getModeType(argv[1]) == AlgorithmMode) {
		//-						0		  1			2			3			4				5
		//– Prototype : [Execution file] - a [Algorithm] [Given input] [Output parameter(s)]
		//– Prototype : [Execution file] - a [Algorithm] [Input size] [Input order] [Output parameter(s)]
		//– Prototype : [Execution file] - a [Algorithm] [Input size] [Output parameter(s)]
		if (getAlgorithmType(argv[2]) == ErrorAlgorithm)
			return ErrorCommandType;

		// Command 1, 3, argc = 5
		if (argc == 5 && getOutputParameterType(argv[4]) != ErrorOutputParameter) {
			if (getInputType(argv[3]) == GivenInput)
				return Command1;
			if (getInputType(argv[3]) == InputSize)
				return Command3;
		}

		// Command 2
		if (getInputType(argv[3]) == InputSize && getInputOrderType(argv[4]) != ErrorInputOrder && getOutputParameterType(argv[5]) != ErrorOutputParameter)
			return Command2;

		return ErrorCommandType;
	}
	// Command 4,5
	if (getModeType(argv[1]) == ComparisonMode) {
		//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Given input]
		//– Prototype : [Execution file] - c [Algorithm 1][Algorithm 2][Input size][Input order]
		if (getAlgorithmType(argv[2]) == ErrorAlgorithm || getAlgorithmType(argv[3]) == ErrorAlgorithm)
			return ErrorCommandType;

		if (getInputType(argv[4]) == GivenInput)
			return Command4;
		if (argc == 6 && getInputType(argv[4]) == InputSize && getInputOrderType(argv[5]) != ErrorInputOrder)
			return Command5;
	}

	return ErrorCommandType;
}

