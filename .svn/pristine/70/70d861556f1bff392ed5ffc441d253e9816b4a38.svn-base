#define MSVC
#ifdef MSVC
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
//#include <crtdbg.h>
#endif

#include "au_list.h"
#include <cassert>
#include <iostream>


void task0()
{
	using namespace containers;
	int a = 0;
	au_list<int>::value_type vt = a;
	au_list<int>::reference ref = a;
	au_list<int>::const_reference cref = a;
	au_list<int>::pointer ptr = &a;
	au_list<int>::const_pointer cptr = &a;
	au_list<int>::size_type size = 0;
	(void)vt;
	(void)ref;
	(void)cref;
	(void)ptr;
	(void)cptr;
	(void)size;
}

void task1()
{
	using namespace containers;
	au_list<int>::node node;
	const au_list<int>::node cnode;
	au_list<int>::reference ref = node.get_value();
	assert(ref == int());
	au_list<int>::const_reference cref = cnode.get_value();
	assert(cref == int());

	int a = 5;
	node.set_value(a);
	node.get_value()++;
	assert(a == 5);
	assert(node.get_value() == a + 1);
}

void task2()
{
	using namespace containers;
	au_list<int> list;
	assert(list.begin() == list.end());
	assert(list.empty());
	assert(list.size() == 0);

	const au_list<int> clist;
	assert(clist.begin() == clist.end());
	assert(clist.empty());
	assert(clist.size() == 0);
}

template <class T>
void print_list(containers::au_list<T> &list)
{
    using namespace containers;
    
    au_list<int>::node* tmp = list.begin();
    while (tmp != list.end())
        std::cout << tmp->get_value() << ' ', tmp = tmp->get_next();
    
    std::cout << '\n';
}

void task3()
{
	using namespace containers;
	au_list<int> list;

        list.insert(list.end(), 5);
        assert(list.begin()->get_value() == 5);
	assert(!list.empty());
	assert(list.size() == 1);
	
        int arr[] = {1, 2, 3, 4};
        list.insert(list.begin(), &arr[0], &arr[3]);
	assert(!list.empty());
	assert(list.size() == 5);
        
        print_list(list);
        
	au_list<int> list_copy(list);
	assert(!list_copy.empty());
	assert(list_copy.size() == 5);
        
        print_list(list_copy);
        
        au_list<int> lst;
        for (int i = 1; i < 5; i++)
            lst.insert(lst.end(), i);
        
        print_list(lst);
}

void task4()
{
	using namespace containers;
	au_list<int> list;
	int arr[] = {1, 2, 3, 4};
	list.insert(list.begin(), &arr[0], &arr[3]);
        
        std::cout << '\n';
        print_list(list);
        
	auto after_erased = list.erase(list.begin());
        print_list(list);
	assert(list.size() == 3);
	assert(after_erased->get_value() == 2);
        
	au_list<int> cpy(list);
        
        list.clear();
        assert(list.size() == 0);
        print_list(cpy);
        assert(cpy.size() == 3);
        
        std::cout << '\n';
        after_erased = list.erase(list.begin(), list.end());
	assert(list.size() == 0);
	assert(after_erased == list.end());
        
        for (int i = 1; i < 5; i++)
            list.insert(list.end(), i);
        
        print_list(list);
        assert(list.size() == 4);
}

int main()
{
	task0();
	task1();
	task2();
	task3();
	task4();
	return 0;
}