
namespace s21 {

template <typename K, typename T>
std::pair<typename Tree<K, T>::Iterator, bool> Map<K, T>::insert(const K& key, const T& obj) {
    auto result = Tree<K, T>::FindContains(key);
    if (result.second) {
        result.second = !result.second;
        return result;
    }
    result.first = Tree<K, T>::insert(key);
    result.first.node_->data_->second = obj;
    result.second = !result.second;
    return result;
}

template <typename K, typename T>
std::pair<typename Tree<K, T>::Iterator, bool> Map<K, T>::insert_or_assign(const K& key, const T& obj) {
    auto result = Tree<K, T>::FindContains(key);
    if (!result.second) result.first = Tree<K, T>::insert(key);
    result.first.node_->data_->second = obj;
    result.second = !result.second;
    return result;
}

template <typename K, typename T>
typename Map<K, T>::value_type Map<K, T>::Mapiterator::operator*() {
    if (!this->node_) throw std::out_of_range("ERROR: iterator is nullptr");
    return *this->node_->data_;
}

template <typename K, typename T>
typename Map<K, T>::Mapiterator Map<K, T>::begin() const {
    Mapiterator it;
    if (this->root_) it.node_ = this->root_->MinimalNode();
    return it;
}

template <typename K, typename T>
typename Map<K, T>::Mapiterator Map<K, T>::end() const {
    Mapiterator it;
    if (this->root_) it.node_ = this->nil_;
    return it;
}

template <typename K, typename T>
T& Map<K, T>::operator[](const K& key) {
    auto result = Tree<K, T>::FindContains(key);
    if (!result.second) result.first = Tree<K, T>::insert(key);
    return result.first.node_->data_->second;
}

template <typename K, typename T>
T& Map<K, T>::at(const K& key) {
    if (!Tree<K, T>::FindContains(key).second) throw std::out_of_range("ERROR: key is out of range");
    return (*this)[key];
}

template <typename K, typename T>
template <typename ... Args>
vector<std::pair<typename Tree<K, T>::Iterator, bool>> Map<K, T>::emplace(Args&&... args) {
    vector<std::pair<typename Tree<K, T>::Iterator, bool>> result;
    const auto args_list = { args... };
    for (auto it = args_list.begin(); it != args_list.end();) {
        auto tmp = *it;
        ++it;
        result.push_back(insert(tmp, *it));
        ++it;
    }
    return result;
}

template <typename K, typename T>
Map<K, T>& Map<K, T>::operator=(Map<K, T>&& other) {
    if (this->root_) {
        this->clear();
    }
    this->size_ = other.size_;
    this->root_ = other.root_;
    this->nil_ = other.nil_;
    other.size_ = 0;
    other.root_ = nullptr;
    other.nil_ = nullptr;
    return *this;
}

template <typename K, typename T>
void Map<K, T>::merge(Map<K, T>& other) {
    auto tmp(other);
    for (auto&& value : tmp) {
        if (insert(value.first, value.second).second) other.erase(other.find(value.first));
    }
}
}  // namespace s21
