#ifndef BST_H
#define BST_H

#include <iostream>
#include <fstream>
#include <string>

template <typename T>
class BST {
private:
    struct Node {
        T key;
        int count;
        Node* left;
        Node* right;
        Node(T k) : key(k), count(1), left(nullptr), right(nullptr) {}
    };

    Node* root;

    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);
        if (value < node->key)
            node->left = insert(node->left, value);
        else if (value > node->key)
            node->right = insert(node->right, value);
        else
            node->count++;
        return node;
    }

    int getDepth(Node* node) {
        if (!node) return 0;
        int leftDepth = getDepth(node->left);
        int rightDepth = getDepth(node->right);
        return 1 + (leftDepth > rightDepth ? leftDepth : rightDepth);
    }

    Node* searchNode(Node* node, T value) {
        if (!node || node->key == value) return node;
        if (value < node->key)
            return searchNode(node->left, value);
        else
            return searchNode(node->right, value);
    }

    void collectNodes(Node* node, Node** arr, int& index) {
        if (!node) return;
        collectNodes(node->left, arr, index);
        arr[index++] = node;
        collectNodes(node->right, arr, index);
    }

    int countNodes(Node* node) {
        if (!node) return 0;
        return 1 + countNodes(node->left) + countNodes(node->right);
    }

    void sortByFrequency(Node** arr, int size) {
        for (int i = 0; i < size - 1; i++) {
            for (int j = 0; j < size - i - 1; j++) {
                if (arr[j]->count < arr[j + 1]->count) {
                    Node* temp = arr[j];
                    arr[j] = arr[j + 1];
                    arr[j + 1] = temp;
                }
            }
        }
    }

    void clearTree(Node* node) {
        if (!node) return;
        clearTree(node->left);
        clearTree(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}
    ~BST() { clearTree(root); }

    void insert(T value) {
        root = insert(root, value);
    }

    int depth() {
        return getDepth(root);
    }

    Node* search(T value) {
        return searchNode(root, value);
    }

    void printByFrequency(std::ostream& out = std::cout) {
        int size = countNodes(root);
        if (size == 0) return;
        Node** nodes = new Node*[size];
        int index = 0;
        collectNodes(root, nodes, index);
        sortByFrequency(nodes, size);
        for (int i = 0; i < size; i++) {
            out << nodes[i]->key << " " << nodes[i]->count << std::endl;
        }
        delete[] nodes;
    }
};

#endif
