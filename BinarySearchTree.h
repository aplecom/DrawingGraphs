#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "TreeNode.h"

template<typename T>
class BinarySearchTree {
private:
    TreeNode<T>* root;

    TreeNode<T>* insert(TreeNode<T>* node, const T& value) {
        if (node == nullptr)
            return new TreeNode<T>(value);
        if (value < node->data)
            node->setLeft(insert(node->getLeft(), value));
        else if (value > node->data)
            node->setRight(insert(node->getRight(), value));

        return node;
    }

    void inorderTraversal(TreeNode<T>* node, int& count) {
        if (node != nullptr) {
            inorderTraversal(node->getLeft(), count);
            if (node->getLeft() != nullptr && node->getRight() != nullptr)
                count++;
            inorderTraversal(node->getRight(), count);
        }
    }

public:
    BinarySearchTree() {
        this->root = nullptr;
    }

    void insert(const T& value) {
        root = insert(root, value);
    }

    int countNodesWithTwoChildren() {
        int count = 0;
        inorderTraversal(root, count);
        return count;
    }
};

#endif // BINARYSEARCHTREE_H
