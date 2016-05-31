#pragma once
#include <list>
#include <vector>
#include <utility>
#include <cstdlib>
#include <exception>

class au_allocator
{
public:
    
    explicit au_allocator(size_t max_order = 7)
        : max_order(max_order)
    {
        buckets.resize(max_order);
        used_mem.resize(max_order);
        free_mem_offset.assign(max_order, 0);
        
        size_t max_size = (2 << (max_order-1));
        if (N < max_size)
        {
            throw -1;
        }
    }
    
    ~au_allocator()
    {
        for (size_t i = 0; i < max_order; i++)
            for (char* chunk : buckets[i])
                delete [] chunk;
    }
    
    void* allocate(size_t size)
    {
        size_t p = get_idx(size);
        
        if (p >= max_order) return malloc(size);
        else return allocate_in_bucket(p);
    }
    
    void deallocate(void* ptr, size_t size)
    {
        size_t p = get_idx(size);
        
        if (p >= max_order) free(ptr);
        else used_mem[p].push_back((char*)ptr);
    }
    
    template <class T, class ... Args>
    T* allocate(Args&&... args)
    {
        void* mem = allocate(sizeof(T));
        
        T* obj = new (mem) T(std::forward<Args>(args)...);
        return obj;
    }
    
    template <class T>
    void deallocate(T* ptr)
    {
        size_t p = get_idx(sizeof(T));
        ptr->~T();
        if (p >= max_order) free(ptr);
        else used_mem[p].push_back((char*)ptr);
    }
    
private:
    
    size_t get_idx(size_t size)
    {
        size_t p = 0;
        size_t sz = 1;
        while (sz < size)
            sz <<= 1, p++;
        return p;
    }
    
    void* allocate_in_bucket(size_t i)
    {
        // allocation size
        size_t size = 2 << i;
        
        if (buckets[i].size() == 0 || free_mem_offset[i] + size - 1 >= N)
        {
            buckets[i].push_back(new char[N]);
            free_mem_offset[i] = 0;
        }
        
        if (used_mem[i].size() > 0)
        {
            char* mem = used_mem[i].front();
            used_mem[i].pop_front();
            return mem;
        }
        else 
        {
            char* mem = (char*) (buckets[i].back() + free_mem_offset[i]);
            free_mem_offset[i] += size;
            return mem;
        }
    }
    
    const size_t N = 4096;
    size_t max_order;
    
    std::vector<std::list<char*>> buckets, used_mem;
    std::vector<int> free_mem_offset;
};