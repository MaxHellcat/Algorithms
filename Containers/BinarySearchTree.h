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

// An implementation of a binary search tree.
// Since there's no any guarrantee on whether a tree is balanced, all running times below
// depend on tree height h, and not number of elements n. The height is O(lgn) for a balanced tree
// and O(n) for unbalanced.
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
	Element *search(int aKey) const
	{
		auto elem = _root;

		while (elem && elem->key != aKey)
		{
			elem = aKey < elem->key ? elem->left : elem->right;
		}

		return elem;
	}

	// Time: O(h)
	Element *searchRecursive(Element *root, int aKey) const
	{
		assert(root);
		
		if (root == nullptr || aKey == root->key)
		{
			return root;
		}
		
		if (aKey < root->key)
		{
			return searchRecursive(root->left, aKey);
		}
		else
		{
			return searchRecursive(root->right, aKey);
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
	void insertRecursive(Element *root, Element *elem)
	{
		assert(root);
		assert(elem);

		if (elem->key < root->key)
		{
			if (root->left)
			{
				insertRecursive(root->left, elem);
			}
			else
			{
				root->left = elem;
				elem->parent = root;
			}
		}
		else
		{
			if (root->right)
			{
				insertRecursive(root->right, elem);
			}
			else
			{
				root->right = elem;
				elem->parent = root;
			}
		}

		if (root == _root)
		{
			_size++;
		}
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
	Element *minimum(Element *root) const
	{
		assert(root);

		while (root->left)
		{
			root = root->left;
		}

		return root;
	}

	// Time: O(h)
	Element *minimumRecursive(Element *root) const
	{
		assert(root);

		if (root->left)
		{
			return minimumRecursive(root->left);
		}

		return root;
	}

	// Time: O(h)
	Element *maximum(Element *root) const
	{
		assert(root);

		while (root->right)
		{
			root = root->right;
		}

		return root;
	}

	// Time: O(h)
	Element *maximumRecursive(Element *root) const
	{
		assert(root);

		if (root->right)
		{
			return maximumRecursive(root->right);
		}

		return root;
	}

	// Time: O(h)
	Element *successor(Element *elem) const
	{
		assert(elem);

		if (elem->right)
		{
			return minimum(elem->right);
		}

		auto y = elem->parent;

		while (y && elem == y->right)
		{
			elem = y;
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
	// TODO: Iterative version of this method.
	void traverseInorder(Element *root) const
	{
		if (root)
		{
			traverseInorder(root->left);

			cout << root->key << " ";

			traverseInorder(root->right);
		}

		if (root == _root)
		{
			cout << "(size: " << _size << ")";
		}
	}

	// Time: Ø(n)
	void traverseInorderIterative(Element *root) const
	{
		Element *lastVisited = nullptr;

		while (root)
		{
			if (lastVisited == root->right)
			{
				lastVisited = root;
				root = root->parent;
				continue;
			}

			if (lastVisited != root->left && root->left)
			{
				lastVisited = root;
				root = root->left;
				continue;
			}

			cout << root->key << " ";

			if (root->right)
			{
				lastVisited = root;
				root = root->right;
				continue;
			}

			// Case when we printed a leaf
			lastVisited = root;
			root = root->parent;
		}

		cout << "(size: " << _size << ")";
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

		cout << "Min (iterative): " << tree.minimum(tree.root())->key << "\n";
		cout << "Min (recursive): " << tree.minimumRecursive(tree.root())->key << "\n";
		cout << "Max (iterative): " << tree.maximum(tree.root())->key << "\n";
		cout << "Max (recursive): " << tree.maximumRecursive(tree.root())->key << "\n";

		{
			const int kSuccessorKey = 15;
			auto element = tree.search(kSuccessorKey);
			cout << "Successor of " << kSuccessorKey << ": " << tree.successor(element)->key << endl;
		}

		{
			const int kSuccKeyRightNil = 13;
			auto element = tree.search(kSuccKeyRightNil);
			cout << "Successor of " << kSuccKeyRightNil << ": " << tree.successor(element)->key << endl;
		}

		{
			const int kPredKey = 15;
			auto element = tree.search(kPredKey);
			cout << "Predecessor of " << kPredKey << ": " << tree.predecessor(element)->key << endl;
		}

		{
			const int kPredKey = 9;
			auto element = tree.search(kPredKey);
			cout << "Predecessor of " << kPredKey << ": " << tree.predecessor(element)->key << endl;
		}

		{
			const int kSearchedKey = 6;
			auto element = tree.search(kSearchedKey);
			cout << "Searching (iterative) key " << kSearchedKey << ": " << element << endl;

			element = tree.searchRecursive(tree.root(), kSearchedKey);
			cout << "Searching (recursive) key " << kSearchedKey << ": " << element << endl;
		}

		{
			const int kRemovedKeyLeaf = 4;
			cout << "Removing (leaf) key " << kRemovedKeyLeaf << endl;
			auto element = tree.search(kRemovedKeyLeaf);
			tree.remove(element);
		}

		{
			const int kRemovedKeyRightNil = 3;
			cout << "Removing (right nil) key " << kRemovedKeyRightNil << endl;
			auto element = tree.search(kRemovedKeyRightNil);
			tree.remove(element);
		}

		{
			// This deletion must go before
			const int kRemovedKeyLeftNilRightNotMin = 7;
			cout << "Removing (left nil, right not min) key " << kRemovedKeyLeftNilRightNotMin << endl;
			auto element = tree.search(kRemovedKeyLeftNilRightNotMin);
			tree.remove(element);
		}

		{
			// this one
			const int kRemovedKeyLeftNilRightMin = 9;
			cout << "Removing (left nil, right min) " << kRemovedKeyLeftNilRightMin << endl;
			auto element = tree.search(kRemovedKeyLeftNilRightMin);
			tree.remove(element);
		}

		tree.traverseInorder(tree.root());
		cout << endl;

		{
			const int kInsertedKey = 16;
			cout << "Inserting key (iterative) " << kInsertedKey << endl;
			tree.insert(new BinarySearchTree::Element(kInsertedKey));

			tree.traverseInorderIterative(tree.root());
			cout << endl;
		}

		{
			const int kInsertedKey = 14;
			cout << "Inserting key (recursive) " << kInsertedKey << endl;
			tree.insertRecursive(tree.root(), new BinarySearchTree::Element(kInsertedKey));

			tree.traverseInorderIterative(tree.root());
			cout << endl;
		}
	}
}

#endif /* BinarySearchTree_h */
