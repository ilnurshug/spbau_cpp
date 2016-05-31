#include <iostream>
#include <fstream>
#include "mergesort.h"
#include <cstdlib>
using namespace std;

void resize(int* &array, size_t old_size, size_t new_size) {
    int* tmp = new int[new_size];
    for (size_t i = 0; i < old_size; i++)
        tmp[i] = array[i];
    
    delete [] array;
    array = tmp;
}
 
int main()
{
    fstream in("bin/input.txt");
    fstream out("bin/output.txt");
    
    size_t cur_size = 2;
    int* array = new int[cur_size];
    int num;
    size_t n = 0;
    while (in >> num) 
    {
        if (n >= cur_size)
        {
            resize(array, n, cur_size * 2);
            cur_size = cur_size * 2;
        }
        array[n++] = num;
    }
    mergesort(array, n);
    
    for (size_t i = 0; i < n; ++i)
    {
        out << array[i] << ' ';
    }
    
    return 0;
}