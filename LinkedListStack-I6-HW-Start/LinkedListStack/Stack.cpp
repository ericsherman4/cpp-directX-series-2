#include "Stack.h"
#include "assert.h"

Stack::Stack()
{
    size = 0;
    start = nullptr;
}

void Stack::Push(int val)
{

    if (size == 0)
    {
        start = new Node(val);
        ++size;
        return;
    }

    Node* test = start;

    while (test->next != nullptr)
    {
        test = test->next;
    }

    test->next = new Node(val);

    size++;
}

int Stack::Pop()
{
    if (Empty())
    {
        return 0;
    }

    if (size == 1)
    {
        int return_val = start->val;
        delete start;
        start = nullptr;
        size = 0;
        return return_val;
    }

    Node* test = start;
    Node* prev_node = nullptr;

    while (test->next != nullptr)
    {
        prev_node = test;
        test = test->next;
    }

    int return_val = test->val;
    delete prev_node->next;
    prev_node->next = nullptr;

    --size;
    return return_val;
}

int Stack::Size() const
{
    return size;
}

bool Stack::Empty() const
{
    return size == 0;
}

Stack::~Stack()
{
    if (!Empty())
    {
        delete start;
    }
}

Stack::Stack(const Stack& other)
{
    *this = other;

}

Stack& Stack::operator=(const Stack& other)
{
    assert(this != &other);

    if (other.size == 0)
    {
        return *this;
    }


    size = other.size;

    if (start == nullptr)
    {
        start = new Node(other.start->val);
    }
    Node* this_stack = start;
    Node* other_stack = other.start;

    while (other_stack->next != nullptr)
    {
        this_stack->next = new Node(other_stack->val);
        this_stack = this_stack->next;
        other_stack = other_stack->next;
    }


    return *this;
}

Node::Node(int val_in)
    : val(val_in)
    , next( nullptr)
{
}

Node::~Node()
{
    if (next != nullptr)
    {
        delete next;
    }
    next = nullptr;
}

// copy constructor
Node::Node(const Node& other)
{
    val = other.val;
    next = new Node(other.next->val);

}

//copy assign
Node& Node::operator=(const Node& other)
{
    assert(this != &other);

    // free the existing pointer
    delete next;
    next = nullptr;

    // copy the values over while making new node
    val = other.val;
    next = new Node(other.next->val);

    return *this;
}
