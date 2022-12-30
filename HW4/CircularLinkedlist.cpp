#include "node.h"

int main() {
	NODE* n = createNode(9);

	List* l = createList(n);
	cout << "List hien tai:\n";
	printList(l);
	cout << "addHead(1)\n";
	addHead(l, 1);
	printList(l);
	addHead(l, 3);
	addHead(l, 4);
	addHead(l, 2);
	addHead(l, 5);
	cout << "Sau khi add Head 1 vai so:\n";
	printList(l);
	addTail(l, 6);
	cout << "Sau khi addTail(6):\n";
	printList(l);
	cout << "Sau khi removeHead(l)\n";
	removeHead(l);
	printList(l);
	cout << "Sau khi removeTail(l)\n";
	removeTail(l);
	printList(l);
	cout << "Sau khi addAfter(l, 15, 3), them 15 sau 3\n";
	addAfter(l, 15, 3);
	printList(l);
	cout << "Sau khi addAfter(l, 16, 11), them 16 sau 11\n";
	cout << "Vi khong co 11 nen khong lam gi\n";
	addAfter(l, 16, 11);
	printList(l);

	cout << "Sau khi removeAfter(l, 15), xoa so sau 15\n";
	removeAfter(l, 15);
	printList(l);
	cout << "Sau khi removeAfter(l, 13), xoa so sau 13\n";
	cout << "Vi khong co 13 nen khong lam gi\n";
	removeAfter(l, 13);
	printList(l);



	return 0;
}
