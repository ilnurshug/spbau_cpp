#pragma once

#include "huffman.h"
// #include <unordered_map>
#include <vector>
#include <queue>

namespace huffman 
{
    
class encoder {
public:
    
    static void encode(huffman::char_map<int>& freq_map, huffman::char_map<huffman::code> &code_map, node* &root);
    
private:
    
    static node* build_tree(huffman::char_map<int>& freq_map, std::vector<node*>& leaf);
    
    static huffman::code get_code(node* leaf);
    
    class compare_node
    {
    public:
        bool operator () (node* lhs, node* rhs)
        {
            return lhs->freq >= rhs->freq;
        }
    };
};

} // huffman