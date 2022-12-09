
namespace s21 {

template <typename T>
LSQContainer<T>::LSQContainer() : size_(0), head_(nullptr), tail_(nullptr) {}

template <typename T>
LSQContainer<T>::LSQContainer(const std::initializer_list<T> &items)
    : LSQContainer() {
  for (auto &value : items) push(value);
}

template <typename T>
LSQContainer<T>::LSQContainer(size_t size_n) : LSQContainer() {
  for (size_t i = 0; i < size_n; i++) push(0);
}

template <typename T>
LSQContainer<T>::LSQContainer(const LSQContainer &l) : LSQContainer() {
  *this = l;
}

template <typename T>
LSQContainer<T>::LSQContainer(LSQContainer &&l) : LSQContainer() {
  *this = std::move(l);
}

template <typename T>
LSQContainer<T>::~LSQContainer() {
  while (size_) {
    pop();
  }
  head_ = nullptr;
  tail_ = nullptr;
}

template <typename T>
void LSQContainer<T>::print() const {
  Node<T> *result = this->head_;
  while (result != nullptr) {
    std::cout << result->data_ << " ";
    result = result->pNext_;
  }
  std::cout << std::endl;
}

template <typename T>
void LSQContainer<T>::swap(LSQContainer &other) {
  std::swap(size_, other.size_);
  std::swap(head_, other.head_);
  std::swap(tail_, other.tail_);
}

template <typename T>
LSQContainer<T> &LSQContainer<T>::operator=(LSQContainer &&l) {
    swap(l);
    return *this;
}

template <typename T>
LSQContainer<T> &LSQContainer<T>::operator=(const LSQContainer &l) {
  Node<T> *result = l.head_;
  while (result != nullptr) {
    push(result->data_);
    result = result->pNext_;
  }
  size_ = l.size_;
  return *this;
}

template <typename T>
void LSQContainer<T>::push(const T & value) {
  if (head_ == nullptr) {
    head_ = new Node<T>(value);
    tail_ = head_;
  } else {
    Node<T> *newNode = new Node<T>(value);
    tail_->pNext_ = newNode;
    newNode->pPrev_ = tail_;
    tail_ = newNode;
  }
  size_++;
}

template <typename T>
void LSQContainer<T>::pop() {
  if (empty()) {
    throw std::logic_error("Error: pop_back(): The LSQContainer is empty");
  }
  if (head_ != nullptr) {
    Node<T> *tmp = tail_;
    tail_ = tail_->pPrev_;
    delete tmp;
    if (tail_ != nullptr) {
      tail_->pNext_ = nullptr;
    }
    size_--;
  }
}

template <typename T>
bool LSQContainer<T>::empty() {
  return size_ == 0;
}

}  // namespace s21