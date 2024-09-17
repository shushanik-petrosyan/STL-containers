#ifndef S21_STACK_H
#define S21_STACK_H

#include <initializer_list>
#include <iostream>

#include "s21_list.h"

namespace s21 {

template <typename T>
class stack {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using size_type = std::size_t;

  stack() : l() {}
  stack(std::initializer_list<value_type> const &items) : l() {
    for (auto it : items) {
      l.push_front(it);
    }
  }

  stack(const stack &s) : l(s.l) {}

  stack(stack &&s) : l(std::move(s.l)) {}

  ~stack() { this->l.clear(); }

  stack &operator=(stack &&s) {
    this->l = std::move(s.l);
    return *this;
  }

  const_reference top() { return l.front(); }

  bool empty() { return l.empty(); }

  size_type size() { return l.size(); }

  void push(const_reference &value) { this->l.push_front(value); }
  void pop() { this->l.pop_front(); }
  void swap(stack &other) { this->l.swap(other.l); }

  template <typename... Args>
  void insert_many_front(Args &&...args) {
    (push(std::forward<Args>(args)), ...);
  }

 private:
  s21::list<value_type> l;
};

}  // namespace s21

#endif