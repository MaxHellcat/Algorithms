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

// A max heap implementation using dynamic array
class MaxHeap
{
public:
	// Core dictionary methods

	// Time O(lgn)
	void insert(int key)
	{
		_vec.push_back(key);

		// Bubble-up if needed
		auto i = static_cast<int>(_vec.size()-1);

		while (parent(i) >= 0 && _vec[parent(i)] < key)
		{
			swap(_vec[i], _vec[parent(i)]);
			i = parent(i);
		}
	}

	// Time O(1)
	int max() const
	{
		assert(_vec.size() >= 1);

		return _vec[0];
	}

	// Time O(lgn)
	int extractMax()
	{
		assert(_vec.size() >= 1);

		const int maxVal = _vec[0];

		_vec[0] = _vec[_vec.size()-1];

		_vec.resize(_vec.size()-1);

		heapify(0);

		return maxVal;
	}

// Aux methods
	// Time O(n)
	void build()
	{
		for (auto i=(int)_vec.size()/2-1; i >= 0; i--)
		{
			heapify(i);
		}
	}

	// Time O(lgn)
	void heapify(int index)
	{
		const int leftIndex = left(index);
		const int rightIndex = right(index);

		int maxIndex = index;

		if (leftIndex < _vec.size() && _vec[leftIndex] > _vec[maxIndex]) {
			maxIndex = leftIndex;
		}

		// Note, if leftIndex >= _vec.size(), so is rightIndex
		if (rightIndex < _vec.size() && _vec[rightIndex] > _vec[maxIndex]) {
			maxIndex = rightIndex;
		}

		if (index != maxIndex)
		{
			swap(_vec[index], _vec[maxIndex]);

			heapify(maxIndex);
		}
	}

	int left(int index) const { return 2*index + 1; }
	int right(int index) const { return 2*index + 2; }
	int parent(int index) const { return (index-1) / 2; }

	size_t size() const { return _vec.size(); }
	void setSize(size_t size) { _vec.resize(size); }

	// TODO: Does heap provide this? Added only for heap sort.
	int &operator[](size_t index) { assert(index < size()); return _vec[index]; }

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
		for (int i=(int)size()/2-1; i >= 0; i--)
		{
			if (_vec[left(i)] > _vec[i] || _vec[right(i)] > _vec[i])
			{
				return false;
			}
		}
		
		return true;
	}

private:
	std::vector<int> _vec;
};

void test_Heap()
{
	MaxHeap heap;

	heap.insert(3);
	heap.insert(1);
	heap.insert(2);
	heap.insert(5);
	heap.insert(4);

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
