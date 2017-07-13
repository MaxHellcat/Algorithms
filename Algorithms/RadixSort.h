//
//  RadixSort.h
//  Algorithms
//
//  Created by Max Reshetey on 13/07/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef RadixSort_h
#define RadixSort_h

#include "Defines.h"
#include "CountingSort.h"

// Prerequisites:
// The implementation here assumes all numbers have the same number of digits. It can be easily
// upgraded to support variable-bit numbers by prepending shorter numbers with zeroes.

// Time: Ø(d(n+k)) (or Ø((b/r)(n+2^r)) = Ø(n), for r (bits per digit) <= lgn, see 8.3 Radix sort in CRLS)
// Space: Ø(n + k)
void radixSort(Array &arr, int d)
{
	const int kMaxDigitValue = 9; // Assuming each digit is a decimal number

	for (int i = 0; i < d; i++)
	{
		// The least significant digit first
		const int indexOfDigitToSortBy = d - i - 1;

		countingSort(arr, kMaxDigitValue, indexOfDigitToSortBy);
	}
}

void test_radixSort()
{
//	Array arr = {329, 457, 657, 839, 436, 720, 355};
	Array arr(25);
	for (auto &val : arr)
	{
		val = random(100, 999);
	}

	print(arr);

	const int d = numberOfDigits(arr[0]);

	radixSort(arr, d);

	print(arr);
}


#endif /* RadixSort_h */
