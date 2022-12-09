namespace s21 {
template <typename T>
vector<T>::vector() {
    this->buffer_ = new T[1]{};
    this->capacity_ = 0;
    this->size_ = 0;
}

template <typename T>
vector<T>::vector(size_type n) {
    if (n > this->max_size()) {
        throw std::length_error("try make vector larger than max_size()");
    }

    this->capacity_ = n;
    this->size_ = n;
    this->buffer_ = new T[capacity_]{};
}

template <class T>
vector<T>::vector(std::initializer_list<value_type> const& items)
    : vector(items.size()) {
    this->size_ = 0;
    for (auto& item : items) {
        this->buffer_[this->size_] = item;
        this->size_++;
    }
}

template <typename T>
vector<T>::vector(const vector& v) {
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;
    this->buffer_ = new T[this->capacity_]{};
    for (size_type i = 0; i < v.size_; ++i) {
        this->buffer_[i] = v.buffer_[i];
    }
}

template <typename T>
vector<T>::vector(vector&& v) {
    this->buffer_ = v.buffer_;
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;

    v.buffer_ = nullptr;
    v.capacity_ = 0;
    v.size_ = 0;
}

template <class T>
vector<T>& vector<T>::operator=(vector&& v) {
    if (this == &v) {
        return *this;
    }

    remove_vector();
    this->capacity_ = v.capacity_;
    this->size_ = v.size_;

    std::swap(this->buffer_, v.buffer_);
    v.capacity_ = 0;
    v.size_ = 0;

    return *this;
}

template <typename T>
vector<T>::~vector() {
    remove_vector();
}

template <typename T>
void vector<T>::remove_vector() {
    if (this->buffer_ != nullptr) {
        delete[] this->buffer_;
        this->buffer_ = nullptr;
    }
    capacity_ = 0;
    this->size_ = 0;
}

template <typename T>
void vector<T>::resize(vector<T>::size_type size) {
    vector<value_type> newVector(size);
    for (size_type i = 0; i < this->size_; ++i) {
        newVector.buffer_[i] = this->buffer_[i];
    }

    delete[] this->buffer_;
    this->buffer_ = newVector.buffer_;
    newVector.buffer_ = nullptr;

    this->capacity_ = newVector.capacity_;
}

template <typename T>
void vector<T>::reserve(vector<T>::size_type size) {
    if (size > this->max_size()) {
        throw std::length_error("try make vector larger than max_size()");
    }

    if (size > capacity_) {
        resize(size);
    }
}

template <typename T>
void vector<T>::shrink_to_fit() {
    if (this->size_ < capacity_) {
        resize(this->size_);
    }
}

template <typename T>
void vector<T>::clear() {
    this->size_ = 0;
}


template <typename T>
typename vector<T>::iterator vector<T>::insert(iterator pos,
    const_reference value) {
    size_type pos_index = pos - this->buffer_;
    if (this->size_ == capacity_) {
        if (capacity_ == 0) capacity_++;
        reserve(capacity_ * 2);
    }

    for (size_type i = this->size_; i > pos_index; --i) {
        this->buffer_[i] = this->buffer_[i - 1];
        if (i == pos_index) {
            this->buffer_[i] = value;
        }
    }

    this->size_++;
    this->buffer_[pos_index] = value;
    pos = this->buffer_ + pos_index;
    return pos;
}

template <typename T>
void vector<T>::erase(const iterator pos) {
    if (this->size_ > 0) {
        size_type pos_index = pos - this->buffer_;
        for (size_type i = pos_index; i < this->size_ - 1; ++i) {
            this->buffer_[i] = this->buffer_[i + 1];
        }
        this->size_--;
    }
}

template <typename T>
void vector<T>::push_back(const_reference value) {
    if (this->size_ == 0 && this->capacity_ == 0) {
        capacity_++;
    }
    if (this->size_ == capacity_) {
        reserve(capacity_ * 2);
    }
    this->buffer_[this->size_] = value;
    this->size_++;
}

template <typename T>
void vector<T>::pop_back() {
    if (this->size_ > 0) {
        this->size_--;
    }
}

template <typename T>
void vector<T>::swap(vector& other) {
    std::swap(this->buffer_, other.buffer_);
    std::swap(this->capacity_, other.capacity_);
    std::swap(this->size_, other.size_);
}

template <typename T>
template <typename... Args>
typename vector<T>::iterator vector<T>::emplace(const_iterator pos,
    Args&&... args) {
    iterator it = (iterator)pos;
    for (auto value : { args... }) {
        it = insert(it, value);
        ++it;
    }
    return --it;
}

template <typename T>
template <typename... Args>
void vector<T>::emplace_back(Args&&... args) {
    emplace(this->buffer_ + this->size_, args...);
}
}  // namespace s21
