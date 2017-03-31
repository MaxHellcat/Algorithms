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

class MaxHeap
{
public:
	MaxHeap(int heapSize) : _arr(heapSize, true), _heapSize(heapSize) {}

//	int parent(int index) { return (index - 1) / 2; }
	int leftChildIndex(int index) { return 2*index + 1; }
	int rightChildIndex(int index) { return 2*index + 2; }
	int maxValue() { return _arr[0]; }

	void heapSort()
	{
		buildMaxHeap();

		for (int i = 0; i < _arr.size(); i++)
		{
			const int tmpVal = _arr[0];
			_arr[0] = _arr[heapSize() - 1];
			_arr[heapSize() - 1] = tmpVal;

			_heapSize = _heapSize - 1;

			heapify(0);
		}
	}

	void heapify(int index)
	{
		const int leftChildIndex = this->leftChildIndex(index);
		const int rightChildIndex = this->rightChildIndex(index);

		int indexOfLargest = index;

		if (leftChildIndex < heapSize() && _arr[leftChildIndex] > _arr[indexOfLargest])
		{
			indexOfLargest = leftChildIndex;
		}
		if (rightChildIndex < heapSize() && _arr[rightChildIndex] > _arr[indexOfLargest])
		{
			indexOfLargest = rightChildIndex;
		}

		if (indexOfLargest != index)
		{
			const int tmpVal = _arr[index];
			_arr[index] = _arr[indexOfLargest];
			_arr[indexOfLargest] = tmpVal;

			heapify(indexOfLargest);
		}
	}

	void buildMaxHeap()
	{
		for (int i = (heapSize() - 1) / 2; i >= 0; i--)
		{
			heapify(i);
		}
	}

	int heapSize() const { return _heapSize; }

	void print() { _arr.print(); }

private:
	Array _arr;

	int _heapSize;
};

#endif /* HeapSort_h */
