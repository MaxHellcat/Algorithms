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
	MaxHeap(size_t size, bool randomize = false) : Array(size, randomize) {}
	MaxHeap(std::initializer_list<int> list) : Array(list) {}

//	int parent(int index) { return (index - 1) / 2; }
	int left(int index) { return 2*index + 1; }
	int right(int index) { return 2*index + 2; }

	void build()
	{
		heapSize = (int)size();

		for (int i = (heapSize - 1) / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}

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
			const int tmpVal = _pointer[index];
			_pointer[index] = _pointer[indexOfLargest];
			_pointer[indexOfLargest] = tmpVal;

			heapify(indexOfLargest);
		}
	}

	int heapSize = 0;
};

void heapSort(MaxHeap & heap)
{
	heap.build();

	for (int i = (int)heap.size() - 1; i > 0 ; i--)
	{
		const int tmpVal = heap[0];
		heap[0] = heap[i];
		heap[i] = tmpVal;

		heap.heapSize = heap.heapSize - 1;

		heap.heapify(0);
	}
}

#endif /* HeapSort_h */