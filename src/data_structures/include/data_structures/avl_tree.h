#ifndef DATA_STRUCTURES_AVL_TREE_H
#define DATA_STRUCTURES_AVL_TREE_H

#include <memory>
#include <optional>
#include <vector>
#include <algorithm>
#include <utility>

namespace data_structures {

/**
 * @brief AVL树节点结构
 * 
 * @tparam T 节点存储的数据类型
 */
template<typename T>
struct AVLNode {
    T data;                                 ///< 节点数据
    std::shared_ptr<AVLNode<T>> left;       ///< 左子节点
    std::shared_ptr<AVLNode<T>> right;      ///< 右子节点
    int height;                             ///< 节点高度
    
    explicit AVLNode(const T& value) 
        : data(value), left(nullptr), right(nullptr), height(1) {}
    
    explicit AVLNode(T&& value) 
        : data(std::move(value)), left(nullptr), right(nullptr), height(1) {}
};

/**
 * @brief AVL树（自平衡二叉搜索树）
 * 
 * AVL树是一种高度平衡的二叉搜索树，通过旋转操作维护平衡性质：
 * 任意节点的左右子树高度差不超过1。
 * 
 * @tparam T 树中存储的元素类型，必须支持比较运算符（<, >, ==）
 * 
 * @note 时间复杂度: insert/remove/search 均为 O(log n)
 * @note 空间复杂度: O(n)
 * @note 平衡性质: |height(left) - height(right)| ≤ 1
 * @note 旋转操作: 支持LL、RR、LR、RL四种旋转
 * 
 * @example
 * AVLTree<int> tree;
 * tree.insert(10);
 * tree.insert(5);
 * tree.insert(15);
 * bool found = tree.search(5);  // true
 * tree.remove(5);
 * auto sorted = tree.inorderTraversal();  // {10, 15}
 */
template<typename T>
class AVLTree {
public:
    AVLTree() : root_(nullptr), size_(0) {}
    
    /**
     * @brief 插入元素（左值版本）
     * @param value 要插入的元素值
     * @note 时间复杂度: O(log n)
     * @note 不允许重复值
     */
    void insert(const T& value);
    
    /**
     * @brief 插入元素（右值版本）
     * @param value 要插入的元素值（支持移动语义）
     * @note 时间复杂度: O(log n)
     */
    void insert(T&& value);
    
    /**
     * @brief 删除指定元素
     * @param value 要删除的元素值
     * @return 成功删除返回true，元素不存在返回false
     * @note 时间复杂度: O(log n)
     * @note 删除后自动重新平衡树
     */
    bool remove(const T& value);
    
    /**
     * @brief 查找指定元素
     * @param value 要查找的元素值
     * @return 找到返回true，否则返回false
     * @note 时间复杂度: O(log n)
     */
    bool search(const T& value) const;
    
    /**
     * @brief 查找最小元素
     * @return std::optional<T>，包含最小值；树为空时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<T> findMin() const;
    
    /**
     * @brief 查找最大元素
     * @return std::optional<T>，包含最大值；树为空时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<T> findMax() const;
    
    /**
     * @brief 获取树的高度
     * @return 树的高度，空树返回0
     * @note 时间复杂度: O(1)
     */
    int height() const;
    
    /**
     * @brief 获取树中元素个数
     * @return 元素数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief 检查树是否为空
     * @return 树为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return root_ == nullptr; }
    
    /**
     * @brief 清空树中所有元素
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept;
    
    /**
     * @brief 中序遍历树，返回有序元素列表
     * @return 升序排列的元素向量
     * @note 时间复杂度: O(n)
     * @note 空间复杂度: O(n)
     */
    std::vector<T> inorderTraversal() const;
    
private:
    std::shared_ptr<AVLNode<T>> root_;
    size_t size_;
    
    // Helper methods
    std::shared_ptr<AVLNode<T>> insert(std::shared_ptr<AVLNode<T>> node, const T& value);
    std::shared_ptr<AVLNode<T>> insert(std::shared_ptr<AVLNode<T>> node, T&& value);
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
void AVLTree<T>::insert(T&& value) {
    root_ = insert(root_, std::move(value));
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
std::shared_ptr<AVLNode<T>> AVLTree<T>::insert(std::shared_ptr<AVLNode<T>> node, T&& value) {
    // Standard BST insertion with move semantics
    if (!node) {
        size_++;
        return std::make_shared<AVLNode<T>>(std::move(value));
    }
    
    if (value < node->data) {
        node->left = insert(node->left, std::move(value));
    } else if (value > node->data) {
        node->right = insert(node->right, std::move(value));
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
        
        // Case 1: Node with no child or one child
        if (!node->left) {
            size_--;  // 只在真正删除节点时减少计数
            return node->right;
        } else if (!node->right) {
            size_--;  // 只在真正删除节点时减少计数
            return node->left;
        }
        
        // Case 2: Node with two children
        // Find inorder successor (minimum in right subtree)
        auto successor = findMin(node->right);
        node->data = successor->data;
        // 递归删除后继节点，size_会在递归中正确处理
        node->right = remove(node->right, successor->data);
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
void AVLTree<T>::clear() noexcept {
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