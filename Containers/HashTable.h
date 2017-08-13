//
//  HashTable.h
//  Algorithms
//
//  Created by Max Reshetey on 11/08/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

using namespace std; // For brief logging

// TODO:
// a) Open addressing for collision resolution
// b) Array auto-adjusting depending on load factor a = n/m
// c) Wider range of hash functions

// A simple hash table implementation using chaining for resolving collisions.
// All three dictionary operations take constant time if n = O(m), as a = O(m) / m = O(1).
class HashTable
{
public:
	struct Element
	{
		Element(int aKey) : key(aKey) {}

		Element *next = nullptr, *prev = nullptr;
		int key;
	};

public:
	HashTable()
	{
		for (auto &val : _arr)
		{
			val = nullptr;
		}
	}

	~HashTable()
	{
		for (auto &val : _arr)
		{
			while (val)
			{
				remove(val);
			}
		}
	}

// Core dictionary methods

	// Time: Ø(1 + loadFactor) - average, Ø(n) - worst
	Element *search(int aKey) const
	{
		auto element = _arr[hash(aKey)];

		while (element && element->key != aKey)
		{
			element = element->next;
		}

		return element;
	}

	// Time: Ø(1)
	void insert(Element *element)
	{
		assert(element);

		const auto slotIndex = hash(element->key);

		if (!_arr[slotIndex])
		{
			_arr[slotIndex] = element;
		}
		else
		{
			element->next = _arr[slotIndex];
			_arr[slotIndex]->prev = element;

			_arr[slotIndex] = element;
		}

		_size++;
	}

	// Time: Ø(1)
	void remove(Element *element)
	{
		assert(element);

		if (element->prev)
		{
			element->prev->next = element->next;
		}
		else
		{
			_arr[hash(element->key)] = element->next;
		}

		if (element->next)
		{
			element->next->prev = element->prev;
		}

		delete element;

		_size--;
	}

// Extra methods
	size_t size() const { return _size; }

	float loadFactor() const
	{
		return static_cast<float>(_size) / kNumberOfSlots;
	}

	void dump() const
	{
		cout << "============ Hash table =============" << endl;

		for (size_t i=0; i<kNumberOfSlots; i++)
		{
			cout << i << ": ";

			auto element = _arr[i];

			if (!element)
			{
				cout << "/" << endl;
				continue;
			}

			cout << "(";

			while (element)
			{
				cout << element->key << (element->next ? ", " : "");

				element = element->next;
			}

			cout << ")" << endl;
		}

		cout << "Load factor: " << loadFactor() << endl;

		cout << "=====================================" << endl;
	}

private:
	size_t hash(int key) const
	{
		return key % kNumberOfSlots;
	}

private:
	static const int kNumberOfSlots = 17;

	Element *_arr[kNumberOfSlots];

	size_t _size = 0;
};

void test_HashTable()
{
	HashTable t;

	for (int i = 0; i < 17*3; i++)
	{
//		const int key = random(1, 999);
		const int key = i;

		auto element = new HashTable::Element(key);

		t.insert(element);
	}

	t.dump();

	auto key = 958;
	auto element = t.search(key);
	cout << "Search for key " << key << ": " << element << endl;

	key = 32;
	element = t.search(key);
	cout << "Search for key: " << key << ": " << element << endl;

	// Removing in the middle of a slot's list
	cout << "Removing element " << element->key << endl;
	t.remove(element);

	// Removing tail
	key = 15;
	element = t.search(key);
	cout << "Removing element " << element->key << endl;
	t.remove(element);

	// Removing head
	key = 49;
	element = t.search(key);
	cout << "Removing element " << element->key << endl;
	t.remove(element);

	t.dump();
}

#endif /* HashTable_h */
