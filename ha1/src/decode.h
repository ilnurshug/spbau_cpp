#pragma once

#include "huffman.h"
#include <vector>

namespace huffman 
{

class decoder 
{
public:
    static void decode(std::vector<char>& in, long long input_len, std::vector<char>& out, huffman::node* root);
};

} // huffman