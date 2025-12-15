#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>
#include <utility>

namespace data_structures {

/**
 * @brief 二叉堆数据结构（最小堆或最大堆）
 * 
 * 基于完全二叉树实现的优先队列，使用数组存储。
 * 支持自定义比较器，默认为最小堆（std::less）。
 * 使用std::greater可创建最大堆。
 * 
 * @tparam T 堆中存储的元素类型
 * @tparam Compare 比较器类型，默认为std::less<T>（最小堆）
 * 
 * @note 时间复杂度: insert O(log n), extractTop O(log n), top O(1)
 * @note 空间复杂度: O(n)，其中n是元素数量
 * @note 最小堆性质: 父节点值 <= 子节点值
 * @note 最大堆性质: 父节点值 >= 子节点值（使用std::greater）
 * 
 * @example
 * // 最小堆
 * Heap<int> minHeap;
 * minHeap.insert(5);
 * minHeap.insert(2);
 * auto min = minHeap.top();  // 返回 std::optional<int>(2)
 * 
 * @example
 * // 最大堆
 * Heap<int, std::greater<int>> maxHeap;
 * maxHeap.insert(5);
 * maxHeap.insert(2);
 * auto max = maxHeap.top();  // 返回 std::optional<int>(5)
 */
template<typename T, typename Compare = std::less<T>>
class Heap {
public:
    /**
     * @brief 默认构造函数，创建空堆
     */
    Heap() : size_(0) {}
    
    /**
     * @brief 使用自定义比较器构造空堆
     * @param comp 自定义比较器对象
     */
    explicit Heap(Compare comp) : comparator_(comp), size_(0) {}
    
    /**
     * @brief 从向量构建堆
     * @param values 初始元素向量
     * @note 时间复杂度: O(n)（使用buildHeap算法）
     */
    explicit Heap(const std::vector<T>& values);
    
    /**
     * @brief 从向量构建堆，使用自定义比较器
     * @param values 初始元素向量
     * @param comp 自定义比较器对象
     * @note 时间复杂度: O(n)
     */
    Heap(const std::vector<T>& values, Compare comp);
    
    /**
     * @brief 插入元素（左值版本）
     * @param value 要插入的元素（左值引用）
     * @note 时间复杂度: O(log n)
     */
    void insert(const T& value);
    
    /**
     * @brief 插入元素（右值版本）
     * @param value 要插入的元素（右值引用，支持移动语义）
     * @note 时间复杂度: O(log n)
     */
    void insert(T&& value);
    
    /**
     * @brief 提取并移除堆顶元素
     * @return std::optional<T>，包含堆顶元素；堆为空时返回std::nullopt
     * @note 时间复杂度: O(log n)
     */
    std::optional<T> extractTop();
    
    /**
     * @brief 查看堆顶元素（不移除）
     * @return std::optional<T>，包含堆顶元素；堆为空时返回std::nullopt
     * @note 时间复杂度: O(1)
     */
    std::optional<T> top() const;
    
    /**
     * @brief 获取堆中元素个数
     * @return 堆中元素的数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief 检查堆是否为空
     * @return 堆为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return size_ == 0; }
    
    /**
     * @brief 清空堆中所有元素
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept;
    
private:
    std::vector<T> data_;       ///< 内部存储数组
    Compare comparator_;        ///< 比较器对象
    size_t size_;               ///< 堆中元素个数
    
    // Helper methods
    
    /**
     * @brief 向上调整堆，维护堆性质
     * @param index 起始索引
     */
    void heapifyUp(size_t index);
    
    /**
     * @brief 向下调整堆，维护堆性质
     * @param index 起始索引
     */
    void heapifyDown(size_t index);
    
    /**
     * @brief 从无序数组构建堆
     * @note 时间复杂度: O(n)
     */
    void buildHeap();
    
    // Index helpers
    size_t parent(size_t index) const { return (index - 1) / 2; }
    size_t leftChild(size_t index) const { return 2 * index + 1; }
    size_t rightChild(size_t index) const { return 2 * index + 2; }
};

// Template implementations

template<typename T, typename Compare>
Heap<T, Compare>::Heap(const std::vector<T>& values) : size_(0) {
    data_ = values;
    size_ = values.size();
    buildHeap();
}

template<typename T, typename Compare>
Heap<T, Compare>::Heap(const std::vector<T>& values, Compare comp) 
    : comparator_(comp), size_(0) {
    data_ = values;
    size_ = values.size();
    buildHeap();
}

template<typename T, typename Compare>
void Heap<T, Compare>::insert(const T& value) {
    data_.push_back(value);
    size_++;
    heapifyUp(size_ - 1);
}

template<typename T, typename Compare>
void Heap<T, Compare>::insert(T&& value) {
    data_.push_back(std::move(value));
    size_++;
    heapifyUp(size_ - 1);
}

template<typename T, typename Compare>
std::optional<T> Heap<T, Compare>::extractTop() {
    if (size_ == 0) {
        return std::nullopt;
    }
    
    T topValue = data_[0];
    
    data_[0] = data_[size_ - 1];
    data_.pop_back();
    size_--;
    
    if (size_ > 0) {
        heapifyDown(0);
    }
    
    return topValue;
}

template<typename T, typename Compare>
std::optional<T> Heap<T, Compare>::top() const {
    if (size_ == 0) {
        return std::nullopt;
    }
    return data_[0];
}

template<typename T, typename Compare>
void Heap<T, Compare>::clear() noexcept {
    data_.clear();
    size_ = 0;
}

template<typename T, typename Compare>
void Heap<T, Compare>::heapifyUp(size_t index) {
    while (index > 0) {
        size_t parentIdx = parent(index);
        if (comparator_(data_[index], data_[parentIdx])) {
            std::swap(data_[index], data_[parentIdx]);
            index = parentIdx;
        } else {
            break;
        }
    }
}

template<typename T, typename Compare>
void Heap<T, Compare>::heapifyDown(size_t index) {
    while (leftChild(index) < size_) {
        size_t smallestOrLargest = index;
        size_t left = leftChild(index);
        size_t right = rightChild(index);
        
        if (left < size_ && comparator_(data_[left], data_[smallestOrLargest])) {
            smallestOrLargest = left;
        }
        
        if (right < size_ && comparator_(data_[right], data_[smallestOrLargest])) {
            smallestOrLargest = right;
        }
        
        if (smallestOrLargest != index) {
            std::swap(data_[index], data_[smallestOrLargest]);
            index = smallestOrLargest;
        } else {
            break;
        }
    }
}

template<typename T, typename Compare>
void Heap<T, Compare>::buildHeap() {
    // Start from last non-leaf node and heapify down
    if (size_ <= 1) return;
    
    for (int i = static_cast<int>(size_ / 2) - 1; i >= 0; i--) {
        heapifyDown(static_cast<size_t>(i));
    }
}

} // namespace data_structures

#endif // DATA_STRUCTURES_HEAP_H