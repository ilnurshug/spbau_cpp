#include "mergesort.h"

node* mergesort(node* input, size_t size) {
    if (size <= 1) return input;
    
    if (size == 2) 
    {
        node* first = input;
        node* second = input->next;
        if (first->key > second->key)
        {
            int tmp = first->key;
            first->key = second->key;
            second->key = tmp;
        }
        return input;
    }
    
    node* second = input;
    node* first  = input;
    
    size_t count = 0;
    for (size_t i = 0; i < size / 2; i++, count++)
        second = second->next;
    
    first  = mergesort(first, size - count);
    second = mergesort(second, count);
    
    int* array = new int[size];
    size_t i = 0, j = 0, p = 0;
    while (i < size - count && j < count) 
    {
        if (first->key <= second->key) array[p++] = first->key, first = first->next, i++;
        else array[p++] = second->key, second = second->next, j++;
    }
    
    while (i < size - count) array[p++] = first->key, first = first->next, i++;
    while (j < count) array[p++] = second->key, second = second->next, j++;
    
    node* cur = input;
    for (size_t i = 0; i < size; i++)
        cur->key = array[i], cur = cur->next;
    
    return input;
}