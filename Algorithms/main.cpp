//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "iostream" // For time()

//#include "Sorting.h"

#include "Array.h"

int main(int argc, const char * argv[])
{
// TODO: Find a decent place for this
	srand( (unsigned)time(nullptr) );

//	test_quickSort();
	
	Array arr(10);
	
	print(arr);

	return 0;
}
