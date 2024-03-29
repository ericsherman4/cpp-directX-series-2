#include <iostream>
#include <vector>


class Thing
{
public:
    Thing()
    {
        std::cout << "Calling constructor" << std::endl;
    }
    Thing(Thing&& t) noexcept
    {
        std::cout << "Calling move constructor" << std::endl;
    }
    Thing(const Thing& t)
    {
        std::cout << "Calling copy constructor" << std::endl;
    }
    ~Thing()
    {
        std::cout << "Calling destructor" << std::endl;
    }
};

int main()
{
    std::vector<Thing> t;
    t.emplace_back();
    std::cout << "-------" << std::endl;
    t.emplace_back();
    std::cout << "-------" << std::endl;
    t.emplace_back();


    std::cin.get();
    return 0;
}





#if 0
int sum(int a, int b)
{
    if (a == 77)
    {
        throw std::runtime_error ("<a> is a bad number");
    }

    if (b == 55)
    {
        throw 1337;
    }

    return a + b;
}

int f(int x, int y, int z)
{
    try
    {
        return sum(x, y) * sum(y, z);
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Caught in f: " << e.what() << std::endl;
        throw; // throw e also works but just using throw will automatically rethrow the error.
    }
}


int main()
{

    try
    {
        std::cout << f(1, 55, 7) << std::endl;
    }
    catch (const std::runtime_error& e)
    {
        std::cout << "Caught in main: " << e.what() << std::endl;
    }
    // can supply multiple errors.
    catch (const int& i)
    {
        std::cout << "Caught an int in main: " << i << std::endl;
    }
    // catches anything that tries to come throw.
    // Doens't help cause there's no object
    catch (...)
    {
    std:: cout << "Caught *something* in main" << std::endl;
    }

    std::cin.get();
    return 0;
}
#endif