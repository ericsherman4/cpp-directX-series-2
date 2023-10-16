#include <stdio.h>

int sum(const int * arr, int size)
{
    int sum = 0;
    const int* const end = arr + size;
    for (; arr < end; arr++)
    {
        sum += *arr;
    }
    return sum;
}

void reverse(int* arr, int size)
{
    for (int i = 0; i < size/2; i++)
    {
        
        int temp = arr[size - i -1];
        arr[size -i - 1] = arr[i];
        arr[i] = temp;
    }
}

int main()
{

    int arr[5] = { 1,2,3,4,5 };
    int arr2[6] = { 1,2,3,4,5,6 };
    sum(arr, 5);
    reverse(arr, 5);
    reverse(arr2, 6);


    return 0;
}