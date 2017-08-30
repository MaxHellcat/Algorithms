//
//  BinarySearchTree.h
//  Algorithms
//
//  Created by Max Reshetey on 29/08/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef BinarySearchTree_h
#define BinarySearchTree_h

#include "iostream" // For logging
#include "cassert"

using namespace std; // For shorter logging

// TODO:
// a) We lack good visualisation of a tree
// b) Reliable test for a randomly built tree
// c) Both recursive/iterative versions for core dictionary methods

class BinarySearchTree final
{
public:
	struct Element
	{
		Element(int aKey) : key(aKey) {}

		Element *parent = nullptr, *left = nullptr, *right = nullptr;
		int key;
	};

	~BinarySearchTree()
	{
		deleteTree(_root);

		cout << "Tree deleted, size: " << _size << endl;
	}

// Core dictionary methods

	// Time: O(h)
	Element *search(Element *root, int aKey) const
	{
		assert(root);

		if (root == nullptr || aKey == root->key)
		{
			return root;
		}

		if (aKey < root->key)
		{
			return search(root->left, aKey);
		}
		else
		{
			return search(root->right, aKey);
		}
	}

	// Time: O(h)
	void insert(Element *element)
	{
		assert(element);

		Element *y = nullptr;
		auto x = _root;

		while (x)
		{
			y = x;

			if (element->key < x->key)
			{
				x = x->left;
			}
			else
			{
				x = x->right;
			}
		}

		element->parent = y;

		if (!y)
		{
			_root = element;
		}
		else if (element->key < y->key)
		{
			y->left = element;
		}
		else
		{
			y->right = element;
		}

		_size++;
	}

	// Time: O(h)
	void remove(Element *element)
	{
		assert(element);

		if (element->right == nullptr)
		{
			transplant(element, element->left);
		}
		else if (element->left == nullptr)
		{
			transplant(element, element->right);
		}
		else
		{
			auto y = minimum(element->right);

			if (y->parent != element)
			{
				transplant(y, y->right);
				y->right = element->right;
				y->right->parent = y;
			}

			transplant(element, y);
			y->left = element->left;
			y->left->parent = y;
		}

		delete element;

		_size--;
	}

	// Time: O(h)
	Element *minimum(Element *element) const
	{
		assert(element);

		if (element->left)
		{
			return minimum(element->left);
		}

		return element;
	}

	// Time: O(h)
	Element *maximum(Element *element) const
	{
		assert(element);

		if (element->right)
		{
			return maximum(element->right);
		}

		return element;
	}

	// Time: O(h)
	Element *successor(Element *element) const
	{
		assert(element);

		if (element->right)
		{
			return minimum(element->right);
		}

		auto y = element->parent;

		while (y && element == y->right)
		{
			element = y;
			y = y->parent;
		}

		return y;
	}

	// Time: O(h)
	Element *predecessor(Element *elem) const
	{
		assert(elem);

		if (elem->left)
		{
			return maximum(elem->left);
		}

		auto y = elem->parent;

		while (y && elem == y->left)
		{
			elem = y;
			y = y->parent;
		}

		return y;
	}

// Aux methods
	// Time: Ø(n)
	void traverseInorder(Element *root) const
	{
		if (root)
		{
			traverseInorder(root->left);

			std::cout << root->key << " ";

			traverseInorder(root->right);
		}

		if (root == _root)
		{
			cout << "(size: " << _size << ")";
		}
	}

	Element *root() const { return _root; }

	size_t size() const { return _size; }

private:
	// Time: O(1)
	void transplant(Element *u, Element *v)
	{
		if (u->parent == nullptr)
		{
			_root = v;
		}
		else if (u->parent->left == u)
		{
			u->parent->left = v;
		}
		else
		{
			u->parent->right = v;
		}

		if (v)
		{
			v->parent = u->parent;
		}
	}

	void deleteTree(Element *root)
	{
		if (root)
		{
			deleteTree(root->left);
			deleteTree(root->right);

			remove(root);
		}
	}

private:
	Element *_root = nullptr;

	size_t _size = 0;
};

void test_binarySearchTree()
{
	{
		BinarySearchTree tree;

		Array<int> arr = {15, 6, 18, 3, 7, 17, 20, 2, 4, 13, 9};
		for (int i=0; i<arr.size(); i++)
		{
			tree.insert(new BinarySearchTree::Element(arr[i]));
		}

		tree.traverseInorder(tree.root());
		cout << endl;

		cout << "Min: " << tree.minimum(tree.root())->key << "\n";
		cout << "Max: " << tree.maximum(tree.root())->key << "\n";
		
		{
			const int kSuccessorKey = 15;
			auto element = tree.search(tree.root(), kSuccessorKey);
			cout << "Successor of " << kSuccessorKey << ": " << tree.successor(element)->key << endl;
		}

		{
			const int kSuccKeyRightNil = 13;
			auto element = tree.search(tree.root(), kSuccKeyRightNil);
			cout << "Successor of " << kSuccKeyRightNil << ": " << tree.successor(element)->key << endl;
		}

		{
			const int kPredKey = 15;
			auto element = tree.search(tree.root(), kPredKey);
			cout << "Predecessor of " << kPredKey << ": " << tree.predecessor(element)->key << endl;
		}

		{
			const int kPredKey = 9;
			auto element = tree.search(tree.root(), kPredKey);
			cout << "Predecessor of " << kPredKey << ": " << tree.predecessor(element)->key << endl;
		}

		{
			const int kSearchedKey = 6;
			auto element = tree.search(tree.root(), kSearchedKey);
			cout << "Searching key " << kSearchedKey << ": " << element << endl;
		}

		{
			const int kRemovedKeyLeaf = 4;
			cout << "Removing leaf: " << kRemovedKeyLeaf << endl;
			auto element = tree.search(tree.root(), kRemovedKeyLeaf);
			tree.remove(element);
		}

		{
			const int kRemovedKeyRightNil = 3;
			cout << "Removing right nil: " << kRemovedKeyRightNil << endl;
			auto element = tree.search(tree.root(), kRemovedKeyRightNil);
			tree.remove(element);
		}

		{
			// This deletion must go before
			const int kRemovedKeyLeftNilRightNotMin = 7;
			cout << "Removing left nil, right not min: " << kRemovedKeyLeftNilRightNotMin << endl;
			auto element = tree.search(tree.root(), kRemovedKeyLeftNilRightNotMin);
			tree.remove(element);
		}

		{
			// this one
			const int kRemovedKeyLeftNilRightMin = 9;
			cout << "Removing left nil, right min: " << kRemovedKeyLeftNilRightMin << endl;
			auto element = tree.search(tree.root(), kRemovedKeyLeftNilRightMin);
			tree.remove(element);
		}

		tree.traverseInorder(tree.root());
		cout << endl;

		{
			const int kInsertedKey = 16	;
			cout << "Inserting element with key " << kInsertedKey << endl;
			tree.insert(new BinarySearchTree::Element(kInsertedKey));
		}

		tree.traverseInorder(tree.root());
		cout << endl;
	}
}

#endif /* BinarySearchTree_h */
