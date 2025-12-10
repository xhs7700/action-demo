#ifndef DATA_STRUCTURES_STACK_QUEUE_H
#define DATA_STRUCTURES_STACK_QUEUE_H

#include <vector>
#include <optional>
#include <stdexcept>

namespace data_structures {

/**
 * 栈（后进先出）
 */
template<typename T>
class Stack {
public:
    Stack() = default;
    
    // 压栈
    void push(const T& value);
    
    // 弹栈
    bool pop();
    
    // 获取栈顶元素
    std::optional<T> top() const;
    
    // 获取大小
    size_t size() const { return data_.size(); }
    
    // 是否为空
    bool empty() const { return data_.empty(); }
    
    // 清空栈
    void clear() { data_.clear(); }
    
private:
    std::vector<T> data_;
};

/**
 * 队列（先进先出）
 */
template<typename T>
class Queue {
public:
    Queue() = default;
    
    // 入队
    void enqueue(const T& value);
    
    // 出队
    bool dequeue();
    
    // 获取队首元素
    std::optional<T> front() const;
    
    // 获取队尾元素
    std::optional<T> back() const;
    
    // 获取大小
    size_t size() const { return data_.size(); }
    
    // 是否为空
    bool empty() const { return data_.empty(); }
    
    // 清空队列
    void clear() { data_.clear(); }
    
private:
    std::vector<T> data_;
};

// Stack 模板实现
template<typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template<typename T>
bool Stack<T>::pop() {
    if (data_.empty()) {
        return false;
    }
    data_.pop_back();
    return true;
}

template<typename T>
std::optional<T> Stack<T>::top() const {
    if (data_.empty()) {
        return std::nullopt;
    }
    return data_.back();
}

// Queue 模板实现
template<typename T>
void Queue<T>::enqueue(const T& value) {
    data_.push_back(value);
}

template<typename T>
bool Queue<T>::dequeue() {
    if (data_.empty()) {
        return false;
    }
    data_.erase(data_.begin());
    return true;
}

template<typename T>
std::optional<T> Queue<T>::front() const {
    if (data_.empty()) {
        return std::nullopt;
    }
    return data_.front();
}

template<typename T>
std::optional<T> Queue<T>::back() const {
    if (data_.empty()) {
        return std::nullopt;
    }
    return data_.back();
}

} // namespace data_structures

#endif // DATA_STRUCTURES_STACK_QUEUE_H
