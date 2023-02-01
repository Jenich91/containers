namespace sfleta_ {
template <typename K>
size_t multiset<K>::count(const K& key) {
    size_type result = 0;
    for (auto it = lower_bound(key); it != upper_bound(key); ++it) result++;
    return result;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::lower_bound(const K& key) {
    auto it = this->find(key);
    auto res = it;
    while (*it == key) {
    res = it;
    --it;
    }
    return res;
}

template <typename K>
typename multiset<K>::iterator multiset<K>::upper_bound(const K& key) {
    auto it = this->find(key);
    auto res = it;
    while (*it == key) {
    ++it;
    res = it;
    }
    return res;
}

template <typename K>
std::pair<typename multiset<K>::iterator, typename multiset<K>::iterator>
multiset<K>::equal_range(const K& key) {
    std::pair<multiset<K>::iterator, multiset<K>::iterator> res;
    res.first = lower_bound(key);
    res.second = upper_bound(key);
    return res;
}

template <typename K>
template <typename... Args>
vector<typename multiset<K>::iterator> multiset<K>::emplace(Args&&... args) {
    vector<typename multiset<K>::iterator> vec;
    const auto args_list = { args... };
    for (auto it = args_list.begin(); it != args_list.end(); ++it) {
        vec.push_back(insert(*it));
    }
    return vec;
}
}  // namespace sfleta_
