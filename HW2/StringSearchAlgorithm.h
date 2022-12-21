#pragma once
#include "Libraries.h"

class StringSearchAlgorithm
{
public:
	static int BruteForce(string text, string pattern);
	static int RabinKarp(string text, string pattern);
	static int KnuthMorrisPatt(string text, string pattern);
	static int BoyerMoore(string text, string pattern);
};

