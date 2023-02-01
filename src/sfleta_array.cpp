namespace sfleta_ {
template<typename T, size_t N>
array<T, N>::array() {
    this->buffer_ = new T[N]{};
    this->size_ = N;
}

template<typename T, size_t N>
array<T, N>::array(std::initializer_list<value_type> const& items) : array() {
    this->size_ = 0;
    if (items.size() > N) {
        throw std::out_of_range("Too big initializer list");
    }

    for (auto& item : items) {
        this->buffer_[this->size_] = item;
        this->size_++;
    }
}

template<typename T, size_t N>
array<T, N>::array(const array& v) {
    this->size_ = v.size_;
    this->buffer_ = new T[this->size_]{};
    for (size_type i = 0; i < v.size_; ++i) {
        this->buffer_[i] = v.buffer_[i];
    }
}

template<typename T, size_t N>
array<T, N>::array(array&& v) {
    if (this == &v) {
        return;
    }

    this->buffer_ = v.buffer_;
    this->size_ = v.size_;

    v.buffer_ = nullptr;
    v.size_ = 0;
}

template <typename T, size_t N>
array<T, N>& array<T, N>::operator=(array&& v) {
    if (this == &v) {
        return *this;
    }

    remove_array();
    this->size_ = v.size_;

    std::swap(this->buffer_, v.buffer_);
    v.size_ = 0;

    return *this;
}

template<typename T, size_t N>
array<T, N>::~array() {
    remove_array();
}

template<typename T, size_t N>
void array<T, N>::remove_array() {
    if (this->buffer_ != nullptr) {
        delete[] this->buffer_;
        this->buffer_ = nullptr;
    }
    this->size_ = 0;
}

template<typename T, size_t N>
void array<T, N>::swap(array& other) {
    std::swap(this->buffer_, other.buffer_);
    std::swap(this->size_, other.size_);
}

template<typename T, size_t N>
void array<T, N>::fill(const_reference value) {
    for (size_type i = 0; i < this->size_; ++i) {
        this->buffer_[i] = value;
    }
}

template<typename T, size_t N>
typename array<T, N>::reference array<T, N>::at(size_type pos) const {
    if (pos > N - 1) {
        throw std::out_of_range("It pos is out of bound");
    }
    return *(this->data() + pos);
}

template<typename T, size_t N>
typename array<T, N>::iterator array<T, N>::end() {
    if (this->empty()) {
        throw std::invalid_argument("Is empty container");
    }
    return (this->data() + N);
}
}  // namespace sfleta_
