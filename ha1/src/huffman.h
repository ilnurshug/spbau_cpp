#pragma once
#include <cstring>
#include <vector>

namespace huffman 
{
class node 
{
public:
    int freq;
    char sym;
    node *l, *r, *p;

    node(int freq = 0, char sym = ' ', node* l = 0, node* r = 0, node* p = 0) 
        : freq(freq)
        , sym(sym)
        , l(l)
        , r(r)
        , p(p)
    {
        
    }
    
    ~node()
    {
        delete l;
        delete r;
    }
};

struct code 
{
    size_t len;
    long long data;
        
    code() : len(0), data(0) {}
};

/*
    установить i-ый бит числа data в значение val
*/
inline void set(size_t i, size_t val, long long& data)
{
    data = ((~(1 << i)) & data) | (val << i); 
}

/*
    получить значение i-го бита числа data
*/
inline size_t get(size_t i, long long data)
{
    return ((1 << i) & data) >> i;
}

template <class T>
class char_map
{
public:
    char_map() 
    {
        data_.assign(256, T());
    }
    
    T& operator [] (char i)
    {
        return data_[i + 128];
    }
    
private:
    
    std::vector<T> data_;
};

} // huffman