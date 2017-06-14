//
//  Defines.h
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Defines_h
#define Defines_h

#include "iostream"
//#include "cstdlib" // For rand, srand

using std::cout;

int random(int min, int max)
{
	return min + (rand() % (max - min + 1));
}

void swap(int & val1, int & val2)
{
	const int tmpVal = val1;
	val1 = val2;
	val2 = tmpVal;
}

class Array
{
public:
	Array(size_t size) : _pointer(new int[size]), _size(size)
	{
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

	int& operator[](int index) { return _pointer[index]; }

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

	// Produces a uniform random permutation (any of n! with equal probability) of the array
	void permute()
	{
		for (int i = 0; i < _size; i++)
		{
			swap(_pointer[i], _pointer[random(i, (int)size() - 1)]);
		}
	}

protected:
	int * _pointer;

private:
	size_t _size;
};

void print(Array & arr, int leftIndex = 0, int rightIndex = INT_MIN)
{
	if (rightIndex == INT_MIN)
	{
		rightIndex = (int)arr.size() - 1;
	}

	cout << "[";

	for (int i = leftIndex; i < rightIndex + 1; i++)
	{
		cout << const_cast<Array*>(&arr)->operator[](i) << ((i < rightIndex) ? ", " : "");
	}

	cout << "] (size " << rightIndex - leftIndex + 1 << ", " << (arr.isSorted(leftIndex, rightIndex)?"sorted":"unsorted") << ")\n";
}


#endif /* Defines_h */
