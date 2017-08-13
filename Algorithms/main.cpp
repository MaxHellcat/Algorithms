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
	srand( (unsigned)time(nullptr) );

	test_HashTable();

	HashTable t;

	for (int i = 0; i < 17; i++)
	{
		const int key = random(1, 999);
//		const int key = i;

		auto element = new HashTable::Element(key);

		t.insert(element);
	}

	t.dump();

	cout << "Load factor: " << t.loadFactor() << endl;
	

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
