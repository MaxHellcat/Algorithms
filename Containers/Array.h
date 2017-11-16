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
#include "cassert"

template<typename T>
class Array
{
public:
	Array(size_t size) : _pointer(new T[size]), _size(size) {}

	Array(size_t size, T defaultValue) : _pointer(new T[size]), _size(size)
	{
		for (auto &val : *this)
		{
			val = defaultValue;
		}
	}

	Array(std::initializer_list<T> list) : _pointer(new T[list.size()]), _size(list.size())
	{
		for (int i = 0; i < list.size(); i++)
		{
			_pointer[i] = *(list.begin() + i);
		}
	}

	~Array()
	{
		delete [] _pointer;
	}

	size_t size() const { return _size; }

	T &operator[](size_t index) { assert(index < size()); return _pointer[index]; }
	const T &operator[](size_t index) const { assert(index < size()); return _pointer[index]; }

	const Array &operator=(const Array &rhs)
	{
		if (size() != rhs.size())
		{
			delete [] _pointer;

			_pointer = new T[rhs.size()];
			_size = rhs.size();
		}

		for (int i = 0; i < size(); i++)
		{
			_pointer[i] = rhs[i];
		}

		return *this;
	}

	bool sorted() const
	{
		for (int i = 0; i < size()-1; i++)
		{
			if (_pointer[i] > _pointer[i+1])
			{
				return false;
			}
		}

		return true;
	}

	T max() const
	{
		assert(size() > 0);

		auto max = operator[](0);

		for (auto it = begin() + 1; it < end(); it++)
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
	T *begin() const { return _pointer; }
	T *end() const { return _pointer + _size; }

protected:
	T *_pointer;

private:
	size_t _size;
};

template<typename T>
void print(Array<T> &arr)
{
	std::cout << "[";

	for (int i = 0; i < arr.size(); i++)
	{
		std::cout << arr[i] << ((i < arr.size()-1) ? ", " : "");
	}

	std::cout << "] (size " << arr.size() << ", " << (arr.sorted()?"sorted":"unsorted") << ")\n";
}

#endif /* Array_h */
