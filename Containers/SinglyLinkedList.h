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
	~SinglyLinkedList()
	{
		removeAll();
	}

// Core dictionary methods
	Node *search(int aKey) const
	{
		auto node = _head;

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

		if (_head == nullptr)
		{
			assert(atNode == nullptr);

			_head = aNode;
		}
		else if (atNode == _head)
		{
			aNode->next = _head;
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

		if (aNode == _head)
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
//	const Node *head() const { return _head; }
//	bool empty() const { return _head == nullptr; } // Uncommment when needed

	void pushFront(Node *aNode) { insert(aNode, _head); }
	void pushBack(Node *aNode) { insert(aNode, nullptr); }

	void removeAll()
	{
		while (_head)
		{
			remove(_head);
		}
	}

	// TODO: Must go away after iterator is introduced.
	std::string description() const
	{
		std::string desc = "(";

		auto *node = _head;

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
	Node *previous(const Node *ofNode) const
	{
		auto node = _head;

		while (node && node->next != ofNode)
		{
			node = node->next;
		}

		return node;
	}

private:
	Node *_head = nullptr;
};

// TODO: Rewrite to carefully test all functionality
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

	list.removeAll();
	std::cout << list.description() << std::endl << std::endl;
};

#endif /* SinglyLinkedList_h */
