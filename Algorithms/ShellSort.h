//
//  ShellSort.h
//  Algorithms
//
//  Created by Max Reshetey on 04/09/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef ShellSort_h
#define ShellSort_h

void shellSort(Array<int> &arr)
{

}

void test_shellSort()
{
	for (int i = 2; i < 10; i++)
	{
		Array<int> arr(i);
		for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
		arr.permute();
		
		print(arr);
		shellSort(arr);
		print(arr);
		
		std::cout << std::endl;
	}
}

#endif /* ShellSort_h */
