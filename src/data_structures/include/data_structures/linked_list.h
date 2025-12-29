#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <memory>
#include <optional>
#include <utility>

namespace data_structures {

/**
 * @brief 单链表节点结构
 * 
 * @tparam T 节点存储的数据类型
 */
template<typename T>
struct Node {
    T data;                           ///< 节点存储的数据
    std::shared_ptr<Node<T>> next;    ///< 指向下一个节点的智能指针
    
    explicit Node(const T& value) : data(value), next(nullptr) {}
    explicit Node(T&& value) : data(std::move(value)), next(nullptr) {}
};

/**
 * @brief 单链表数据结构
 * 
 * 基于智能指针实现的泛型单链表，支持在头部和尾部插入元素。
 * 维护头指针、尾指针和大小计数器，确保O(1)的尾部插入性能。
 * 
 * @tparam T 链表中存储的元素类型
 * 
 * @note 时间复杂度: pushFront O(1), pushBack O(1), popFront O(1), find O(n)
 * @note 空间复杂度: O(n)，其中n是元素数量
 * @note 内存管理: 使用std::shared_ptr自动管理内存
 * 
 * @example
 * LinkedList<int> list;
 * list.pushBack(1);
 * list.pushBack(2);
 * list.pushFront(0);
 * // list: 0 -> 1 -> 2
 */
template<typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr), tail_(nullptr), size_(0) {}
    
    /**
     * @brief 拷贝构造函数，执行深拷贝
     * @param other 要拷贝的链表
     * @note 时间复杂度: O(n)
     */
    LinkedList(const LinkedList& other) : head_(nullptr), tail_(nullptr), size_(0) {
        // 遍历原链表，逐个拷贝节点
        auto current = other.head_;
        while (current) {
            pushBack(current->data);
            current = current->next;
        }
    }
    
    /**
     * @brief 移动构造函数，转移所有权
     * @param other 要移动的链表（移动后将为空）
     * @note 时间复杂度: O(1)
     */
    LinkedList(LinkedList&& other) noexcept 
        : head_(std::move(other.head_)), 
          tail_(other.tail_), 
          size_(other.size_) {
        // 将源对象置为有效但未指定状态
        other.tail_ = nullptr;
        other.size_ = 0;
    }
    
    /**
     * @brief 拷贝赋值运算符
     * @param other 要拷贝的链表
     * @return 当前对象的引用
     * @note 时间复杂度: O(n + m)，n为当前链表长度，m为源链表长度
     */
    LinkedList& operator=(const LinkedList& other) {
        if (this != &other) {
            // 使用拷贝交换惯用法 (copy-and-swap idiom)
            LinkedList temp(other);
            swap(temp);
        }
        return *this;
    }
    
    /**
     * @brief 移动赋值运算符
     * @param other 要移动的链表
     * @return 当前对象的引用
     * @note 时间复杂度: O(1)
     */
    LinkedList& operator=(LinkedList&& other) noexcept {
        if (this != &other) {
            // 释放当前资源
            clear();
            // 转移所有权
            head_ = std::move(other.head_);
            tail_ = other.tail_;
            size_ = other.size_;
            // 将源对象置为有效但未指定状态
            other.tail_ = nullptr;
            other.size_ = 0;
        }
        return *this;
    }
    
    /**
     * @brief 析构函数，自动释放所有资源
     * @note 使用智能指针，自动管理内存
     */
    ~LinkedList() = default;
    
    /**
     * @brief 在链表头部插入元素（左值版本）
     * @param value 要插入的元素（左值引用）
     * @note 时间复杂度: O(1)
     */
    void pushFront(const T& value);
    
    /**
     * @brief 在链表头部插入元素（右值版本）
     * @param value 要插入的元素（右值引用，支持移动语义）
     * @note 时间复杂度: O(1)
     */
    void pushFront(T&& value);
    
    /**
     * @brief 在链表尾部插入元素（左值版本）
     * @param value 要插入的元素（左值引用）
     * @note 时间复杂度: O(1)（通过维护tail_指针实现）
     */
    void pushBack(const T& value);
    
    /**
     * @brief 在链表尾部插入元素（右值版本）
     * @param value 要插入的元素（右值引用，支持移动语义）
     * @note 时间复杂度: O(1)（通过维护tail_指针实现）
     */
    void pushBack(T&& value);
    
    /**
     * @brief 删除链表头部元素
     * @return 成功返回true，链表为空时返回false
     * @note 时间复杂度: O(1)
     */
    bool popFront();
    
    /**
     * @brief 在链表中查找指定元素
     * @param value 要查找的元素值
     * @return 找到返回true，否则返回false
     * @note 时间复杂度: O(n)
     */
    bool find(const T& value) const;
    
    /**
     * @brief 获取链表中元素个数
     * @return 链表中元素的数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return size_; }
    
    /**
     * @brief 检查链表是否为空
     * @return 链表为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return head_ == nullptr; }
    
    /**
     * @brief 获取链表头部元素（不移除）
     * @return std::optional<T>，包含头部元素；链表为空时返回std::nullopt
     * @note 时间复杂度: O(1)
     */
    std::optional<T> front() const;
    
    /**
     * @brief 清空链表中所有元素
     * @note 时间复杂度: O(n)（智能指针的析构过程）
     */
    void clear();
    
    /**
     * @brief 与另一个链表交换内容
     * @param other 要交换的链表
     * @note 时间复杂度: O(1)
     */
    void swap(LinkedList& other) noexcept {
        std::swap(head_, other.head_);
        std::swap(tail_, other.tail_);
        std::swap(size_, other.size_);
    }
    
private:
    std::shared_ptr<Node<T>> head_;  ///< 头指针，拥有链表节点的所有权
    Node<T>* tail_;                  ///< 尾指针（观察者指针，不拥有所有权）
    size_t size_;                    ///< 链表元素个数
};

// 模板实现
template<typename T>
void LinkedList<T>::pushFront(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    newNode->next = head_;
    head_ = newNode;
    
    // 如果链表原本为空，tail_也要指向新节点
    if (size_ == 0) {
        tail_ = newNode.get();
    }
    
    size_++;
}

template<typename T>
void LinkedList<T>::pushFront(T&& value) {
    auto newNode = std::make_shared<Node<T>>(std::move(value));
    newNode->next = head_;
    head_ = newNode;
    
    // 如果链表原本为空，tail_也要指向新节点
    if (size_ == 0) {
        tail_ = newNode.get();
    }
    
    size_++;
}

template<typename T>
void LinkedList<T>::pushBack(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    
    if (!head_) {
        // 链表为空，head_和tail_都指向新节点
        head_ = newNode;
        tail_ = newNode.get();
    } else {
        // 链表不为空，直接在tail_后插入
        tail_->next = newNode;
        tail_ = newNode.get();
    }
    size_++;
}

template<typename T>
void LinkedList<T>::pushBack(T&& value) {
    auto newNode = std::make_shared<Node<T>>(std::move(value));
    
    if (!head_) {
        // 链表为空，head_和tail_都指向新节点
        head_ = newNode;
        tail_ = newNode.get();
    } else {
        // 链表不为空，直接在tail_后插入
        tail_->next = newNode;
        tail_ = newNode.get();
    }
    size_++;
}

template<typename T>
bool LinkedList<T>::popFront() {
    if (!head_) {
        return false;
    }
    head_ = head_->next;
    size_--;
    
    // 如果删除后链表为空，tail_也要置空
    if (size_ == 0) {
        tail_ = nullptr;
    }
    
    return true;
}

template<typename T>
bool LinkedList<T>::find(const T& value) const {
    auto current = head_;
    while (current) {
        if (current->data == value) {
            return true;
        }
        current = current->next;
    }
    return false;
}

template<typename T>
std::optional<T> LinkedList<T>::front() const {
    if (head_) {
        return head_->data;
    }
    return std::nullopt;
}

template<typename T>
void LinkedList<T>::clear() {
    head_ = nullptr;
    tail_ = nullptr;  // 清空时也要将tail_置空
    size_ = 0;
}

} // namespace data_structures

#endif // DATA_STRUCTURES_LINKED_LIST_H