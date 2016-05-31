#pragma once
#include <cstring>

struct node 
{
	int key;
	node* next;
};

node* mergesort(node* input, size_t size);
