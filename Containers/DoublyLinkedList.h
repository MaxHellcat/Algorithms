//
//  DoublyLinkedList.h
//  Algorithms
//
//  Created by Max Reshetey on 28/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef DoublyLinkedList_h
#define DoublyLinkedList_h

#include "iostream" // For std::string
#include "cassert"

template<typename T>
class DoublyLinkedList
{
public:
	struct Node
	{
		Node(T aKey) : key(aKey) {}

		Node *next = nullptr, *prev = nullptr;
		T key;
	};

public:
	// TODO: Duplicates SinglyLinkedList::~SinglyLinkedList()
	~DoublyLinkedList()
	{
		while (head())
		{
			remove(head());
		}
	}

// Core dictionary methods

	// TODO: Duplicates SinglyLinkedList::search()
	Node *search(T aKey) const
	{
		auto node = head();

		while (node && node->key != aKey)
		{
			node = node->next;
		}

		return node;
	}

	void insert(Node *aNode, Node *atNode)
	{
		assert(aNode);
		assert(aNode->next == nullptr && aNode->prev == nullptr);

		// TODO: This unrolled if-else chain isn't ideal
		if (_head == nullptr)
		{
			assert(atNode == nullptr);

			_head = aNode;
		
		}
		else if (atNode == _head)
		{
			aNode->next = _head;
			_head->prev = aNode;
			_head = aNode;
		}
		else
		{
			Node *tail = nullptr;

			// If we're appending, we need to locate tail first
			if (!atNode)
			{
				tail = _head;

				while (tail->next)
				{
					tail = tail->next;
				}
			}

			if (atNode)
			{
				aNode->prev = atNode->prev;
				aNode->next = atNode;
				atNode->prev->next = aNode;
				atNode->prev = aNode;
			}
			else
			{
				aNode->prev = tail;
				tail->next = aNode;
			}
		}
	}

	void remove(Node *aNode)
	{
		assert(aNode);

		if (aNode == _head)
		{
			_head = _head->next;
		}
		else
		{
			aNode->prev->next = aNode->next;
		}

		if (aNode->next)
		{
			aNode->next->prev = aNode->prev;
		}

		delete aNode;
	}

// Extra methods
// TODO: All duplicate the ones in SinglyLinkedList
	Node *head() const { return _head; }
	bool empty() const { return _head == nullptr; }

	void pushFront(Node *aNode) { insert(aNode, head()); }
	void pushBack(Node *aNode) { insert(aNode, nullptr); }

	size_t size() const
	{
		auto node = head();

		size_t count = 0;
		while (node)
		{
			node = node->next;
			count++;
		}

		return count;
	}

// TODO: Duplicates SinglyLinkedList::description()
	std::string description() const
	{
		std::string desc = "(";

		auto * node = head();

		while (node)
		{
			desc += std::to_string(node->key);
			desc += (node->next ? ", " : "");

			node = node->next;
		}

		desc += ")";

		return desc;
	}

private:
	Node *_head = nullptr;
};

// TODO: Rewrite to carefully test all functionality
void test_DoublyLinkedList()
{
	const int kNumberOfElements = 10;

	DoublyLinkedList<int> list;

	for (int i = 0; i < kNumberOfElements; i++)
	{
		list.insert(new DoublyLinkedList<int>::Node(i), nullptr);
		list.insert(new DoublyLinkedList<int>::Node(kNumberOfElements + i), list.head());
	}
	std::cout << list.description() << std::endl << std::endl;

	auto node = list.search(12);
	std::cout << "Searched element " << node << ", key " << node->key << std::endl << std::endl;

	list.insert(new DoublyLinkedList<int>::Node(-49), node);
	std::cout << list.description() << std::endl << std::endl;

	list.remove(node);
	std::cout << list.description() << std::endl << std::endl;

	for (int i = 0; i < kNumberOfElements * 2; i++)
	{
		list.remove(list.head());
	}
	std::cout << list.description() << std::endl << std::endl;
}

#endif /* DoublyLinkedList_h */
