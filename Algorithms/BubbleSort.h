//
//  BubbleSort.h
//  Algorithms
//
//  Created by Max Reshetey on 29/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef BubbleSort_h
#define BubbleSort_h

#include "Array.h"

// Time: Ø(n^2) - worst/average/best (tiny modification yields Ø(n) best-case running time)
// Space: O(1)
// Stable: true
void bubbleSort(Array<int> &arr)
{
	for (size_t i = 0; i < arr.size() - 1; i++)
	{
		for (size_t j = 1; j < arr.size() - i; j++)
		{
			if (arr[j] < arr[j - 1])
			{
				swap(arr[j], arr[j - 1]);
			}
		}
	}
}

void test_bubbleSort()
{
	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		bubbleSort(arr);
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* BubbleSort_h */
