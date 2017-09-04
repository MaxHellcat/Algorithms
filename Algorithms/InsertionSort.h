//
//  InsertionSort.h
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef InsertionSort_h
#define InsertionSort_h

#include "Array.h"
#include "DoublyLinkedList.h"

// Time: Ø(n^2) - worst/average, Ø(n) - best
// Space: Ø(1)
// Stable: true
void insertionSort(Array<int> &arr)
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

// TODO: Add description
template<typename T>
void insertionSort(DoublyLinkedList<T> &list)
{
	auto node = list.head()->next;

	while (node)
	{
		const auto key = node->key;

		auto innerNode = node->prev;

		while (innerNode && innerNode->key > key)
		{
			innerNode->next->key = innerNode->key;
			innerNode = innerNode->prev;
		}

		if (innerNode != node->prev)
		{
			if (!innerNode)
			{
				list.head()->key = key;
			}
			else
			{
				innerNode->next->key = key;
			}
		}

		node = node->next;
	}
}

void test_insertionSortOnDLL()
{
	DoublyLinkedList<int> list;
	for (int i=0; i < 10; i++)
	{
		list.insert(new DoublyLinkedList<int>::Node(10 - i), nullptr);
	}
	std::cout << list.description() << std::endl;

	insertionSort(list);
	std::cout << list.description() << std::endl;
}

void test_insertionSort()
{
	initTestEnvironment();

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		insertionSort(arr);
		print(arr);

		std::cout << std::endl;
	}

	test_insertionSortOnDLL();
}

#endif /* InsertionSort_h */
