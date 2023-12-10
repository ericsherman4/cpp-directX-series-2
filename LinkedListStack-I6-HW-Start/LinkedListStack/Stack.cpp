#include "Stack.h"
#include "assert.h"

Node::Node(int val_in)
    : val{val_in}
    , next{nullptr}
{
}

Node::Node(int val_in, Node* next_in)
    : val{val_in}
    , next{next_in}
{
}

Node::~Node()
{
    // should never call delete on a node that has a null next pointer right/
    delete next;
    next = nullptr;
}

Node::Node(const Node& other)
    : val{other.val}
    , next{nullptr}
{
    if (other.next != nullptr)
    {
        // This should recursively copy every node.
        next = new Node(*other.next);
    }
}

Node* Node::DisconnectNode(void)
{
    Node* ptr_to_next = next;
    next = nullptr;
    return ptr_to_next;
}

Stack::Stack()
    : size{0}
    , top{nullptr}
{
}

Stack::~Stack()
{
    if (!Empty()) // same as checking if top is nullptr
    {
        delete top; //should delete everything down the chain
    }
}

Stack::Stack(const Stack& other)
{
    *this = other;
}

Stack& Stack::operator=(const Stack& other)
{
    // check for self assignment
    if (this == &other)
    {
        return *this;
    }

    // check if self is empty or not
    if (!Empty())
    {
        delete top;
        top = nullptr;
    }

    // Check for assigning nothing over.
    if (other.Empty())
    {
        size = 0;
        top = nullptr;
        return *this;
    }

    size = other.size;
    top = new Node(*other.top);
    return *this;
}

void Stack::Push(int val)
{
    Node* new_node = new Node{ val, top };
    top = new_node;
    ++size;
}

int Stack::Pop()
{
    if (Empty())
    {
        return -1;
    }

    int popped_val = top->val;
    Node * new_top = top->DisconnectNode();
    delete top;
    top = new_top;
    --size;
    return popped_val;
}

int Stack::Size() const
{
    return size;
}

bool Stack::Empty() const
{
    return size == 0;
}
