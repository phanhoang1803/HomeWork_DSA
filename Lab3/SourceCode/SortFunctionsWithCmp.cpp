#include "SortFunctionsWithCmp.h"
#include <math.h>
#include "FuncsSupportSort.h"
//---------------------------------------------------------------//
unsigned long long  selectionSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	nCmp += n - 1 + 1;
	
	for (int i = 0;  i < n - 1; i++) {
		int  posMin = i;
		nCmp += (n - (i + 1)) + 1;
		for (int j = i + 1; j < n; j++) {
			if (++nCmp && a[j] < a[posMin])
				posMin = j;
		}
		swap(a[posMin], a[i]);
	}

	return nCmp;
}

unsigned long long  insertionSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	nCmp += n - 1 + 1;
	for (int i = 1; ++nCmp && i < n; i++) {
		int  tmp = a[i];
		int j = i - 1;

		while (++nCmp && j >= 0 && ++nCmp && tmp < a[j]) {
			a[j + 1] = a[j];
			j--;
		}

		a[j + 1] = tmp;
	}

	return nCmp;
}

unsigned long long  bubbleSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	nCmp += n - 1 - 0 + 1;
	for (int i = 0; i < n - 1; i++)
		for (int j = n - 1; ++nCmp && j > i; j--)
			if (++nCmp && a[j] < a[j - 1])
				swap(a[j], a[j - 1]);
		
	return nCmp;
}

unsigned long long  shakerSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	int  l = 0, r = n - 1, flag = 0;
	while (++nCmp&& l < r) {
		nCmp += r - l + 1;
		for (int i = l;  i < r; i++)
			if (++nCmp && a[i] > a[i + 1]) {
				swap(a[i], a[i + 1]);
				flag = i;
			}
		r = flag;

		nCmp += r - l + 1;
		for (int i = r;  i > l; i--)
			if (++nCmp&& a[i] < a[i - 1]) {
				swap(a[i], a[i - 1]);
				flag = i;
			}
		l = flag;
	}

	return nCmp;
}

unsigned long long  shellSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	for (int gap = n / 2; ++nCmp && gap > 0; gap /= 2)
	{
		nCmp += n - gap + 1;
		for (int i = gap; i < n; i += 1)
		{
			int  temp = a[i];

			int  j;
			for (j = i; ++nCmp && j >= gap && ++nCmp && a[j - gap] > temp; j -= gap)
				a[j] = a[j - gap];

			a[j] = temp;
		}
	}

	return nCmp;
}

unsigned long long  heapSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	int  l = n / 2, r = n - 1;
	// Tạo heap
	while (++nCmp && l >= 1) {
		sift(a, l, r, nCmp);
		l--;
	}

	// Đưa phần tử nhỏ nhất (lớn nhất về cuối) - Tiếp tục tạo heap trong phần còn lại - ....
	while (++nCmp && r >= 1) {
		swap(a[0], a[r]);
		sift(a, 0, --r, nCmp);
	}

	return nCmp;

}

unsigned long long  mergeSortCmp(int  a[], int  begin, int  end) {
	unsigned long long  nCmp = 0;

	if (++nCmp && begin >= end)
		return nCmp;

	int  mid = begin + (end - begin) / 2;

	int  s1 = mid - begin + 1, s2 = end - mid;
	int* a1 = copyArray(a, s1), * a2 = copyArray(a + s1, s2);

	nCmp += mergeSortCmp(a1, begin, mid);
	nCmp += mergeSortCmp(a2, mid + 1, end);
	merge(a, a1, s1, a2, s2, nCmp);

	delete[]a1;
	delete[]a2;

	return nCmp;
}

unsigned long long  quickSortCmp(int  a[], int  l, int  r) {
	unsigned long long  nCmp = 0;

	if (l < r) {
		int  s = partition(a, l, r, nCmp);
		nCmp += quickSortCmp(a, l, s - 1);
		nCmp += quickSortCmp(a, s + 1, r);
	}

	return nCmp;
}

unsigned long long  coutingSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	int* b = new int[n];
	int  min = a[0], max = a[0];

	// Tìm Min và Max của mảng
	nCmp += n - 0 + 1;
	for (int i = 0; i < n; i++) {
		if (++nCmp && a[i] < min)
			min = a[i];
		if (++nCmp && a[i] > max)
			max = a[i];
	}

	// Tạo mảng tần số [min -> max]
	int  sizeF = max - min + 1;
	int* f = new int[sizeF];
	nCmp += sizeF - 0 + 1;
	for (int i = 0; i < sizeF; i++) {
		f[i] = 0;
	}

	// Đếm số lần xuất hiện của số x (f[x]) trong mảng a

	nCmp += n - 0 + 1;
	for (int i = 0; i < n; i++) {
		f[a[i] - min]++;
	}

	// Số phần tử có trong mảng a <= a[i] || Hay f[i] là số phần tử trong mảng a <= a[i]
	nCmp += sizeF - 1 + 1;
	for (int i = 1; i < sizeF; i++) {
		f[i] += f[i - 1];
	}

	// Ý tưởng:
	// Tạo mảng tần số [min; max]: 0 0 0 0 0 0 0 0
	// Đếm số lần xuất hiện a[i]: f[a[i]]
	// Tính số phần tử <= a[i] (kể cả a[i]): f[a[i]]
	// -> Vị trí của a[i] là: f[a[i]] - 1.

	nCmp += n - 0 + 1;
	for (int i = n - 1; i >= 0; i--) {
		b[f[a[i] - min] - 1] = a[i];
		f[a[i] - min]--;
	}

	nCmp += n - 0 + 1;
	for (int i = 0; i < n; i++) {
		a[i] = b[i];
	}

	delete[]b;
	delete[]f;

	return nCmp;

}

unsigned long long  radixSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	int  max = a[0];
	nCmp += n - 1 + 1;
	for (int i = 1; i < n; i++) {
		if (++nCmp && a[i] > max)
			max = a[i];
	}

	for (int i = 0; ++nCmp && i < (int)log10(max) + 1; i++) {
		subRadixSort(a, n, i, nCmp);
	}

	return nCmp;
}

unsigned long long  flashSortCmp(int  a[], int  n) {
	unsigned long long  nCmp = 0;

	int  min = a[0], max = a[0];
	nCmp += n - 1 + 1;
	for (int i = 1; i < n; i++) {
		if (++nCmp && a[i] > max)
			max = a[i];
		if (++nCmp && a[i] < min)
			min = a[i];
	}

	// Chia thành m lô [0, m-1]
	int  m = 0.43 * n;
	int* L = new int[m];
	nCmp += m - 0 + 1;
	for (int i = 0; i < m; L[i++] = 0);

	// Đếm số phần tử mỗi lô
	nCmp += n - 0 + 1;
	for (int i = 0; i < n; i++) {
		long long k = (long long)(m - 1) * (a[i] - min) / (max - min);
		L[k]++;
	}

	// L[k] - 1 là chỉ mục của phần tử cuối cùng của phân vùng k
	nCmp += m - 1 + 1;
	for (int k = 1; k < m; k++) {
		L[k] += L[k - 1];
	}

	// Phần tử chưa đúng vùng là phần tử có chỉ số i <= L[k] - 1
	long long k = m - 1;
	int i = 0, nImp = 0, x;
	while (++nCmp && nImp < n - 1) {
		// 
		while (++nCmp && i > L[k] - 1) {
			i++;
			k = (long long)(m - 1) * (a[i] - min) / (max - min);
		}

		x = a[i];
		while (++nCmp && i <= L[k] - 1) {
			k = (long long)(m - 1) * (x - min) / (max - min);
			int  tmp = a[L[k] - 1];
			a[L[k] - 1] = x;
			x = tmp;
			L[k]--;
			nImp++;
		}
	}

	// Insertion sort
	nCmp += n - 1 + 1;
	for (int i = 1; i < n; i++) {
		int  tmp = a[i];
		int  j = i - 1;
		while (++nCmp && j >= 0 && ++nCmp && a[j] > tmp) {
			a[j + 1] = a[j];
			j--;
		}
		a[j + 1] = tmp;
	}

	delete[]L;

	return nCmp;
}
