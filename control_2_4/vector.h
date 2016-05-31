#pragma once
#include <stdexcept>
namespace my
{
    template <typename T>
    struct vector
    {
        private:
            T* array = nullptr;
            size_t reserved_size = 0;
            size_t used = 0;

            T* allocate( size_t size )
            {
                return static_cast<T*>( operator new[]( size * sizeof( T ) ) );
            }

            void release_buf( T* mem_ptr, size_t size )
            {
                for( size_t i = 0; i < size; ++i )( mem_ptr + i )->~T();
                delete[] mem_ptr;
            }

            // 1. Keeping all dangerous operations with reallocation in one place
            // 2. Providing safety
            // 3. It's safe to change structure invariant after this functon
            T* safe_copy( T* src, size_t src_size, size_t dst_size, bool move )
            {
                T* dst = allocate( dst_size );
                try
                {
                    for( size_t i = 0; i < src_size; ++i )
                    {
                        if( move )
                            new( dst + i ) T( std::move_if_noexcept( src[i] ) );
                        else
                            new( dst + i ) T( src[i] );
                    }
                }
                catch( ... )
                {
                    delete[] dst;
                    throw;
                }

                return dst;
            }

        public:
             explicit vector( size_t capacity_ )
                : array( allocate( capacity_ ) )
                , reserved_size( capacity_ )
                , used( 0 )
            {
                for(size_t i = 0; i < capacity_; ++i)
                    push_back(T());
            }
 
            vector()
                : array( allocate( 1 ) )
            {
                reserved_size = 1;
                used = 0;
            }

            vector( const vector<T>& rhs )
                : array( safe_copy( rhs.array, rhs.used, rhs.used, false ) )
                , reserved_size( rhs.reserved_size )
                , used( rhs.used )
            {}

            vector( vector<T>&& rhs )
                : array( std::move( rhs.array ) )
                , reserved_size( rhs.reserved_size )
                , used( rhs.used )
            {
                rhs.array = nullptr;
                rhs.reserved_size = 0;
                rhs.used = 0;
            }

            void swap( vector<T>& rhs )
            {
                if( this != &rhs )
                {
                    std::swap( array, rhs.array );
                    std::swap( reserved_size, rhs.reserved_size );
                    std::swap( used, rhs.used );
                }
            }

            vector<T>& operator=( vector<T> rhs )
            {
                swap( rhs );
                return *this;
            }

            ~vector()
            {
                release_buf( array, used );
            }

            T& operator[]( size_t pos )
            {
                return array[pos];
            }

            const T& operator[]( size_t pos ) const
            {
                return array[pos];
            }
            
            T& at(size_t pos) 
            {
                if (pos >= size()) throw std::out_of_range("err");
                
                return array[pos];
            }
            
            const T& at(size_t pos) const
            {
                if (pos >= size()) throw std::out_of_range("err");
                
                return array[pos];
            }

            size_t size() const
            {
                return  used;
            }

            size_t capacity() const
            {
                return reserved_size;
            }

            void reserve( size_t new_capacity )
            {
                if (new_capacity <= reserved_size) return;
                
                auto new_buffer = safe_copy( array, used, new_capacity, true );
                release_buf( array, used );
                array = new_buffer;
                reserved_size = new_capacity;
            }

            bool empty() const
            {
                return used == 0;
            }

            void push_back( T const& new_element ) // amortized O(1)
            {
                if( used == reserved_size )
                    reserve( reserved_size * 2);
                new( array + used++ ) T( new_element );
            }

            void push_back( T&& new_element )
            {
                if( used == reserved_size )
                    reserve( 2 * reserved_size);
                new( array + used++ ) T( std::move( new_element ) );
            }

            template <typename... Args>
            void emplace_back( Args&& ... args )
            {
                if( used == reserved_size )
                    reserve( 2 * reserved_size);
                new( array + used++ ) T( std::forward<Args>( args )... );
            }


            // for personal use
            typedef T* iterator;
            iterator begin()
            {
                return array;
            }

            iterator end()
            {
                return array + used;
            }
    };

    template <class T>
    void swap(vector<T>& lhs, vector<T>& rhs)
    {
        lhs.swap(rhs);
    }
} // vector