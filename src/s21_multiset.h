#ifndef SRC_21_MULTISET_H
#define SRC_21_MULTISET_H

#include <initializer_list>
#include <iostream>
#include <utility>

#include "s21_binary_tree/s21_tree.h"

namespace s21 {

template <typename Key>
class multiset : public RBTree<Key> {
 public:
  using key_type = Key;
  using value_type = key_type;
  using reference = value_type&;
  using const_reference = const value_type&;
  using iterator = typename RBTree<Key>::iterator;
  using const_iterator = typename RBTree<Key>::const_iterator;
  using size_type = size_t;

  multiset() : RBTree<Key>(){};
  multiset(const multiset& other) : RBTree<Key>(other){};
  multiset(multiset&& other) : RBTree<Key>(std::move(other)){};
  multiset& operator=(multiset&& other) noexcept = default;

  multiset(std::initializer_list<value_type> const& items) : multiset() {
    for (const auto& item : items) {
      this->InsertNotUnique(item);
    }
  }

  ~multiset() = default;

  iterator insert(const value_type& value) {
    return this->InsertNotUnique(value);
  }

  void merge(multiset& other) { this->MergeMultiset(other); }

  bool contains(const Key& key) const noexcept { return this->Contains(key); }

  iterator lower_bound(const Key& key) noexcept {
    iterator start = this->begin();
    iterator end = this->end();
    if (this->size() == 0) return end;
    for (; start != end && *start != key; start++)
      ;
    return start;
  }

  iterator upper_bound(const Key& key) noexcept {
    iterator start = lower_bound(key);
    iterator end = this->end();
    if (this->size() == 0) return end;
    for (; start != end && *start == key; ++start)
      ;
    return start;
  }

  std::pair<iterator, iterator> equal_range(const Key& key) noexcept {
    return std::pair<iterator, iterator>(lower_bound(key), upper_bound(key));
  }

  size_type count(const Key& key) noexcept {
    iterator lower_bound = this->lower_bound(key);
    size_type counter = 0;
    iterator end = this->end();
    for (; lower_bound != end && *lower_bound == key; ++lower_bound) ++counter;
    return counter;
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args&&... args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.insert_many_back(
         s21::RBTree<int>::InsertManyNotUnique(std::forward<Args>(args))),
     ...);
    return results;
  }

};  // class multiset
}  // namespace s21

#endif  // SRC_21_MULTISET_H