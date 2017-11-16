//
//  Stack.h
//  Algorithms
//
//  Created by Max Reshetey on 17/11/2017.
//  Copyright © 2017 Max Reshetey. All rights reserved.
//

#ifndef Stack_h
#define Stack_h

#include "iostream" // For string
#include "cassert"

using namespace std;

// TODO: Add implementation using fixed size array

// A flexible size stack implementation using linked nodes.
class Stack
{
public:
	struct Node
	{
        Node(int aKey) : key(aKey) {}

		Node *next = nullptr;
		int key;
	};

    Stack() { cout << "Created stack " << this << endl; }

    ~Stack()
    {
        while (_top)
        {
            pop();
        }

        cout << "Deleted stack " << this << endl;
    }

// Core dictionary methods

    // Time O(1)
	void push(Node *node)
	{
		assert(node);

		node->next = _top;
		_top = node;
	}

    // Time O(1)
    void pop()
    {
        if (_top == nullptr) {
            throw "Stack underflow.";
        }

        const auto node = _top;

        _top = _top->next;

        delete node;
    }

// Aux methods
    bool empty() const { return _top == nullptr; }
    Node *top() const { return _top; }

    void push(int key) { push(new Node(key)); }

    string description() const
    {
        return traverseStack(_top) + ")";
    }

private:
    string traverseStack(const Node *node) const
    {
        if (node == nullptr) {
            return "(";
        }

        return traverseStack(node->next) + to_string(node->key) + ((node == _top) ? "" : ", ");
    }

private:
	Node *_top = nullptr;
};

void test_Stack()
{
    Stack stack;

    stack.push(1);
    stack.push(2);
    stack.push(3);
    stack.push(4);
    stack.push(5);

    cout << stack.description() << endl;
    
    cout << "Top: " << stack.top()->key << endl;
    
    stack.pop();
    stack.pop();

    cout << stack.description() << endl;
    
    cout << endl;
}

#endif /* Stack_h */
