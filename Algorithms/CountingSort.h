//
//  CountingSort.h
//  Algorithms
//
//  Created by Max Reshetey on 27/06/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef CountingSort_h
#define CountingSort_h

#include "Array.h"

// Note: When indexOfDigitToSortBy isn't -1, the counting sort is used as part of a radix sort, i.e.
// sorts the input array by a specific digit.

// Prerequisites:
// Input array consists of n integers, each being in the range 0 to k. Therefore it's crucial
// to supply correct k, which ordinarily is the max element in the array.
// Example:	A = {1, 10, 9, 5, 3, 6, 7, 2, 8, 4} (k = n, running time: Ø(n)),
//			A = {5, 3, 5, 6, 1, 4, 3, 3, 2, 1} (k < n, running time: Ø(n)),
//			A = {1, 35, 135, 25, 3} (k > n, running time: Ø(k))

// Time: Ø(n + k) (or Ø(n), provided k = O(n), which is a typical case as Cormen claims)
// Space: Ø(n + k)
// Stable: true
void countingSort(Array<int> &arr, int k, int indexOfDigitToSortBy = -1)
{
	Array<int> sortedArray(arr.size());
	Array<int> tmpArray(k + 1);

	for (auto &val : tmpArray)
	{
		val = 0;
	}

	const bool partOfRadixSort = indexOfDigitToSortBy != -1;

	for (int j = 0; j < arr.size(); j++)
	{
		if (partOfRadixSort)
		{
			const int digit = digitAtIndex(arr[j], indexOfDigitToSortBy);
			tmpArray[digit] += 1;
		}
		else
		{
			tmpArray[arr[j]] += 1;
		}
	}

	for (int i = 1; i < tmpArray.size(); i++)
	{
		tmpArray[i] += tmpArray[i-1];
	}

	for (int j = (int)arr.size() - 1; j >= 0; j--)
	{
		const int val = partOfRadixSort ? digitAtIndex(arr[j], indexOfDigitToSortBy) : arr[j];

		sortedArray[tmpArray[val] - 1] = arr[j];
		tmpArray[val] -= 1;
	}

	// Note, copying back for convenience only, it's not a part of counting sort.
	arr = sortedArray;
}

void test_countingSort()
{
	{
		Array<int> arr = {1, 35, 135, 25, 3};

		print(arr);
		countingSort(arr, arr.max());
		print(arr);
	}

	{
		Array<int> arr = {5, 3, 5, 6, 1, 4, 3, 3, 5, 1};

		print(arr);
		countingSort(arr, arr.max());
		print(arr);
	}

	{
		Array<int> arr(25);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		countingSort(arr, arr.max());
		print(arr);
	}
}

#endif /* CountingSort_h */
