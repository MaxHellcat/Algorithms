//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "iostream" // For time()

#include "Sorting.h"
#include "Containers.h"

int main(int argc, const char * argv[])
{
// TODO: Find a decent place for this
	srand( (unsigned)time(nullptr) );

//	test_SinglyLinkedList();
//	test_DoublyLinkedList();

//	Array<float> arr = {0.45, 0.62, 0.56};
//	print(arr);
	
	test_mergeSort();
	



	return 0;
}
