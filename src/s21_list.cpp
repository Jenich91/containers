namespace s21 {
template <typename T>
typename list<T>::reference list<T>::iterator::operator*() {
  if (pNode_ == nullptr)
    throw std::logic_error("error s21_operator*(): iterator is empty");

  return pNode_->data_;
}

template <typename T>
typename list<T>::listIterator &list<T>::listIterator::operator++() {
  if (pNode_->pNext_) pNode_ = pNode_->pNext_;
  return *this;
}

template <typename T>
typename list<T>::listIterator &list<T>::listIterator::operator--() {
  if (pNode_->pPrev_) pNode_ = pNode_->pPrev_;
  return *this;
}

template <typename T>
typename list<T>::listIterator &list<T>::listIterator::operator=(
    const listIterator &other) {
  this->pNode_ = other.pNode_;
  return *this;
}

template <typename T>
bool list<T>::listIterator::operator==(const listIterator &other) const {
  bool res = false;
  if (this->pNode_ == other.pNode_) {
    res = true;
  }
  return res;
}

template <typename T>
bool list<T>::listIterator::operator!=(const listIterator &other) const {
  bool res = this->operator==(other);
  return !res;
}

template <typename T>
typename list<T>::const_reference list<T>::const_iterator::operator*() {
  if (this->pNode_ == nullptr)
    throw std::logic_error("error s21_operator*(): iterator is empty");

  return this->pNode_->data_;
}

template <typename T>
list<T>::list() : LSQContainer<T>() {
  p_after_tail_ = new Node<T>();
}

template <typename T>
list<T>::list(size_type n) : list() {
  if (n >= max_size()) {
    throw std::out_of_range("error s21_list(size_type n): over maximum size");
  }
  for (size_type i = 0; i < n; ++i) {
    Node<T> *tmp = new Node<T>();
    if (!this->head_ && !this->tail_) {
      this->head_ = this->tail_ = tmp;
      tmp->pNext_ = p_after_tail_;
      tmp->pPrev_ = p_after_tail_;
      p_after_tail_->pPrev_ = tmp;
      p_after_tail_->pNext_ = tmp;
    } else {
      tmp->pNext_ = this->head_;
      tmp->pPrev_ = p_after_tail_;
      p_after_tail_->pNext_ = tmp;
      this->head_->pPrev_ = tmp;
      this->head_ = tmp;
    }
    this->size_++;
  }
}

template <typename T>
list<T>::list(std::initializer_list<T> const &items)
    : LSQContainer<T>::LSQContainer(items) {
  p_after_tail_ = new Node<T>();
  this->head_->pPrev_ = p_after_tail_;
  this->tail_->pNext_ = p_after_tail_;
  p_after_tail_->pPrev_ = this->tail_;
  p_after_tail_->pNext_ = this->head_;
}

template <typename T>
list<T>::list(const list &l) : list() {
  auto it = l.cbegin();
  while (it != l.cend()) {
    this->push_back(*it);
    ++it;
  }
  p_after_tail_->pNext_ = this->head_;
  p_after_tail_->pPrev_ = this->tail_;
  this->size_ = l.size_;
}

template <typename T>
list<T>::list(list &&l) : list() {
  *this = std::move(l);
}

template <typename T>
typename list<T>::const_reference list<T>::front() const {
  if (!this->head_) {
    value_type &d = this->p_after_tail_->data_;
    return d;
  } else {
    value_type &d = this->head_->data_;
    return d;
  }
}

template <typename T>
typename list<T>::const_reference list<T>::back() const {
  if (!this->tail_) {
    value_type &d = this->p_after_tail_->data_;
    return d;
  } else {
    value_type &d = this->tail_->data_;
    return d;
  }
}

template <typename T>
typename list<T>::size_type list<T>::size() const {
  return this->size_;
}

template <typename T>
typename list<T>::size_type list<T>::max_size() const {
  return std::numeric_limits<size_t>::max() / (sizeof(Node<T>) * 2);
}

template <typename T>
void list<T>::push_front(const_reference value) {
  Node<T> *tmp = new Node<T>(value);
  if (!this->head_ && !this->tail_) {
    this->head_ = this->tail_ = tmp;
    tmp->pNext_ = p_after_tail_;
    tmp->pPrev_ = p_after_tail_;
    p_after_tail_->pPrev_ = tmp;
    p_after_tail_->pNext_ = tmp;
  } else {
    tmp->pNext_ = this->head_;
    tmp->pPrev_ = p_after_tail_;
    p_after_tail_->pNext_ = tmp;
    this->head_->pPrev_ = tmp;
    this->head_ = tmp;
  }
  this->size_++;
}

template <typename T>
void list<T>::pop_front() {
  if (this->head_ == nullptr) {
    throw std::range_error("error s21_pop_front(): the list is empty");
  }
  Node<T> *tmp = this->head_;
  if (this->head_->pNext_ != p_after_tail_) {
    this->head_ = this->head_->pNext_;
    this->head_->pPrev_ = p_after_tail_;
    p_after_tail_->pNext_ = this->head_;
  } else {
    this->head_ = this->tail_ = nullptr;
  }
  delete tmp;
  this->size_--;
}

template <typename T>
void list<T>::push_back(const_reference value) {
  Node<T> *tmp = new Node<T>(value);
  if (!this->head_ && !this->tail_) {
    this->head_ = this->tail_ = tmp;
    tmp->pNext_ = p_after_tail_;
    tmp->pPrev_ = p_after_tail_;
    p_after_tail_->pPrev_ = tmp;
    p_after_tail_->pNext_ = tmp;
  } else {
    tmp->pNext_ = this->p_after_tail_;
    tmp->pPrev_ = this->tail_;
    p_after_tail_->pPrev_ = tmp;
    this->tail_->pNext_ = tmp;
    this->tail_ = tmp;
  }
  this->size_++;
}

template <typename T>
void list<T>::pop_back() {
  if (this->tail_ == nullptr) {
    throw std::range_error("error s21_pop_back(): the list is empty");
  }
  Node<T> *tmp = this->tail_;
  if (this->tail_->pPrev_ != p_after_tail_) {
    this->tail_ = this->tail_->pPrev_;
    this->tail_->pNext_ = p_after_tail_;
    p_after_tail_->pPrev_ = this->tail_;
  } else {
    this->head_ = this->tail_ = nullptr;
  }
  delete tmp;
  this->size_--;
}

template <typename T>
void list<T>::clear() {
  while (this->size_) {
    pop_front();
  }
}

template <typename T>
void list<T>::swap(list &other) {
  std::swap(this->size_, other.size_);
  std::swap(this->head_, other.head_);
  std::swap(this->tail_, other.tail_);
  std::swap(this->p_after_tail_, other.p_after_tail_);
}

template <typename T>
void list<T>::reverse() {
  if (!this->empty()) {
    size_type left = 0;
    size_type right = this->size_ - 1;
    iterator it_left = this->begin();
    iterator it_right = --this->end();
    while (left < right) {
      std::swap(it_left.pNode_->data_, it_right.pNode_->data_);
      ++left;
      --right;
      ++it_left;
      --it_right;
    }
  }
}

template <typename T>
list<T> &list<T>::operator=(list<T> &&l) {
  if (this == &l)
    throw std::invalid_argument("error s21_operator=: moving object to itself");

  if (!this->empty()) {
    this->clear();
  }
  delete p_after_tail_;

  this->head_ = l.head_;
  this->tail_ = l.tail_;
  this->size_ = l.size_;
  this->p_after_tail_ = l.p_after_tail_;

  l.p_after_tail_->pNext_ = nullptr;
  l.p_after_tail_->pPrev_ = nullptr;
  l.head_ = l.tail_ = l.p_after_tail_ = nullptr;
  l.size_ = 0;

  return *this;
}

template <typename T>
bool list<T>::empty() const {
  return this->size_ == 0;
}

template <typename T>
typename list<T>::iterator list<T>::begin() {
  if (!this->empty()) {
    return iterator(this->head_);
  } else {
    return iterator(p_after_tail_);
  }
}

template <typename T>
typename list<T>::iterator list<T>::end() {
  if (!this->empty()) {
    return iterator(p_after_tail_);
  } else {
    return iterator(p_after_tail_);
  }
}

template <typename T>
typename list<T>::const_iterator list<T>::cbegin() const {
  if (!this->empty()) {
    return const_iterator(this->head_);
  } else {
    return const_iterator(p_after_tail_);
  }
}

template <typename T>
typename list<T>::const_iterator list<T>::cend() const {
  if (!this->empty()) {
    return const_iterator(p_after_tail_);
  } else {
    return const_iterator(p_after_tail_);
  }
}

template <typename T>
void list<T>::sort() {
  if (!this->empty()) {
    size_type left = 0;
    size_type right = this->size_ - 1;
    iterator iter = this->begin();
    while (left < right) {
      bool sorted = true;
      for (size_type i = left; i < right; ++i) {
        if (iter.pNode_->data_ > iter.pNode_->pNext_->data_) {
          std::swap(iter.pNode_->data_, iter.pNode_->pNext_->data_);
          sorted = false;
        }
        ++iter;
      }
      --right;
      --iter;

      if (sorted) {
        break;
      }
      sorted = true;

      for (size_type i = right; i > left; --i) {
        if (iter.pNode_->data_ < iter.pNode_->pPrev_->data_) {
          std::swap(iter.pNode_->data_, iter.pNode_->pPrev_->data_);
          sorted = false;
        }
        --iter;
      }
      ++left;
      ++iter;

      if (sorted) {
        break;
      }
    }
  }
}

template <typename T>
void list<T>::erase(iterator pos) {
  if (pos.pNode_ == nullptr) {
    throw std::range_error(
        "error erase(): the iterator is empty or the list is empty");
  } else if (pos.pNode_ == this->p_after_tail_) {
    throw std::range_error(
        "error erase(): pointer being freed was not allocated");
  }

  if (pos.pNode_ == this->head_) {
    this->pop_front();
  } else if (pos.pNode_ == this->tail_) {
    this->pop_back();
  } else {
    Node<T> *tmp = pos.pNode_;
    pos.pNode_->pPrev_->pNext_ = pos.pNode_->pNext_;
    pos.pNode_->pNext_->pPrev_ = pos.pNode_->pPrev_;
    delete tmp;
    this->size_--;
  }
}

template <typename T>
void list<T>::unique() {
  if (!this->empty()) {
    iterator pos;
    iterator pos_del;
    iterator pos_end = this->end();
    for (pos = this->begin(); pos != pos_end; ++pos) {
      if (pos.pNode_ != this->head_) {
        if (pos.pNode_->data_ == pos.pNode_->pPrev_->data_) {
          pos_del = pos;
          ++pos;
          this->erase(pos_del);
        }
      }
    }
  }
}

template <typename T>
typename list<T>::listIterator list<T>::insert(iterator pos,
                                               const_reference value) {
  Node<T> *tmp;
  if (this->empty()) {
    this->push_front(value);
    tmp = this->head_;
  } else if (pos.pNode_ == this->head_) {
    this->push_front(value);
    tmp = this->head_;
  } else if (pos.pNode_ == this->p_after_tail_) {
    this->push_back(value);
    tmp = this->tail_;
  } else {
    tmp = new Node<T>(value);
    tmp->pNext_ = pos.pNode_;
    tmp->pPrev_ = pos.pNode_->pPrev_;

    pos.pNode_->pPrev_->pNext_ = tmp;
    pos.pNode_->pPrev_ = tmp;
    this->size_++;
  }
  return iterator(tmp);
}

template <typename T>
void list<T>::merge(list &other) {
  if (this->empty()) {
    this->swap(other);
  } else if (!this->empty() && !other.empty()) {
    iterator it_this, it_other;
    it_other = other.begin();
    it_this = this->begin();
    while (it_this != this->end() && it_other != other.end()) {
      if (*it_this < *it_other) {
        ++it_this;
      } else {
        this->insert(it_this, *it_other);
        ++it_other;
      }
    }

    if (!other.empty()) {
      it_this = this->end();
      while (it_other != other.end()) {
        this->insert(it_this, *it_other);
        ++it_other;
      }
    }
  }
  other.clear();
}

template <typename T>
void list<T>::splice(const_iterator pos, list &other) {
  if (this->size() + other.size() >= this->max_size()) {
    throw std::out_of_range("splice() error: maximum size exceeded");
  }
  if (!other.empty()) {
    iterator it_other = other.begin();
    while (it_other != other.end()) {
      this->insert(pos, *it_other);
      ++it_other;
      other.pop_front();
    }
  }
}

template <typename T>
template <typename... Args>
typename list<T>::listIterator list<T>::emplace(const_iterator pos,
                                                Args &&...args) {
  list<T> tmp_l{args...};
  size_t size_args = tmp_l.size();
  iterator tmp_it;
  if (size_args == 0) {
    Node<T> *tmp_n = new Node<T>();
    tmp_it = this->insert(pos, tmp_n->data_);
    delete tmp_n;
  } else {
    for (iterator i = tmp_l.begin(); i != tmp_l.end(); ++i) {
      tmp_it = this->insert(pos, *i);
    }
  }
  return tmp_it;
}

template <typename T>
template <typename... Args>
void list<T>::emplace_back(Args &&...args) {
  list<T> tmp_l{args...};
  size_t size_args = tmp_l.size();
  if (size_args == 0) {
    Node<T> *tmp_n = new Node<T>();
    this->push_back(tmp_n->data_);
    delete tmp_n;
  } else {
    for (iterator i = tmp_l.begin(); i != tmp_l.end(); ++i) {
      this->push_back(*i);
    }
  }
}

template <typename T>
template <typename... Args>
void list<T>::emplace_front(Args &&...args) {
  list<T> tmp_l{args...};
  size_t size_args = tmp_l.size();
  if (size_args == 0) {
    Node<T> *tmp_n = new Node<T>();
    this->push_front(tmp_n->data_);
    delete tmp_n;
  } else {
    for (iterator i = --tmp_l.end(); i != --tmp_l.begin(); --i) {
      this->push_front(*i);
    }
  }
}

template <typename T>
void list<T>::print() {
  Node<T> *tmp = this->head_;
  if (this->p_after_tail_) {
    if (tmp == nullptr) {
      std::cout << p_after_tail_->data_ << std::endl;
    } else {
      while (tmp != p_after_tail_) {
        std::cout << tmp->data_ << " ";
        tmp = tmp->pNext_;
      }
      std::cout << std::endl;
    }
  }
}

}  // namespace s21
