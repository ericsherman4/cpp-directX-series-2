#include <iostream>
#include <vector>

int main()
{
    std::vector<int> v = { 0,1,2,3, 4,5,6,7 };

    // the vector class has an iterator defined.
    // iterators are like a pointer under the hood but better.
    // std::vector<int>::iterator i = v.begin();
    auto i = v.begin(); // cleaner


    v.erase(v.begin() + 3); // you have to use an iterator with the erase function. 
    // erase can also take a begginning an end. IT DOES INCLUDE BEGINNING BUT DOES NOT INCLUDE END.
    // this is basically python splicing. You can do this sequences of elements from one vector to another.
    // you can also initialize a new container using a subrange from another container with iterators
    v.erase(v.begin() + 3, v.begin() + 6);


    //std::cout << *i;    // have to deference the interator to get the element.
    //                    // This will typically return a reference to the element, not a value
    //i++;

    // super imporant to do preincrement because it can cause an iterator to be copied (because it returns current val and then increments object).
    // performance is better with it before.
    for (auto i = v.begin(), e = v.end(); i != e; ++i)
    {
        std::cout << *i << " ";
    }

    std::cout << std::endl << (v.end() - v.begin()); //prints distance between pointers

    //iterators will throw an expection if you try to access outside of array bounds which is super nice. they can also alert you to other problems that pointers and indexing cannot.
    // or say if you had an iterator to a certain location and then some other function deleted that location, the original interator would through an exception.
    // OR like in the case of vectors, say you had an element after you already made a couple of iterators, the array might reallocate to resize which would invalidate the iteators.


    // for looping for removing elements without being screwed on indices
    std::vector<int> w = { 0,1,2,3, 4,5,6,7 };

    for (auto i = w.begin(), e = w.end(); i != e;)
    {
        // erase all multiples of 3
        if (*i % 3 == 0)
        {
            // w.erase will return an iterator to the value after the erased one.
            i = w.erase(i);
            e = w.end(); // because e gets invalided with erase call (see docs) need to assign.
        }
        else
        {
            ++i;
        }
    }

  





    std::cin.get();
    return 0;
}