#ifndef DATA_STRUCTURES_BTREEMAP_H
#define DATA_STRUCTURES_BTREEMAP_H

#include <memory>
#include <optional>
#include <array>
#include <vector>
#include <utility>
#include <stdexcept>
#include <algorithm>

namespace data_structures {

/**
 * @brief B-Tree 节点结构
 * 
 * @tparam K 键类型
 * @tparam V 值类型
 */
template<typename K, typename V>
struct BTreeNode {
    static constexpr int ORDER = 4;
    static constexpr int MIN_KEYS = ORDER / 2 - 1;      // 1
    static constexpr int MAX_KEYS = ORDER - 1;          // 3
    static constexpr int MAX_CHILDREN = ORDER;          // 4
    
    bool isLeaf;
    int numKeys;
    std::array<std::pair<K, V>, MAX_KEYS> entries;      // 键值对数组
    std::array<std::unique_ptr<BTreeNode>, MAX_CHILDREN> children; // 子节点指针
    
    explicit BTreeNode(bool leaf = true) 
        : isLeaf(leaf), numKeys(0), entries(), children() {}
    
    /**
     * @brief 检查节点是否已满
     * @return 节点键数达到最大值时返回true
     */
    bool isFull() const {
        return numKeys == MAX_KEYS;
    }
    
    /**
     * @brief 检查节点是否键数不足
     * @return 节点键数少于最小值时返回true
     */
    bool isUnderflow() const {
        return numKeys < MIN_KEYS;
    }
    
    /**
     * @brief 在节点中查找键的位置（使用二分查找）
     * @param key 要查找的键
     * @return 第一个大于等于 key 的索引
     */
    int findKeyIndex(const K& key) const {
        int left = 0, right = numKeys;
        while (left < right) {
            int mid = left + (right - left) / 2;
            if (entries[mid].first < key) {
                left = mid + 1;
            } else {
                right = mid;
            }
        }
        return left;
    }
};

/**
 * @brief BTreeMap（B树映射）数据结构
 * 
 * B-Tree 是一种自平衡的多路搜索树，特别适合用于数据库和文件系统。
 * 本实现使用阶数为4的B树（每个节点最多3个键，最少1个键）。
 * 
 * @tparam K 键类型，必须支持比较运算符（<, >, ==）
 * @tparam V 值类型
 * 
 * @note 时间复杂度: insert/find/remove 均为 O(log n)
 * @note 空间复杂度: O(n)
 * @note 平衡性质: 所有叶子节点在同一层
 * @note 节点阶数: ORDER = 4（每个节点最多3个键，最多4个子节点）
 * 
 * @example
 * BTreeMap<int, std::string> map;
 * map.insert(10, "ten");
 * map.insert(5, "five");
 * auto value = map.find(10);  // std::optional<std::string>("ten")
 * bool exists = map.contains(5);  // true
 * map.remove(5);
 */
template<typename K, typename V>
class BTreeMap {
public:
    /**
     * @brief 默认构造函数
     */
    BTreeMap() : root_(nullptr), size_(0) {}
    
    /**
     * @brief 默认析构函数
     */
    ~BTreeMap() = default;
    
    // ==================== 基本操作 ====================
    
    /**
     * @brief 插入键值对（左值版本）
     * @param key 要插入的键
     * @param value 要插入的值
     * @note 时间复杂度: O(log n)
     * @note 如果键已存在，更新其值
     */
    void insert(const K& key, const V& value);
    
    /**
     * @brief 插入键值对（右值版本）
     * @param key 要插入的键（支持移动语义）
     * @param value 要插入的值（支持移动语义）
     * @note 时间复杂度: O(log n)
     */
    void insert(K&& key, V&& value);
    
    /**
     * @brief 查找指定键的值
     * @param key 要查找的键
     * @return std::optional<V>，包含对应的值；键不存在时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<V> find(const K& key) const;
    
    /**
     * @brief 检查键是否存在
     * @param key 要检查的键
     * @return 键存在返回true，否则返回false
     * @note 时间复杂度: O(log n)
     */
    bool contains(const K& key) const;
    
    /**
     * @brief 删除指定键值对
     * @param key 要删除的键
     * @return 成功删除返回true，键不存在返回false
     * @note 时间复杂度: O(log n)
     */
    bool remove(const K& key);
    
    /**
     * @brief 清空所有键值对
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept;
    
    // ==================== 容量相关 ====================
    
    /**
     * @brief 获取键值对数量
     * @return 元素数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief 检查是否为空
     * @return 为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return root_ == nullptr; }
    
    // ==================== 访问操作 ====================
    
    /**
     * @brief 访问指定键的值（const版本）
     * @param key 要访问的键
     * @return 对应的值的引用
     * @throws std::out_of_range 键不存在时抛出异常
     * @note 时间复杂度: O(log n)
     */
    const V& at(const K& key) const;
    
    /**
     * @brief 访问指定键的值（非const版本）
     * @param key 要访问的键
     * @return 对应的值的引用
     * @throws std::out_of_range 键不存在时抛出异常
     * @note 时间复杂度: O(log n)
     */
    V& at(const K& key);
    
    /**
     * @brief 访问指定键的值（不存在时插入默认值）
     * @param key 要访问的键
     * @return 对应的值的引用
     * @note 时间复杂度: O(log n)
     * @note 如果键不存在，插入默认构造的值
     */
    V& operator[](const K& key);
    
    // ==================== 范围查询 ====================
    
    /**
     * @brief 查找第一个不小于指定键的元素
     * @param key 查找的键
     * @return std::optional<std::pair<K, V>>，包含找到的键值对；未找到返回std::nullopt
     * @note 时间复杂度: O(log n + k)，k为结果数量
     */
    std::optional<std::pair<K, V>> lower_bound(const K& key) const;
    
    /**
     * @brief 查找第一个大于指定键的元素
     * @param key 查找的键
     * @return std::optional<std::pair<K, V>>，包含找到的键值对；未找到返回std::nullopt
     * @note 时间复杂度: O(log n + k)，k为结果数量
     */
    std::optional<std::pair<K, V>> upper_bound(const K& key) const;
    
    /**
     * @brief 查找最小键值对
     * @return std::optional<std::pair<K, V>>，包含最小键值对；树为空时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<std::pair<K, V>> findMin() const;
    
    /**
     * @brief 查找最大键值对
     * @return std::optional<std::pair<K, V>>，包含最大键值对；树为空时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<std::pair<K, V>> findMax() const;
    
    // ==================== 迭代器 ====================
    
    /**
     * @brief 前向迭代器类
     */
    class Iterator {
    public:
        using iterator_category = std::forward_iterator_tag;
        using value_type = std::pair<K, V>;
        using difference_type = std::ptrdiff_t;
        using pointer = const value_type*;
        using reference = const value_type&;
        
        Iterator() : isEnd_(true) {}
        
        reference operator*() const {
            if (isEnd_ || stack_.empty()) {
                throw std::out_of_range("Iterator dereference out of range");
            }
            const auto& frame = stack_.back();
            return frame.node->entries[frame.keyIndex];
        }
        
        pointer operator->() const {
            return &(operator*());
        }
        
        Iterator& operator++();
        
        Iterator operator++(int) {
            Iterator tmp = *this;
            ++(*this);
            return tmp;
        }
        
        bool operator==(const Iterator& other) const {
            if (isEnd_ && other.isEnd_) return true;
            if (isEnd_ != other.isEnd_) return false;
            if (stack_.size() != other.stack_.size()) return false;
            if (stack_.empty()) return true;
            
            const auto& f1 = stack_.back();
            const auto& f2 = other.stack_.back();
            return f1.node == f2.node && f1.keyIndex == f2.keyIndex;
        }
        
        bool operator!=(const Iterator& other) const {
            return !(*this == other);
        }
        
    private:
        friend class BTreeMap;
        
        struct StackFrame {
            const BTreeNode<K, V>* node;
            int keyIndex;
        };
        
        std::vector<StackFrame> stack_;
        bool isEnd_;
        
        explicit Iterator(bool isEnd) : isEnd_(isEnd) {}
    };
    
    /**
     * @brief 返回指向最小键的迭代器
     * @return 迭代器
     * @note 时间复杂度: O(log n)
     */
    Iterator begin() const;
    
    /**
     * @brief 返回尾后迭代器
     * @return 迭代器
     * @note 时间复杂度: O(1)
     */
    Iterator end() const {
        return Iterator(true);
    }
    
private:
    std::unique_ptr<BTreeNode<K, V>> root_;
    size_t size_;
    
    // ==================== 插入辅助函数 ====================
    
    void insertNonFull(BTreeNode<K, V>* node, const K& key, const V& value);
    void insertNonFull(BTreeNode<K, V>* node, K&& key, V&& value);
    void splitChild(BTreeNode<K, V>* parent, int index);
    
    // ==================== 查找辅助函数 ====================
    
    V* findHelper(BTreeNode<K, V>* node, const K& key) const;
    
    // ==================== 删除辅助函数 ====================
    
    bool removeHelper(BTreeNode<K, V>* node, const K& key);
    void removeFromLeaf(BTreeNode<K, V>* node, int index);
    void removeFromNonLeaf(BTreeNode<K, V>* node, int index);
    std::pair<K, V> getPredecessor(BTreeNode<K, V>* node);
    std::pair<K, V> getSuccessor(BTreeNode<K, V>* node);
    void ensureChildHasEnoughKeys(BTreeNode<K, V>* node, int childIndex);
    void borrowFromLeftSibling(BTreeNode<K, V>* parent, int childIndex);
    void borrowFromRightSibling(BTreeNode<K, V>* parent, int childIndex);
    void mergeWithLeftSibling(BTreeNode<K, V>* parent, int childIndex);
    void mergeWithRightSibling(BTreeNode<K, V>* parent, int childIndex);
};

// ==================== 模板实现 ====================

// 插入操作（左值版本）
template<typename K, typename V>
void BTreeMap<K, V>::insert(const K& key, const V& value) {
    if (!root_) {
        root_ = std::make_unique<BTreeNode<K, V>>(true);
        root_->entries[0] = {key, value};
        root_->numKeys = 1;
        size_++;
        return;
    }
    
    // 如果根节点已满，需要分裂
    if (root_->isFull()) {
        auto newRoot = std::make_unique<BTreeNode<K, V>>(false);
        newRoot->children[0] = std::move(root_);
        splitChild(newRoot.get(), 0);
        root_ = std::move(newRoot);
    }
    
    insertNonFull(root_.get(), key, value);
}

// 插入操作（右值版本）
template<typename K, typename V>
void BTreeMap<K, V>::insert(K&& key, V&& value) {
    if (!root_) {
        root_ = std::make_unique<BTreeNode<K, V>>(true);
        root_->entries[0] = {std::move(key), std::move(value)};
        root_->numKeys = 1;
        size_++;
        return;
    }
    
    // 如果根节点已满，需要分裂
    if (root_->isFull()) {
        auto newRoot = std::make_unique<BTreeNode<K, V>>(false);
        newRoot->children[0] = std::move(root_);
        splitChild(newRoot.get(), 0);
        root_ = std::move(newRoot);
    }
    
    insertNonFull(root_.get(), std::move(key), std::move(value));
}

// 向非满节点插入（左值版本）
template<typename K, typename V>
void BTreeMap<K, V>::insertNonFull(BTreeNode<K, V>* node, const K& key, const V& value) {
    int i = node->findKeyIndex(key);
    
    if (node->isLeaf) {
        // 检查键是否已存在
        if (i < node->numKeys && node->entries[i].first == key) {
            node->entries[i].second = value;  // 更新值
            return;
        }
        
        // 在叶子节点中插入键值对
        for (int j = node->numKeys; j > i; j--) {
            node->entries[j] = node->entries[j - 1];
        }
        node->entries[i] = {key, value};
        node->numKeys++;
        size_++;
    } else {
        // 内部节点：找到应下降的子节点
        if (i < node->numKeys && node->entries[i].first == key) {
            node->entries[i].second = value;  // 更新值
            return;
        }
        
        // 如果子节点已满，先分裂
        if (node->children[i]->isFull()) {
            splitChild(node, i);
            if (key > node->entries[i].first) {
                i++;
            } else if (key == node->entries[i].first) {
                node->entries[i].second = value;  // 更新值
                return;
            }
        }
        
        insertNonFull(node->children[i].get(), key, value);
    }
}

// 向非满节点插入（右值版本）
template<typename K, typename V>
void BTreeMap<K, V>::insertNonFull(BTreeNode<K, V>* node, K&& key, V&& value) {
    int i = node->findKeyIndex(key);
    
    if (node->isLeaf) {
        // 检查键是否已存在
        if (i < node->numKeys && node->entries[i].first == key) {
            node->entries[i].second = std::move(value);  // 更新值
            return;
        }
        
        // 在叶子节点中插入键值对
        for (int j = node->numKeys; j > i; j--) {
            node->entries[j] = std::move(node->entries[j - 1]);
        }
        node->entries[i] = {std::move(key), std::move(value)};
        node->numKeys++;
        size_++;
    } else {
        // 内部节点：找到应下降的子节点
        if (i < node->numKeys && node->entries[i].first == key) {
            node->entries[i].second = std::move(value);  // 更新值
            return;
        }
        
        // 如果子节点已满，先分裂
        if (node->children[i]->isFull()) {
            splitChild(node, i);
            if (key > node->entries[i].first) {
                i++;
            } else if (key == node->entries[i].first) {
                node->entries[i].second = std::move(value);  // 更新值
                return;
            }
        }
        
        insertNonFull(node->children[i].get(), std::move(key), std::move(value));
    }
}

// 分裂子节点
template<typename K, typename V>
void BTreeMap<K, V>::splitChild(BTreeNode<K, V>* parent, int index) {
    auto fullChild = parent->children[index].get();
    auto newNode = std::make_unique<BTreeNode<K, V>>(fullChild->isLeaf);
    
    // 中间键提升到父节点（索引1）
    auto midEntry = fullChild->entries[1];
    
    // 新节点接收右半部分（索引2）
    newNode->entries[0] = fullChild->entries[2];
    newNode->numKeys = 1;
    
    // 如果不是叶子节点，分配子节点
    if (!fullChild->isLeaf) {
        newNode->children[0] = std::move(fullChild->children[2]);
        newNode->children[1] = std::move(fullChild->children[3]);
    }
    
    // 原节点只保留左半部分（索引0）
    fullChild->numKeys = 1;
    
    // 在父节点中插入中间键
    for (int j = parent->numKeys; j > index; j--) {
        parent->entries[j] = parent->entries[j - 1];
        parent->children[j + 1] = std::move(parent->children[j]);
    }
    
    parent->entries[index] = midEntry;
    parent->children[index + 1] = std::move(newNode);
    parent->numKeys++;
}

// 查找操作
template<typename K, typename V>
std::optional<V> BTreeMap<K, V>::find(const K& key) const {
    if (!root_) {
        return std::nullopt;
    }
    
    V* result = findHelper(root_.get(), key);
    if (result) {
        return *result;
    }
    return std::nullopt;
}

// 查找辅助函数
template<typename K, typename V>
V* BTreeMap<K, V>::findHelper(BTreeNode<K, V>* node, const K& key) const {
    int i = node->findKeyIndex(key);
    
    if (i < node->numKeys && node->entries[i].first == key) {
        return const_cast<V*>(&node->entries[i].second);
    }
    
    if (node->isLeaf) {
        return nullptr;
    }
    
    return findHelper(node->children[i].get(), key);
}

// 检查键是否存在
template<typename K, typename V>
bool BTreeMap<K, V>::contains(const K& key) const {
    return find(key).has_value();
}

// 清空操作
template<typename K, typename V>
void BTreeMap<K, V>::clear() noexcept {
    root_ = nullptr;
    size_ = 0;
}

// 删除操作
template<typename K, typename V>
bool BTreeMap<K, V>::remove(const K& key) {
    if (!root_) {
        return false;
    }
    
    bool removed = removeHelper(root_.get(), key);
    
    if (removed) {
        // 如果根节点没有键且不是叶子节点,降低树高
        if (root_->numKeys == 0) {
            if (!root_->isLeaf) {
                root_ = std::move(root_->children[0]);
            } else {
                // 根节点是叶子且为空,清空整个树
                root_ = nullptr;
            }
        }
    }
    
    return removed;
}

// 删除辅助函数
template<typename K, typename V>
bool BTreeMap<K, V>::removeHelper(BTreeNode<K, V>* node, const K& key) {
    int i = node->findKeyIndex(key);
    
    // 情况1: 键在当前节点中
    if (i < node->numKeys && node->entries[i].first == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, i);
        } else {
            removeFromNonLeaf(node, i);
        }
        return true;
    }
    
    // 情况2: 键不在当前节点,且是叶子节点
    if (node->isLeaf) {
        return false;
    }
    
    // 情况3: 键可能在子节点中
    // 在下降之前,确保子节点有足够的键
    bool lastChild = (i == node->numKeys);
    
    if (node->children[i]->numKeys <= BTreeNode<K, V>::MIN_KEYS) {
        // 尝试从兄弟借键或合并
        if (i > 0 && node->children[i - 1] && 
            node->children[i - 1]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
            borrowFromLeftSibling(node, i);
        }
        else if (i < node->numKeys && node->children[i + 1] && 
                 node->children[i + 1]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
            borrowFromRightSibling(node, i);
        }
        else {
            // 需要合并
            if (i > 0 && node->children[i - 1]) {
                // 与左兄弟合并,当前子节点被合并到左兄弟中
                mergeWithLeftSibling(node, i);
                // 合并后,目标键在左兄弟中
                i--;
            } else if (i < node->numKeys && node->children[i + 1]) {
                // 与右兄弟合并,右兄弟被合并到当前子节点中
                mergeWithRightSibling(node, i);
                // 合并后,目标键仍在当前子节点中(索引不变)
            }
        }
    }
    
    // 如果是最后一个子节点,且父节点的键数可能已经改变
    if (lastChild && i > node->numKeys) {
        i = node->numKeys;
    }
    
    return removeHelper(node->children[i].get(), key);
}

// 从叶子节点删除键
template<typename K, typename V>
void BTreeMap<K, V>::removeFromLeaf(BTreeNode<K, V>* node, int index) {
    for (int i = index; i < node->numKeys - 1; i++) {
        node->entries[i] = node->entries[i + 1];
    }
    node->numKeys--;
    size_--;
}

// 从内部节点删除键
template<typename K, typename V>
void BTreeMap<K, V>::removeFromNonLeaf(BTreeNode<K, V>* node, int index) {
    const K& key = node->entries[index].first;
    
    // 如果左子节点有足够的键，用前驱替换
    if (node->children[index]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
        auto pred = getPredecessor(node->children[index].get());
        node->entries[index] = pred;
        removeHelper(node->children[index].get(), pred.first);
    }
    // 如果右子节点有足够的键，用后继替换
    else if (node->children[index + 1]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
        auto succ = getSuccessor(node->children[index + 1].get());
        node->entries[index] = succ;
        removeHelper(node->children[index + 1].get(), succ.first);
    }
    // 否则合并子节点
    else {
        mergeWithLeftSibling(node, index + 1);
        removeHelper(node->children[index].get(), key);
    }
}

// 获取前驱（左子树最大值）
template<typename K, typename V>
std::pair<K, V> BTreeMap<K, V>::getPredecessor(BTreeNode<K, V>* node) {
    while (!node->isLeaf) {
        node = node->children[node->numKeys].get();
    }
    return node->entries[node->numKeys - 1];
}

// 获取后继（右子树最小值）
template<typename K, typename V>
std::pair<K, V> BTreeMap<K, V>::getSuccessor(BTreeNode<K, V>* node) {
    while (!node->isLeaf) {
        node = node->children[0].get();
    }
    return node->entries[0];
}

// 确保子节点有足够的键
template<typename K, typename V>
void BTreeMap<K, V>::ensureChildHasEnoughKeys(BTreeNode<K, V>* node, int childIndex) {
    // 检查子节点是否存在
    if (!node->children[childIndex]) {
        return;
    }
    
    auto child = node->children[childIndex].get();
    
    if (child->numKeys > BTreeNode<K, V>::MIN_KEYS) {
        return;
    }
    
    // 尝试从左兄弟借键
    if (childIndex > 0 && node->children[childIndex - 1] && 
        node->children[childIndex - 1]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
        borrowFromLeftSibling(node, childIndex);
    }
    // 尝试从右兄弟借键
    else if (childIndex < node->numKeys && node->children[childIndex + 1] && 
             node->children[childIndex + 1]->numKeys > BTreeNode<K, V>::MIN_KEYS) {
        borrowFromRightSibling(node, childIndex);
    }
    // 合并节点
    else {
        if (childIndex > 0 && node->children[childIndex - 1]) {
            mergeWithLeftSibling(node, childIndex);
        } else if (childIndex < node->numKeys && node->children[childIndex + 1]) {
            mergeWithRightSibling(node, childIndex);
        }
    }
}

// 从左兄弟借键
template<typename K, typename V>
void BTreeMap<K, V>::borrowFromLeftSibling(BTreeNode<K, V>* parent, int childIndex) {
    auto child = parent->children[childIndex].get();
    auto leftSibling = parent->children[childIndex - 1].get();
    
    // 将子节点的键右移
    for (int i = child->numKeys; i > 0; i--) {
        child->entries[i] = child->entries[i - 1];
    }
    
    // 如果不是叶子节点，移动子节点指针
    if (!child->isLeaf) {
        for (int i = child->numKeys + 1; i > 0; i--) {
            child->children[i] = std::move(child->children[i - 1]);
        }
        child->children[0] = std::move(leftSibling->children[leftSibling->numKeys]);
    }
    
    // 从父节点下移一个键到子节点
    child->entries[0] = parent->entries[childIndex - 1];
    child->numKeys++;
    
    // 从左兄弟上移一个键到父节点
    parent->entries[childIndex - 1] = leftSibling->entries[leftSibling->numKeys - 1];
    leftSibling->numKeys--;
}

// 从右兄弟借键
template<typename K, typename V>
void BTreeMap<K, V>::borrowFromRightSibling(BTreeNode<K, V>* parent, int childIndex) {
    auto child = parent->children[childIndex].get();
    auto rightSibling = parent->children[childIndex + 1].get();
    
    // 从父节点下移一个键到子节点
    child->entries[child->numKeys] = parent->entries[childIndex];
    child->numKeys++;
    
    // 如果不是叶子节点，移动子节点指针
    if (!child->isLeaf) {
        child->children[child->numKeys] = std::move(rightSibling->children[0]);
    }
    
    // 从右兄弟上移一个键到父节点
    parent->entries[childIndex] = rightSibling->entries[0];
    
    // 右兄弟的键左移
    for (int i = 0; i < rightSibling->numKeys - 1; i++) {
        rightSibling->entries[i] = rightSibling->entries[i + 1];
    }
    
    // 如果不是叶子节点，移动子节点指针
    if (!rightSibling->isLeaf) {
        for (int i = 0; i < rightSibling->numKeys; i++) {
            rightSibling->children[i] = std::move(rightSibling->children[i + 1]);
        }
    }
    
    rightSibling->numKeys--;
}

// 与左兄弟合并
template<typename K, typename V>
void BTreeMap<K, V>::mergeWithLeftSibling(BTreeNode<K, V>* parent, int childIndex) {
    auto child = parent->children[childIndex].get();
    auto leftSibling = parent->children[childIndex - 1].get();
    
    // 从父节点下移一个键到左兄弟
    leftSibling->entries[leftSibling->numKeys] = parent->entries[childIndex - 1];
    leftSibling->numKeys++;
    
    // 将子节点的所有键复制到左兄弟
    for (int i = 0; i < child->numKeys; i++) {
        leftSibling->entries[leftSibling->numKeys] = child->entries[i];
        leftSibling->numKeys++;
    }
    
    // 如果不是叶子节点，复制子节点指针
    if (!child->isLeaf) {
        for (int i = 0; i <= child->numKeys; i++) {
            leftSibling->children[leftSibling->numKeys - child->numKeys + i] = 
                std::move(child->children[i]);
        }
    }
    
    // 从父节点删除键
    for (int i = childIndex - 1; i < parent->numKeys - 1; i++) {
        parent->entries[i] = parent->entries[i + 1];
    }
    
    // 移动父节点的子节点指针
    for (int i = childIndex; i < parent->numKeys; i++) {
        parent->children[i] = std::move(parent->children[i + 1]);
    }
    
    parent->numKeys--;
}

// 与右兄弟合并
template<typename K, typename V>
void BTreeMap<K, V>::mergeWithRightSibling(BTreeNode<K, V>* parent, int childIndex) {
    auto child = parent->children[childIndex].get();
    auto rightSibling = parent->children[childIndex + 1].get();
    
    // 从父节点下移一个键到子节点
    child->entries[child->numKeys] = parent->entries[childIndex];
    child->numKeys++;
    
    // 将右兄弟的所有键复制到子节点
    for (int i = 0; i < rightSibling->numKeys; i++) {
        child->entries[child->numKeys] = rightSibling->entries[i];
        child->numKeys++;
    }
    
    // 如果不是叶子节点，复制子节点指针
    if (!child->isLeaf) {
        for (int i = 0; i <= rightSibling->numKeys; i++) {
            child->children[child->numKeys - rightSibling->numKeys + i] = 
                std::move(rightSibling->children[i]);
        }
    }
    
    // 从父节点删除键
    for (int i = childIndex; i < parent->numKeys - 1; i++) {
        parent->entries[i] = parent->entries[i + 1];
    }
    
    // 移动父节点的子节点指针
    for (int i = childIndex + 1; i < parent->numKeys; i++) {
        parent->children[i] = std::move(parent->children[i + 1]);
    }
    
    parent->numKeys--;
}

// at 操作（const版本）
template<typename K, typename V>
const V& BTreeMap<K, V>::at(const K& key) const {
    V* result = findHelper(root_.get(), key);
    if (!result) {
        throw std::out_of_range("Key not found in BTreeMap");
    }
    return *result;
}

// at 操作（非const版本）
template<typename K, typename V>
V& BTreeMap<K, V>::at(const K& key) {
    V* result = findHelper(root_.get(), key);
    if (!result) {
        throw std::out_of_range("Key not found in BTreeMap");
    }
    return *result;
}

// operator[] 操作
template<typename K, typename V>
V& BTreeMap<K, V>::operator[](const K& key) {
    if (root_) {
        V* result = findHelper(root_.get(), key);
        if (result) {
            return *result;
        }
    }
    
    // 键不存在，插入默认值
    insert(key, V{});
    return *findHelper(root_.get(), key);
}

// findMin 操作
template<typename K, typename V>
std::optional<std::pair<K, V>> BTreeMap<K, V>::findMin() const {
    if (!root_) {
        return std::nullopt;
    }
    
    auto node = root_.get();
    while (!node->isLeaf) {
        node = node->children[0].get();
    }
    
    return node->entries[0];
}

// findMax 操作
template<typename K, typename V>
std::optional<std::pair<K, V>> BTreeMap<K, V>::findMax() const {
    if (!root_) {
        return std::nullopt;
    }
    
    auto node = root_.get();
    while (!node->isLeaf) {
        node = node->children[node->numKeys].get();
    }
    
    return node->entries[node->numKeys - 1];
}

// lower_bound 操作
template<typename K, typename V>
std::optional<std::pair<K, V>> BTreeMap<K, V>::lower_bound(const K& key) const {
    auto it = begin();
    while (it != end()) {
        if ((*it).first >= key) {
            return *it;
        }
        ++it;
    }
    return std::nullopt;
}

// upper_bound 操作
template<typename K, typename V>
std::optional<std::pair<K, V>> BTreeMap<K, V>::upper_bound(const K& key) const {
    auto it = begin();
    while (it != end()) {
        if ((*it).first > key) {
            return *it;
        }
        ++it;
    }
    return std::nullopt;
}

// begin 迭代器
template<typename K, typename V>
typename BTreeMap<K, V>::Iterator BTreeMap<K, V>::begin() const {
    if (!root_) {
        return Iterator(true);
    }
    
    Iterator it(false);
    auto node = root_.get();
    
    // 下降到最左的叶子节点
    while (!node->isLeaf) {
        it.stack_.push_back({node, 0});
        node = node->children[0].get();
    }
    
    it.stack_.push_back({node, 0});
    return it;
}

// Iterator operator++
template<typename K, typename V>
typename BTreeMap<K, V>::Iterator& BTreeMap<K, V>::Iterator::operator++() {
    if (isEnd_ || stack_.empty()) {
        isEnd_ = true;
        return *this;
    }
    
    auto& frame = stack_.back();
    
    if (!frame.node->isLeaf) {
        // 内部节点：下降到右子树的最左节点
        auto child = frame.node->children[frame.keyIndex + 1].get();
        frame.keyIndex++;
        
        while (!child->isLeaf) {
            stack_.push_back({child, 0});
            child = child->children[0].get();
        }
        stack_.push_back({child, 0});
    } else {
        // 叶子节点：移动到下一个键
        frame.keyIndex++;
        
        // 如果当前节点的键已遍历完，回溯到父节点
        while (!stack_.empty() && stack_.back().keyIndex >= stack_.back().node->numKeys) {
            stack_.pop_back();
        }
        
        if (stack_.empty()) {
            isEnd_ = true;
        }
    }
    
    return *this;
}

} // namespace data_structures

#endif // DATA_STRUCTURES_BTREEMAP_H
