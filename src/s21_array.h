#ifndef S21_ARRAY
#define S21_ARRAY

#include <initializer_list>
#include <iostream>
#include <utility>

namespace s21 {
template <typename T, std::size_t N>
class array {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  // construct
  array() = default;

  array(std::initializer_list<value_type> const &items) {
    if (items.size() > max_size()) {
      throw std::length_error("\n Size larger then max size\n");
    } else {
      std::copy(items.begin(), items.end(), data_);
    }
  }

  array(const array &a) { std::copy(a.cbegin(), a.cend(), data_); }

  array(array &&a) { std::move(a.data_, a.data_ + N, data_); }

  ~array() = default;

  array &operator=(const array &a) {
    if (this != &a) {
      std::copy(a.data_, a.data_ + N, data_);
    }
    return *this;
  }

  array &operator=(array &&a) {
    if (this != &a) {
      for (size_t i = 0; i < N; ++i) {
        data_[i] = std::move(a.data_[i]);
      }
    }
    return *this;
  }

  // iterators
  iterator begin() { return data_; }

  iterator end() { return data_ + N; }

  const_iterator cbegin() const { return data_; }

  const_iterator cend() const { return data_ + N; }

  // element access
  reference at(size_type pos) {
    if (pos < size())
      return data_[pos];
    else {
      throw std::out_of_range("\n out of range\n");
    }
  }

  const_reference at(size_type pos) const {
    if (pos < size())
      return data_[pos];
    else {
      throw std::out_of_range("\n out of range\n");
    }
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const { return data_[0]; }

  const_reference back() const { return data_[N - 1]; }

  reference front() { return data_[0]; }

  reference back() { return data_[N - 1]; }

  iterator data() { return data_; }

  const_iterator data() const { return data_; }
  // methods
  size_type size() const { return N; }

  bool empty() { return ((size() == 0) ? 1 : 0); }

  size_type max_size() const { return size(); }

  void swap(array &other) { std::swap_ranges(data_, data_ + N, other.data_); }

  void fill(const_reference value) { std::fill(data_, data_ + N, value); }

 private:
  value_type data_[N] = {};
};
}  // namespace s21

#endif