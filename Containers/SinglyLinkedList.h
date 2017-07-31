//
//  SinglyLinkedList.h
//  Algorithms
//
//  Created by Max Reshetey on 27/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef SinglyLinkedList_h
#define SinglyLinkedList_h

#include "iostream" // For std::string
#include "cassert"

class SinglyLinkedList
{
public:
	struct Node
	{
		Node(int aKey) : key(aKey) {}

		Node * next = nullptr;
		int key;
	};

public:
// Core methods
	Node *search(int aKey) const
	{
		auto node = head();

		while (node && node->key != aKey)
		{
			node = node->next;
		}

		return node;
	}

	// Pushes back, if atNode is nil
	void insert(Node *aNode, Node *atNode)
	{
		assert(aNode);

		if (empty() || atNode == head())
		{
			aNode->next = _head; // TODO: See if it can be merged with similar below
			_head = aNode;
		}
		else
		{
			auto prevNode = previous(atNode);
			assert(prevNode);

			aNode->next = atNode;
			prevNode->next = aNode;
		}
	}

	void remove(Node *aNode)
	{
		assert(aNode);

		if (aNode == head())
		{
			_head = _head->next;
		}
		else
		{
			auto prevNode = previous(aNode);
			assert(prevNode);

			prevNode->next = aNode->next;
		}

		delete aNode;
	}

// Extra methods
	Node *head() const { return _head; }
	bool empty() const { return _head == nullptr; }

	void pushFront(Node *aNode)
	{
		insert(aNode, head());
	}

	void pushBack(Node *aNode)
	{
		insert(aNode, nullptr);
	}

	// TODO: Must go away after iterator is introduced.
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
	// Returns tail, if ofNode is nil
	Node *previous(Node *ofNode) const
	{
		auto prevNode = head();

		while (prevNode && prevNode->next != ofNode)
		{
			prevNode = prevNode->next;
		}

		return prevNode;
	}

private:
	Node *_head = nullptr;
};

void test_SinglyLinkedList()
{
	const int kNumberOfElements = 10;

	SinglyLinkedList list;

	for (int i = 0; i < kNumberOfElements; i++)
	{
		list.pushBack(new SinglyLinkedList::Node(i));
		list.pushFront(new SinglyLinkedList::Node(kNumberOfElements + i));
	}
	std::cout << list.description() << std::endl << std::endl;

	auto node = list.search(12);
	std::cout << "Searched element " << node << ", key " << node->key << std::endl << std::endl;

	list.insert(new SinglyLinkedList::Node(-49), node);
	std::cout << list.description() << std::endl << std::endl;

	list.remove(node);
	std::cout << list.description() << std::endl << std::endl;

	for (int i = 0; i < kNumberOfElements * 2; i++)
	{
		list.remove(list.head());
	}
	std::cout << list.description() << std::endl << std::endl;
};

#endif /* SinglyLinkedList_h */
