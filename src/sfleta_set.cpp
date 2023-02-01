namespace s21 {
template <typename K>
std::pair<typename set<K>::iterator, bool> set<K>::insert(const K& value) {
    std::pair<set<K>::iterator, bool> res;
    res.second = !contains(value);
    if (res.second) {
        res.first = set_->insert(value);
    } else {
        res.first = find(value);
    }
    return res;
}

template <typename K>
template <typename... Args>
vector<std::pair<typename set<K>::iterator, bool>> set<K>::emplace(Args&&... args) {
    vector<std::pair<typename set<K>::iterator, bool>> vec;
    const auto args_list = { args... };
    for (auto it = args_list.begin(); it != args_list.end(); ++it) {
        vec.push_back(insert(*it));
    }
    return vec;
}
}  // namespace s21
