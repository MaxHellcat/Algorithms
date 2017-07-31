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

	// Core methods

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

		if (empty() || atNode == head())
		{
			aNode->next = _head;

			if (!empty())
			{
				_head->prev = aNode;
			}

			_head = aNode;
		}
		else if (!atNode)
		{
			auto tail = head();

			while (tail->next)
			{
				tail = tail->next;
			}

			tail->next = aNode;
			aNode->prev = tail;
		}
		else
		{
			atNode->prev->next = aNode;
			aNode->prev = atNode->prev;
			aNode->next = atNode;
			atNode->prev = aNode;
		}
	}

	void remove(Node *aNode)
	{
		assert(aNode);

		if (aNode == head())
		{
			_head = aNode->next;
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
	Node *head() const { return _head; }
	bool empty() const { return _head == nullptr; }

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
