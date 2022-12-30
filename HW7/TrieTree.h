#pragma once
#include "Libraries.h"

typedef struct TrieNode* tref;
struct TrieNode {
	int ID;					// If ID != 0 -> It is the last char of word
	TrieNode* next[26];
};

TrieNode* getNode();
bool isLeaf(tref node);
void getAllWordsInDictionary(TrieNode* Dic, vector<string>& result, string& word);
void displayVector(vector<string> obj);
void releaseMemory(TrieNode*& Dic);

//-------------------------------//

void Insert(TrieNode*& Dic, string word, int ID);
void createTrie(TrieNode*& Dic, string dicFile);
int lookUp(TrieNode* Dic, string word);
vector<string> lookUpPrefix(TrieNode* Dic, string prefix);
void Remove(TrieNode*& Dic, string word, int depth = 0);