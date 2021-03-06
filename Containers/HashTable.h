//
//  HashTable.h
//  Algorithms
//
//  Created by Max Reshetey on 11/08/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef HashTable_h
#define HashTable_h

#include "iostream" // For logging
#include "cassert"

using namespace std; // For shorter logging

// TODO:
// a) Add remaining probing methods
// b) Array auto-adjusting depending on load factor a = n/m
// c) Wider range of hash functions

// A hash table implementation using various collisions handling strategies.
class HashTable final
{
public:
	// TODO: This struct contains extra fields that open addressing doesn't need.
	struct Element
	{
		Element(int aKey) : key(aKey) {}

		Element *next = nullptr, *prev = nullptr;
		int key;
	};

	void freeAll()
	{
		_collisionStrategy->freeArray(_arr);
	}

public:
	class CollisionResolutionStrategy
	{
	public:
		virtual ~CollisionResolutionStrategy() {}

		virtual Element *search(int aKey, Element *arr[]) const = 0;
		virtual void insert(Element *element, Element *arr[]) = 0;
		virtual void remove(Element *element, Element *arr[]) = 0;

		virtual void freeArray(Element *arr[]) = 0;
		virtual void dumpSlot(Element *element) = 0;

	protected:
		size_t hash(int key) const
		{
			return key % kNumberOfSlots;
		}
	};

	// For chaining, all three dictionary operations take constant time on average if
	// n = O(m), as a = O(m) / m = O(1).
	class Chaining : public CollisionResolutionStrategy
	{
	public:
		// TODO: Add detailed logging for dictionary methods
		virtual Element *search(int aKey, Element *arr[]) const override
		{
			auto element = arr[hash(aKey)];

			while (element && element->key != aKey)
			{
				element = element->next;
			}

			return element;
		}

		virtual void insert(Element *element, Element *arr[]) override
		{
			const auto slotIndex = hash(element->key);

			if (!arr[slotIndex])
			{
				arr[slotIndex] = element;
			}
			else
			{
				element->next = arr[slotIndex];
				arr[slotIndex]->prev = element;

				arr[slotIndex] = element;
			}
		}

		virtual void remove(Element *element, Element *arr[]) override
		{
			if (element->prev)
			{
				element->prev->next = element->next;
			}
			else
			{
				arr[hash(element->key)] = element->next;
			}

			if (element->next)
			{
				element->next->prev = element->prev;
			}

			delete element;
		}

		virtual void freeArray(Element *arr[]) override
		{
			for (int i=0; i<kNumberOfSlots; i++)
			{
				while (arr[i])
				{
					remove(arr[i], arr);
				}
			}
		}

		virtual void dumpSlot(Element *element) override
		{
			if (!element)
			{
				cout << "/" << endl;
				return ;
			}

			cout << "(";

			while (element)
			{
				cout << element->key << (element->next ? ", " : "");

				element = element->next;
			}

			cout << ")" << endl;
		}
	};

	// TODO: Add time/space bounds
	class OpenAddressing : public CollisionResolutionStrategy
	{
	public:
		// Special value indicating that slot's element has been deleted
		// TODO: Must be static
		Element *const DELETED = reinterpret_cast<Element *const>(0xDEADBEAF);

		virtual Element *search(int aKey, Element *arr[]) const override
		{
			cout << "Search " << aKey << " in slot ";

			for (int i=0; i<kNumberOfSlots; i++)
			{
				const auto slotIndex = quadraticProbing(aKey, i);

				cout << slotIndex;

				if (!arr[slotIndex])
				{
					cout << endl;

					return nullptr;
				}

				// We skip slots marked DELETED (they look valid, yet in fact nullptrs)
				if (arr[slotIndex] != DELETED && arr[slotIndex]->key == aKey)
				{
					cout << endl;

					return arr[slotIndex];
				}

				cout << ", ";
			}

			cout << endl;

			return nullptr;
		}

		virtual void insert(Element *element, Element *arr[]) override
		{
			cout << "Insert " << element->key << " into slot ";

			for (int i=0; i<kNumberOfSlots; i++)
			{
				const auto slotIndex = quadraticProbing(element->key, i);

				cout << slotIndex;

				if (!arr[slotIndex] || arr[slotIndex] == DELETED)
				{
					arr[slotIndex] = element;

					cout << endl;

					return ;
				}

				cout << ", ";
			}

			cout << endl;

			throw "hash table overflow";
		}

		virtual void remove(Element *element, Element *arr[]) override
		{
			cout << "Remove " << element->key << " from slot ";

			for (int i=0; i<kNumberOfSlots; i++)
			{
				const auto slotIndex = quadraticProbing(element->key, i);

				cout << slotIndex;

				if (arr[slotIndex] == element)
				{
					delete arr[slotIndex];

					arr[slotIndex] = DELETED;

					cout << endl;

					return ;
				}

				cout << ", ";
			}

			cout << endl;

			throw "element " + to_string(element->key) + " not in table";
		}

		virtual void freeArray(Element *arr[]) override
		{
			for (int i=0; i<kNumberOfSlots; i++)
			{
				if (arr[i] == DELETED)
				{
					arr[i] = nullptr;
				}
				else
				{
					// Double-delete of a pointer not set to nullptr after 1st delete, causes crash.
					delete arr[i];
//					arr[i] = nullptr;
				}
			}
		}

		virtual void dumpSlot(Element *element) override
		{
			if (element == DELETED)
			{
				cout << "del" << endl;
			}
			else
			{
				cout << (element ? "("+to_string(element->key)+")" : "/") << endl;
			}
		}

	private:
		size_t linearProbing(int aKey, int i) const
		{
			return (hash(aKey) + i) % kNumberOfSlots;
		}

		// TODO: Test this
		size_t quadraticProbing(int aKey, int i) const
		{
			const int c1 = 1, c2 = 3; // TODO: Wrong values cause probing sequences to not cover all slots.

			return (hash(aKey) + c1*i + c2*i*i) % kNumberOfSlots;
		}
	};

public:
	HashTable(CollisionResolutionStrategy *strategy): _collisionStrategy(strategy)
	{
		for (auto &val : _arr)
		{
			val = nullptr;
		}
	}

	~HashTable()
	{
		_collisionStrategy->freeArray(_arr);

		delete _collisionStrategy;
	}

// Core dictionary methods

	// Time: Ø(1 + loadFactor) - average, Ø(n) - worst
	Element *search(int aKey) //const
	{
		return _collisionStrategy->search(aKey, _arr);
	}

	// Time: Ø(1)
	void insert(Element *element)
	{
		assert(element);

		_size++;

		_collisionStrategy->insert(element, _arr);
	}

	// Time: Ø(1)
	void remove(Element *element)
	{
		assert(element);

		_size--;

		_collisionStrategy->remove(element, _arr);
	}

// Extra methods
	size_t size() const { return _size; }

	float loadFactor() const
	{
		return static_cast<float>(_size) / kNumberOfSlots;
	}

	void dump() //const
	{
		cout << "============ Hash table =============" << endl;

		for (size_t i=0; i<kNumberOfSlots; i++)
		{
			cout << i << ": ";

			_collisionStrategy->dumpSlot(_arr[i]);
		}

		cout << "Load factor: " << loadFactor() << endl;

		cout << "=====================================" << endl;
	}

private:
	static const int kNumberOfSlots = 17;

	Element *_arr[kNumberOfSlots];

	size_t _size = 0;

	CollisionResolutionStrategy *_collisionStrategy;
};

// TODO: Add tests for open addressing
void test_HashTable()
{
	HashTable t(new HashTable::Chaining);

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


	// TODO: Open addressing crashes with quadratic probing.
//	HashTable t(new HashTable::OpenAddressing);
//	
//	const int kNumOfSlots = 17;
//	
//	Array<int> arr(kNumOfSlots);
//	for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
//	arr.permute();
//	
//	for (int i = 0; i < kNumOfSlots; i++)
//	{
//		const int key = random(1, 99);
//		//		const int key = i;
//		//		const int key = arr[i];
//		
//		auto element = new HashTable::Element(key);
//		
//		t.insert(element);
//	}
//	
//	t.dump();
//	
//	const int key = 43;
//	auto elem = t.search(key);
//	
//	t.remove(elem);
//	t.dump();
//	
//	elem = t.search(39);
//	t.remove(elem);
//	t.dump();
//	
//	auto element = new HashTable::Element(9);
//	t.insert(element);
//	t.dump();
}

#endif /* HashTable_h */
