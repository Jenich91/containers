#ifndef SRC_LSQCONTAINER_H_
#define SRC_LSQCONTAINER_H_
#include <stddef.h>

#include <initializer_list>
#include <iostream>

#include "Node.h"
namespace s21 {
template <typename T>
class LSQContainer : public Node<T> {
 protected:
  size_t size_;
  Node<T> *head_;
  Node<T> *tail_;
 public:
  LSQContainer();
  explicit LSQContainer(const std::initializer_list<T> &items);
  explicit LSQContainer(size_t size_n);
  LSQContainer(const LSQContainer &l);
  LSQContainer(LSQContainer &&l);
  ~LSQContainer();
  LSQContainer<T> &operator=(LSQContainer &&l);
  LSQContainer<T> &operator=(const LSQContainer &l);

  bool empty();
  inline size_t size() { return size_; }

  void swap(LSQContainer &other);
  void push(const T &value);
  void print() const;
  void pop();
};
}  // namespace s21
#include "LSQContainer.inl"
#endif  // SRC_LSQCONTAINER_H_
