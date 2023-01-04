#include "FuncsSupportSort.h"
#include <iostream>

void swap(int& num1, int& num2) {
	int  tmp = num1;
	num1 = num2;
	num2 = tmp;
}

int* copyArray(int* a, int  size) {
	if (size <= 0)
		return nullptr;

	int* b = new int[size];
	for (int i = 0; i < size; b[i++] = a[i]);

	return b;
}

void printArray(int  a[], int  size) {
	for (int i = 0; i < size; i++)
		std::cout << a[i] << " ";
}

void sift(int  a[], int  l, int  r) {
	int  i = l, j = 2 * i + 1, x = a[i];
	while (j <= r) {
		if (j < r)
			if (a[j] < a[j + 1])
				j++;
		if (x >= a[j])
			break;
		swap(a[i], a[j]);
		i = j;
		j = 2 * i + 1;
	}
}
void sift(int  a[], int  l, int  r, unsigned long long& nCmp) {
	int  i = l, j = 2 * i + 1, x = a[i];
	while (++nCmp && j <= r) {
		if (++nCmp && j < r)
			if (++nCmp && a[j] < a[j + 1])
				j++;
		if (++nCmp && x >= a[j])
			break;
		swap(a[i], a[j]);
		i = j;
		j = 2 * i + 1;
	}
}

int  partition(int  a[], int  l, int  r) {
	int pivot = a[l + (r - l)/2];

	int count = 0;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = l + count;
	swap(a[pivotIndex], a[l]);

	// Sorting left and right parts of the pivot element
	int i = l, j = r;

	while (i < pivotIndex && j > pivotIndex) {

		while (a[i] <= pivot) {
			i++;
		}

		while (a[j] > pivot) {
			j--;
		}
		if (i < pivotIndex && j > pivotIndex) {
			swap(a[i++], a[j--]);
		}
	}

	return pivotIndex;
}

int  partition(int  a[], int l, int r, unsigned long long& nCmp) {
	int pivot = a[l + (r - l) / 2];

	int count = 0;
	nCmp += r - l + 1;
	for (int i = l + 1; i <= r; i++) {
		if (a[i] <= pivot)
			count++;
	}

	// Giving pivot element its correct position
	int pivotIndex = l + count;
	swap(a[pivotIndex], a[l]);

	// Sorting left and right parts of the pivot element
	int i = l, j = r;

	while (++nCmp && i < pivotIndex && ++nCmp && j > pivotIndex) {

		while (++nCmp && a[i] <= pivot) {
			i++;
		}

		while (++nCmp && a[j] > pivot) {
			j--;
		}
		if (++nCmp && i < pivotIndex && ++nCmp && j > pivotIndex) {
			swap(a[i++], a[j--]);
		}
	}

	return pivotIndex;
}

void merge(int* a, int* a1, int  s1, int* a2, int  s2) {
	int  i = 0, j = 0, k = 0;
	while (i < s1 && j < s2) {
		a[k++] = a1[i] < a2[j] ? a1[i++] : a2[j++];
	}

	while (i < s1) {
		a[k++] = a1[i++];
	}

	while (j < s2) {
		a[k++] = a2[j++];
	}
}
void merge(int* a, int* a1, int  s1, int* a2, int  s2, unsigned long long& nCmp) {
	int  i = 0, j = 0, k = 0;
	while (++nCmp && i < s1 && ++nCmp && j < s2) {
		++nCmp;
		a[k++] = a1[i] < a2[j] ? a1[i++] : a2[j++];
	}

	while (++nCmp && i < s1) {
		a[k++] = a1[i++];
	}

	while (++nCmp && j < s2) {
		a[k++] = a2[j++];
	}
}

int  digit(int  n, int  k) {
	int  res = 0;
	for (int i = 0; i <= k; i++) {
		res = n % 10;
		n /= 10;
	}
	return res;
}

void subRadixSort(int* a, int  n, int  k) {
	int  f[10] = { 0 };
	int* b = new int[n];

	for (int i = 0; i < n; i++)
		f[digit(a[i], k)]++;

	for (int i = 1; i < 10; i++)
		f[i] += f[i - 1];

	for (int i = n - 1; i >= 0; i--) {
		int  j = digit(a[i], k);
		b[f[j] - 1] = a[i];
		f[j]--;
	}

	for (int i = 0; i < n; a[i++] = b[i]);

	delete[]b;
}
void subRadixSort(int* a, int  n, int  k, unsigned long long& nCmp) {
	int  f[10] = { 0 };
	int* b = new int[n];

	for (int i = 0; ++nCmp && i < n; i++)
		f[digit(a[i], k)]++;

	for (int i = 1; ++nCmp && i < 10; i++)
		f[i] += f[i - 1];

	for (int i = n - 1; ++nCmp && i >= 0; i--) {
		int  j = digit(a[i], k);
		b[f[j] - 1] = a[i];
		f[j]--;
	}

	for (int i = 0; ++nCmp && i < n; a[i++] = b[i]);

	delete[]b;
}
