#ifndef SRC_sfleta_SET_H_
#define SRC_sfleta_SET_H_
#include "tree.h"
#include "sfleta_vector.h"
namespace sfleta_ {
template <typename K>
class set {
 public:
    using key_type = K;
    using value_type = K;
    using reference = K&;
    using const_reference = const K&;
    using iterator = typename Tree<K, std::nullptr_t>::Iterator;
    using size_type = size_t;

 protected:
    Tree<key_type, std::nullptr_t> *set_;

 public:
    set() {set_ = new Tree<key_type, std::nullptr_t>();}
    explicit set(std::initializer_list<value_type> const &items) : set()
    {for (auto &value : items) insert(value);}
    set(const set &s) {set_ = new Tree<key_type, std::nullptr_t>(*s.set_);}
    set(set &&s) {*this = std::move(s);}
    ~set() {delete set_;}
    set<key_type>& operator=(set &&s) {if (this == &s) {return *this;}
    set_ = std::move(s.set_); s.set_ = nullptr; return *this;}

    iterator begin() const {return set_->begin();}
    iterator end() const {return set_->end();}

    bool empty() const {return set_ ? set_->empty() : !set_;}
    size_type size() const {return set_->size();}
    size_type max_size() const {return set_->max_size();}

    void clear() {set_->clear();}
    std::pair<iterator, bool> insert(const value_type& value);
    template <typename... Args>
    vector<std::pair<iterator, bool>> emplace(Args&&... args);
    void erase(iterator pos) {set_->erase(pos);}
    void swap(const set& other) {set_->swap(*other.set_);}
    void merge(const set& other) {set_->merge(other.set_, 1);}

    iterator find(const_reference key) {return set_->find(key);}
    bool contains(const_reference key) {return set_->contains(key);}
};
}  // namespace sfleta_
#include "sfleta_set.cpp"
#endif  // SRC_sfleta_SET_H_
