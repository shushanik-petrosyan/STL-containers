#ifndef S21_LIST_H
#define S21_LIST_H

#include <cassert>
#include <cstddef>
#include <iostream>
#include <limits>

#include "stdio.h"

namespace s21 {

using namespace std;

template <typename T>
class list {
 public:
  using value_type = T;
  using size_type = size_t;
  using difference_type = ptrdiff_t;
  using pointer = value_type*;
  using const_pointer = const value_type*;
  using reference = value_type&;
  using const_reference = const value_type&;

 private:
  struct node {
    node* next = nullptr;
    node* prev = nullptr;
    value_type data;

    node(const_reference item) noexcept : data{item} {};
  };

  size_type m_size = 0;
  node* head = nullptr;
  node* tail = nullptr;

 public:
  class ConstIterator {
   private:
    explicit ConstIterator(const node* ptr) : m_current{ptr} {}

    friend class list;

   public:
    using difference_type = list::difference_type;
    using value_type = list::value_type;
    using pointer = list::const_pointer;
    using reference = list::const_reference;
    using iterator_category = bidirectional_iterator_tag;

    reference operator*() const noexcept {
      assert(m_current != nullptr);
      return m_current->data;
    }

    pointer operator->() {
      assert(m_current != nullptr);
      return m_current->data;
    }

    ConstIterator& operator++() noexcept {
      assert(m_current != nullptr);
      m_current = m_current->next;
      return *this;
    }

    ConstIterator& operator++(int) noexcept {
      assert(m_current != nullptr);
      auto copy = *this;

      m_current = m_current->next;
      return *copy;
    }

    ConstIterator& operator--() noexcept {
      assert(m_current != nullptr);
      m_current = m_current->prev;
      return *this;
    }

    ConstIterator& operator--(int) noexcept {
      assert(m_current != nullptr);
      auto copy = *this;

      m_current = m_current->prev;
      return *copy;
    }

    bool operator==(ConstIterator other) const noexcept {
      return m_current == other.m_current;
    }

    bool operator!=(ConstIterator other) const noexcept {
      return !(*this == other);
    }

   protected:
    const node* m_current;
    const node* Get() const noexcept { return m_current; }
  };

  class Iterator : public ConstIterator {
   private:
    friend class list;

    explicit Iterator(node* ptr) noexcept : ConstIterator{ptr} {}

   public:
    using difference_type = list::difference_type;
    using value_type = list::value_type;
    using pointer = list::pointer;
    using reference = list::reference;
    using iterator_category = std::bidirectional_iterator_tag;

    reference operator*() noexcept {
      return const_cast<reference>(ConstIterator::operator*());
    }
    Iterator& operator++() noexcept {
      ConstIterator::operator++();
      return *this;
    }

    Iterator& operator--() noexcept {
      ConstIterator::operator--();
      return *this;
    }

    Iterator operator++(int) noexcept {
      auto res = ConstIterator::operator--(0);
      return Iterator{const_cast<node*>(res.Get())};
    }
  };

  using iterator = Iterator;
  using const_iterator = ConstIterator;

  list() = default;

  list(const list& other) : list() {
    node* cur = other.head;
    while (cur) {
      push_back(cur->data);
      cur = cur->next;
    }
  }

  list(list&& other) noexcept {
    swap(other);
    other.head = nullptr;
    other.tail = nullptr;
    other.m_size = 0;
  }

  list(std::initializer_list<value_type> items) {
    for (auto& item : items) {
      push_back(item);
    }
  }

  ~list() { clear(); }

  void pop_front() {
    if (head) {
      auto ptr = head->next;
      if (ptr) {
        ptr->prev = nullptr;
      } else {
        tail = nullptr;
      }
      delete head;
      head = ptr;
      m_size--;
    }
  }
  void pop_back() {
    if (tail) {
      auto ptr = tail->prev;
      if (ptr) {
        ptr->next = nullptr;
      } else {
        head = nullptr;
      }
      delete tail;
      tail = ptr;
      m_size--;
    }
  }

  void clear() {
    while (head) {
      pop_front();
    }
  }

  void push_front(const_reference item) {
    auto new_node = new node{item};
    if (head) {
      head->prev = new_node;
      new_node->next = head;
      head = new_node;
    } else {
      head = tail = new_node;
    }
    m_size++;
  }
  void push_back(const_reference item) {
    auto new_node = new node{item};
    if (tail) {
      tail->next = new_node;
      new_node->prev = tail;
      tail = new_node;
    } else {
      tail = new_node;
      head = new_node;
    }
    m_size++;
  }

  void insert(const_iterator place, const_reference item) {
    auto ptr = const_cast<node*>(place.Get());
    if (!ptr) {
      push_back(item);
    } else {
      auto new_node = new node{item};
      new_node->next = ptr;
      new_node->prev = ptr->prev;

      if (ptr->prev) {
        ptr->prev->next = new_node;
      }

      ptr->prev = new_node;
    }
    m_size++;
  }

  void erase(const_iterator place) noexcept {
    auto ptr = const_cast<node*>(place.Get());
    assert(ptr != nullptr);

    if (ptr->prev) {
      ptr->prev->next = ptr->next;
    } else {
      head = ptr->next;
    }

    if (ptr->next) {
      ptr->next->prev = ptr->prev;
    } else {
      tail = ptr->prev;
    }
    delete ptr;
    m_size--;
  }

  const_reference front() {
    const_reference tmp = head->data;
    return tmp;
  }
  const_reference back() {
    const_reference tmp = tail->data;
    return tmp;
  }

  const_iterator begin() const noexcept { return const_iterator{head}; }
  const_iterator end() const noexcept { return const_iterator{nullptr}; }
  const_iterator cbegin() const noexcept { return const_iterator{head}; }
  const_iterator cend() const noexcept { return const_iterator{nullptr}; }

  iterator begin() noexcept { return iterator{head}; }
  iterator end() noexcept { return iterator{nullptr}; }

  list(size_type n) {
    for (size_type i = 0; i < n; ++i) {
      push_back(value_type());
    }
  }

  bool empty() { return (head ? false : true); }
  size_type size() { return m_size; }
  size_type max_size() { return std::numeric_limits<difference_type>::max(); }

  iterator find_next(const_reference item, iterator pos) noexcept {
    auto it = pos;
    ++it;
    for (; it != end(); ++it) {
      if (*it == item) {
        return it;
      }
    }
    return iterator{nullptr};
  }

  void swap(list& other) {
    node* head_tmp = head;
    node* tail_tmp = tail;
    size_type size_tmp = m_size;

    head = other.head;
    tail = other.tail;
    m_size = other.m_size;

    other.head = head_tmp;
    other.tail = tail_tmp;
    other.m_size = size_tmp;
  }

  void merge_sort(list& left, list& right) {
    node* left_node = left.head;
    node* right_node = right.head;
    node* node_tmp = nullptr;

    node* this_head = nullptr;
    node* this_tail = nullptr;
    value_type this_size = 0;

    while (left_node != nullptr || right_node != nullptr) {
      node* next_node;

      bool choose_left =
          (right_node == nullptr ||
           (left_node != nullptr && left_node->data <= right_node->data));

      if (choose_left) {
        next_node = left_node;
        left_node = left_node->next;
      } else {
        next_node = right_node;
        right_node = right_node->next;
      }

      if (node_tmp != nullptr) {
        node_tmp->next = next_node;
        next_node->prev = node_tmp;
      } else {
        this_head = next_node;
        next_node->prev = nullptr;
      }

      node_tmp = next_node;
    }

    this_tail = node_tmp;
    this_size = left.m_size + right.m_size;

    left.head = nullptr;
    left.tail = nullptr;
    left.m_size = 0;

    right.head = nullptr;
    right.tail = nullptr;
    right.m_size = 0;

    head = this_head;
    tail = this_tail;
    m_size = this_size;
  }

  void merge(list& other) { merge_sort(*this, other); }

  void splice(const_iterator pos, list& other) {
    if (other.empty()) {
      return;
    }

    node* before =
        (pos == begin()) ? nullptr : const_cast<node*>(pos.Get())->prev;
    node* after = (pos == end()) ? nullptr : const_cast<node*>(pos.Get());
    if (before) {
      before->next = other.head;
    } else {
      head = other.head;
    }
    other.head->prev = before;

    if (after) {
      after->prev = other.tail;
    } else {
      tail = other.tail;
    }
    other.tail->next = after;

    m_size += other.m_size;

    other.m_size = 0;
    other.head = nullptr;
    other.tail = nullptr;
  }
  void reverse() {
    if (m_size > 1) {
      node* cur = head;
      node* prev_node = nullptr;
      node* next_node = nullptr;

      while (cur) {
        next_node = cur->next;

        cur->next = prev_node;
        cur->prev = next_node;

        prev_node = cur;
        cur = next_node;
      }
      std::swap(head, tail);
    }
  }
  void unique() {
    if (m_size <= 1) {
      return;
    }
    iterator it = begin();
    while (it != end()) {
      iterator it_f = find_next(*it, it);
      while ((it_f) != end() && it_f != it) {
        erase(it_f);
        it_f = find_next(*it, it);
      }
      ++it;
    }
  }
  void sort() {
    if (m_size <= 1) {
      return;
    }

    list<value_type> left_half;
    list<value_type> right_half;

    node* middle = head;
    node* cur = head;

    while (cur && cur->next) {
      cur = cur->next->next;
      if (cur) {
        middle = middle->next;
      }
    }

    right_half.head = middle->next;
    right_half.tail = tail;
    right_half.m_size = m_size / 2;

    left_half.head = head;
    left_half.tail = middle;
    left_half.m_size = m_size - right_half.m_size;

    middle->next = nullptr;
    right_half.head->prev = nullptr;

    left_half.sort();
    right_half.sort();

    merge_sort(left_half, right_half);
  }

  template <typename... Args>
  iterator insert_many(const_iterator pos, Args&&... args) {
    iterator place = iterator{const_cast<node*>(pos.Get())};
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
    return place;
  }

  template <typename... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <typename... Args>
  void insert_many_front(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_front(arg);
    }
  }
};
}  // namespace s21
#endif