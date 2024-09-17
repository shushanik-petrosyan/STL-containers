#ifndef SRC_21_MAP_H
#define SRC_21_MAP_H

#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_binary_tree/s21_tree.h"

namespace s21 {

template <typename Key, typename Value>
struct MapCompare {
  using value_type = std::pair<Key, Value>;
  bool operator()(const value_type &pair1,
                  const value_type &pair2) const noexcept {
    return pair1.first < pair2.first;
  }
};

template <typename Key, typename Value>
class map : public RBTree<std::pair<Key, Value>, MapCompare<Key, Value>> {
 public:
  using key_type = Key;
  using mapped_type = Value;
  using value_type = std::pair<key_type, mapped_type>;
  using reference = value_type &;
  using const_reference = const value_type &;
  using size_type = size_t;
  using Compare = MapCompare<Key, Value>;
  using iterator = typename RBTree<std::pair<Key, Value>, Compare>::Iterator;
  using const_iterator =
      typename RBTree<std::pair<Key, Value>, Compare>::ConstIterator;

  map() : RBTree<value_type, Compare>(){};
  map(const map &other) : RBTree<value_type, Compare>(other){};
  map(map &&other) : RBTree<value_type, Compare>(std::move(other)){};
  map(std::initializer_list<value_type> const &items)
      : RBTree<value_type, Compare>(items){};
  ~map() = default;

  map &operator=(map &&other) noexcept = default;

  mapped_type &at(const Key &key) {
    value_type temp_pair{key, mapped_type{}};
    iterator it = this->find(temp_pair);
    if (it == this->end()) {
      throw std::out_of_range("No such element exists");
    }
    return (*it).second;
  }

  mapped_type &operator[](const key_type &key) {
    value_type temp_pair{key, mapped_type{}};
    if (!this->Contains(temp_pair)) {
      this->insert(temp_pair);
    }
    iterator it = this->find(temp_pair);
    return (*it).second;
  }

  bool contains(const Key &key) {
    value_type temp_pair{key, mapped_type{}};
    return this->Contains(temp_pair);
  }

  std::pair<iterator, bool> insert(const value_type &value) {
    return this->InsertUnique(value);
  }

  std::pair<iterator, bool> insert(const Key &k, mapped_type &&obj) {
    return this->InsertUnique(value_type{k, obj});
  }

  std::pair<iterator, bool> insert_or_assign(const Key &key, const Value &obj) {
    value_type temp_pair{key, obj};
    iterator it = this->find(temp_pair);
    if (it == this->end()) {
      return this->insert(temp_pair);
    } else {
      (*it).second = std::move(obj);
      return {it, false};
    }
  }

};  // class map
}  // namespace s21

#endif  // SRC_21_MAP_H