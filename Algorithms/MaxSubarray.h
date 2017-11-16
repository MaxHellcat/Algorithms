//
//  MaxSubarray.h
//  Algorithms
//
//  Created by Max Reshetey on 14/11/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef MaxSubarray_h
#define MaxSubarray_h

#include "Array.h"

// TODO: Add divide'n'conquer implementation
// TODO: Return indices as well

// Time: Ø(n), space O(1)
int maxSubarray(const Array<int> &arr)
{
	// Note, this implementation ignores max subarrays with sum < 0.  If that is important, then
	// start maxSum with INT_MIN and modify body accordingly.
	int sumSoFar = 0, maxSum = 0;

	for (int i = 0; i < arr.size(); i++)
	{
		// We must take into account all differences, including negative ones
		sumSoFar += arr[i];

		if (sumSoFar < 0)
		{
			sumSoFar = 0;
		}
		else if (sumSoFar > maxSum)
		{
			maxSum = sumSoFar;
		}
	}

	return maxSum;
}

namespace MaxSubarray
{
	void test()
	{
		Array<int> arr = {13, -3, -25, 20, -3, -16, -23, 18, 20, -7, 12, -5, -22, 15, -4, 7}; // 43
//		Array<int> arr = {1, -4, 3, -4}; // 3
//		Array<int> arr = {-100};
//		Array<int> arr = {};

		print(arr);

		const auto maxSum = maxSubarray(arr);

        std::cout << "Max subarray: " << maxSum << std::endl;
	}
}

#endif /* MaxSubarray_h */
