// Copyright 2024 <Copyright Owner>

#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_

#include <algorithm>
#include <vector>

template <typename T>
class BST {
 public:
  struct Item {
    T value;
    int count;
  };

  BST() : root_(nullptr), size_(0), total_(0) {}

  BST(const BST&) = delete;

  BST& operator=(const BST&) = delete;

  ~BST() {
    clear(root_);
  }

  void insert(const T& value) {
    total_++;

    if (root_ == nullptr) {
      root_ = new Node(value);
      size_++;
      return;
    }

    Node* current = root_;

    while (current != nullptr) {
      if (value == current->value) {
        current->count++;
        return;
      }

      if (value < current->value) {
        if (current->left == nullptr) {
          current->left = new Node(value);
          size_++;
          return;
        }
        current = current->left;
      } else {
        if (current->right == nullptr) {
          current->right = new Node(value);
          size_++;
          return;
        }
        current = current->right;
      }
    }
  }

  bool search(T value) const {
    Node* current = root_;

    while (current != nullptr) {
      if (value == current->value) {
        return true;
      }

      if (value < current->value) {
        current = current->left;
      } else {
        current = current->right;
      }
    }

    return false;
  }

  int depth() const {
    return depth(root_);
  }

  int size() const {
    return size_;
  }

  int total() const {
    return total_;
  }

  std::vector<Item> items() const {
    std::vector<Item> result;
    fillItems(root_, &result);
    return result;
  }

 private:
  struct Node {
    T value;
    int count;
    Node* left;
    Node* right;

    explicit Node(const T& node_value)
        : value(node_value), count(1), left(nullptr), right(nullptr) {}
  };

  Node* root_;
  int size_;
  int total_;

  void clear(Node* node) {
    if (node == nullptr) {
      return;
    }

    clear(node->left);
    clear(node->right);
    delete node;
  }

  int depth(Node* node) const {
    if (node == nullptr) {
      return 0;
    }

    return 1 + std::max(depth(node->left), depth(node->right));
  }

  void fillItems(Node* node, std::vector<Item>* result) const {
    if (node == nullptr) {
      return;
    }

    fillItems(node->left, result);
    result->push_back({node->value, node->count});
    fillItems(node->right, result);
  }
};

#endif  // INCLUDE_BST_H_
