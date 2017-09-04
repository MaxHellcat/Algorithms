//
//  SelectionSort.h
//  Algorithms
//
//  Created by Max Reshetey on 29/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef SelectionSort_h
#define SelectionSort_h

#include "Array.h"

// Time: Ø(n^2) - worst/average/best
// Space: Ø(1)
// Stable: ?
void selectionSort(Array<int> &arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		int minJndex = i;

		for (int j = i + 1; j < arr.size(); j++)
		{
			if (arr[j] < arr[minJndex])
			{
				minJndex = j;
			}
		}

		if (minJndex != i)
		{
			swap(arr[i], arr[minJndex]);
		}
	}
}

void test_selectionSort()
{
	initTestEnvironment();

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		selectionSort(arr);
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* SelectionSort_h */
