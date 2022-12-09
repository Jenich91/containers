#ifndef SRC_S21_MULTISET_H_
#define SRC_S21_MULTISET_H_
#include "s21_set.h"
namespace s21 {
template <typename K>

class multiset : public set<K> {
 public:
    using key_type = K;
    using value_type = K;
    using reference = K&;
    using const_reference = const K&;
    using iterator = typename Tree<K, std::nullptr_t>::Iterator;
    using size_type = size_t;
    multiset() {}
    explicit multiset(std::initializer_list<value_type> const &items) {for (auto &value : items)
    this->set_->insert(value);}
    explicit multiset(const multiset &ms) : multiset<K>()
    {delete this->set_; this->set_ = new Tree<key_type, std::nullptr_t>(*ms.set_);}
    multiset(multiset &&ms) {*this = std::move(ms);}
    ~multiset() {delete this->set_; this->set_ = nullptr;}
    multiset<key_type>&operator=(multiset &&ms) {if (this == &ms) {return *this;}
    if (this->set_) {delete this->set_;}
    this->set_ = std::move(ms.set_); ms.set_ = nullptr; return *this;}
    iterator insert(const value_type& value) {return this->set_->insert(value);}
    template <typename... Args>
    vector<iterator> emplace(Args&&... args);
    void merge(const multiset& other) {this->set_->merge(other.set_, 0);}
    size_type count(const_reference key);
    std::pair<iterator, iterator> equal_range(const_reference key);
    iterator lower_bound(const_reference key);
    iterator upper_bound(const_reference key);
};
}  // namespace s21
#include "s21_multiset.cpp"
#endif  // SRC_S21_MULTISET_H_
