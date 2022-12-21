#include "PriorityQueueByMinHeap.h"

// Left child : 2i + 1
// Right child: 2i + 2
// Parent     : i/2

template <class T>
void swap1(T& a, T& b) {
	T tmp = b;
	b = a;
	a = tmp;
}

void PrintPriorityQueue(PQBMH p) {
	cout << "Priority queue:\n";
	for (int i = 0; i < p.heap.size(); i++) {
		Information t = p.heap[i];
		cout << "\t" << i << ". ID = " << t.ID << ", Order = " << t.order << ", Priority = " << t.priority << ".\n";
	}
}

void DemoPQByMinHeap() {
	PQBMH p;
	string ID;
	int prior;
	int order = 0;

	cout << "\tThe program demo functions in priority queue using MIN-HEAP.\n";
	cout << "\tATTENTION: The element with lower priority value is higher priority.\n";

	cout << "\nInsert priority queue. (Enter priority = 0 to quit).\n\n";
	while (1) {
		cout << "Element " << order++ << ": " << endl;
		
		cout << "\tID = ";
		cin >> ws;
		getline(cin, ID);

		cout << "\tPriority = ";
		cin >> prior;
		if (prior == 0)
			break;

		Insert(p, ID, prior);
	}
	PrintPriorityQueue(p); cout << endl;

	/*Extract(p);
	cout << "After extracting. ";
	PrintPriorityQueue(p); cout << endl;*/

	while (1) {
		cout << "Enter ID of the element you want to remove.\n\tID = ";
		cin >> ws;
		getline(cin, ID);
		Remove(p, ID);
		cout << "After removing the element have ID(" << ID << "). ";
		PrintPriorityQueue(p); cout << endl;
	}

	/*cout << "Enter information of the element you want to change priority.\n\tID = ";
	cin >> ws;
	getline(cin, ID);
	cout << "\tPriority = ";
	cin >> prior;
	changePriority(p, ID, prior);
	cout << "After changing the priority of the element have ID(" << ID << "). ";
	PrintPriorityQueue(p); cout << endl;*/
}

void MinHeapify(vector<Information>& heap, int l, int r) {
	int i = l;
	int j = 2 * l + 1;

	while (j <= r) {
		if (j < r)
			if (heap[j + 1].priority < heap[j].priority) // Get index of the element has less priority value.
				j++;
		
		if (heap[i].priority <= heap[j].priority)
			return;
		
		swap1(heap[i], heap[j]);
		i = j;
		j = 2 * i + 1;
	}
}

void IncreasingHeap(vector<Information>& heap, int i) {
	int parent = (i - 1) / 2; // Index parent of i

	while (i > 0 && heap[i].priority < heap[parent].priority) {
		swap1(heap[i], heap[parent]);
		i = parent;
		parent = (i - 1) / 2;
	}
}

int Search(vector<Information> heap, string ID) {
	for (int i = 0; i < heap.size(); i++)
		if (heap[i].ID == ID)
			return i;
	return -1;
}

bool isEmpty(PQBMH p) {
	return p.heap.size() == 0;
}

void Insert(PQBMH& p, string ID, int priority) {
	int size = p.heap.size();
	//cout << size << endl;
	p.heap.push_back(Information{ ID, size, priority });

	// Fix the heap from the recently added element to top of the heap.
	IncreasingHeap(p.heap, size);
}

Information Extract(PQBMH& p) {
	if (isEmpty(p)) {
		cerr << "Error: Priority Queue is empty.\n";
		exit(1);
	}

	Information res = p.heap[0];
	int size = p.heap.size();

	// Swap first and last element, then we delete the last element.
	p.heap[0] = p.heap[size - 1];

	p.heap.pop_back(); 
	size--;

	// Fix the heap from top to bottom of the heap.
	MinHeapify(p.heap, 0, size - 1);

	return res;
}

bool Remove(PQBMH& p, string ID) {
	int loc = Search(p.heap, ID);

	// If doesn't exist element with this ID, return false.
	if (loc == -1)
		return false;

	int size = p.heap.size();

	// Swap first and last element, then we delete the last element.
	swap1(p.heap[loc], p.heap[size - 1]);
	p.heap.pop_back();
	size--;

	// Recreate heap.
	for (int i = size / 2 - 1; i >= 0; i--)
		MinHeapify(p.heap, i, size - 1);

	return true;
}

void changePriority(PQBMH& p, string ID, int priority) {
	int loc = Search(p.heap, ID);

	// If doesn't exist element with this ID, return.
	if (loc == -1)
		return;

	int oldPriority = p.heap[loc].priority;
	p.heap[loc].priority = priority;

	// If the priority is higher than the old one,
	// it must be pushed to the front of the heap
	// Otherwise, be pushed to the back.
	if (priority > oldPriority)
		MinHeapify(p.heap, loc, p.heap.size() - 1);
	else
		IncreasingHeap(p.heap, loc);
}