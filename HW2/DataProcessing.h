#pragma once
#include "Libraries.h"

class DataProcessing
{
private:
	string _fileName;			// The file name include the text.
	string _text;				// The text that we will look for the pattern within.
	string _pattern;			// The search string.
	string _algorithmType;		// Contains an abbreviated string to determine which search algorithm is required.

public:
	// Read information and text from the file.
	void readCommand(int argc, char* argv[]);
	
	// Print output to the console.
	void displayOutput();
	
	// Calculate the number of occurrences of the pattern in the text and the running time of the algorithm.
	static string calculateNumSubsAndTime(string text, string pattern, int(*p)(string, string));
};

