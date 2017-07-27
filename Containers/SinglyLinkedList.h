//
//  SinglyLinkedList.h
//  Algorithms
//
//  Created by Max Reshetey on 27/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef SinglyLinkedList_h
#define SinglyLinkedList_h

class SinglyLinkedList
{
public:
	struct Node
	{
		Node(int aKey) : key(aKey) {}

		Node * next = nullptr;
		int key = 0;
	};

	Node *head() const { return _head; }

	void insert(Node *aNode)
	{
		aNode->next = _head;
		_head = aNode;
	}

	void remove(Node *aNode)
	{
		if (empty())
		{
			return;
		}

		if (aNode == head())
		{
			_head = _head->next;
			delete aNode;
		}
		else
		{
			auto tmpNode = head();

			while (tmpNode && tmpNode->next != aNode)
			{
				tmpNode = tmpNode->next;
			}

			if (tmpNode)
			{
				tmpNode->next = aNode->next;
				delete aNode;
			}
		}
	}

	Node *search(int aKey) const
	{
		auto node = head();

		while (node && node->key != aKey)
		{
			node = node->next;
		}

		return node;
	}

	bool empty() const { return _head == nullptr; }

private:
	Node *_head = nullptr;
};


#endif /* SinglyLinkedList_h */
