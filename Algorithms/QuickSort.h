//
//  QuickSort.h
//  Algorithms
//
//  Created by Max Reshetey on 07/04/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef QuickSort_h
#define QuickSort_h

#include "Defines.h"

int partition(Array & arr, int leftIndex, int rightIndex);
int randomPartition(Array & arr, int leftIndex, int rightIndex);

// Time: Ø(nlgn) - expected/best, Ø(n^2) - worst
// Space: O(1)
void quickSort(Array & arr, int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex)
	{
//		const int q = partition(arr, leftIndex, rightIndex);
		const int q = randomPartition(arr, leftIndex, rightIndex);

		quickSort(arr, leftIndex, q - 1);
		quickSort(arr, q + 1, rightIndex);
	}
}

int partition(Array & arr, int leftIndex, int rightIndex)
{
	const int x = arr[rightIndex];

	int i = leftIndex - 1;

	for (int j = leftIndex; j < rightIndex; j++)
	{
		if (arr[j] <= x)
		{
			i = i + 1;

			swap(arr[i], arr[j]);
		}
	}

	swap(arr[i + 1], arr[rightIndex]);

	return i + 1;
}

int randomPartition(Array & arr, int leftIndex, int rightIndex)
{
	const int pivotIndex = random(leftIndex, rightIndex);

	swap(arr[pivotIndex], arr[rightIndex]);

	return partition(arr, leftIndex, rightIndex);
}

#endif /* QuickSort_h */
