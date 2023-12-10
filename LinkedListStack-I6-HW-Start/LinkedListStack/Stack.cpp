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
    if (next != nullptr)
    {
        delete next;
        next = nullptr;
    }
}

Node::Node(const Node& other)
{
    *this = other;
}

Node& Node::operator=(const Node& other)
{
    if (this == &other)
    {
        return *this;
    }

    if (next != nullptr)
    {
        delete next;
    }
    val = other.val;
    next = new Node(other.next->val);
    return *this;
}

Stack::Stack()
    : size{0}
    , top{nullptr}
{
}

Stack::~Stack()
{
    if (top != nullptr)
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
    if (this == &other)
    {
        return *this;
    }

    if (other.size == 0)
    {
        size = other.size;
        top = nullptr;
        return *this;
    }

    size = other.size;

    if (size >= 1)
    {

        top = new Node(other.top->val); 
        //top = other.top; //this DOES NOT call copy constructor. it just assigns a pointer.
        //*top = *other.top; // copy contents of other.top to top. but you cant call node copy constructor on a nullptr as lhs.
        //*top = Node(*other.top);
    }

    Node* this_itr = top;
    Node* other_itr = other.top;

    while (other_itr->next != nullptr)
    {
        //*this_itr->next = *other_itr->next;
        //*this_itr->next = Node(*other_itr->next);
        this_itr->next = new Node(other_itr->next->val);
        this_itr = this_itr->next;
        other_itr = other_itr->next;
    }




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
    if (size == 0)
    {
        return -1;
    }
    int popped_val = top->val;
    Node* new_top = top->next;
    top->next = nullptr;
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
