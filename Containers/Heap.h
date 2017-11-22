//
//  Heap.h
//  Algorithms
//
//  Created by Max Reshetey on 22/11/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

#include "vector"

#include "Array.h"
#include "Defines.h"

// A max heap implementation using dynamic array
class MaxHeap
{
public:
	MaxHeap() {}

	MaxHeap(Array<int> &arr) // Heap sort related
	{
		_heapSize = arr.size();
		_vec.resize(_heapSize);

		for (int i = 0; i < _heapSize; i++) { _vec[i] = arr[i]; }
	}

// Core dictionary methods
	// Time O(lgn)
	void insert(int key)
	{
		_vec.push_back(key);
		_heapSize += 1;

		// Bubble-up if needed
		auto i = static_cast<int>(_heapSize-1);

		while (parent(i) >= 0 && _vec[parent(i)] < key)
		{
			swap(_vec[i], _vec[parent(i)]);
			i = parent(i);
		}
	}

	// Time O(1)
	int max() const
	{
		assert(_heapSize >= 1);

		return _vec[0];
	}

	// Time O(lgn)
	int extractMax()
	{
		assert(_vec.size() >= 1);

		const int maxVal = _vec[0];

		_vec[0] = _vec[_vec.size()-1];

		_vec.resize(_vec.size()-1);
		_heapSize -= 1;

		heapify(0);

		return maxVal;
	}

	int left(int index) const { return 2*index + 1; }
	int right(int index) const { return 2*index + 2; }
	int parent(int index) const { return (index-1) / 2; }

// Aux methods
	// Time O(lgn)
	void heapify(int index)
	{
		const int leftIndex = left(index);
		const int rightIndex = right(index);

		int maxIndex = index;

		if (leftIndex < _heapSize && _vec[leftIndex] > _vec[maxIndex]) {
			maxIndex = leftIndex;
		}

		// Note, if leftIndex >= _vec.size(), so is rightIndex
		if (rightIndex < _heapSize && _vec[rightIndex] > _vec[maxIndex]) {
			maxIndex = rightIndex;
		}

		if (index != maxIndex)
		{
			swap(_vec[index], _vec[maxIndex]);

			heapify(maxIndex);
		}
	}

	std::string description() const
	{
		std::string str = "[";

		for (int i = 0; i < _vec.size(); i++)
		{
			str += std::to_string(_vec[i]) + ((i < _vec.size()-1) ? ", " : "");
		}

		str += "] (size " + std::to_string(_vec.size()) + ")";

		return str;
	}

	bool isHeap() const
	{
		for (int i=(int)_heapSize/2-1; i >= 0; i--)
		{
			if (_vec[left(i)] > _vec[i] || _vec[right(i)] > _vec[i])
			{
				return false;
			}
		}

		return true;
	}

	// Time O(n)
	void build() // Heap sort related
	{
		for (auto i=(int)_vec.size()/2-1; i >= 0; i--)
		{
			heapify(i);
		}
	}

	size_t heapSize() const { return _heapSize; } // Heap sort related
	void decrementHeapSize() { _heapSize -= 1; } // Heap sort related
	void swapFirstWithLast() { swap(_vec[0], _vec[_heapSize-1]); } // Heap sort related

private:
	std::vector<int> _vec;

	size_t _heapSize = 0; // Heap sort uses this to be in-place, and we have to maintain
};

void test_Heap()
{
	initTestEnvironment();

	Array<int> arr(7);
	for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
	arr.permute();

	MaxHeap heap;
	for (const auto &val : arr) { heap.insert(val); }

	std::cout << "Heap: " << heap.description() << std::endl;
	std::cout << "Is heap: " << heap.isHeap() << std::endl;

	std::cout << std::endl;

	std::cout << "Max: " << heap.max() << std::endl;
	std::cout << "Extract max: " << heap.extractMax() << std::endl;

	std::cout << std::endl;

	std::cout << "Heap: " << heap.description() << std::endl;
	std::cout << "Is heap: " << heap.isHeap() << std::endl;
	
	std::cout << std::endl;
}

#endif /* Heap_h */
