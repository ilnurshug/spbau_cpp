#ifndef PRIORITY_H
#define PRIORITY_H

#include <functional>
#include <queue>

template <class P = size_t, class Compare = std::less<P>>
struct priority_task_queue
{
    typedef std::function<void()> callback;
    typedef std::pair<callback, P> task;
    typedef std::function<bool(const task &, const task &)> cmp_t;
    typedef std::priority_queue< task, std::vector< task >, cmp_t > p_queue;
    
    Compare cmp;
    p_queue q;
    
    static bool compare(std::function<bool(P, P)> cmp, const task &lhs, const task &rhs)
    {
        return cmp(lhs.second, rhs.second);
    }
    
public:
    
    priority_task_queue(const Compare &cmp = Compare()) 
        : cmp(cmp)
    {
        q = p_queue(std::bind(compare, cmp, std::placeholders::_1, std::placeholders::_2));
    }
    
    void push(const std::function<void()> &t, P p)
    {
        q.push(std::make_pair(t, p));
    }
    
    size_t run_one()
    {
        if (empty()) return 0;
        
        auto t = q.top();
        q.pop();
        t.first();
        
        return 1;
    }
    
    size_t run()
    {
        size_t c = q.size();
        while (!empty())
        {
            run_one();
        }
        
        return c;
    }
    
    bool empty() const
    {
        return q.empty();
    }
    
    priority_task_queue(const priority_task_queue&) = delete;
    priority_task_queue& operator =(const priority_task_queue&) = delete;
    
    priority_task_queue(priority_task_queue &&rhs) noexcept
        : cmp(std::move(rhs.cmp))
        , q(std::move(rhs.q))
    {
        
    }
  
    priority_task_queue& operator =(priority_task_queue &&rhs)
    {
        q = std::move(rhs.q);
        cmp = std::move(rhs.cmp);
        return *this;
    }
};

#include <vector>

template <class Iterator>
void sleep_sort(Iterator first, Iterator last)
{
    priority_task_queue<typename Iterator::value_type, std::greater<typename Iterator::value_type> > pq;
    Iterator cur = first;
    std::vector<typename Iterator::value_type> out;
    while (cur != last)
    {
        auto l = [&out, cur] () {
            out.push_back(*cur);
        };
        pq.push(l, *cur);
        
        ++cur;
    }
    pq.run();
    
    cur = first;
    for(auto v : out)
    {
        *cur = v;
        ++cur;
    }
}

#endif
