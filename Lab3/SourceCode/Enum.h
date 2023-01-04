#pragma once

enum CommandType {
	Command1,
	Command2,
	Command3,
	Command4,
	Command5,
	ErrorCommandType
};

enum ModeType {
	AlgorithmMode,
	ComparisonMode,
	ErrorMode
};

enum AlgorithmType {
	SelectionSort,
	InsertionSort,
	BubbleSort,
	ShakerSort,
	ShellSort,
	HeapSort,
	MergeSort,
	QuickSort,
	CountingSort,
	RadixSort,
	FlashSort,
	ErrorAlgorithm
};

enum InputType {
	GivenInput,
	InputSize,
	ErrorInput
};

enum InputOrderType {
	Rand,
	Nsorted,
	Sorted,
	Rev,
	ErrorInputOrder
};

enum OutputParameterType {
	Time,
	Comp,
	Both,
	ErrorOutputParameter
};
