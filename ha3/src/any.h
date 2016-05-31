#pragma once
#include <typeinfo>
#include <string>

namespace utils
{

using std::type_info;

class any
{
    
#define ANY_CAST( T )                                   \
                                                        \
template<class T>                                       \
friend T* any_cast(any*);                               \
                                                        \
template<class T>                                       \
friend const T* any_cast(const any*);                   \
                                                        \
template<class T>                                       \
friend T& any_cast(any&);                               \
                                                        \
template<class T>                                       \
friend const T& any_cast(const any&);                   \
    
    class _container
    {
    public:
        virtual ~_container() {}
        
        virtual _container*      copy() = 0;
        virtual const type_info& type() = 0;
    };

    template<class T>
    class container : public _container
    {
        T obj_;

    public:
        
        container(const T& obj)
            : obj_(obj)
        {}

        _container* copy()
        {
            return new container<T>(obj_);
        }
        
        const type_info& type()
        {
            return typeid(T);
        }
        
        ANY_CAST(U)

    };
    
    _container* c_;
    
    ANY_CAST(T)

public:
    
    any()
        : c_(nullptr)
    {}

    any(const any& rhs)
    {
        c_ = rhs.c_ != nullptr ? rhs.c_->copy() : nullptr;
    }
    
    ~any()
    {
        delete c_;
    }

    any& swap(any& rhs)
    {
        std::swap(c_, rhs.c_);
        return *this;
    }
    
    const type_info& type() const
    {
        return !empty() ? c_->type() : typeid(void);
    }
    
    template<class T>
    any(const T& rhs)
    {
        c_ = new container<T>(rhs);
    }

    any& operator = (const any& rhs)
    {
        any(rhs).swap(*this);
        return *this;
    }

    template<class T>
    any& operator = (const T& rhs)
    {
        if (c_)
            delete c_;

        c_ = new container<T>(rhs);
        return *this;
    }

    bool empty() const { return c_ == nullptr; }
}; 


void swap(any& lhs, any& rhs) { lhs.swap(rhs); }


class bad_any_cast: public std::exception
{
    const std::string msg_;

public:
    explicit bad_any_cast(const std::string msg)
        : msg_(msg)
    {}

    const char* what() const _GLIBCXX_USE_NOEXCEPT
    {
        return msg_.c_str();
    }
};


template<class T>
T* any_cast(any* obj)
{
    if (obj != nullptr && obj->c_->type() == typeid(T))
    {
        auto tmp = static_cast<any::container<T>*>(obj->c_);
        
        return &(tmp->obj_);
    }
    else return nullptr;
}

template<class T>
const T* any_cast(const any* obj)
{
    return any_cast<T>(const_cast<any*>(obj));
}   


template<class T>
T& any_cast(any& obj)
{
    typedef typename std::remove_reference<T>::type rem_ref;
    any::container<rem_ref>* c = static_cast<any::container<rem_ref>*>(obj.c_);
    
    if (c && obj.c_->type() == typeid(T))
        return c->obj_;
        
    throw bad_any_cast(std::string("cast error: ") + typeid(T).name());
}

template<class T>
const T& any_cast(const any& obj)
{
    typedef typename std::remove_reference<T>::type rem_ref;
    
    return any_cast<rem_ref const&>(const_cast<any&>(obj));
}
 

} // utils