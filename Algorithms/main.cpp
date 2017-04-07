//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "Sorting.h"

#include "Defines.h"

int main(int argc, const char * argv[])
{
//	Array arr = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
	Array arr(100, true);

//	Array arr = {1, 2, 3, 4, 5};
//	Array arr = {5, 4, 3, 2, 1};
//	Array arr = {1, 1, 1, 1, 1};

	print(arr);

	quickSort(arr, 0, (int)arr.size() - 1);

	print(arr);

//	MaxHeap heap = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
//	MaxHeap heap(100, true);
//	heap.print();
//	heapSort(heap);
//	heap.print();

	return 0;
}
