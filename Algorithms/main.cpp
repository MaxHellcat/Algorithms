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
// TODO: Find a decent place for this
	srand( (unsigned)time(nullptr) );

//	Array arr = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
//	Array arr = {4, 7, 16, 9, 14, 15, 5, 11, 3, 12, 1, 6, 13, 10, 2, 8};
	Array arr(16);
	arr.permute();
	print(arr);

	quickSort(arr, 0, (int)arr.size() - 1);

	print(arr);

//	MaxHeap heap = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
//	MaxHeap heap(100, true);
//	print(heap);
//	heapSort(heap);
//	print(heap);

	return 0;
}
