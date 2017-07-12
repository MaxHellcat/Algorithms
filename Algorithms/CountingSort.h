//
//  CountingSort.h
//  Algorithms
//
//  Created by Max Reshetey on 27/06/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef CountingSort_h
#define CountingSort_h

#include "Defines.h"

// Prerequisites:
// Input array consists of n integers, each being in the range 0 to k.
// Therefore it's crucial to supply correct k, which ordinarily is the max element in the array.
// Example:	A = {1, 10, 9, 5, 3, 6, 7, 2, 8, 4} (k = n, running time: Ø(n)),
//			A = {5, 3, 5, 6, 1, 4, 3, 3, 2, 1} (k < n, running time: Ø(n)),
//			A = {1, 35, 135, 25, 3} (k > n, running time: Ø(k))

// Time: Ø(n + k) (or Ø(n), provided k = O(n), which is a typical case as Cormen claims)
// Space: Ø(n)
// Stable: yes
void countingSort(Array &arr, int k)
{
	Array sortedArray(arr.size());
	Array tmpArray(k + 1);

	for (auto &val : tmpArray)
	{
		val = 0;
	}

	for (int j = 0; j < arr.size(); j++)
	{
		tmpArray[arr[j]] += 1;
	}

	for (int i = 1; i < tmpArray.size(); i++)
	{
		tmpArray[i] += tmpArray[i-1];
	}

	for (int j = (int)arr.size() - 1; j >= 0; j--)
	{
		sortedArray[tmpArray[arr[j]] - 1] = arr[j];
		tmpArray[arr[j]] -= 1;
	}

	// Note, copying back for convenience only, it's not a part of counting sort.
	arr = sortedArray;
}

void test_countingSort()
{
	{
		Array arr = {1, 35, 135, 25, 3};
		const int kMaxElement = 135; // TODO: Replace with method

		print(arr);
		countingSort(arr, kMaxElement);
		print(arr);
	}

	{
		Array arr = {5, 3, 5, 6, 1, 4, 3, 3, 5, 1};
		const int kMaxElement = 6; // TODO: Replace with method

		print(arr);
		countingSort(arr, kMaxElement);
		print(arr);
	}

	{
		const int kMaxElement = 25; // TODO: Replace with method
		Array arr(kMaxElement);

		arr.permute();

		print(arr);
		countingSort(arr, kMaxElement);
		print(arr);
	}
}

#endif /* CountingSort_h */
