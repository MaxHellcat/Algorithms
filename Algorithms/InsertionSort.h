//
//  InsertionSort.h
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef InsertionSort_h
#define InsertionSort_h

#include "Defines.h"

// Time: Ø(n^2) - worst/average, Ø(n) - best
// Space: Ø(1)
// Stable: true
void insertionSort(Array &arr)
{
	for (int i = 1; i < arr.size(); i++)
	{
		const int key = arr[i];

		int j = i - 1;

		while (j >= 0 && arr[j] > key)
		{
			arr[j + 1] = arr[j];
			j = j - 1;
		}

		if (j != i - 1)
		{
			arr[j + 1] = key;
		}
	}
}

void test_insertionSort()
{
	for (int i = 0; i < 10; i++)
	{
		Array arr(10);
		arr.permute();

		print(arr);
		insertionSort(arr);
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* InsertionSort_h */
