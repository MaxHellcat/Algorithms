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

void quickSort(Array & arr, int leftIndex, int rightIndex)
{
//	cout << "In quickSort, arr: \n";
//	print(arr, leftIndex, rightIndex);
//	cout << "\n";

	if (leftIndex < rightIndex)
	{
		const int q = partition(arr, leftIndex, rightIndex);
		quickSort(arr, leftIndex, q - 1);
		quickSort(arr, q + 1, rightIndex);
	}
}

int partition(Array & arr, int leftIndex, int rightIndex)
{
	const int x = arr[rightIndex];

//	cout << "\nIn partition, pivot: " << x << ", ";

	int i = leftIndex - 1;

	for (int j = leftIndex; j < rightIndex; j++)
	{
		if (arr[j] <= x)
		{
			i = i + 1;

			const int tmpVal = arr[i];
			arr[i] = arr[j];
			arr[j] = tmpVal;
		}
	}

	const int tmpVal = arr[i + 1];
	arr[i + 1] = arr[rightIndex];
	arr[rightIndex] = tmpVal;
	
//	cout << "q: " << i + 1 << "\n";
//	cout << "\n";

	return i + 1;
}

#endif /* QuickSort_h */
