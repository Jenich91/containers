#ifndef SRC_sfleta_ARRAY_H_
#define SRC_sfleta_ARRAY_H_
#include "sfleta_VA_Container.h"
namespace s21 {
template <typename T, size_t N>
class array : public VA_Container<T> {
 public:
    using value_type = T;
    using reference = T&;
    using const_reference = const T&;
    using iterator = T*;
    using const_iterator = const T*;
    using size_type = size_t;

 private:
    void remove_array();

 public:
    array();
    explicit array(std::initializer_list<value_type> const& items);
    explicit array(const array& v);
    explicit array(array&& v);
    ~array();
    array& operator=(array&& v);

    void swap(array& other);
    void fill(const_reference value);

    const_reference back() override { return this->operator[](N - 1); }
    reference at(size_type pos) const override;
    iterator end() override;
    size_type max_size() override { return N; }
    size_type size() const override { return N; }
};
}  // namespace s21
#include "sfleta_array.cpp"
#endif  // SRC_sfleta_ARRAY_H_
