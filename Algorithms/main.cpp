//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "iostream" // For time()

//#include "Sorting.h"

//#include "Array.h"
#include "SinglyLinkedList.h"

int main(int argc, const char * argv[])
{
// TODO: Find a decent place for this
	srand( (unsigned)time(nullptr) );

//	test_quickSort();

//	Array arr(10);
//	print(arr);

	SinglyLinkedList list;

	list.insert(new SinglyLinkedList::Node(3));
	list.insert(new SinglyLinkedList::Node(5));
	list.insert(new SinglyLinkedList::Node(8));

	auto node = list.head();
	while (node)
	{
		std::cout << node->key << " -> ";

		node = node->next;
	}
	
	node = list.search(5);

	std::cout << "Found node with key " << node->key << std::endl;

	list.remove(list.head());
	list.remove(list.head());
//	list.remove(list.head());
	
	std::cout << std::endl;

	node = list.head();
	while (node)
	{
		std::cout << node->key << " -> ";
		
		node = node->next;
	}

	return 0;
}
