#include <iostream>
#include <fstream>
#include "mergesort.h"
#include <cstdlib>
using namespace std;
#include <cassert>
 
int main()
{
 
        node* empty_list = new node{};
        assert(empty_list == mergesort(empty_list, 0));
        delete empty_list;
 
        node* one_list = new node{ 255 };
        node* result_head = mergesort(one_list, 1);
        assert(one_list == result_head);
        delete one_list;
 
        node* two_list_tail = new node{ 2 };
        node* two_list_head = new node{ 3, two_list_tail };
        result_head = mergesort(two_list_head, 2);
        assert(result_head->key == two_list_tail->key);
        assert(result_head->next == two_list_head);
        assert(result_head->next->next == nullptr);
        delete two_list_head;
        delete two_list_tail;
}