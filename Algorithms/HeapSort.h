//
//  HeapSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h

#include "Defines.h"

struct MaxHeap: public Array
{
	MaxHeap(size_t size) : Array(size) {}
	MaxHeap(std::initializer_list<int> list) : Array(list) {}

//	int parent(int index) { return (index - 1) / 2; }
	int left(int index) { return 2*index + 1; }
	int right(int index) { return 2*index + 2; }

// Time: O(n)
// Space: O(1)
	void build()
	{
		heapSize = (int)size();

		for (int i = (heapSize - 1) / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}

// Time: O(lgn)
// Space: O(1)
	void heapify(int index)
	{
		const int left = this->left(index);
		const int right = this->right(index);

		int indexOfLargest = index;

		if (left < heapSize && _pointer[left] > _pointer[indexOfLargest])
		{
			indexOfLargest = left;
		}

		if (right < heapSize && _pointer[right] > _pointer[indexOfLargest])
		{
			indexOfLargest = right;
		}

		if (indexOfLargest != index)
		{
			swap(_pointer[index], _pointer[indexOfLargest]);

			heapify(indexOfLargest);
		}
	}

	int heapSize = 0;
};

// TODO: Add test cases

// Time: Ø(n*lgn) - worst/average, O(n*lgn) - best(?)
// Space: O(1)
// Stable: false
void heapSort(MaxHeap &heap)
{
	heap.build();

	for (int i = (int)heap.size() - 1; i > 0 ; i--)
	{
		swap(heap[0], heap[i]);

		heap.heapSize = heap.heapSize - 1;

		heap.heapify(0);
	}
}

void test_heapSort()
{
	for (int i = 2; i < 10; i++)
	{
		MaxHeap arr(i);
		arr.permute();

		print(arr);
		heapSort(arr);
		print(arr);

		std::cout << std::endl;
	}
}

#endif /* HeapSort_h */
