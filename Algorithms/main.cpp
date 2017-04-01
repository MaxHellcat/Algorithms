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
//	Array arr(100, true);

//	arr.print();

//	insertionSort(arr);
//	selectionSort(arr);
//	bubbleSort(arr);
//	mergeSort(arr, 0, (int)arr.size() - 1);

//	arr.print();

//	MaxHeap heap = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
	MaxHeap heap(100, true);
	heap.print();

	heapSort(heap);

	heap.print();

	return 0;
}
