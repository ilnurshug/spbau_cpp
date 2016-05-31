#include "encode.h"

#include<iostream>
using namespace std;

namespace huffman 
{

void encoder::encode(huffman::char_map<int>& freq_map, huffman::char_map<huffman::code> &code_map, node* &root)
{
    std::vector<node*> leaf;
    root = build_tree(freq_map, leaf);
    
    for (auto l : leaf)
    {
        code_map[l->sym] = get_code(l);
    }
}

node* encoder::build_tree(huffman::char_map<int>& freq_map, std::vector<node*>& leaf)
{
    std::priority_queue<node*, std::vector<node*>, compare_node> q;
    
    for (int c = -128; c <= 127; ++c)
    {
        if (freq_map[c] == 0) continue;
        
        node* l = new node(freq_map[c], (char)c);
        q.push(l);
        
        leaf.push_back(l);
    }
    /*for (auto pair : freq_map)
    {
        node* l = new node(pair.second, pair.first);
        q.push(l);
        
        leaf.push_back(l);
    }*/
    
    if (!q.size()) return 0;
    
    while (q.size() != 1) 
    {
        node* a = q.top(); q.pop();
        node* b = q.top(); q.pop();

	node* p = new node(a->freq + b->freq, ' ', a, b);
	a->p = b->p = p;
	q.push(p);
    }
    
    return q.top();
}

huffman::code encoder::get_code(node *leaf)
{
    huffman::code c;
    
    if (!leaf->p)
    {
        c.len  = 1;
        c.data = 0;
        return c;
    }
    
    while (leaf && leaf->p)
    {
        node* p = leaf->p;
        if (leaf == p->l)  set(c.len, 1, c.data);
        else               set(c.len, 0, c.data);
        
        leaf = p;
        c.len++;
    }
    
    return c;
}
    
} // huffman