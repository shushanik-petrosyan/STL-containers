#ifndef S21_VECTOR
#define S21_VECTOR

#include <algorithm>
#include <iostream>
#include <limits>

namespace s21 {
template <typename T>
class vector {
 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  vector() {
    capacity_ = 0;
    size_ = 0;
    data_ = nullptr;
  }

  vector(size_type n) {
    size_ = n;
    capacity_ = n;
    data_ = reinterpret_cast<T *>(new int8_t[n * sizeof(T)]);
    std::fill_n(data_, n, value_type());
  }
  vector(const vector &v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = reinterpret_cast<T *>(new int8_t[v.capacity_ * sizeof(T)]);
    std::copy(v.data_, v.data_ + v.size_, data_);
  }

  vector(vector &&v) {
    size_ = v.size_;
    capacity_ = v.capacity_;
    data_ = nullptr;
    *this = std::move(v);
  }

  vector(std::initializer_list<T> const &items) {
    size_ = items.size();
    capacity_ = items.size();
    data_ = reinterpret_cast<T *>(new int8_t[items.size() * sizeof(T)]);
    int index = 0;
    for (auto i : items) {
      new (data_ + index) T(i);
      index++;
    }
  }

  vector &operator=(vector<T> &&v) {
    if (this != &v) {
      this->DeleteVector();
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = v.data_;
      v.capacity_ = 0;
      v.size_ = 0;
      v.data_ = nullptr;
    }
    return *this;
  }

  vector &operator=(const vector<T> &v) {
    if (this != &v) {
      this->DeleteVector();
      size_ = v.size_;
      capacity_ = v.capacity_;
      data_ = new T[capacity_];
      std::copy(v.data_, v.data_ + v.size_, data_);
    }
    return *this;
  }

  ~vector() {
    DeleteVector();
    data_ = nullptr;
    size_ = 0;
    capacity_ = 0;
  }

  reference at(size_type pos) {
    if (pos >= size_) {
      throw std::out_of_range("\n index out of range\n");
    } else {
      return data_[pos];
    }
  }

  reference operator[](size_type pos) { return data_[pos]; }

  const_reference operator[](size_type pos) const { return data_[pos]; }

  const_reference front() const {
    if (size_ != 0)
      return data_[0];
    else {
      throw std::out_of_range("\n index out of range\n");
    }
  }

  const_reference back() const {
    if (size_ != 0)
      return data_[size_ - 1];
    else {
      throw std::out_of_range("\n index out of range\n");
    }
  }

  iterator data() const {
    if (data_ != nullptr)
      return data_;
    else {
      throw std::out_of_range("\n does not exist\n");
    }
  }

  iterator begin() { return &data_[0]; }

  iterator end() { return &data_[size_]; }

  const_iterator cbegin() const { return &data_[0]; }

  const_iterator cend() const { return &data_[size_]; }

  bool empty() const { return (size_ == 0) ? 1 : 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<std::size_t>::max() / sizeof(value_type) / 2;
  }

  void reserve(size_type size) {
    if (size <= capacity_) return;
    if (size > this->max_size()) {
      throw std::out_of_range("\n bigger then max size\n");
    } else if (size > capacity_) {
      T *newarr = reinterpret_cast<T *>(new int8_t[size * sizeof(T)]);
      try {
        std::uninitialized_copy(data_, data_ + size_, newarr);
      } catch (...) {
        delete[] reinterpret_cast<int8_t *>(newarr);
        throw;
      }
      DeleteVector();
      data_ = newarr;
      capacity_ = size;
    }
  }

  size_type capacity() const { return capacity_; }

  void shrink_to_fit() {
    if (capacity_ > size_) {
      T *newarr = reinterpret_cast<T *>(new int8_t[size_ * sizeof(T)]);
      try {
        std::uninitialized_copy(data_, data_ + size_, newarr);
      } catch (...) {
        delete[] reinterpret_cast<int8_t *>(newarr);
        throw;
      }
      DeleteVector();
      data_ = newarr;
      capacity_ = size_;
    }
  }

  void clear() { size_ = 0; }

  iterator insert(iterator pos, const_reference value) {
    iterator new_pos = pos;
    if (size_ == capacity_) {
      if (capacity_ != 0) {
        capacity_ *= 2;
      } else {
        capacity_ = 1;
      }
    }
    T *newarr = reinterpret_cast<T *>(new int8_t[capacity_ * sizeof(T)]);
    if (pos == nullptr) {
      DeleteVector();
      new (newarr) T(value);
      new_pos = newarr;
    } else {
      for (size_type new_index = 0, cur_index = 0; new_index < (size_ + 1);
           ++new_index, ++cur_index) {
        if (&data_[cur_index] == pos) {
          new (newarr + new_index) T(value);
          new_pos = &newarr[new_index];
          ++new_index;
        }
        if (cur_index < size_) {
          new (newarr + new_index) T(data_[cur_index]);
        }
      }
      DeleteVector();
    }
    data_ = newarr;
    ++size_;
    return new_pos;
  }

  void erase(const iterator pos) {
    T *newarr = reinterpret_cast<T *>(new int8_t[capacity_ * sizeof(T)]);
    for (size_type new_index = 0, cur_index = 0; new_index <= (size_ - 1);
         ++new_index) {
      if (&data_[new_index] != pos) {
        new (newarr + cur_index) T(data_[new_index]);
        cur_index++;
      }
    }
    DeleteVector();
    size_ -= 1;
    data_ = newarr;
  }

  void push_back(const_reference value) {
    if (size_ == capacity_) {
      if (capacity_ == 0)
        reserve(1);
      else
        reserve(capacity_ * 2);
    }
    new (data_ + size_) T(value);
    size_ += 1;
  }

  void pop_back() {
    if (size_ > 0) {
      size_ -= 1;
      (data_ + size_)->~T();
    }
  }

  void swap(vector<T> &other) {
    std::swap(size_, other.size_);
    std::swap(capacity_, other.capacity_);
    std::swap(data_, other.data_);
  }

  template <typename... Args>
  void insert_many_back(Args &&...args) {
    if (size_ == capacity_) {
      reserve(capacity_ + sizeof...(args));
    }
    for (auto i : {args...}) {
      push_back(i);
    }
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args &&...args) {
    int current = pos - cbegin();
    if (capacity_ == size_) {
      reserve(capacity_ + sizeof...(args));
    }
    iterator result = (iterator)(pos);
    for (auto i : {args...}) {
      result = insert(begin() + current, i);
    }
    return result;
  }

 private:
  value_type *data_;
  size_type capacity_;
  size_type size_;

  void DeleteVector() {
    if (data_) {
      for (size_t i = 0; i < size_; ++i) {
        data_[i].~T();
      }
      delete[] reinterpret_cast<int8_t *>(data_);
    }
  }
};
}  // namespace s21

#endif