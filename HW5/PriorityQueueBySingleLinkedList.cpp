#define _CRT_SECURE_NO_WARNINGS

#include "PriorityQueueBySingleLinkedList.h"

pref getNode(const char* ID, int priority) {
	static int countOrder = -1;

	pref p = new node{ NULL, countOrder++, priority, NULL };

	if (!ID)
		return p;

	p->ID = _strdup(ID);

	return p;
}

void initPQBSLL(PQBSLL& p) {
	// Initialize a fake node.
	p.head = getNode("", -1);
}

void PrintPriorityQueue(PQBSLL p) {
	cout << "Priority queue:\n";
	int i = 0;
	for (pref p1 = p.head->next; p1; p1 = p1->next)
		cout << "\t" << i++ << ". ID = " << p1->ID <<", Order = " << p1->order << ", Priority = " << p1->priority << "\n";
}

void DemoPQBySingleLinkedList() {
	PQBSLL p;
	initPQBSLL(p);
	int prior;
	int order = 0;
	char ID[256];

	cout << "\tThe program demo functions in priority queue using SINGLE LINKED LIST.\n";
	cout << "\tATTENTION: The element with lower priority value is higher priority.\n";

	cout << "\nInsert priority queue. (Enter priority = 0 to quit).\n\n";
	while (1) {
		cout << "Element " << order++ << ": " << endl;

		cout << "\tID = ";
		cin >> ws;
		scanf("%[^\n]s", ID);

		cout << "\tPriority = ";
		cin >> ws;
		cin >> prior;

		if (prior == 0)
			break;

		Insert(p, ID, prior);

		//free(ID);
	}
	PrintPriorityQueue(p); cout << endl;

	// Extract
	pref res = Extract(p);
	free(res->ID); delete res;
	cout << "After extracting. ";
	PrintPriorityQueue(p); cout << endl;

	// Remove
	cout << "Enter ID of the element you want to remove.\n\tID = ";
	cin >> ws;
	scanf("%[^\n]s", ID);
	Remove(p, ID);
	cout << "After removing the element have ID(" << ID << "). ";
	PrintPriorityQueue(p); cout << endl;

	// Change priority
	cout << "Enter information of the element you want to change priority.\n\tID = ";
	cin >> ws;
	scanf("%[^\n]s", ID);
	cout << "\tPriority = ";
	cin >> prior;
	changePriority(p, ID, prior);
	cout << "After changing the priority of the element have ID(" << ID << "). ";
	PrintPriorityQueue(p); cout << endl;
}

void releaseMemory(PQBSLL& p) {
	if (isEmpty(p))
		return;

	pref head = p.head;
	p.head = NULL;

	while (head != NULL) {
		pref tmp = head;

		head = head->next;

		free(tmp->ID);
		delete tmp;
	}
}

bool isEmpty(PQBSLL p) {
	return p.head->next == NULL;
}

void Insert(PQBSLL p, const char* ID, int priority) {
	pref tmp = getNode(ID, priority);

	// p2 is always the previous node of p1
	pref p2 = p.head, p1 = p2->next;

	for (; p1; p2 = p2->next, p1 = p1->next)
		if (priority < p1->priority) {
			// Connect and then return
			p2->next = tmp;
			tmp->next = p1;

			return;
		}
	
	// If this priority is smallest -> push it at the end of the queue.
	if (!p1)
		p2->next = tmp;
}

pref Extract(PQBSLL p) {
	if (isEmpty(p))
		return NULL;

	pref res = p.head->next;
	p.head->next = p.head->next->next;

	return res;
}
bool Remove(PQBSLL p, const char* ID) {
	// p2 is always the previous node of p1
	pref p2 = p.head, p1 = p.head->next;

	// Search the ID
	for (; p1; p2 = p2->next, p1 = p1->next)
		if (strcmp(p1->ID, ID) == 0)
			break;

	// If this ID exist in the priority queue.
	// Delete
	if (p1) {
		p2->next = p1->next;

		free(p1->ID);
		delete p1;

		return true;
	}

	return false;
}

void changePriority(PQBSLL& p, const char* ID, int priority) {
	// p2 is always the previous node of p1
	pref p2 = p.head, p1 = p.head->next;

	pref changed = nullptr; // The node is changed the priority.
	for (; p1; p2 = p2->next, p1 = p1->next)
		if (strcmp(p1->ID, ID) == 0) {
			// Remove the changed node from the priority queue.
			p1->priority = priority;
			changed = p1;
			p2->next = p1->next;
			changed->next = NULL;

			break;
		}

	// If this queue doesn't exist ID -> return
	if (!p1)	
		return;

	// Insert the changed node into the priority queue.
	p2 = p.head, p1 = p.head->next;
	for (; p1; p2 = p2->next, p1 = p1->next)
		if (changed->priority < p1->priority) { 
			changed->next = p1;
			p2->next = changed;
			return;
		}

	// If this priority is smallest -> push it at the end of the queue.
	if (!p1)
		p2->next = changed;
}