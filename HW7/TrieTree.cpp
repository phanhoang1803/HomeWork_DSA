#include "TrieTree.h"


TrieNode* getNode() {
	TrieNode* node = new TrieNode;
	node->ID = 0;
	for (int i = 0; i < 26; i++)
		node->next[i] = NULL;
	return node;
}

bool isLeaf(tref node) {
	// A node is a leaf node when it has no children.
	for (int i = 0; i < 26; i++)
		if (node->next[i] != NULL)
			return false;

	return true;
}
void getAllWordsInDictionary(TrieNode* Dic, vector<string>& result, string& word){
	if (!Dic)
		return;

	if (Dic->ID != 0) // If is end character of word -> push
		result.push_back(word);

	if (isLeaf(Dic))
		return;

	for (int i = 0; i < 26; i++)
		if (Dic->next[i]) {
			// Backtracking
			word.push_back(i + 'a');
			getAllWordsInDictionary(Dic->next[i], result, word);
			word.pop_back();
		}
}

void displayVector(vector<string> obj) {
	for (int i = 0; i < obj.size(); i++)
		cout << i + 1 << ": " << obj[i] << endl;
}

void releaseMemory(TrieNode*& Dic) {
	if (!Dic)
		return;

	if (isLeaf(Dic)) {
		delete Dic;
		Dic = NULL;
		return;
	}

	for (int i = 0; i < 26; i++)
		releaseMemory(Dic->next[i]);

	// After delete all subtrees,
	// we need to delete the root.
	delete Dic;
	Dic = NULL;
}


//-------------------------------//

void Insert(TrieNode*& Dic, string word, int ID) {
	// TrieTree just display words that have characters lowercase alphabet.
	string pattern = "[a-z]*";
	if (!regex_match(word, regex(pattern)))
		return;

	if (!Dic)
		Dic = getNode();

	TrieNode* current = Dic;
	for (int i = 0; i < word.size(); i++) {
		// If there is no word[i] -> add word[i],
		// and then move to word[i]
		if (current->next[word[i] - 'a'] == NULL)
			current->next[word[i] - 'a'] = getNode();
		current = current->next[word[i] - 'a'];
	}

	current->ID = ID;
}
void createTrie(TrieNode*& Dic, string dicFile) {
	if (!Dic)
		Dic = getNode();

	// Read file.
	ifstream is;
	is.open(dicFile);

	// If cann't open file, exit.
	if (is.fail()) {
		cerr << "Error: " << dicFile << " doesn't exist.\n";
		return;
	}

	// Format each line: word ID
	string word;
	int ID;
	// Read data and insert data into the TrieTree
	while (!is.eof()) {
		is >> word;
		is >> ID;
		Insert(Dic, word, ID);
	}

	is.close();
}
int lookUp(TrieNode* Dic, string word) {
	if (!Dic)
		return 0;	// return ID = 0, that is not the end character of the word.

	TrieNode* current = Dic;
	for (int i = 0; i < word.size(); i++) {
		// If doesn't exist word[i], return 0.
		if (current->next[word[i] - 'a'] == NULL) 
			return 0;
		current = current->next[word[i] - 'a'];
	}

	// Word exist.
	return current->ID;
}

vector<string> lookUpPrefix(TrieNode* Dic, string prefix) {
	vector<string> res;

	if (!Dic)
		return res;

	TrieNode* current = Dic;
	int i = 0;
	int sizeOfPrefix = prefix.size();
	// Move to the leaf of prefix word.
	for (; i < sizeOfPrefix && current != NULL; i++) 
		current = current->next[prefix[i] - 'a'];

	// The above loop stop when (i == sizeOfPrefix || current == NULL)
	if (i == sizeOfPrefix) { // i.e: exist words that have this prefix in the TrieTree
		string word = "";

		// Current node is leaf of prefix.
		// Get all words in the dictionary with root = current.
		getAllWordsInDictionary(current, res, word);
		
		// Print prefix + word of TrieTree(root = current).
		for (int i = 0; i < res.size(); i++)
			res[i] = prefix + res[i];
	}

	return res;
}
void Remove(TrieNode*& Dic, string word, int depth) {
	if (!Dic)
		return;

	// If this position is the end of word. We delete.
	if (depth == word.size()) {
		Dic->ID = 0;		// Delete word.

		// If we have come to the leaves, we need to release memory.
		if (isLeaf(Dic)) {
			delete Dic;
			Dic = NULL;	
		}

		return;
	}

	// Delete all characters except for the first char of word.
	Remove(Dic->next[word[depth] - 'a'], word,depth + 1);

	// Delete the first char of word
	// if this character is a leaf or not the end character of the word.
	if (isLeaf(Dic) && Dic->ID == 0) {
		delete Dic;
		Dic = NULL;
	}
}