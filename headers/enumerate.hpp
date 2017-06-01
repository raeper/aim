#pragma once
#include <pair>

namespace raep {
        /*
        template <typename T>
        struct enumerate {
                using iteration_value_t = std::pair<std::size_t, T::value_type>;
                struct iterator {
                        typedef iterator self_type;
                        typedef iteration_value_t value_type;
                        //typedef T& reference;
                        //typedef T* pointer;
                        typedef std::forward_iterator_tag iterator_category;
                        typedef int difference_type;
                        iterator(pointer ptr) : ptr_(ptr) { }
                        self_type operator++() { self_type i = *this; ptr_++; return i; }
                        self_type operator++(int junk) { ptr_++; return *this; }
                        reference operator*() { return *ptr_; }
                        pointer operator->() { return ptr_; }
                        bool operator==(const self_type& rhs) { return ptr_ == rhs.ptr_; }
                        bool operator!=(const self_type& rhs) { return ptr_ != rhs.ptr_; }
                private:
                        pointer ptr_;
                };

                enumerate(T& collection)
                        : collection(collection)
                {}

                iterator begin()
                {

                }
        
        private:
                mutable std::size_t index = 0;
                T collection;
        };
        */
}