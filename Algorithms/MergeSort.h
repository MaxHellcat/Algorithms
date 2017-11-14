//
//  MergeSort.h
//  Algorithms
//
//  Created by Max Reshetey on 31/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef MergeSort_h
#define MergeSort_h

#include "Array.h"
#include "DoublyLinkedList.h"

// TODO: Implement merge sort for linked list!

using Node = DoublyLinkedList<int>::Node;

void merge_DLL(DoublyLinkedList<int> &list, Node **leftNode, Node **midNode, Node **rightNode);

struct Info
{
	Info(Node *left, Node *mid, Node *right): leftNode(left), midNode(mid), rightNode(right) {}

	Node *leftNode, *midNode, *rightNode;
};

// TODO: Draft version, not working properly
Info mergeSort_DLL(DoublyLinkedList<int> &list, Node *leftNode, Node *rightNode)
{
	std::cout << "(" << leftNode->key << ", " << rightNode->key << ")" << std::endl;
	
	Node *outerMidNode = leftNode;

	if (leftNode != rightNode)
	{
		// Divide (locate middle node between left and right nodes)
		auto node = leftNode;

		int count = 1;
		while (node != rightNode)
		{
			node = node->next;
			count++;
		}

		const int kNumberOfNodes = count;

		auto midNode = leftNode;
		count = 1;
		while (count < kNumberOfNodes/2)
		{
			midNode = midNode->next;
			count++;
		}
		
		outerMidNode = midNode;

		// Conquer
		mergeSort_DLL(list, leftNode, midNode);
		Info info = mergeSort_DLL(list, midNode->next, rightNode);
		
		leftNode = info.leftNode;
		midNode = info.midNode;
		rightNode = info.rightNode;

		// Combine
		merge_DLL(list, &leftNode, &midNode, &rightNode);
	}
	
	return Info(leftNode, outerMidNode, rightNode);
}

void merge_DLL(DoublyLinkedList<int> &list, Node **firstNode, Node **midNode, Node **lastNode)
{
	const auto kFirstNodePrev = (*firstNode)->prev;
	const auto kLastNodeNext = (*lastNode)->next;

	auto leftNode = *firstNode;
	auto rightNode = (*midNode)->next;

//	auto node = leftNode;
//	int count = 1;
//	while (node != *lastNode)
//	{
//		node = node->next;
//		count++;
//	}
//
//	const int kNumberOfNodes = count;
//	count = 1;

	while (true)
	{
		if (leftNode->key <= rightNode->key)
		{
			leftNode = leftNode->next;
		}
		else
		{
			const auto rightNodeNext = rightNode->next;

//			7, 8, 5, 6
//			5, 7, 8, 6
//			6, 5, 7, 8

			*midNode = rightNode;

			// Cut mid from current place
			if (rightNode->prev) {
				rightNode->prev->next = rightNode->next;
			}
			if (rightNode->next) {
				rightNode->next->prev = rightNode->prev;
			}

			rightNode->prev = nullptr;
			rightNode->next = nullptr;
			list.insert(rightNode, leftNode);

			rightNode = rightNodeNext; // jumps over lastNode finally
			
			if (rightNode == kLastNodeNext || leftNode == *midNode)
			{
				std::cout << "Break cos condition!" << std::endl;
				break;
			}

		}

//		count++;
	}

	if (kFirstNodePrev) {
		*firstNode = kFirstNodePrev->next;
	}
	else {
		*firstNode = list.head();
	}
	if (kLastNodeNext) {
		*lastNode = kLastNodeNext->prev;
	}
	else
	{
		auto node = list.head();
		while (node->next) { node = node->next; }
		*lastNode = node;
	}

	std::cout << list.description() << std::endl;
}

void merge(Array<int> &arr, int leftIndex, int midIndex, int rightIndex);

// Time: Ø(n*lgn) - worst/average/best
// Space: Ø(n)
// Stable: yes
// Adaptive: no
void mergeSort(Array<int> &arr, int leftIndex, int rightIndex)
{
	if (leftIndex < rightIndex)
	{
		const int midIndex = (leftIndex + rightIndex) / 2;

		mergeSort(arr, leftIndex, midIndex);
		mergeSort(arr, midIndex + 1, rightIndex);

		merge(arr, leftIndex, midIndex, rightIndex);
	}
}

void merge(Array<int> &arr, int leftIndex, int midIndex, int rightIndex)
{
	const int kLeftArraySize = midIndex - leftIndex + 1;
	Array<int> leftArray(kLeftArraySize);

	for (int i = 0; i < kLeftArraySize; i++)
	{
		leftArray[i] = arr[leftIndex + i];
	}

	const int kRightArraySize = rightIndex - midIndex;
	Array<int> rightArray(kRightArraySize);

	for (int i = 0; i < kRightArraySize; i++)
	{
		rightArray[i] = arr[(midIndex + 1) + i];
	}

	int li = 0, ri = 0;
	for (int i = leftIndex; i < rightIndex + 1; i++)
	{
		if (li < leftArray.size() && ri < rightArray.size())
		{
			if (leftArray[li] <= rightArray[ri])
			{
				arr[i] = leftArray[li];
				li = li + 1;
			}
			else
			{
				arr[i] = rightArray[ri];
				ri = ri + 1;
			}
		}
		else if (li == leftArray.size())
		{
			while (i < rightIndex + 1)
			{
				arr[i] = rightArray[ri];
				i = i + 1;
				ri = ri + 1;
			}

			break;
		}
		else if (ri == rightArray.size())
		{
			while (i < rightIndex + 1)
			{
				arr[i] = leftArray[li];
				i = i + 1;
				li = li + 1;
			}

			break;
		}
	}
}

void test_mergeSort()
{
	initTestEnvironment();

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		mergeSort(arr, 0, static_cast<int>(arr.size() - 1));
		print(arr);

		std::cout << std::endl;
	}
}

void test_mergeSort_DLL()
{
	initTestEnvironment();

	DoublyLinkedList<int> list;

	for (int i = 8; i > 0; i--)
	{
		list.insert(new DoublyLinkedList<int>::Node(i), nullptr);
	}

	std::cout << "Original list: " << std::endl;
	std::cout << list.description() << std::endl;

	auto node = list.head();
	while (node->next) { node = node->next; }

	mergeSort_DLL(list, list.head(), node);

	std::cout << "Sorted list: " << std::endl;
	std::cout << list.description() << std::endl;
}

#endif /* MergeSort_h */
