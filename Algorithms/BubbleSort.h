//
//  BubbleSort.h
//  Algorithms
//
//  Created by Max Reshetey on 29/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef BubbleSort_h
#define BubbleSort_h

#include "Defines.h"

void bubbleSort(Array & arr)
{
	for (int i = 0; i < arr.size() - 1; i++)
	{
		for (int j = (int)arr.size() - 1; j > i; j--)
		{
			if (arr[j] < arr[j - 1])
			{
				const int tmpVal = arr[j];
				arr[j] = arr[j - 1];
				arr[j - 1] = tmpVal;
			}

			// First I wrote this way and it also works!
//			if (arr[j] < arr[i])
//			{
//				const int tmpVal = arr[i];
//				arr[i] = arr[j];
//				arr[j] = tmpVal;
//			}
		}
	}
}

#endif /* BubbleSort_h */
