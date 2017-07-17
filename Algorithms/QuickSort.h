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

int partition(Array &arr, int leftIndex, int rightIndex);
int randomPartition(Array &arr, int leftIndex, int rightIndex);
int hoarePartition(Array &arr, int leftIndex, int rightIndex);

// TODO: Add test cases

// Time: Ø(n*lgn) - expected/best, Ø(n^2) - worst
// Space: O(1) (maybe O(lgn) for expected/best and O(n) for the worst?)
// Stable: false (classic implementation with Lomuto/Hoare partitions as provided here)
void quickSort(Array &arr, int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex)
	{
//		const int q = partition(arr, leftIndex, rightIndex);
//		const int q = randomPartition(arr, leftIndex, rightIndex);

//		quickSort(arr, leftIndex, q - 1);
//		quickSort(arr, q + 1, rightIndex);

		const int q = hoarePartition(arr, leftIndex, rightIndex);
		quickSort(arr, leftIndex, q);
		quickSort(arr, q + 1, rightIndex);
	}
}

int partition(Array &arr, int leftIndex, int rightIndex)
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

int randomPartition(Array &arr, int leftIndex, int rightIndex)
{
	const int pivotIndex = random(leftIndex, rightIndex);

	swap(arr[pivotIndex], arr[rightIndex]);

	return partition(arr, leftIndex, rightIndex);
}

int hoarePartition(Array &arr, int leftIndex, int rightIndex)
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
	for (int i = 2; i < 10; i++)
	{
		Array arr(i);
		arr.permute();

		print(arr);
		quickSort(arr, 0, static_cast<int>(arr.size() - 1));
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* QuickSort_h */
