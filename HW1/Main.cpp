#include <iostream>
#include <string.h>
#include <iomanip>
#include <string>

using namespace std;

// Examine the input syntax is valid or not.
bool isValid(int argc, char* argv[])
{
	for (int i = 1; i < argc; i++)
		for (int j = 0; j < strlen(argv[i]); j++)
			if (!('0' <= argv[i][j] && argv[i][j] <= '9'))
				return false;

	return true;
}

// Convert the input data to a integer array.
// The first element in the array is the value we want to search.
// The rest of array is data.
void convertToIntArray(int argc, char* argv[], int*& arr, int& size)
{
	// If input syntax is invalid, exit the program.
	if (!isValid(argc, argv))
	{
		cerr << "ERROR: wrong input syntax!\n";
		exit(1);
	}

	// Dynamic array allocation.
	size = argc - 1;
	arr	 = new int[size];

	// Convert each string to integer.
	for (int i = 1; i < argc; i++)
		arr[i - 1] = stoi(argv[i]);
}

// Examine the array is sorted ascending or not.
bool isSortedAscending(int arr[], int n) {
	for (int i = 0; i < n - 1; i++)
		if (arr[i] > arr[i + 1])
			return false;

	return true;
}

int interpolationSearch(int a[], int n, int k, int& nLoop)
{
	// The interpolation search algorithm must to search the array is sorted ascending.
	if (!isSortedAscending(a + 1, n - 1))
		return -1;

	int l = 0, r = n - 1, iSearch = 0;
	// We can imagine that index is the horizontal axis, value is the vertical axis
	while (l <= r && a[l] <= k && k <= a[r])
	{
		// Count number of loops.
		nLoop = nLoop + 1;

		// Calculate index of the element has the most possible key.
		iSearch = (k - a[l]) * (r - l) / (a[r] - a[l]) + l;

		// If found, return index
		if (a[iSearch] == k)
			return iSearch;
		
		// If k is greater than the value of the position we've just searched,
		// we need to move the search area to an area has value larger than the one we've just searched for.
		// Else smaller.
		if (a[iSearch] < k)
			l = iSearch + 1;
		else
			r = iSearch - 1;
	}

	return -1;
}

int main(int argc, char* argv[])
{
	int* arr, size, nLoop = 0;

	// Get the array that will be searched.
	convertToIntArray(argc, argv, arr, size);

	int res = interpolationSearch(arr + 1, size - 1, arr[0], nLoop);
	
	// Print the output to the console.
	if (res == -1)
		cout << res;
	else
		cout << res + 1;
	cout << " - " << nLoop;

	delete[]arr;

	return 0;
}