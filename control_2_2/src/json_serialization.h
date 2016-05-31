#pragma once
#include <string>
#include <map>

namespace serialization
{
    using std::is_arithmetic;
    using std::string;
    using std::enable_if;
    
    struct json_value_t
    {
        /*
         * json value can be a string
         * or a mapping of (string key => json_value_t).
         */
        std::string value_;
        std::map<std::string, json_value_t> mapping_;
    };
    
    struct printer_proc_arithm_t
    {
        printer_proc_arithm_t(json_value_t& d)
            : d(d)
        {}

        template <class T>
        void operator () (T& f, const string& name) const
        {
            write(d.mapping_[name], f);
        }

        json_value_t& d;

    };

    struct reader_proc_arithm_t
    {
        reader_proc_arithm_t(const json_value_t& d)
            : d(d)
        {}

        template <class T>
        void operator () (T& f, const string& name) const
        {
            try 
            {
                read(d.mapping_.at(name), f);
            }
            catch (...) {}
        }

        const json_value_t& d;
    };

    // WRITE
    template <class T>
    void write(json_value_t& d, 
               const T& obj,
               typename enable_if<is_arithmetic<T>::value>::type* = nullptr)
    {
        std::stringstream stream;
        stream << obj;
        stream >> d.value_;
    }

    template <class T>
    void write(json_value_t& d, 
               const T& obj,
               typename enable_if<!is_arithmetic<T>::value>::type* = nullptr)
    {
        printer_proc_arithm_t proc(d);
        reflect_type(proc, const_cast<T&>(obj));
    }

    // READ
    template <class T>
    void read(const json_value_t& d, 
              T& obj,
              typename enable_if<is_arithmetic<T>::value>::type* = nullptr)
    {
        std::stringstream stream;
        stream << d.value_;
        stream >> obj;
    }
    
    template <class T>
    void read(const json_value_t& d, 
              T& obj,
              typename enable_if<!is_arithmetic<T>::value>::type* = nullptr)
    {
        reader_proc_arithm_t proc(d);
        reflect_type(proc, obj);
    }

} // serialization
