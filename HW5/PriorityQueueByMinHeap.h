#pragma once
#include "Libraries.h"

struct Information{
	string ID;
	int order;
	int priority;
};

struct PQBMH {
	vector<Information> heap;
};

template <class T>
void swap1(T& a, T& b);

void PrintPriorityQueue(PQBMH p);
void DemoPQByMinHeap();

void MinHeapify(vector<Information>& heap, int l, int r);
void IncreasingHeap(vector<Information>& heap, int i);

int Search(vector<Information> heap, string ID);
bool isEmpty(PQBMH p);
void Insert(PQBMH& p, string ID, int priority);
Information Extract(PQBMH& p);
bool Remove(PQBMH& p, string ID);
void changePriority(PQBMH& p, string ID, int priority);