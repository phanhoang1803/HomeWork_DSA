#include "Demo.h"
#include <conio.h>

void printMenu() {
	cout << "\nSome features:\n";
	cout << "\t1. Create trie tree from file\n";
	cout << "\t2. Insert word\n";
	cout << "\t3. Look up a word\n";
	cout << "\t4. Look up prefix\n";
	cout << "\t5. Remove a word\n";
	cout << "\t6. Print all words in the trie tree\n";
	cout << "\tOther. Quit\n";
	cout << "Please enter your choice: ";
}

void demo() {
	cout << "Trie tree program.\n";

	string word = "";
	string empty = "";
	int ID = 0;
	string prefix = "";
	string dicFileName = "";
	vector<string> wordList;
	vector<string> wordListSearchPrefix;
	TrieNode* dic = NULL;
	int depth = 0;
	int choice = 0;

	while (1) {
		printMenu();
		cin >> choice;
		switch (choice)
		{
		case 1:
			cout << "\nEnter the file name of the dictionary: ";
			cin >> dicFileName;
			createTrie(dic, dicFileName);
			break;
		case 2:
			cout << "\n\tEnter a word need to insert: ";
			cin >> word;
			cout << "\tEnter ID                   : ";
			cin >> ID;
			Insert(dic, word, ID);
			break;
		case 3:
			cout << "\n\tEnter a word need to search: ";
			cin >> word;
			if (!lookUp(dic, word)) {
				cout << "The dictionary doesn't have this word.\n";
				break;
			}
			cout << "Word \"" << word << "\" has ID: " << lookUp(dic, word) << endl;
			break;
		case 4:
			cout << "\n\tEnter a prefix word need to search: ";
			cin >> prefix;
			wordListSearchPrefix = lookUpPrefix(dic, prefix);
			cout << "Word list have prefix \"" << prefix << "\" are:\n";
			displayVector(wordListSearchPrefix);
			break;
		case 5:
			cout << "\n\tEnter a word need to remove: ";
			cin >> word;
			Remove(dic, word, depth = 0);
			break;
		case 6:
			wordList.resize(0);
			getAllWordsInDictionary(dic, wordList, empty);
			cout << "\nAll words in the trie tree are:\n";
			displayVector(wordList);
			break;
		default:
			releaseMemory(dic);
			return;
		}
	}
}