#ifndef DATA_STRUCTURES_SKIP_LIST_H
#define DATA_STRUCTURES_SKIP_LIST_H

#include <memory>
#include <optional>
#include <vector>
#include <random>
#include <cmath>

namespace data_structures {

/**
 * @brief 跳表节点结构
 * 
 * @tparam T 节点存储的数据类型
 */
template<typename T>
struct SkipNode {
    std::optional<T> data;                              ///< 节点数据（头节点为nullopt）
    bool is_header;                                     ///< 标记是否为头节点
    std::vector<std::shared_ptr<SkipNode<T>>> forward; ///< 各层级的前向指针数组
    
    /**
     * @brief 普通节点构造函数
     * @param value 节点值
     * @param level 节点层级
     */
    SkipNode(const T& value, int level) 
        : data(value), is_header(false), forward(level + 1, nullptr) {}
    
    /**
     * @brief 头节点构造函数
     * @param level 头节点的最大层级
     * @param header 标记为头节点
     */
    SkipNode(int level, bool header) 
        : data(std::nullopt), is_header(header), forward(level + 1, nullptr) {}
};

/**
 * @brief 跳表（Skip List）数据结构
 * 
 * 跳表是一种基于概率平衡的数据结构，通过多层链表实现快速查找。
 * 底层是完整的有序链表，上层是下层的"快速通道"。
 * 新节点的层级通过随机算法确定，期望时间复杂度为O(log n)。
 * 
 * @tparam T 跳表中存储的元素类型，必须支持比较运算符（<, ==）
 * 
 * @note 时间复杂度: search/insert/remove 期望 O(log n)，最坏 O(n)
 * @note 空间复杂度: 期望 O(n)
 * @note 层级概率: P = 0.5（每个节点有50%概率晋升到上一层）
 * @note 最大层级: 16
 * @note 优点: 实现简单，不需要旋转操作，支持并发访问
 * 
 * @example
 * SkipList<int> list;
 * list.insert(3);
 * list.insert(1);
 * list.insert(5);
 * bool found = list.search(3);  // true
 * list.remove(3);
 * found = list.search(3);       // false
 */
template<typename T>
class SkipList {
public:
    static constexpr int MAX_LEVEL = 16;        ///< 最大层级
    static constexpr float PROBABILITY = 0.5f;  ///< 层级晋升概率
    
    /**
     * @brief 构造函数，初始化空跳表
     */
    SkipList();
    
    /**
     * @brief 插入元素
     * @param value 要插入的元素值
     * @note 时间复杂度: 期望 O(log n)
     * @note 不允许重复值
     */
    void insert(const T& value);
    
    /**
     * @brief 删除指定元素
     * @param value 要删除的元素值
     * @return 成功删除返回true，元素不存在返回false
     * @note 时间复杂度: 期望 O(log n)
     */
    bool remove(const T& value);
    
    /**
     * @brief 查找指定元素
     * @param value 要查找的元素值
     * @return 找到返回true，否则返回false
     * @note 时间复杂度: 期望 O(log n)
     */
    bool search(const T& value) const;
    
    /**
     * @brief 获取跳表中元素个数
     * @return 元素数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief 检查跳表是否为空
     * @return 跳表为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return size_ == 0; }
    
    /**
     * @brief 清空跳表中所有元素
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept;
    
    /**
     * @brief 获取当前跳表的最大层级
     * @return 当前最高节点的层级
     * @note 时间复杂度: O(1)
     */
    int maxLevel() const noexcept { return currentMaxLevel_; }
    
private:
    std::shared_ptr<SkipNode<T>> header_;
    int currentMaxLevel_;
    size_t size_;
    std::mt19937 randomGen_;
    std::uniform_real_distribution<float> distribution_;
    
    // Helper methods
    int randomLevel();
    std::shared_ptr<SkipNode<T>> createNode(const T& value, int level);
};

// Template implementations

template<typename T>
SkipList<T>::SkipList() 
    : currentMaxLevel_(0), size_(0), distribution_(0.0f, 1.0f) {
    // Create header node with maximum possible level (使用头节点专用构造函数)
    header_ = std::make_shared<SkipNode<T>>(MAX_LEVEL, true);
    
    // Initialize random generator
    std::random_device rd;
    randomGen_.seed(rd());
}

template<typename T>
int SkipList<T>::randomLevel() {
    int level = 0;
    while (distribution_(randomGen_) < PROBABILITY && level < MAX_LEVEL) {
        level++;
    }
    return level;
}

template<typename T>
std::shared_ptr<SkipNode<T>> SkipList<T>::createNode(const T& value, int level) {
    return std::make_shared<SkipNode<T>>(value, level);
}

template<typename T>
void SkipList<T>::insert(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(MAX_LEVEL + 1);
    auto current = header_;
    
    // Find position to insert
    for (int i = currentMaxLevel_; i >= 0; i--) {
        while (current->forward[i] && 
               !current->forward[i]->is_header && 
               current->forward[i]->data.has_value() &&
               current->forward[i]->data.value() < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Check if element already exists
    if (current && !current->is_header && 
        current->data.has_value() && 
        current->data.value() == value) {
        // Duplicate - optionally handle differently
        return;
    }
    
    // Generate random level for new node
    int newLevel = randomLevel();
    
    // Update max level if necessary
    if (newLevel > currentMaxLevel_) {
        for (int i = currentMaxLevel_ + 1; i <= newLevel; i++) {
            update[i] = header_;
        }
        currentMaxLevel_ = newLevel;
    }
    
    // Create new node
    auto newNode = createNode(value, newLevel);
    
    // Insert node by updating forward pointers
    for (int i = 0; i <= newLevel; i++) {
        newNode->forward[i] = update[i]->forward[i];
        update[i]->forward[i] = newNode;
    }
    
    size_++;
}

template<typename T>
bool SkipList<T>::remove(const T& value) {
    std::vector<std::shared_ptr<SkipNode<T>>> update(MAX_LEVEL + 1);
    auto current = header_;
    
    // Find the node to remove
    for (int i = currentMaxLevel_; i >= 0; i--) {
        while (current->forward[i] && 
               !current->forward[i]->is_header && 
               current->forward[i]->data.has_value() &&
               current->forward[i]->data.value() < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Check if element exists
    if (!current || current->is_header || 
        !current->data.has_value() || 
        current->data.value() != value) {
        return false;
    }
    
    // Remove node by updating forward pointers
    for (int i = 0; i <= currentMaxLevel_; i++) {
        if (update[i]->forward[i] != current) {
            break;
        }
        update[i]->forward[i] = current->forward[i];
    }
    
    // Update max level if necessary
    while (currentMaxLevel_ > 0 && !header_->forward[currentMaxLevel_]) {
        currentMaxLevel_--;
    }
    
    size_--;
    return true;
}

template<typename T>
bool SkipList<T>::search(const T& value) const {
    auto current = header_;
    
    // Traverse from top level to bottom
    for (int i = currentMaxLevel_; i >= 0; i--) {
        while (current->forward[i] && 
               !current->forward[i]->is_header && 
               current->forward[i]->data.has_value() &&
               current->forward[i]->data.value() < value) {
            current = current->forward[i];
        }
    }
    
    // Move to next node at level 0
    current = current->forward[0];
    
    // Check if we found the value
    return current && !current->is_header && 
           current->data.has_value() && 
           current->data.value() == value;
}

template<typename T>
void SkipList<T>::clear() noexcept {
    // Clear all forward pointers from header
    for (int i = 0; i <= MAX_LEVEL; i++) {
        header_->forward[i] = nullptr;
    }
    
    currentMaxLevel_ = 0;
    size_ = 0;
}

} // namespace data_structures

#endif // DATA_STRUCTURES_SKIP_LIST_H