//
//  main.cpp
//  Algorithms
//
//  Created by Max Reshetey on 28/03/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#include "iostream" // For time()

#include "Sorting.h"
#include "Containers.h"

#include "unordered_set"

using namespace std;

int main(int argc, const char * argv[])
{
// TODO: Find a decent place for this
//	srand( (unsigned)time(nullptr) );

//	test_HashTable();
	
	HashTable t(new HashTable::OpenAddressing);

	const int kNumOfSlots = 17;

	Array<int> arr(kNumOfSlots);
	for (int i = 0; i < arr.size(); i++) { arr[i] = i + 1; }
	arr.permute();

	for (int i = 0; i < kNumOfSlots; i++)
	{
		const int key = random(1, 99);
//		const int key = i;
//		const int key = arr[i];

		auto element = new HashTable::Element(key);

		t.insert(element);
	}

	t.dump();

	const int key = 43;
	auto elem = t.search(key);

	t.remove(elem);
	t.dump();
	
	elem = t.search(39);
	t.remove(elem);
	t.dump();
	
	auto element = new HashTable::Element(9);
	t.insert(element);
	t.dump();
	

//	unordered_set<int> set;

//	set.max_load_factor(2.0);

//	auto f = set.hash_function();
	
//	for (int i = 0; i < 10; i++)
//	{
//		const int key = random(1, 999);
////		const int key = i;
//
////		set.insert("Hello" + to_string(i));
//		set.insert(key);
//	
////		auto element = new HashTable::Element(key);
////		t.insert(element);
//
////		cout << "Inserted " << key << " into slot " << f(key) << endl;
//	}
	
//	set.rehash(15);
	
//	cout << "See it " << set.max_bucket_count() << endl;
	
	
//	for (int i=0; i < set.bucket_count(); i++)
//	{
//		cout << i << ": ";
//
//		for (auto it=set.begin(i); it != set.end(i); it++)
//		{
//			cout << *it << ", ";
//		}
//
//		cout << endl;
//	}
//	
//	cout << "Load factor: " << set.load_factor() << endl;
	

	
	return 0;
}
