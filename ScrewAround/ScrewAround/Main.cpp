#include <memory>
#include <string>
#include <iostream>

class Thing
{
public:
    Thing()
    {
        std::cout << "ctor called" << std::endl;
    }

    Thing(const Thing&)
    {
        std::cout << "copy ctr called" << std::endl;
    }

    ~Thing()
    {
        std::cout << "dtor called" << std::endl;
    }

    void mint() const
    {
        std::cout << "mint!\n";
    }
};

void f(const Thing t)
{
    std::cout << "f(): ";
    t.mint();
}

void g(const Thing& t)
{
    std::cout << "g(): ";
    t.mint();
}

void h(const Thing* t)
{
    std::cout << "h(): ";
    t->mint();
}

class ThingGrabber
{
public:

    // recommended to pass unique pointers by value
    //YOU CANNOT MAKE A COPY OF A UNIQUE POINTER DOESNT MAKE SENSE
    // need to use move semantics!
    void Give(std::unique_ptr<Thing> t)
    {
        pThing = std::move(t);
    }
    std::unique_ptr<Thing> Take()
    {
        return std::move(pThing);
    }
private:
    std::unique_ptr<Thing> pThing;
};

// typical OOP factory function
std::unique_ptr<Thing> MakeThing()
{
    // notice dont need to do move semantics if you define a local variable and then return that
    // compiler realizes it will die anyway so will move resources for you.
    // if you are returning directly, its a temporary so its an rvalue reference already
    return std::make_unique<Thing>();
}

int main() 
{
    // Important to note that classes with unique pointers can't be copied because it will be blocked!
    // no copy constrcutor defined for unique pointer. but move constructor will work.

    {
        ThingGrabber tg;
#if 0        
        auto t = MakeThing();
        tg.Give(std::move(t));
#else
        // gets passed as an rvalue since its a temporary
        tg.Give(MakeThing());
#endif
        tg.Take();
    }

    std::cin.get();
    return 0;
}