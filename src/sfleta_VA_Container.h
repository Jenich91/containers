#ifndef SRC_sfleta_VA_CONTAINER_H_
#define SRC_sfleta_VA_CONTAINER_H_
#include <iostream>
#include <stdexcept>
#include <cmath>

namespace s21 {
template <typename T>
class VA_Container {
 public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 protected:
    value_type* buffer_;
    size_type size_;

 public:
    VA_Container() : buffer_(nullptr), size_(0) {}
    virtual reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference front();
    virtual const_reference back();
    iterator data() const;

    iterator begin();
    virtual iterator end();

    bool empty();
    virtual size_type size() const { return size_; }
    virtual size_type max_size() { return std::numeric_limits<size_type>::max() / 2 / sizeof(value_type); }
};
}  // namespace s21
#include "sfleta_VA_Container.cpp"
#endif  // SRC_sfleta_VA_CONTAINER_H_
