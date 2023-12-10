#pragma once

class Stack
{
public:
	Stack();
	void Push( int val );
	int Pop();
	int Size() const;
	bool Empty() const;

	~Stack();
	Stack(const Stack& other);
	Stack& operator=(const Stack& other);

private:
	int size;
	class Node* top;
};

class Node
{
public:
	Node(int val_in);
	Node(int val_in, Node* next_in);
	~Node();
	Node(const Node& other);
	Node& operator=(const Node& other);

public:
	int val;
	Node* next;
};