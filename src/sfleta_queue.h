#ifndef SRC_sfleta_QUEUE_H_
#define SRC_sfleta_QUEUE_H_
#include <stddef.h>

#include <initializer_list>
#include <iostream>

#include "sfleta_stack.h"

namespace s21 {
template <typename T>
class Queue : public LSQContainer<T> {
 public:
  using value_type = T;
  using const_reference = const T &;

 public:
  Queue() : LSQContainer<value_type>::LSQContainer() {}
  explicit Queue(const std::initializer_list<value_type> &items)
      : LSQContainer<value_type>::LSQContainer(items) {}

  void pop();
  const_reference front();
  const_reference back() { return LSQContainer<T>::tail_->data_; }
};
}  // namespace s21
#include "sfleta_queue.cpp"
#endif  // SRC_sfleta_QUEUE_H_
