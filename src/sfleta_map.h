#ifndef SRC_sfleta_MAP_H_
#define SRC_sfleta_MAP_H_

#include "tree.h"
// #include <vector>
#include "sfleta_vector.h"

namespace s21 {
template <typename K, typename T>
class Map : public Tree<K, T> {
 public:
    using key_type = K;
    using mapped_type = T;
    using value_type = std::pair<K, T>;
    using const_reference = const value_type&;
    using iterator = typename Tree<K, T>::Iterator;

    class Mapiterator : public iterator {
     public:
        Mapiterator() : iterator::Iterator() {}
        value_type operator*();
    };
    Mapiterator begin() const;
    Mapiterator end() const;

    Map() : Tree<K, T>() {}
    Map(Map<K, T>&& t) { *this = std::move(t); }
    explicit Map(const Map<K, T>& t) : Tree<K, T>() { for (auto value : t) insert(value); }
    explicit Map(std::initializer_list<value_type> const& items) { for (auto& value : items) insert(value); }

    template <typename ... Args>
    vector<std::pair<iterator, bool>> emplace(Args&&... args);
    std::pair<iterator, bool> insert(const_reference value) { return insert(value.first, value.second); }
    std::pair<iterator, bool> insert_or_assign(const K& key, const T& obj);
    std::pair<iterator, bool> insert(const K& key, const T& obj);
    Map<K, T>& operator=(Map<K, T>&& other);
    void merge(Map<K, T>& other);
    T& operator[](const K& key);
    T& at(const K& key);
};
}  // namespace s21

#include "sfleta_map.cpp"
#endif  //  SRC_sfleta_MAP_H_
