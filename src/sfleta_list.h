#ifndef SRC_sfleta_LIST_H_
#define SRC_sfleta_LIST_H_
#include <exception>
#include <limits>

#include "LSQContainer.h"
namespace sfleta_ {
template <typename T>
class list : public LSQContainer<T> {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  class listIterator {
   private:
   public:
    Node<T> *pNode_;

    listIterator() : pNode_(nullptr) {}
    explicit listIterator(Node<T> *node) : pNode_(node) {}
    explicit listIterator(const list &l) : pNode_(l.head_) {}
    listIterator(const listIterator &other) : pNode_(other.pNode_) {}

    reference operator*();
    listIterator &operator++();
    listIterator &operator--();
    listIterator &operator=(const listIterator &other);
    bool operator!=(const listIterator &other) const;
    bool operator==(const listIterator &other) const;
  };

  class listConstIterator : public listIterator {
   public:
    listConstIterator() : listIterator() {}
    explicit listConstIterator(Node<T> *node) : listIterator(node) {}
    explicit listConstIterator(const list<T> &l) : listIterator(l) {}
    listConstIterator(const listConstIterator &other) : listIterator(other) {}
    const_reference operator*();
  };
  using iterator = listIterator;
  using const_iterator = listConstIterator;

 private:
  Node<T> *p_after_tail_;

 public:
  list();
  explicit list(size_type n);
  explicit list(std::initializer_list<T> const &items);
  list(const list &l);
  list(list &&l);
  ~list() {
    clear();
    delete p_after_tail_;
  }

  const_reference front() const;
  const_reference back() const;

  size_type size() const;
  size_type max_size() const;

  void push_front(const_reference value);
  void pop_front();
  void push_back(const_reference value);
  void pop_back();
  void clear();
  void swap(list &other);
  void reverse();
  list<T> &operator=(list &&l);

  bool empty() const;
  iterator begin();
  iterator end();
  const_iterator cbegin() const;
  const_iterator cend() const;

  void sort();
  void erase(iterator pos);
  void unique();
  iterator insert(iterator pos, const_reference value);
  void merge(list &other);
  void splice(const_iterator pos, list &other);

  template <typename... Args>
  iterator emplace(const_iterator pos, Args &&...args);
  template <typename... Args>
  void emplace_back(Args &&...args);
  template <typename... Args>
  void emplace_front(Args &&...args);

  void print();
};
}  // namespace sfleta_
#include "sfleta_list.cpp"
#endif  // SRC_sfleta_LIST_H_
