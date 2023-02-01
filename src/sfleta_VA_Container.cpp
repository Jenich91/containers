namespace sfleta_ {
template<typename T>
typename VA_Container<T>::reference VA_Container<T>::at(size_type pos) const {
    if (pos >= size_) {
        throw std::out_of_range("It pos is out of bound");
    }
    return buffer_[pos];
}

template<typename T>
typename VA_Container<T>::reference VA_Container<T>::operator[](size_type pos) {
    return at(pos);
}

template<typename T>
typename VA_Container<T>::const_reference VA_Container<T>::front() {
    if (empty()) {
        throw std::invalid_argument("Is empty container, front");
    }
    return buffer_[0];
}

template<typename T>
typename VA_Container<T>::const_reference VA_Container<T>::back() {
    if (empty()) {
        throw std::invalid_argument("Is empty container, back");
    }
    return buffer_[size_ - 1];
}

template<typename T>
typename VA_Container<T>::iterator VA_Container<T>::data() const {
    return buffer_;
}

template<typename T>
typename VA_Container<T>::iterator VA_Container<T>::begin() {
    return data();
}

template<typename T>
typename VA_Container<T>::iterator VA_Container<T>::end() {
    return buffer_ + size_;
}

template<typename T>
bool VA_Container<T>::empty() {
    return size_ == 0;
}
}  // namespace sfleta_
