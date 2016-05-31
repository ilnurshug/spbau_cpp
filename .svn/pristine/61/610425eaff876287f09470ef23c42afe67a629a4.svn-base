#pragma once
#include "reflection.h"
#include <iostream>
#include <cassert>
#include <type_traits>
#include <sstream>

namespace serialization
{
    using namespace reflection;
    
    struct printer_proc_t
    {
        printer_proc_t(std::ostream& os)
            : os(os)
        {}
        
        
        template <class field_type>
        void operator () (field_type& value, const char* key)
        {
            os.write(reinterpret_cast<char*>(&value), sizeof(value));
        }
        
        std::ostream& os;
    };

    
    struct reader_proc_t
    {
        reader_proc_t(std::istream& is)
            : is(is)
        {}
        
        
        template <class field_type>
        void operator () (field_type& value, const char* key)
        {
            is.read(reinterpret_cast<char*>(&value), sizeof(value));
        }
        
        std::istream& is;
    };
    
    // pod
    template<class type>
    void write(std::ostream& os, 
               type& obj,
               typename std::enable_if<std::is_pod<type>::value>::type* = nullptr)
    {
        os.write(reinterpret_cast<char*>(&obj), sizeof(obj));
    }
    
    // not_pod
    template<class type>
    void write(std::ostream& os, 
               type& obj,
               typename std::enable_if<!std::is_pod<type>::value>::type* = nullptr)
    {
        printer_proc_t proc(os);
        reflect_type<printer_proc_t>(proc, obj);
    }
    
    // pod
    template<class type>
    void read(std::istream& is,
              type& obj,
              typename std::enable_if<std::is_pod<type>::value>::type* = nullptr)
    {
        is.read(reinterpret_cast<char*>(&obj), sizeof(obj));
    }

    // not_pod
    template<class type>
    void read(std::istream& is,
              type& obj,
              typename std::enable_if<!std::is_pod<type>::value>::type* = nullptr)
    {
        reader_proc_t proc(is);
        reflect_type<reader_proc_t>(proc, obj);
    }

    
} // serialization
