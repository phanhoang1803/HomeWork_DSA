#pragma once
#include "Libraries.h"

typedef struct node* pref;
struct node {
	char* ID;
	int order;
	int priority;
	pref next;
};

struct PQBSLL { // Priority Queue By Single Linked List
	pref head;
};

pref getNode(const char* ID, int priority);
void initPQBSLL(PQBSLL& p);
void PrintPriorityQueue(PQBSLL p);
void DemoPQBySingleLinkedList();
void releaseList(PQBSLL& p);

bool isEmpty(PQBSLL p);
void Insert(PQBSLL p, const char* ID, int priority);
pref Extract(PQBSLL p);
bool Remove(PQBSLL p, const char* ID);
void changePriority(PQBSLL& p, const char* ID, int priority);

