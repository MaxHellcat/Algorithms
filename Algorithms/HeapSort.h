//
//  HeapSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h

#include "Array.h"
#include "Heap.h"

// Time: O(n*lgn)
// Space: O(1)
// Stable: false
// Adaptive: no
void heapSort(MaxHeap &heap)
{
	heap.build();

	for (auto i = (int)heap.heapSize() - 1; i > 0 ; i--)
	{
		heap.swapFirstWithLast();

		heap.decrementHeapSize();

		heap.heapify(0);
	}
}

void test_heapSort()
{
	initTestEnvironment();

	for (int i = 1; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		MaxHeap heap(arr);

		std::cout << "Array: " << heap.description() << std::endl;

		heapSort(heap);

		std::cout << "Sorted: " << heap.description() << std::endl;

		std::cout << std::endl;
	}
}

#endif /* HeapSort_h */
