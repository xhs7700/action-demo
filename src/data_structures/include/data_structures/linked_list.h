#ifndef DATA_STRUCTURES_LINKED_LIST_H
#define DATA_STRUCTURES_LINKED_LIST_H

#include <memory>
#include <optional>

namespace data_structures {

/**
 * 单链表节点
 */
template<typename T>
struct Node {
    T data;
    std::shared_ptr<Node<T>> next;
    
    explicit Node(const T& value) : data(value), next(nullptr) {}
};

/**
 * 单链表类
 */
template<typename T>
class LinkedList {
public:
    LinkedList() : head_(nullptr), size_(0) {}
    
    // 在头部插入元素
    void pushFront(const T& value);
    
    // 在尾部插入元素
    void pushBack(const T& value);
    
    // 删除头部元素
    bool popFront();
    
    // 查找元素
    bool find(const T& value) const;
    
    // 获取大小
    size_t size() const { return size_; }
    
    // 是否为空
    bool empty() const { return head_ == nullptr; }
    
    // 获取头部元素
    std::optional<T> front() const;
    
    // 清空链表
    void clear();
    
private:
    std::shared_ptr<Node<T>> head_;
    size_t size_;
};

// 模板实现
template<typename T>
void LinkedList<T>::pushFront(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    newNode->next = head_;
    head_ = newNode;
    size_++;
}

template<typename T>
void LinkedList<T>::pushBack(const T& value) {
    auto newNode = std::make_shared<Node<T>>(value);
    
    if (!head_) {
        head_ = newNode;
    } else {
        auto current = head_;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
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
    size_ = 0;
}

} // namespace data_structures

#endif // DATA_STRUCTURES_LINKED_LIST_H
