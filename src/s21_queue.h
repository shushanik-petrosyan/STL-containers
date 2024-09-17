#ifndef S21_QUEUE_H
#define S21_QUEUE_H

#include <initializer_list>
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class queue {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = size_t;

  queue() : l() {}

  queue(std::initializer_list<value_type> const &items) : l(items) {}

  queue(const queue &q) : l(q.l) {}

  queue(queue &&q) : l(std::move(q.l)) {}

  ~queue() { this->l.clear(); }

  queue &operator=(queue &&q) {
    this->l = std::move(q.l);
    return this;
  }

  const_reference front() { return this->l.front(); }
  const_reference back() { return this->l.back(); }

  bool empty() { return this->l.empty(); }
  size_type size() { return this->l.size(); }

  void push(const_reference value) { this->l.push_back(value); }
  void pop() { this->l.pop_front(); }
  void swap(queue &other) { this->l.swap(other.l); }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  s21::list<value_type> l;
};

}  // namespace s21

#endif