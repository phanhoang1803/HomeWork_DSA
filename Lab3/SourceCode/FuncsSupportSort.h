#pragma once

void swap(int& num1, int& num2);
int* copyArray(int* a, int  size);
void printArray(int  a[], int  size);

void sift(int  a[], int  l, int  r);
void sift(int  a[], int  l, int  r, unsigned long long& nCmp);

int  partition(int  a[], int  l, int  r);
int  partition(int  a[], int  l, int  r, unsigned long long& nCmp);

void merge(int* a, int* a1, int  s1, int* a2, int  s2);
void merge(int* a, int* a1, int  s1, int* a2, int  s2, unsigned long long& nCmp);

int  digit(int  n, int  k);

void subRadixSort(int* a, int  n, int  k);
void subRadixSort(int* a, int  n, int  k, unsigned long long& nCmp);

