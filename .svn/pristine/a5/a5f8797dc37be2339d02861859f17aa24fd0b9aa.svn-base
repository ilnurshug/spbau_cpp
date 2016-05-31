#pragma once
#include <iostream>
#include <string>
#include <memory>

namespace arithmetic 
{

template <class T>
class cmp_operators 
{
public:

    friend bool operator  >(const T& lhs, const T& rhs) { return rhs < lhs; }
    
    friend bool operator <=(const T& lhs, const T& rhs) { return !(rhs < lhs); }
    
    friend bool operator >=(const T& lhs, const T& rhs) { return !(lhs < rhs); }
    
    friend bool operator ==(const T& lhs, const T& rhs) { return !(rhs < lhs) && !(lhs < rhs); }
    
    friend bool operator !=(const T& lhs, const T& rhs) { return !(lhs == rhs); }
};
    
} // arithmetic

namespace aux
{

template <class String>
class proxy_modifier        
{
public:
    typedef typename String::value_type type_t;
    
    proxy_modifier(String& s, size_t i)
        : s(s)
        , i(i) 
    {}
    
    proxy_modifier<String>& operator =(type_t val)
    {
        s.set_at(i, val);
        return *this;
    }
    
    operator type_t () 
    {
        return s.get_at(i);
    }
    
private:
    
    String& s;
    size_t i;
};

template <class T>
class shared_buff
{
public:

    shared_buff()
        : size_(0)
        , ref_cnt_(nullptr)
        , buf_(nullptr)
    {}
    
    shared_buff(size_t sz) 
        : size_(sz)
    {
        buf_     = new T[sz + 1];
        ref_cnt_ = new int(1);
    }
    
    shared_buff(const shared_buff& sb)
    {
        copy(sb);
    }
    
    shared_buff& operator=(shared_buff src)
    {
        release();
        
        copy(src);
        
        return *this;
    }
    
    ~shared_buff()
    {
        release();
    }
    
    void release()
    {
        if (ref_cnt_ == nullptr && buf_ == nullptr)
            return;
        
        if (--(*ref_cnt_) == 0)
        {
            delete [] buf_;
            delete ref_cnt_;
        } 
        
        buf_     = nullptr;
        ref_cnt_ = nullptr;
        size_    = 0;
    }
    
    T* get_data() { return buf_; }
    
    const T* get_data() const { return buf_; }
    
    size_t get_size() const { return size_; }
    
    void swap(shared_buff<T>& rhs)
    {
        std::swap(buf_, rhs.buf_);
        std::swap(size_, rhs.size_);
        std::swap(ref_cnt_, rhs.ref_cnt_);
    }
    
private:
    
    void copy(const shared_buff& sb)
    {
        ref_cnt_ = sb.ref_cnt_;
        buf_     = sb.buf_;
        size_    = sb.size_;
        ++(*ref_cnt_);
    }
    
    size_t size_;
    int* ref_cnt_;
    T* buf_;
};
    
} // aux

namespace std_utils
{
  
using namespace arithmetic;    

template<typename U, typename T>
class concatable
{
public:
    
    friend T operator +(T const& lhs, U const* rhs)
    {
        return lhs + T(rhs);
    }

    friend T operator +(U const* lhs, T const& rhs)
    {
        return T(lhs) + rhs;
    }

    friend T operator +(T const& lhs, U const& rhs)
    {
        return lhs + T(rhs);
    }

    friend T operator +(U const& lhs, T const& rhs)
    {
        return T(lhs) + rhs;
    }
};
    
template <class charT, class traits = std::char_traits<charT>>
class lazy_basic_string 
    : public cmp_operators< lazy_basic_string<charT, traits> >
    , concatable< charT, lazy_basic_string<charT, traits> >
{
public:
    
    typedef traits traits_type;
    typedef typename traits_type::char_type value_type;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef charT* pointer;
    typedef const charT* const_pointer;
    typedef size_t size_type;
    typedef charT* difference_type; // ?
    
    typedef aux::proxy_modifier< lazy_basic_string<charT, traits> > proxy_t;
    typedef aux::shared_buff<charT> buffer;
    
    lazy_basic_string()
        : buf_()
        , size_(0)
    {}
    
    lazy_basic_string(const lazy_basic_string<charT, traits>& rhs)
        : buf_(rhs.buf_)
        , size_(rhs.size_)
    {}
    
    lazy_basic_string(lazy_basic_string<charT, traits>&& rhs)
        : buf_(rhs.buf_)
        , size_(rhs.size_)
    {
        rhs.clear();
    }
    
    lazy_basic_string(const charT* s)
        : buf_(traits::length(s))
        , size_(traits::length(s))
    {
        traits::copy(buf_.get_data(), s, buf_.get_size() + 1);
    }
    
    lazy_basic_string(size_t cnt, charT sym)
        : buf_(cnt)
        , size_(cnt)
    {
        traits::assign(buf_.get_data(), cnt, sym);
    }
    
    lazy_basic_string(const charT& src)
        : lazy_basic_string(1, src)
    {}
    
    ~lazy_basic_string() {}
    
    lazy_basic_string<charT, traits>& operator =(lazy_basic_string<charT, traits> rhs)
    {
        if (*this != rhs)
            swap(rhs);

        return *this;
    }

    charT operator [] (size_t i) const { return get_at(i); }
    
    proxy_t operator[] (size_t i) 
    { 
        return proxy_t(*this, i);
    }
    
    friend bool operator <(const lazy_basic_string<charT, traits>& lhs, const lazy_basic_string<charT, traits>& rhs) 
    {
        size_t l_lhs = lhs.size();
        size_t l_rhs = rhs.size();
 
        int res = traits::compare(lhs.c_str(), rhs.c_str(), std::min(l_lhs, l_rhs));

        if (res < 0)
            return true;
        else if (res == 0)
            return l_lhs < l_rhs;
        else
            return false;
    }

    void swap(lazy_basic_string<charT, traits>& rhs)
    {
        buf_.swap(rhs.buf_);
        std::swap(size_, rhs.size_);
    }
    
    void clear() noexcept
    {
        size_ = 0;
        buf_.release();
    }
    
    const charT* c_str() const noexcept
    {
        return buf_.get_data(); 
    }
    
    bool empty() const noexcept { return size() == 0; }
    
    size_type size() const noexcept { return size_; }
    
    lazy_basic_string<charT, traits>& operator +=(const lazy_basic_string<charT, traits>& rhs)
    {
        buffer tmp(size_ + rhs.size_);
        
        traits::copy(tmp.get_data(), buf_.get_data(), size_);
        traits::copy(tmp.get_data() + size_, rhs.buf_.get_data(), rhs.size_);
        
        buf_ = tmp;
            
        size_ += rhs.size_;
        return *this;
    }
    
    charT get_at(size_t i) const { return buf_.get_data()[i]; }
    
    void set_at(size_t i, charT val)
    {
        size_t len = buf_.get_size();
        
        buffer tmp(buf_);
        
        buf_ = buffer(len);
        traits::copy(buf_.get_data(), tmp.get_data(), len);
        
        buf_.get_data()[i] = val;
    }
    
    template <class C>
    friend std::ostream& operator << (std::ostream& os, const lazy_basic_string<C>& str);
    
private:
    
    buffer buf_;
    size_t size_;
};

template <class charT, class traits>
lazy_basic_string<charT, traits> operator +(const lazy_basic_string<charT, traits>& lhs,        
                                          const lazy_basic_string<charT, traits>& rhs)
{
    auto tmp = lhs;
    tmp += rhs;
    return tmp;
}

template <class charT, class traits>
void swap(lazy_basic_string<charT, traits>& lhs, lazy_basic_string<charT, traits>& rhs)
{
    lhs.swap(rhs);
}

typedef lazy_basic_string<char> lazy_string;
typedef lazy_basic_string<wchar_t> lazy_wstring;

class ichar_traits : public std::char_traits<char> 
{
public:
    static bool eq (char c, char d) { return std::tolower(c) == std::tolower(d); }
    
    static bool lt (char c, char d) { return std::tolower(c) < std::tolower(d); }
    
    static int compare (const char* p, const char* q, std::size_t n) 
    {
        while (n--) 
        {
            if (!eq(*p, *q)) 
                return lt(*p, *q) ? -1 : 1; 
            ++p; ++q;
        }
        return 0;
    }
};

typedef lazy_basic_string<char, ichar_traits> lazy_istring;

template <class charT>
std::ostream& operator << (std::ostream& os, const lazy_basic_string<charT>& str)
{
    os << str.buf_.get_data() << std::endl;
    return os;
}

    
} // std_utils