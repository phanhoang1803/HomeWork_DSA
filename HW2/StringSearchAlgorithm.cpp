#include "StringSearchAlgorithm.h"

int StringSearchAlgorithm::BruteForce(string text, string pattern) {
	int count = 0, n = text.size(), m = pattern.size();

	for (int i = 0; i < n - m + 1; i++) {
		int j = 0;
		for (; j < m; j++)
			if (text[j + i] != pattern[j])
				break;
		
		// If no characters are different
		// the loop exits when the loop condition is false, i.e: j == m.
		if (j == m)
			count++;
	}

	return count;
}

int StringSearchAlgorithm::RabinKarp(string text, string pattern) {
	int count = 0;

	int d = 256; // 256 characters
	int q = d; // A prime number

	int n = text.size(), m = pattern.size();

	// If number of characters in the text is less than in the pattern,
	// of course, doesn't exist pattern in the text.
	if (n < m) 
		return 0;

	unsigned long long hs = 0; // Hash value of text
	unsigned long long hp = 0; // Hash value of pattern
	
	// Preprocessing.

	// Calculate pow(d, m-1) % q
	int powValue = 1; 
	for (int i = 0; i < m - 1; i++)
		powValue = (powValue * d) % q;

	// Calculate hash value of text[0, m - 1], and hash value of the pattern.
	for (int i = 0; i < m; i++) {
		hs = (hs * d + text[i]) % q;
		hp = (hp * d + pattern[i]) % q;
	}

	// Rabin-Karp algorithm.
	for (int i = 0; i < n - m + 1; i++) {
		if (hs == hp) {
			// Same the Brute-Force algorithm.
			int j = 0;

			for (; j < m; j++)
				if (pattern[j] != text[j + i])
					break;
			
			if (j == m)
				count++;
		}

		// Calculate hash value of text[i + 1, i + m].
		if (i < n - m) {
			hs = (d * (hs - powValue * text[i]) + text[i + m]) % q;
			if (hs < 0)
				hs += q;
		}
	}

	return count;
}


int StringSearchAlgorithm::KnuthMorrisPatt(string text, string pattern) {
	int count = 0;

	int n = text.size(), m = pattern.size();
	int i = 0;

	// Preprocessing

	// Compute the table

	// LPS[i] = max{length of proper prefix == length of proper suffix of the pattern[0...i]}
	int* LPS = new int[m]; 
	// Index:         0 1 2 3 4
	// Pattern:		  a b a b a
	
	// Example 1: index = 3 -> pattern[0..3] = a b a b
	// These proper prefix	: a b a > a b > a
	//				suffix	: b a b > a b > b
	//	=>	LPS[3] = 2			      here
	
	// Example 2: index = 4 -> pattern[0..4] = a b a b a
	// These proper prefix	: a b a b > a b a > a b > a
	//				suffix	: b a b a > a b a > b a > a
	//	=>	LPS[4] = 3				    here

	// O(m)
	int j = 0;
	LPS[0] = 0;
	for (i = 1; i < m;)
		if (pattern[j] == pattern[i]) {
			LPS[i] = j + 1;
			i++;
			j++;
		}
		else
			if (j != 0)
				j = LPS[j - 1];
			else
				LPS[i++] = 0;
	
	//KMP Search
	j = 0; // Pattern index
	for (i = 0; i < n;) { // Text index
		if (text[i] == pattern[j]) {
			i++;
			j++;
		}
		else {
			if (j > 0) {
				j = LPS[j - 1];
			}
			else {
				i++;
			}
		}

		if (j == m) {
			count++;
			j = LPS[j - 1];
		}
	}

	delete[]LPS;

	return count;
}

int StringSearchAlgorithm::BoyerMoore(string text, string pattern) {
	int count = 0;
	int n = text.size(), m = pattern.size();

	// Set bad char heuristic
	int badChar[256];
	for (int i = 0; i < 256; i++)
		badChar[i] = -1;
	// The badChar array holds the position of the last character in the pattern.
	for (int i = 0; i < m; i++)
		badChar[(int)pattern[i]] = i;    
	
	// In this algorithm, we start compare from right to left for each character.
	int i = m - 1, j = m - 1;

	while (i < n) {
		// We decrease the iterator until there are different characters
		// or until the beginning of the pattern, mean: we have found a pattern in the text.
		if (text[i] == pattern[j]) {
			if (j == 0) {	// found a pattern
				count++;
				// we start the next iteration at the next character of 
				// the first character we traversed in the previous loop
				i += m;		
				j = m - 1;
			}
			else {
				i--;
				j--;
			}
		}
		else {
			// l stored the index of last character text[i] in the pattern
			int l = badChar[text[i]];

			// l == -1, that mean the text[i] doesn't exist in the pattern, 
			// so the next loop we should compare the text[i+1, ..., i+m]
			if (l == -1)
				i = i + m;
			else
				// l != -1, that mean the text[i] exist in the pattern,
				// so we should align the text[i]
				i = i + (m - j);

			j = m - 1;
		}
	}

	return count;
}