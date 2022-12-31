#include "node.h"

int main() {
	NODE* n = createNode(9);

	List* l = createList(n);
	cout << "Current list:\n";
	printList(l);
	cout << "addHead(1)\n";
	addHead(l, 1);
	printList(l);
	addHead(l, 3);
	addHead(l, 4);
	addHead(l, 2);
	addHead(l, 5);
	cout << "After addHead() a few numbers:\n";
	printList(l);
	addTail(l, 6);
	cout << "After addTail(6):\n";
	printList(l);
	cout << "After removeHead(l)\n";
	removeHead(l);
	printList(l);
	cout << "After removeTail(l)\n";
	removeTail(l);
	printList(l);
	cout << "After addAfter(l, 15, 3) - add 15 after 3\n";
	addAfter(l, 15, 3);
	printList(l);
	cout << "After addAfter(l, 16, 11) - add 16 after 11\n";
	cout << "As 11 does not exist, do nothing\n";
	addAfter(l, 16, 11);
	printList(l);

	cout << "After removeAfter(l, 15) - remove the number after 15\n";
	removeAfter(l, 15);
	printList(l);
	cout << "After removeAfter(l, 13) - remove the number after 13\n";
	cout << "As 13 does not exist, do nothing\n";
	removeAfter(l, 13);
	printList(l);



	return 0;
}
