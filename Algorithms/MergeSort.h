//
//  MergeSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef MergeSort_h
#define MergeSort_h

#include "Array.h"

void merge(Array &arr, int leftIndex, int midIndex, int rightIndex);

// Time: Ø(n*lgn) - worst/average/best
// Space: Ø(n)
// Stable: true
void mergeSort(Array &arr, int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex)
	{
		const int midIndex = (leftIndex + rightIndex) / 2;

		mergeSort(arr, leftIndex, midIndex);
		mergeSort(arr, midIndex + 1, rightIndex);

		merge(arr, leftIndex, midIndex, rightIndex);
	}
}

void merge(Array &arr, int leftIndex, int midIndex, int rightIndex)
{
	const int kLeftArraySize = midIndex - leftIndex + 1;
	Array leftArray(kLeftArraySize);

	for (int i = 0; i < kLeftArraySize; i++)
	{
		leftArray[i] = arr[leftIndex + i];
	}

	const int kRightArraySize = rightIndex - midIndex;
	Array rightArray(kRightArraySize);

	for (int i = 0; i < kRightArraySize; i++)
	{
		rightArray[i] = arr[(midIndex + 1) + i];
	}

	int li = 0, ri = 0;
	for (int i = leftIndex; i < rightIndex + 1; i++)
	{
		if (li < leftArray.size() && ri < rightArray.size())
		{
			if (leftArray[li] <= rightArray[ri])
			{
				arr[i] = leftArray[li];
				li = li + 1;
			}
			else
			{
				arr[i] = rightArray[ri];
				ri = ri + 1;
			}
		}
		else if (li == leftArray.size())
		{
			while (i < rightIndex + 1)
			{
				arr[i] = rightArray[ri];
				i = i + 1;
				ri = ri + 1;
			}

			break;
		}
		else if (ri == rightArray.size())
		{
			while (i < rightIndex + 1)
			{
				arr[i] = leftArray[li];
				i = i + 1;
				li = li + 1;
			}

			break;
		}
	}
}

void test_mergeSort()
{
	for (int i = 2; i < 10; i++)
	{
		Array arr(i);
		arr.permute();

		print(arr);
		mergeSort(arr, 0, static_cast<int>(arr.size() - 1));
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* MergeSort_h */
