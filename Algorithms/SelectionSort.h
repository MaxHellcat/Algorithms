//
//  SelectionSort.h
//  Algorithms
//
//  Created by Max Reshetey on 29/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef SelectionSort_h
#define SelectionSort_h

#include "Defines.h"

// Time: Ø(n^2) - worst/average/best
// Space: Ø(1)
void selectionSort(Array & arr)
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
	for (int i = 2; i < 10; i++)
	{
		Array arr(i);
		arr.permute();

		print(arr);
		selectionSort(arr);
		print(arr);

		std::cout << std::endl;
	}
}


#endif /* SelectionSort_h */
