#ifndef MY_VECTOR_H_
#define MY_VECTOR_H_

#include <cstddef>
#include <iosfwd>
#include <utility>

namespace containers {

template<typename T>
class my_vector {
public:
    my_vector();
    explicit my_vector(std::size_t n);
    my_vector(const my_vector &other);
    ~my_vector();
    
    my_vector<T>& operator=(my_vector other);

    std::size_t size() const;
    std::size_t capacity() const;
    bool empty() const;

    void reserve(std::size_t n);
    void resize(std::size_t n);

    T& operator[](std::size_t index);
    T& operator[](std::size_t index) const;

    void push_back(const T &t);
    void pop_back();
    void clear();

    void print(std::ostream &out) const;

private:
    size_t _capacity;
    size_t _size;
    T* _array;
};

}

template <typename T>
std::ostream& operator<<(std::ostream& out, const containers::my_vector<T> &v);

#include "my_vector_impl.h"

#endif  // MY_VECTOR_H_
