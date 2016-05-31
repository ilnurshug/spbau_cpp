#ifndef ORDERED_H
#define ORDERED_H

#include <functional>
#include <queue>

struct ordered_task_queue
{
public:
    typedef std::function<void()> task;
    
    ordered_task_queue();
    void push(const task &t);
    size_t run_one();
    size_t run();
    bool empty() const;
    
    ordered_task_queue(const ordered_task_queue&) = delete;
    ordered_task_queue& operator =(const ordered_task_queue&) = delete;
    
    ordered_task_queue(ordered_task_queue &&rhs) noexcept
        : q(std::move(rhs.q))
    {
        
    }
  
    ordered_task_queue& operator =(ordered_task_queue &&rhs)
    {
        q = std::move(rhs.q);
        return *this;
    }
    
private:
    
    std::queue<task> q;
};

ordered_task_queue::ordered_task_queue()
{}

void ordered_task_queue::push(const task& t)
{
    q.push(t);
}

size_t ordered_task_queue::run_one()
{
    if (q.empty()) return 0;
    else 
    {
        auto t = q.front();
        q.pop();
        t();
        return 1;
    }
}

size_t ordered_task_queue::run()
{
    size_t c = q.size();
    while (!q.empty())
    {
        auto t = q.front();
        q.pop();
        t();
    }
    return c;
}

bool ordered_task_queue::empty() const 
{
    return q.empty();
}

#endif