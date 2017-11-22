//
//  HeapSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef HeapSort_h
#define HeapSort_h

#include "Heap.h"

//struct MaxHeap: public Array<int>
//{
//	MaxHeap(size_t size) : Array(size) {}
//	MaxHeap(std::initializer_list<int> list) : Array(list) {}
//
////	int parent(int index) { return (index - 1) / 2; }
//	int left(int index) { return 2*index + 1; }
//	int right(int index) { return 2*index + 2; }
//
//// Time: O(n)
//// Space: O(1)
//	void build()
//	{
//		heapSize = (int)size();
//
//		for (int i = (heapSize - 1) / 2; i >= 0; i--)
//		{
//			heapify(i);
//		}
//	}
//
//// Time: O(lgn)
//// Space: O(1)
//	void heapify(int index)
//	{
//		const int left = this->left(index);
//		const int right = this->right(index);
//
//		int indexOfLargest = index;
//
//		if (left < heapSize && _pointer[left] > _pointer[indexOfLargest])
//		{
//			indexOfLargest = left;
//		}
//
//		if (right < heapSize && _pointer[right] > _pointer[indexOfLargest])
//		{
//			indexOfLargest = right;
//		}
//
//		if (indexOfLargest != index)
//		{
//			swap(_pointer[index], _pointer[indexOfLargest]);
//
//			heapify(indexOfLargest);
//		}
//	}
//
//	int heapSize = 0;
//};

// Time: O(n*lgn) - worst/average/best
// Space: O(1)
// Stable: false
// Adaptive: no
void heapSort(MaxHeap &heap)
{
	heap.build();

	for (int i = (int)heap.size() - 1; i > 0 ; i--)
	{
		swap(heap[0], heap[i]);

		heap.setSize(heap.size() - 1);

		heap.heapify(0);
	}
}

#include "Array.h"

void test_heapSort()
{
	initTestEnvironment();

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		MaxHeap heap;
		for (const auto &val : arr) { heap.insert(val); }

		heap.build();
		std::cout << "Heap: " << heap.description() << std::endl;

		// TODO: Decide what to do with heap.size()

		heapSort(heap);
		std::cout << "Array sorted: " << heap.description() << std::endl;

		std::cout << std::endl;
	}
}

#endif /* HeapSort_h */
