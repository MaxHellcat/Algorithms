//
//  ShellSort.h
//  Algorithms
//
//  Created by Max Reshetey on 04/09/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef ShellSort_h
#define ShellSort_h

// Time: O(n^2)
// Space: O(1)
// Stable: ?
// Adaptive: ?
void shellSort(Array<int> &arr)
{
	for (size_t gap = arr.size()/2; gap > 0; gap /= 2)
	{
		for (size_t i = gap; i < arr.size(); i++)
		{
			const int key = arr[i];

			size_t j = i;

			while (j >= gap && arr[j - gap] > key)
			{
				arr[j] = arr[j - gap];
				j = j - gap;
			}

			arr[j] = key;
		}
	}
}

void test_shellSort()
{
	initTestEnvironment();

	bool allPassed = true;

	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();

		print(arr);
		shellSort(arr);
		print(arr);

		const bool passed = arr.sorted();

		allPassed = allPassed && passed;

		std::cout << (passed ? "PASSED" : "FAILED") << std::endl;

		std::cout << std::endl;
	}

	std::cout << (allPassed ? "ALL TESTS PASSED" : "SOME TEST(S) FAILED") << std::endl;
	std::cout << std::endl;
}

#endif /* ShellSort_h */
