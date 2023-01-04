#include "SortFunctions.h"
#include "FuncsSupportSort.h"
#include <iostream>

//---------------------------------------------------------------//

void selectionSort(int  a[], int  n) {
	for (int i = 0; i < n - 1; i++) {
		int  posMin = i;
		for (int j = i + 1; j < n; j++) {
			if (a[j] < a[posMin])
				posMin = j;
		}
		swap(a[posMin], a[i]);
	}
}

void insertionSort(int  a[], int  n) {
	for (int i = 1; i < n; i++) {
		int  tmp = a[i];
		int  j = i - 1;

		while (j >= 0 && tmp < a[j]) {
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = tmp;
	}
}

void bubbleSort(int  a[], int  n) {
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; j > i; j--)
			if (a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
}

void shakerSort(int  a[], int  n) {
	int  l = 0, r = n - 1, flag = 0;
	while (l < r) {
		for (int i = l; i < r; i++)
			if (a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				flag = i;
			}
		r = flag;
		for (int i = r; i > l; i--)
			if (a[i] < a[i - 1]) {
				swap(a[i], a[i - 1]);
				flag = i;
			}
		l = flag;
	}
}

void shellSort(int  a[], int  n) {
	for (int gap = n / 2; gap > 0; gap /= 2)
	{
		for (int i = gap; i < n; i += 1)
		{
			int  temp = a[i];
			
			int  j;
			for (j = i; j >= gap && a[j - gap] > temp; j -= gap)
				a[j] = a[j - gap];

			a[j] = temp;
		}
	}
}

void heapSort(int  a[], int  n) {
	int  l = n / 2, r = n - 1;
	// Tạo heap
	while (l >= 0) {
		sift(a, l, r);
		l--;
	}

	// Đưa phần tử nhỏ nhất (lớn nhất về cuối) - Tiếp tục tạo heap trong phần còn lại - ....
	while (r >= 1) {
		swap(a[0], a[r]);
		sift(a, 0, --r);
	}
}

void mergeSort(int  a[], int  begin, int  end) {
	if (begin >= end)
		return;

	int  mid = begin + (end - begin) / 2;

	int  s1 = mid - begin + 1, s2 = end - mid;
	int* a1 = copyArray(a, s1), * a2 = copyArray(a + s1, s2);

	mergeSort(a1, begin, mid);
	mergeSort(a2, mid + 1, end);
	merge(a, a1, s1, a2, s2);

	delete[]a1;
	delete[]a2;
}

void quickSort(int  a[], int  l, int  r) {
	if (l < r) {
		int  s = partition(a, l, r);
		quickSort(a, l, s - 1);
		quickSort(a, s + 1, r);
	}
}

void coutingSort(int  a[], int  n) {
	int* b = new int[n];
	int  min = a[0], max = a[0];

	// Tìm Min và Max của mảng
	for (int i = 0; i < n; i++) {
		if (a[i] < min)
			min = a[i];
		if (a[i] > max)
			max = a[i];
	}

	// Khởi tạo mảng tần số [min -> max]
	int  sizeF = max - min + 1;
	int* f = new int[sizeF];
	for (int i = 0; i < sizeF; i++)
		f[i] = 0;

	// Đếm số lần xuất hiện của số x (f[x]) trong mảng a
	for (int i = 0; i < n; i++)
		f[a[i] - min]++;

	// Số phần tử có trong mảng a <= a[i] || Hay f[i] là số phần tử trong mảng a <= a[i]
	for (int i = 1; i < sizeF; i++)
		f[i] += f[i - 1];

	// Đưa các phần tử vào đúng vị trí của nó
	for (int i = n - 1; i >= 0; i--) {
		b[f[a[i] - min] - 1] = a[i];
		f[a[i] - min]--;
	}

	// Copy về lại mảng a
	for (int i = 0; i < n; i++)
		a[i] = b[i];

	delete[]b;
	delete[]f;
}

void radixSort(int  a[], int  n) {
	int  max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max)
			max = a[i];
	}

	for (int i = 0; i < (int)log10(max) + 1; i++) {
		subRadixSort(a, n, i);
	}
}

void flashSort(int a[], int n) {
	int  min = a[0], max = a[0];
	for (int i = 1; i < n; i++) {
		if (a[i] > max)
			max = a[i];
		if (a[i] < min)
			min = a[i];
	}

	// Chia thành m lô [0, m-1]
	int  m = 0.43 * n;
	int* L = new int[m];
	for (int i = 0; i < m; i++)
		L[i] = 0;

	// Đếm số phần tử mỗi lô
	for (int i = 0; i < n; i++) {
		long long k = (long long)(m - 1) * (a[i] - min) / (max - min);
		//std::cout << k << std::endl;
		L[k]++;
	}

	// L[k] - 1 là chỉ mục của phần tử cuối cùng của phân vùng k
	for (int k = 1; k < m; k++) {
		L[k] += L[k - 1];
	}
	// Phần tử chưa đúng vùng là phần tử có chỉ số i <= L[k] - 1
	// swap(a[0], a[max]);
	long long k = m - 1;
	int nImp = 0, i = 0, x;
	while (nImp < n - 1) {
		while (i > L[k] - 1) {
			i++;
			k = (long long)(m - 1) * (a[i] - min) / (max - min);
		}

		x = a[i];
		while (i <= L[k] - 1) {
			k = (long long)(m - 1) * (x - min) / (max - min);
			int  tmp = a[L[k] - 1];
			a[L[k] - 1] = x;
			x = tmp;
			L[k]--;	
			nImp++;
		}
	}

	// Insertion sort
	for (int i = 1; i < n; i++) {
		int  tmp = a[i];
		int  j = i - 1;
		while (j >= 0 && a[j] > tmp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}	

	delete[]L;
}