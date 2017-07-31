//
//  BucketSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef BucketSort_h
#define BucketSort_h

#include "Array.h"
#include "DoublyLinkedList.h"
#include "InsertionSort.h"

// TODO: Add description, time, space.
void bucketSort(Array<float> &arr)
{
	Array<DoublyLinkedList<float> *> tmpArr(arr.size(), nullptr);

	for (int i=0; i<arr.size(); i++)
	{
		const int index = arr.size() * arr[i];

		if (!tmpArr[index])
		{
			tmpArr[index] = new DoublyLinkedList<float>;
		}

		auto node = new DoublyLinkedList<float>::Node(arr[i]);
		tmpArr[index]->insert(node, nullptr);
	}

	std::cout << "Array of lists below:" << std::endl;
	for (int i=0; i<arr.size(); i++)
	{
		std::cout << i << ": " << (tmpArr[i] ? tmpArr[i]->description() : "nil") << std::endl;
	}

	for (int i=0; i<arr.size(); i++)
	{
		if (tmpArr[i])
		{
			insertionSort(*(tmpArr[i]));
		}
	}

	int index = 0;
	for (int tmpArrIndex = 0; tmpArrIndex < arr.size(); tmpArrIndex++)
	{
		if (tmpArr[tmpArrIndex])
		{
			auto node = tmpArr[tmpArrIndex]->head();

			while (node)
			{
				arr[index] = node->key;

				node = node->next;
				index++;
			}
		}
	}
}

void test_bucketSort()
{
	Array<float> arr(10);

	for (int i=0; i<arr.size(); i++)
	{
		float val = random(10, 99);
		arr[i] = val / 100;
	
	}
	print(arr);

	bucketSort(arr);
	print(arr);
}


#endif /* BucketSort_h */
