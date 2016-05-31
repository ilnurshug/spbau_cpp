#include "decode.h"

namespace huffman
{
    
void decoder::decode(std::vector<char>& in, long long input_len, std::vector<char>& out, huffman::node* root)
{
    node* t = root;
    
    long long cur = 0;
    for (auto byte : in)
        for (size_t pos = 0; pos < 8 && cur < input_len; ++pos, ++cur)
        {
            size_t bit = huffman::get(7 - pos, byte);
            
            if (t->l && t->r)
            {
                t = (bit == 1 ? t->l : t->r);
            }
            
            if (!t->l && !t->r)
            {
                out.push_back(t->sym);
                t = root;
            }
        }
}
    
} // huffman