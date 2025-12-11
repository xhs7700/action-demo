#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <memory>
#include <optional>
#include <vector>
#include <algorithm>

namespace data_structures {

/**
 * AVL Tree Node
 */
template<typename T>
struct AVLNode {
    T data;
    std::shared_ptr<AVLNode<T>> left;
    std::shared_ptr<AVLNode<T>> right;
    int height;
    
    explicit AVLNode(const T& value) 
        : data(value), left(nullptr), right(nullptr), height(1) {}
};

/**
 * AVL Tree - Self-balancing binary search tree
 */
template<typename T>
class AVLTree {
public:
    AVLTree() : root_(nullptr), size_(0) {}
    
    // Insert element
    void insert(const T& value);
    
    // Remove element
    bool remove(const T& value);
    
    // Search for element
    bool search(const T& value) const;
    
    // Find minimum element
    std::optional<T> findMin() const;
    
    // Find maximum element
    std::optional<T> findMax() const;
    
    // Get height of tree
    int height() const;
    
    // Get size
    size_t size() const { return size_; }
    
    // Check if empty
    bool empty() const { return root_ == nullptr; }
    
    // Clear tree
    void clear();
    
    // In-order traversal
    std::vector<T> inorderTraversal() const;
    
private:
    std::shared_ptr<AVLNode<T>> root_;
    size_t size_;
    
    // Helper methods
    std::shared_ptr<AVLNode<T>> insert(std::shared_ptr<AVLNode<T>> node, const T& value);
    std::shared_ptr<AVLNode<T>> remove(std::shared_ptr<AVLNode<T>> node, const T& value);
    std::shared_ptr<AVLNode<T>> findMin(std::shared_ptr<AVLNode<T>> node) const;
    std::shared_ptr<AVLNode<T>> findMax(std::shared_ptr<AVLNode<T>> node) const;
    bool search(std::shared_ptr<AVLNode<T>> node, const T& value) const;
    
    // Rotation operations
    std::shared_ptr<AVLNode<T>> rotateLeft(std::shared_ptr<AVLNode<T>> node);
    std::shared_ptr<AVLNode<T>> rotateRight(std::shared_ptr<AVLNode<T>> node);
    
    // Balance operations
    std::shared_ptr<AVLNode<T>> balance(std::shared_ptr<AVLNode<T>> node);
    int getHeight(std::shared_ptr<AVLNode<T>> node) const;
    int getBalance(std::shared_ptr<AVLNode<T>> node) const;
    void updateHeight(std::shared_ptr<AVLNode<T>> node);
    
    // Traversal helper
    void inorderTraversal(std::shared_ptr<AVLNode<T>> node, std::vector<T>& result) const;
};

// Template implementations

template<typename T>
void AVLTree<T>::insert(const T& value) {
    root_ = insert(root_, value);
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::insert(std::shared_ptr<AVLNode<T>> node, const T& value) {
    // Standard BST insertion
    if (!node) {
        size_++;
        return std::make_shared<AVLNode<T>>(value);
    }
    
    if (value < node->data) {
        node->left = insert(node->left, value);
    } else if (value > node->data) {
        node->right = insert(node->right, value);
    } else {
        // Duplicate values not allowed
        return node;
    }
    
    // Update height and balance
    updateHeight(node);
    return balance(node);
}

template<typename T>
bool AVLTree<T>::remove(const T& value) {
    size_t oldSize = size_;
    root_ = remove(root_, value);
    return size_ < oldSize;
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::remove(std::shared_ptr<AVLNode<T>> node, const T& value) {
    if (!node) {
        return nullptr;
    }
    
    if (value < node->data) {
        node->left = remove(node->left, value);
    } else if (value > node->data) {
        node->right = remove(node->right, value);
    } else {
        // Node found - perform deletion
        size_--;
        
        // Case 1: No children or one child
        if (!node->left) {
            return node->right;
        } else if (!node->right) {
            return node->left;
        }
        
        // Case 2: Two children
        // Find inorder successor (minimum in right subtree)
        auto successor = findMin(node->right);
        node->data = successor->data;
        node->right = remove(node->right, successor->data);
        size_++; // Compensate for the decrement above
    }
    
    // Update height and balance
    updateHeight(node);
    return balance(node);
}

template<typename T>
bool AVLTree<T>::search(const T& value) const {
    return search(root_, value);
}

template<typename T>
bool AVLTree<T>::search(std::shared_ptr<AVLNode<T>> node, const T& value) const {
    if (!node) {
        return false;
    }
    
    if (value == node->data) {
        return true;
    } else if (value < node->data) {
        return search(node->left, value);
    } else {
        return search(node->right, value);
    }
}

template<typename T>
std::optional<T> AVLTree<T>::findMin() const {
    if (!root_) {
        return std::nullopt;
    }
    auto minNode = findMin(root_);
    return minNode->data;
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::findMin(std::shared_ptr<AVLNode<T>> node) const {
    while (node->left) {
        node = node->left;
    }
    return node;
}

template<typename T>
std::optional<T> AVLTree<T>::findMax() const {
    if (!root_) {
        return std::nullopt;
    }
    auto maxNode = findMax(root_);
    return maxNode->data;
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::findMax(std::shared_ptr<AVLNode<T>> node) const {
    while (node->right) {
        node = node->right;
    }
    return node;
}

template<typename T>
int AVLTree<T>::height() const {
    return getHeight(root_);
}

template<typename T>
void AVLTree<T>::clear() {
    root_ = nullptr;
    size_ = 0;
}

template<typename T>
std::vector<T> AVLTree<T>::inorderTraversal() const {
    std::vector<T> result;
    inorderTraversal(root_, result);
    return result;
}

template<typename T>
void AVLTree<T>::inorderTraversal(std::shared_ptr<AVLNode<T>> node, std::vector<T>& result) const {
    if (!node) {
        return;
    }
    inorderTraversal(node->left, result);
    result.push_back(node->data);
    inorderTraversal(node->right, result);
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::rotateLeft(std::shared_ptr<AVLNode<T>> node) {
    auto rightChild = node->right;
    auto leftOfRight = rightChild->left;
    
    // Perform rotation
    rightChild->left = node;
    node->right = leftOfRight;
    
    // Update heights
    updateHeight(node);
    updateHeight(rightChild);
    
    return rightChild;
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::rotateRight(std::shared_ptr<AVLNode<T>> node) {
    auto leftChild = node->left;
    auto rightOfLeft = leftChild->right;
    
    // Perform rotation
    leftChild->right = node;
    node->left = rightOfLeft;
    
    // Update heights
    updateHeight(node);
    updateHeight(leftChild);
    
    return leftChild;
}

template<typename T>
std::shared_ptr<AVLNode<T>> AVLTree<T>::balance(std::shared_ptr<AVLNode<T>> node) {
    int balanceFactor = getBalance(node);
    
    // Left-Left case
    if (balanceFactor > 1 && getBalance(node->left) >= 0) {
        return rotateRight(node);
    }
    
    // Left-Right case
    if (balanceFactor > 1 && getBalance(node->left) < 0) {
        node->left = rotateLeft(node->left);
        return rotateRight(node);
    }
    
    // Right-Right case
    if (balanceFactor < -1 && getBalance(node->right) <= 0) {
        return rotateLeft(node);
    }
    
    // Right-Left case
    if (balanceFactor < -1 && getBalance(node->right) > 0) {
        node->right = rotateRight(node->right);
        return rotateLeft(node);
    }
    
    return node;
}

template<typename T>
int AVLTree<T>::getHeight(std::shared_ptr<AVLNode<T>> node) const {
    return node ? node->height : 0;
}

template<typename T>
int AVLTree<T>::getBalance(std::shared_ptr<AVLNode<T>> node) const {
    return node ? getHeight(node->left) - getHeight(node->right) : 0;
}

template<typename T>
void AVLTree<T>::updateHeight(std::shared_ptr<AVLNode<T>> node) {
    if (node) {
        node->height = 1 + std::max(getHeight(node->left), getHeight(node->right));
    }
}

} // namespace data_structures

#endif // DATA_STRUCTURES_AVL_TREE_H
