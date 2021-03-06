//
//  QuickSort.h
//  Algorithms
//
//  Created by Max Reshetey on 07/04/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef QuickSort_h
#define QuickSort_h

#include "Array.h"

int partition(Array<int> &arr, int leftIndex, int rightIndex);
int randomPartition(Array<int> &arr, int leftIndex, int rightIndex);
int hoarePartition(Array<int> &arr, int leftIndex, int rightIndex);

// Time: Ø(n^2) - worst, Ø(n*lgn) - expected/best
// Space: O(1) (maybe O(lgn) for expected/best and O(n) for the worst?)
// Stable: false (classic implementation with Lomuto/Hoare partitions as provided here)
// Adaptive: ?
void quickSort(Array<int> &arr, int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex)
	{
//		const int q = partition(arr, leftIndex, rightIndex);
		const int q = randomPartition(arr, leftIndex, rightIndex);

		quickSort(arr, leftIndex, q - 1);
		quickSort(arr, q + 1, rightIndex);

//		const int q = hoarePartition(arr, leftIndex, rightIndex);
//		quickSort(arr, leftIndex, q);
//		quickSort(arr, q + 1, rightIndex);
	}
}

int partition(Array<int> &arr, int leftIndex, int rightIndex)
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

int randomPartition(Array<int> &arr, int leftIndex, int rightIndex)
{
	const int pivotIndex = random(leftIndex, rightIndex);

	swap(arr[pivotIndex], arr[rightIndex]);

	return partition(arr, leftIndex, rightIndex);
}

// TODO: Work out how this partition works.
int hoarePartition(Array<int> &arr, int leftIndex, int rightIndex)
{
	const int x = arr[leftIndex];

	int i = leftIndex - 1;
	int j = rightIndex + 1;

	while (true)
	{
		do
		{
			j = j - 1;
		}
		while (arr[j] > x);

		do
		{
			i = i + 1;
		}
		while (arr[i] < x);

		if (i < j)
		{
			swap(arr[i], arr[j]);
		}
		else
		{
			return j;
		}
	}
}

void test_quickSort()
{
	initTestEnvironment();

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		quickSort(arr, 0, static_cast<int>(arr.size() - 1));
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* QuickSort_h */
