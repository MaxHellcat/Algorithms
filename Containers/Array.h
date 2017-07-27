//
//  Array.h
//  Algorithms
//
//  Created by Max Reshetey on 27/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Array_h
#define Array_h

#include "Defines.h"

class Array
{
public:
	Array(size_t size) : _pointer(new int[size]), _size(size)
	{
		// TODO: Not sure this is with POLA
		for (int i = 0; i < size; i++)
		{
			_pointer[i] = i + 1;
		}
	}

	Array(std::initializer_list<int> list) : _pointer(new int[list.size()]), _size(list.size())
	{
		int i = 0;
		for (auto val : list)
		{
			_pointer[i++] = val;
		}
	}

	~Array()
	{
		delete [] _pointer;
	}

	size_t size() const { return _size; }

	int &operator[](size_t index) { return _pointer[index]; }
	const int &operator[](size_t index) const { return _pointer[index]; }

	const Array &operator=(const Array &rhs)
	{
		if (size() != rhs.size())
		{
			delete [] _pointer;
			
			_pointer = new int[rhs.size()];
			_size = rhs.size();
		}

		for (int i = 0; i < size(); i++)
		{
			_pointer[i] = rhs[i];
		}

		return *this;
	}

	bool isSorted(int leftIndex = 0, int rightIndex = INT_MIN) const
	{
		if (rightIndex == INT_MIN)
		{
			rightIndex = (int)size() - 1;
		}

		for (int i = leftIndex; i < rightIndex; i++)
		{
			if (_pointer[i] > _pointer[i+1])
			{
				return false;
			}
		}

		return true;
	}

	int max() const
	{
		int max = INT_MIN;
		
		for (auto it = begin(); it < end(); it++)
		{
			if (*it > max) {
				max = *it;
			}
		}
		
		return max;
	}

	// Produces a uniform random permutation (any of n! with equal probability) of the array
	void permute()
	{
		for (int i = 0; i < _size; i++)
		{
			swap(_pointer[i], _pointer[random(i, (int)size() - 1)]);
		}
	}

	// To support ranged for loop
	int *begin() const { return _pointer; }
	int *end() const { return _pointer + _size; }

protected:
	int *_pointer;

private:
	size_t _size;
};

void print(Array &arr, int leftIndex = 0, int rightIndex = INT_MIN)
{
	if (rightIndex == INT_MIN)
	{
		rightIndex = (int)arr.size() - 1;
	}
	
	std::cout << "[";
	
	for (int i = leftIndex; i < rightIndex + 1; i++)
	{
		std::cout << const_cast<Array*>(&arr)->operator[](i) << ((i < rightIndex) ? ", " : "");
	}
	
	std::cout << "] (size " << rightIndex - leftIndex + 1 << ", " << (arr.isSorted(leftIndex, rightIndex)?"sorted":"unsorted") << ")\n";
}

#endif /* Array_h */
