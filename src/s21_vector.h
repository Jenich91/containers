#ifndef SRC_S21_VECTOR_H_
#define SRC_S21_VECTOR_H_
#include "s21_VA_Container.h"
namespace s21 {
template <typename T>
class vector : public VA_Container<T> {
 public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 private:
    unsigned int capacity_;
    void remove_vector();
    void resize(size_type size);

 public:
    vector();
    explicit vector(size_type n);
    explicit vector(std::initializer_list<value_type> const& items);
    vector(const vector& v);
    vector(vector&& v);
    ~vector();
    vector<T>& operator=(vector&& v);

    void reserve(size_type size);
    size_type capacity() const { return capacity_; }
    void shrink_to_fit();

    void clear();
    iterator insert(iterator pos, const_reference value);

    void erase(iterator pos);
    void push_back(const_reference value);
    void pop_back();
    void swap(vector& other);

    template <typename... Args>
    iterator emplace(const_iterator pos, Args&&... args);
    template <typename... Args>
    void emplace_back(Args&&... args);
};
}  // namespace s21
#include "s21_vector.cpp"
#endif  // SRC_S21_VECTOR_H_
