#pragma once
#include <iostream>
using namespace std;
struct NODE {
	int key;
	NODE* p_next;
};
struct List {
	NODE* p_head;
	NODE* p_tail;
};
NODE* createNode(int data);
List* createList(NODE* p_node);
bool addHead(List*& l, int data);
bool addTail(List*& l, int data);
void removeHead(List*& l);
void removeTail(List*& l);
bool addAfter(List*& l, int data, int val);
void removeAfter(List*& l, int val);
void printList(List* l);

