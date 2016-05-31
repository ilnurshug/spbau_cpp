#include "compress.h"

namespace huffman
{

long long compress::cmprs(std::vector<char>& in, std::vector<char>& out,
                            huffman::node* &root)
{
    huffman::char_map<int> freq_map;
    for (auto b : in)
    {
        freq_map[b]++;
    }
    
    huffman::char_map<huffman::code> code_map;
    encoder::encode(freq_map, code_map, root);
    
    // compression
    long long byte;
    size_t pos = 0;
    for (auto b : in)
    {
        huffman::code c = code_map[b];
        for (int i = (int)c.len - 1; i >= 0; --i)
        {
            size_t bit = huffman::get(i, c.data);
            
            if (pos == 8)
            {
                out.push_back((char)byte);
                byte = 0;
                pos  = 0;
            }
            
            huffman::set(7 - pos, bit, byte);
            pos++;
        }
    }
    
    long long len = out.size() * 8;
    
    if (pos != 0)
        out.push_back((char)byte), len += pos;
    
    return len;
}
    
} // huffman 