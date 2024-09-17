#ifndef SRC_21_SET_H
#define SRC_21_SET_H

#include <initializer_list>
#include <iostream>
#include <utility>
#include <vector>

#include "s21_binary_tree/s21_tree.h"

namespace s21 {

template <typename Key>
class set : public RBTree<Key> {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type &;
  using const_reference = const value_type &;
  using iterator = typename RBTree<value_type>::Iterator;
  using node = typename RBTree<value_type>::Node;
  using const_iterator = typename RBTree<value_type>::ConstIterator;
  using size_type = size_t;
  using Comparator = std::less<Key>;

 public:
  set() : RBTree<Key>(){};
  set(const set &other) : RBTree<Key>(other){};
  set(set &&other) : RBTree<Key>(std::move(other)){};
  set(std::initializer_list<value_type> const &items) : RBTree<Key>(items){};

  ~set() = default;

  set &operator=(set &&other) noexcept = default;

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->InsertUnique(value);
  }

  bool contains(const Key &key) const noexcept { return this->Contains(key); }

};  // class set
}  // namespace s21

#endif  // SRC_21_SET_H