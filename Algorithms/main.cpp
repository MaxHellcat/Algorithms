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
	srand( unsigned(time(nullptr)) );

//	Array arr = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
//	Array arr(100, true);

	Array arr = {1, 2, 3, 4, 5, 6, 7, 8};
//	Array arr = {8, 7, 6, 5, 4, 3, 2, 1};

	print(arr);

	quickSort(arr, 0, (int)arr.size() - 1);

	print(arr);
	cout << "RunCount: " << runCount << "\n";

//	MaxHeap heap = {5, 4, 6, 3, 10, 2, 9, 7, 8, 1};
//	MaxHeap heap(100, true);
//	heap.print();
//	heapSort(heap);
//	heap.print();

	return 0;
}
