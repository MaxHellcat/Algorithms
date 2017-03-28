//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "InsertionSort.h"
#include "Defines.h"

int main(int argc, const char * argv[])
{
//	Array arr = {5, 4, 6, 3, 1, 2};
	Array arr(100, true);

	arr.print();

	insertionSort(arr);

	arr.print();

	
	return 0;
}
