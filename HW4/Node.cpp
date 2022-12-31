#include "Node.h"

NODE* createNode(int data) {
	NODE* p = new NODE;
	if (p == NULL)		//unable to allocate memory
		exit(0);
	p->key = data;
	p->p_next = NULL;
	return p;
}
List* createList(NODE* p_node) {
	List* l = new List;

	if (l == NULL)		//unable to allocate memory
		exit(0);
	//assgin the node as head and tail
	l->p_head = p_node;
	l->p_tail = p_node;
	//link tail->next to head to create circular list
	l->p_tail->p_next = l->p_head;
	return l;
}
bool addHead(List*& l, int data) {
	NODE* p_node = createNode(data);
	//if list is NULL
	if (l->p_head == NULL)
		return false;
	else {
		//list is already intialized
		p_node->p_next = l->p_head;
		l->p_tail->p_next = p_node;
		l->p_head = p_node;
	}
	return true;
}
bool addTail(List*& l, int data) {
	if (l->p_head == NULL)
		return false;
	else {
		//list is already intialized
		NODE* p = createNode(data);
		p->p_next = l->p_head;
		l->p_tail->p_next = p;
		l->p_tail = p;
	}
	return true;
}
void removeHead(List*& l) {
	if (l->p_head == NULL)
		//if list is empty
		return;
	else if (l->p_head == l->p_tail) {
		//if list has 1 node
		NODE* q = l->p_head;
		l->p_head = NULL;
		//delete the last node
		q->p_next = NULL;
		delete q;
	}
	else {
		//isolate the head
		l->p_tail->p_next = l->p_head->p_next;
		NODE* q = l->p_head;
		l->p_head = l->p_head->p_next;
		//deleting head by deleting q
		q->p_next = NULL;
		delete q;
	}

}
void removeTail(List*& l) {
	if (l->p_head == NULL)
		//if list is empty
		return;
	else if (l->p_head == l->p_tail) {
		//if list has 1 node
		NODE* q = l->p_head;
		l->p_head = NULL;
		//delete the last node
		q->p_next = NULL;
		delete q;
	}
	else {
		//isolate old p_tail
		NODE* q = l->p_tail;

		//find the node before p_tail
		NODE* run = l->p_head;
		while (run->p_next != l->p_tail)
			run = run->p_next;

		run->p_next = l->p_head;
		l->p_tail = run;
		//delete old p_tail after assigning successfully new p_t6il
		q->p_next = NULL;
		delete q;
	}

}
bool addAfter(List*& l, int data, int val) {

	if (l->p_head == NULL)
		return false;

	if (val == l->p_tail->key) {
		addTail(l, data);
		return true;
	}

	//find the node contains val
	NODE* run = l->p_head;
	while (run != l->p_tail && run->key != val)
		run = run->p_next;

	if (run == l->p_tail)
		//list does not contain val
		return false;
	else {
		//create a new node and add it
		NODE* q = createNode(data);
		q->p_next = run->p_next;
		run->p_next = q;
	}
}
void removeAfter(List*& l, int val) {
	if (l->p_head == NULL)
		return;
	//if the delete val is stored in the node previous tail
	if (val == l->p_tail->key)
		removeTail(l);

	//find the node contains val
	NODE* run = l->p_head;
	while (run != l->p_tail && run->key != val)
		run = run->p_next;

	//if the input val is equal to tail->data
	//cannot delete after tail
	if (run == l->p_tail)
		return;
	else {
		NODE* q = run->p_next;
		run->p_next = run->p_next->p_next;
		q->p_next = NULL;
		delete q;
	}

}
void printList(List* l) {
	if (!l->p_head)
		return;

	NODE* run = l->p_head;
	while (run != l->p_tail) {
		cout << run->key << " ";
		run = run->p_next;
	}
	cout << l->p_tail->key << endl;
}