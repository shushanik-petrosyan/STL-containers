#ifndef SRC_21_TREE_H
#define SRC_21_TREE_H

#include <iomanip>
#include <iostream>
#include <sstream>

#include "../s21_vector.h"

namespace s21 {

template <typename Key, typename Comparator = std::less<Key>>
class RBTree {
 public:
  struct Node;
  class Iterator;
  class ConstIterator;

  using key_type = Key;
  using value_type = Key;
  using reference = key_type &;
  using const_reference = const key_type &;
  using iterator = Iterator;
  using const_iterator = ConstIterator;
  using size_type = size_t;

  enum NodeColour { Black, Red };

  struct Node {
    NodeColour colour_;
    Node *parent_;
    Node *left_;
    Node *right_;
    value_type key_;
    Node()
        : colour_(Black),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr),
          key_(value_type{}){};

    Node(Key key)
        : colour_(Red),
          parent_(nullptr),
          left_(nullptr),
          right_(nullptr),
          key_(key){};

    Node *grandparent() {
      if (parent_ != nullptr) {
        return parent_->parent_;
      } else {
        return nullptr;
      }
    }

    Node *uncle() {
      Node *grandpa = grandparent();
      if (grandpa == nullptr) {
        return nullptr;
      } else if (parent_ == grandpa->left_) {
        return grandpa->right_;
      } else {
        return grandpa->left_;
      }
    }

    Node *brother() {
      if (parent_ == nullptr)
        return nullptr;
      else if (this == parent_->left_)
        return parent_->right_;
      else
        return parent_->left_;
    }
  };

  class Iterator {
   public:
    friend RBTree<Key, Comparator>;
    Node *current_;
    RBTree *rbtree_;

    Iterator() = delete;

    explicit Iterator(Node *node, RBTree *tree)
        : current_(node), rbtree_(tree){};

    iterator &operator++() {
      if (rbtree_ != nullptr && current_ != nullptr &&
          !rbtree_->IsNodeNull(current_)) {
        current_ = Successor(current_);

      } else
        current_ = MinNode(rbtree_->head_);
      return *this;
    }

    iterator operator++(int) {
      iterator tmp = *this;
      ++*this;
      return tmp;
    }

    iterator &operator--() {
      if (rbtree_ != nullptr && current_ == nullptr) {
        current_ = MaxNode(rbtree_->head_);
      } else {
        current_ = Predecessor(current_);
      }
      return *this;
    }

    iterator operator--(int) {
      iterator tmp = *this;
      --*this;
      return tmp;
    }

    value_type &operator*() {
      if (current_ != nullptr) {
        return current_->key_;
      } else {
        throw std::out_of_range("This iterator is null pointer");
      }
    }

    bool operator==(const iterator &it) {
      return this->current_ == it.current_;
    }

    bool operator!=(const iterator &it) {
      return this->current_ != it.current_;
    }

    Node *Successor(Node *current) const noexcept {
      if (current->right_ != nullptr) return MinNode(current->right_);

      Node *parent = current->parent_;

      if (current->parent_ == nullptr) {
        return MinNode(rbtree_->head_);
      }

      while (rbtree_->IsNodeNull(parent) != true && current == parent->right_) {
        current = parent;
        parent = parent->parent_;
      }

      return parent;
    }

    Node *Predecessor(Node *current) const noexcept {
      if (current->left_ != nullptr) return MaxNode(current->left_);
      Node *parent = current->parent_;

      if (current->parent_ == nullptr) {
        return MaxNode(rbtree_->head_);
      }

      while (rbtree_->IsNodeNull(parent) != true && current == parent->left_) {
        current = parent;
        parent = parent->parent_;
      }

      return parent;
    }
  };

  class ConstIterator : public Iterator {
   public:
    ConstIterator() : Iterator(){};

    const_reference operator*();
  };

 public:
  RBTree() : head_(new Node()), size_{} {}

  RBTree(const RBTree<value_type, Comparator> &other) : RBTree() {
    Clear();
    if (!other.empty()) {
      head_ = CopyTree(other.head_, nullptr);
      size_ = other.size_;
    } else {
      head_ = new Node;
    }
  }

  RBTree(RBTree &&other) noexcept : RBTree() {
    if (!other.empty()) {
      Clear();
      *this = std::move(other);
    }
  }

  RBTree(std::initializer_list<value_type> const &items) : RBTree() {
    for (const auto &item : items) {
      InsertUnique(item);
    }
  }

  RBTree<Key, Comparator> &operator=(const RBTree<Key, Comparator> &other) {
    if (this != &other && !other.empty()) {
      Clear();
      if (!other.empty()) {
        head_ = CopyTree(other.head_, nullptr);
        size_ = other.size_;
      }
    }
    return *this;
  }

  RBTree<Key, Comparator> &operator=(RBTree<Key, Comparator> &&other) noexcept {
    if (&other != this) {
      Clear();
      head_ = other.head_;
      size_ = other.size_;
      other.head_ = nullptr;
      other.size_ = 0;
    }
    return *this;
  }

  ~RBTree() { Clear(); }

  iterator begin() {
    Node *first_node = MinNode(head_);
    return Iterator(first_node, this);
  }

  iterator end() { return Iterator(nullptr, this); }

  bool empty() const noexcept { return size_ == 0; }

  size_type size() const noexcept { return size_; }

  size_type max_size() const noexcept { return SIZE_MAX / (sizeof(Node)) / 2; }

  iterator find(const Key &key) {
    Node *node_to_find = FindNode(head_, key);
    if (node_to_find == nullptr)
      return end();
    else
      return Iterator(node_to_find, this);
  }

  template <typename... Args>
  s21::vector<std::pair<iterator, bool>> insert_many(Args &&...args) {
    s21::vector<std::pair<iterator, bool>> results;
    (results.insert_many_back(this->InsertUnique(std::forward<Args>(args))),
     ...);
    return results;
  }

  void swap(RBTree &other) {
    std::swap(this->head_, other.head_);
    std::swap(this->size_, other.size_);
    std::swap(this->compare_, other.compare_);
  }

  void erase(iterator pos) {
    if (pos.current_ != nullptr) {
      RemoveNode(pos.current_);
      --size_;
    }
  }

  void clear() noexcept {
    Clear();
    head_ = new Node();
  }

  void merge(RBTree &other) {
    if (!other.empty()) {
      iterator start = other.begin();
      iterator end = other.end();
      for (; start != end; ++start) {
        InsertUnique(*start);
      }
      other.Clear();
    }
  }

 protected:
  Node *head_;
  size_type size_{};
  Comparator compare_;

  bool Contains(const Key &key) const noexcept {
    Node *node_to_find = FindNode(head_, key);
    return node_to_find != nullptr;
  }

  static Node *MinNode(Node *current) {
    while (current != nullptr && current->left_ != nullptr) {
      current = current->left_;
    }
    return current;
  }

  static Node *MaxNode(Node *current) {
    while (current != nullptr && current->right_ != nullptr) {
      current = current->right_;
    }
    return current;
  }

  void MergeMultiset(RBTree &other) {
    if (!other.empty()) {
      iterator start = other.begin();
      iterator end = other.end();
      for (; start != end; ++start) {
        InsertNotUnique(*start);
      }
      other.Clear();
    }
  }

  void Clear() noexcept {
    if (!this->empty()) {
      DeleteNodes(head_);
    } else
      delete head_;
    head_ = nullptr;
    size_ = 0;
  }

  bool IsNodeNull(Node *current) const {
    return current == nullptr || this->size_ == 0;
  }

  std::pair<iterator, bool> InsertUnique(const value_type &value) noexcept {
    Node *insert_node = new Node(value);
    std::pair<iterator, bool> result = Insert(insert_node, true);
    if (result.second == false) {
      delete insert_node;
    }
    return result;
  }

  iterator InsertNotUnique(const value_type &value) noexcept {
    Node *insert_node = new Node(value);
    iterator result = Insert(insert_node, false).first;
    return result;
  }

  std::pair<iterator, bool> InsertManyNotUnique(
      const value_type &value) noexcept {
    Node *insert_node = new Node(value);
    std::pair<iterator, bool> result = Insert(insert_node, false);
    return result;
  }

  void DeleteNodes(Node *current) {
    if (IsNodeNull(current) != true) {
      DeleteNodes(current->left_);
      DeleteNodes(current->right_);
      delete current;
      current = nullptr;
    }
  }

  Node *CopyTree(Node *other_node, Node *parent) {
    if (other_node == nullptr) return nullptr;
    Node *new_node = new Node();
    new_node->key_ = other_node->key_;
    new_node->colour_ = other_node->colour_;
    new_node->parent_ = parent;
    new_node->left_ = CopyTree(other_node->left_, new_node);
    new_node->right_ = CopyTree(other_node->right_, new_node);
    return new_node;
  }

  Node *FindNode(Node *node, key_type key) const {
    if (node != nullptr && !compare_(key, node->key_) &&
        !compare_(node->key_, key))
      return node;
    else if (node == nullptr)
      return nullptr;

    if (compare_(key, node->key_))
      return FindNode(node->left_, key);
    else
      return FindNode(node->right_, key);
  }

  void InsertFixup(Node *current_node) {
    Node *parent = nullptr;
    Node *grandparent = nullptr;
    Node *uncle = nullptr;

    while (current_node != head_ && current_node->colour_ == Red &&
           current_node->parent_->colour_ == Red) {
      parent = current_node->parent_;
      grandparent = current_node->grandparent();
      bool isLeftParent = (parent == grandparent->left_);
      uncle = current_node->uncle();

      if (uncle && uncle->colour_ == Red) {
        uncle->colour_ = Black;
        parent->colour_ = Black;
        grandparent->colour_ = Red;
        current_node = grandparent;

      } else {
        if (isLeftParent && current_node == parent->right_) {
          LeftRotate(parent);
          current_node = parent;
          parent = current_node->parent_;
        } else if (!isLeftParent && current_node == parent->left_) {
          RightRotate(parent);
          current_node = parent;
          parent = current_node->parent_;
        }

        if (isLeftParent) {
          RightRotate(grandparent);
        } else {
          LeftRotate(grandparent);
        }

        std::swap(parent->colour_, grandparent->colour_);
        current_node = parent;
      }
    }

    head_->colour_ = Black;
  }

  // подается узел node_to_rotate, выталкивается наверх узел right_son
  void LeftRotate(Node *node_to_rotate) noexcept {
    Node *right_son = node_to_rotate->right_;
    right_son->parent_ = node_to_rotate->parent_;

    if (node_to_rotate == head_) {
      head_ = right_son;
    } else if (node_to_rotate->parent_->left_ == node_to_rotate) {
      node_to_rotate->parent_->left_ = right_son;
    } else {
      node_to_rotate->parent_->right_ = right_son;
    }

    node_to_rotate->right_ = right_son->left_;

    if (right_son->left_ != nullptr) {
      right_son->left_->parent_ = node_to_rotate;
    }

    node_to_rotate->parent_ = right_son;
    right_son->left_ = node_to_rotate;
  }

  // подается узел node_to_rotate, выталкивается наверх узел left_son
  void RightRotate(Node *node_to_rotate) noexcept {
    Node *left_son = node_to_rotate->left_;
    left_son->parent_ = node_to_rotate->parent_;

    if (node_to_rotate == head_) {
      head_ = left_son;
    } else if (node_to_rotate->parent_->left_ == node_to_rotate) {
      node_to_rotate->parent_->left_ = left_son;
    } else {
      node_to_rotate->parent_->right_ = left_son;
    }

    node_to_rotate->left_ = left_son->right_;

    if (left_son->right_ != nullptr) {
      left_son->right_->parent_ = node_to_rotate;
    }

    node_to_rotate->parent_ = left_son;
    left_son->right_ = node_to_rotate;
  }

  // https://habr.com/ru/articles/573502/
  void RemoveFixupLeft(Node *node_to_fix) {
    Node *brother = node_to_fix->brother();
    // 1) брат черный
    if (brother != nullptr && brother->colour_ == Black) {
      // хотя бы один ребенок брата красный
      if ((brother->left_ != nullptr && brother->left_->colour_ == Red) ||
          (brother->right_ != nullptr && brother->right_->colour_ == Red)) {
        // правый ребенок красный, левый любой (1.1 а) -- тесты прошел
        if (brother->right_ != nullptr && brother->right_->colour_ == Red) {
          // брата в цвет родителя
          brother->colour_ = node_to_fix->parent_->colour_;
          // перекрашиваем родителя в черный
          node_to_fix->parent_->colour_ = Black;
          brother->right_->colour_ = Black;
          LeftRotate(node_to_fix->parent_);
        }
        // левый ребенок красный, правый черный (1.1 б)
        else if (brother->left_ != nullptr && brother->left_->colour_ == Red) {
          brother->left_->colour_ = Black;
          brother->colour_ = Red;
          RightRotate(brother);
          RemoveFixupLeft(node_to_fix);
        }
      }
      // 1.2 оба ребенка брата -- черные (1.2)
      else {
        bool isBlack = node_to_fix->parent_->colour_ == Black;
        brother->colour_ = Red;
        node_to_fix->parent_->colour_ = Black;
        if (isBlack) RemoveFixupLeft(node_to_fix);
      }
    }  // 2) брат красный
    else if (brother != nullptr && brother->colour_ == Red) {
      brother->colour_ = Black;
      node_to_fix->parent_->colour_ = Red;
      LeftRotate(node_to_fix->parent_);
      RemoveFixupLeft(node_to_fix);
    }
  }

  void RemoveFixupRight(Node *node_to_fix) {
    Node *brother = node_to_fix->brother();
    if (brother != nullptr && brother->colour_ == Black) {
      if ((brother->left_ != nullptr && brother->left_->colour_ == Red) ||
          (brother->right_ != nullptr && brother->right_->colour_ == Red)) {
        if (brother->left_ != nullptr && brother->left_->colour_ == Red) {
          brother->colour_ = node_to_fix->parent_->colour_;
          node_to_fix->parent_->colour_ = Black;
          brother->left_->colour_ = Black;
          RightRotate(node_to_fix->parent_);
        }

        else if (brother->right_ != nullptr &&
                 brother->right_->colour_ == Red) {
          brother->right_->colour_ = Black;
          brother->colour_ = Red;
          LeftRotate(brother);
          RemoveFixupRight(node_to_fix);
        }

      } else {
        bool isBlack = node_to_fix->parent_->colour_ == Black;
        brother->colour_ = Red;
        node_to_fix->parent_->colour_ = Black;
        if (isBlack) RemoveFixupRight(node_to_fix);
      }

    } else {
      if (brother != nullptr && brother->colour_ == Red) {
        brother->colour_ = Black;

        node_to_fix->parent_->colour_ = Red;
        RightRotate(node_to_fix->parent_);
        RemoveFixupRight(node_to_fix);
      }
    }
  }

  void RemoveNode(Node *node_to_delete) {
    if (node_to_delete->colour_ == Red && node_to_delete->left_ == nullptr &&
        node_to_delete->right_ == nullptr) {
      if (node_to_delete == node_to_delete->parent_->left_)
        node_to_delete->parent_->left_ = nullptr;
      else
        node_to_delete->parent_->right_ = nullptr;
      delete node_to_delete;
    }

    else if (node_to_delete->colour_ == Red &&
             node_to_delete->left_ != nullptr &&
             node_to_delete->right_ != nullptr) {
      Node *max_left = MaxNode(node_to_delete->left_);
      std::swap(node_to_delete->key_, max_left->key_);
      RemoveNode(max_left);
    }

    else if (node_to_delete->colour_ == Black &&
             node_to_delete->left_ != nullptr &&
             node_to_delete->right_ != nullptr) {
      Node *max_left = MaxNode(node_to_delete->left_);
      std::swap(node_to_delete->key_, max_left->key_);
      RemoveNode(max_left);
    }

    else if (node_to_delete->colour_ == Black &&
             (node_to_delete->left_ != nullptr ||
              node_to_delete->right_ != nullptr)) {
      Node *child = (node_to_delete->left_ != nullptr) ? node_to_delete->left_
                                                       : node_to_delete->right_;
      std::swap(node_to_delete->key_, child->key_);
      RemoveNode(child);
    }

    else if (node_to_delete->colour_ == Black &&
             node_to_delete->left_ == nullptr &&
             node_to_delete->right_ == nullptr) {
      if (node_to_delete->parent_ != nullptr) {
        bool isLeft = node_to_delete == node_to_delete->parent_->left_;
        isLeft ? RemoveFixupLeft(node_to_delete)
               : RemoveFixupRight(node_to_delete);
        if (node_to_delete == node_to_delete->parent_->left_)
          node_to_delete->parent_->left_ = nullptr;
        else
          node_to_delete->parent_->right_ = nullptr;
      }
      if (head_ == node_to_delete) {
        delete head_;
        head_ = nullptr;
        head_ = new Node();
        size_ = 1;
      } else
        delete node_to_delete;
    }
  }

  std::pair<iterator, bool> Insert(Node *insert_node, bool is_unique) {
    Node *current_node = head_;
    Node *previous_node = nullptr;
    while (!IsNodeNull(current_node)) {
      previous_node = current_node;

      if (compare_(insert_node->key_, current_node->key_)) {
        current_node = current_node->left_;
      } else {
        if (is_unique && !compare_(current_node->key_, insert_node->key_)) {
          return std::pair<iterator, bool>(iterator(current_node, this), false);
        }
        current_node = current_node->right_;
      }
    }
    delete current_node;

    if (previous_node == nullptr) {
      head_ = insert_node;
      insert_node->colour_ = Black;
    } else {
      insert_node->parent_ = previous_node;
      if (compare_(insert_node->key_, previous_node->key_)) {
        previous_node->left_ = insert_node;
      } else {
        previous_node->right_ = insert_node;
      }
    }
    ++size_;
    InsertFixup(insert_node);
    return std::pair<iterator, bool>(iterator(insert_node, this), true);
  }

};  // class RBTree
}  // namespace s21

#endif  // SRC_21_TREE_H
