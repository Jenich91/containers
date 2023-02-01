namespace s21 {
template <typename T>
typename Queue<T>::const_reference Queue<T>::front() {
  return this->head_->data_;
}

template <typename T>
void Queue<T>::pop() {
  if (this->empty()) throw std::logic_error("Queue is empty");

  if (this->head_ != nullptr) {
    Node<T> *tmp = this->head_;
    this->head_ = this->head_->pNext_;
    delete tmp;
    if (this->head_ != nullptr) this->head_->pPrev_ = nullptr;
    this->size_--;
  }
}

}  // namespace s21
