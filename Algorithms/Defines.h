//
//  Defines.h
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Defines_h
#define Defines_h

//#include "iostream"
//#include "cstdlib" // For rand, srand

int random(int min, int max)
{
	return min + (rand() % (max - min + 1));
}

void swap(int &val1, int &val2)
{
	const int tmpVal = val1;
	val1 = val2;
	val2 = tmpVal;
}

// TODO: This assumes that val is decimal
int numberOfDigits(int val)
{
	int count = 0;

	while (val && (val /= 10) >= 0) { count++; }

	return count;
}

// TODO: This assumes that val is decimal
int digitAtIndex(int val, int index)
{
	int i = numberOfDigits(val) - 1;

	while (i > index)
	{
		val = val / 10;
		i--;
	}

	return val % 10;
}

#endif /* Defines_h */
