#ifndef DATA_STRUCTURES_STACK_QUEUE_H
#define DATA_STRUCTURES_STACK_QUEUE_H

#include <vector>
#include <deque>
#include <optional>
#include <stdexcept>
#include <utility>

namespace data_structures {

/**
 * @brief 栈数据结构（后进先出，LIFO）
 * 
 * 基于std::vector实现的泛型栈，支持高效的压栈和弹栈操作。
 * 栈遵循后进先出原则，只能在栈顶进行插入和删除操作。
 * 
 * @tparam T 栈中存储的元素类型
 * 
 * @note 时间复杂度: push和pop均为O(1)（摊销）
 * @note 空间复杂度: O(n)，其中n是元素数量
 * 
 * @example
 * Stack<int> stack;
 * stack.push(1);
 * stack.push(2);
 * auto value = stack.top();  // 返回 std::optional<int>(2)
 * stack.pop();               // 弹出 2
 */
template<typename T>
class Stack {
public:
    Stack() = default;
    
    // 五法则: 使用默认实现（内部vector自动处理）
    Stack(const Stack&) = default;                    ///< 拷贝构造函数
    Stack(Stack&&) noexcept = default;                ///< 移动构造函数
    Stack& operator=(const Stack&) = default;         ///< 拷贝赋值运算符
    Stack& operator=(Stack&&) noexcept = default;     ///< 移动赋值运算符
    ~Stack() = default;                               ///< 析构函数
    
    /**
     * @brief 压栈操作（左值版本）
     * @param value 要压入栈的元素（左值引用）
     * @note 时间复杂度: O(1)（摊销）
     */
    void push(const T& value);
    
    /**
     * @brief 压栈操作（右值版本）
     * @param value 要压入栈的元素（右值引用，支持移动语义）
     * @note 时间复杂度: O(1)（摊销）
     */
    void push(T&& value);
    
    /**
     * @brief 弹栈操作，移除栈顶元素
     * @return 成功返回true，栈为空时返回false
     * @note 时间复杂度: O(1)
     */
    bool pop();
    
    /**
     * @brief 获取栈顶元素（不移除）
     * @return std::optional<T>，包含栈顶元素；栈为空时返回std::nullopt
     * @note 时间复杂度: O(1)
     */
    std::optional<T> top() const;
    
    /**
     * @brief 获取栈中元素个数
     * @return 栈中元素的数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return data_.size(); }
    
    /**
     * @brief 检查栈是否为空
     * @return 栈为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return data_.empty(); }
    
    /**
     * @brief 清空栈中所有元素
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept { data_.clear(); }
    
private:
    std::vector<T> data_;  ///< 内部存储容器
};

/**
 * @brief 队列数据结构（先进先出，FIFO）
 * 
 * 基于std::deque实现的泛型队列，支持高效的入队和出队操作。
 * 队列遵循先进先出原则，在队尾插入元素，在队首删除元素。
 * 
 * @tparam T 队列中存储的元素类型
 * 
 * @note 时间复杂度: enqueue和dequeue均为O(1)
 * @note 空间复杂度: O(n)，其中n是元素数量
 * @note 实现细节: 使用std::deque替代std::vector，确保O(1)出队性能
 * 
 * @example
 * Queue<int> queue;
 * queue.enqueue(1);
 * queue.enqueue(2);
 * auto value = queue.front();  // 返回 std::optional<int>(1)
 * queue.dequeue();              // 移除 1
 */
template<typename T>
class Queue {
public:
    Queue() = default;
    
    // 五法则: 使用默认实现（内部deque自动处理）
    Queue(const Queue&) = default;                    ///< 拷贝构造函数
    Queue(Queue&&) noexcept = default;                ///< 移动构造函数
    Queue& operator=(const Queue&) = default;         ///< 拷贝赋值运算符
    Queue& operator=(Queue&&) noexcept = default;     ///< 移动赋值运算符
    ~Queue() = default;                               ///< 析构函数
    
    /**
     * @brief 入队操作（左值版本）
     * @param value 要加入队列的元素（左值引用）
     * @note 时间复杂度: O(1)
     */
    void enqueue(const T& value);
    
    /**
     * @brief 入队操作（右值版本）
     * @param value 要加入队列的元素（右值引用，支持移动语义）
     * @note 时间复杂度: O(1)
     */
    void enqueue(T&& value);
    
    /**
     * @brief 出队操作，移除队首元素
     * @return 成功返回true，队列为空时返回false
     * @note 时间复杂度: O(1)
     */
    bool dequeue();
    
    /**
     * @brief 获取队首元素（不移除）
     * @return std::optional<T>，包含队首元素；队列为空时返回std::nullopt
     * @note 时间复杂度: O(1)
     */
    std::optional<T> front() const;
    
    /**
     * @brief 获取队尾元素（不移除）
     * @return std::optional<T>，包含队尾元素；队列为空时返回std::nullopt
     * @note 时间复杂度: O(1)
     */
    std::optional<T> back() const;
    
    /**
     * @brief 获取队列中元素个数
     * @return 队列中元素的数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept { return data_.size(); }
    
    /**
     * @brief 检查队列是否为空
     * @return 队列为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept { return data_.empty(); }
    
    /**
     * @brief 清空队列中所有元素
     * @note 时间复杂度: O(n)
     */
    void clear() noexcept { data_.clear(); }
    
private:
    std::deque<T> data_;  ///< 内部存储容器，使用deque实现O(1)出队
};

// Stack 模板实现
template<typename T>
void Stack<T>::push(const T& value) {
    data_.push_back(value);
}

template<typename T>
void Stack<T>::push(T&& value) {
    data_.push_back(std::move(value));
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
void Queue<T>::enqueue(T&& value) {
    data_.push_back(std::move(value));
}

template<typename T>
bool Queue<T>::dequeue() {
    if (data_.empty()) {
        return false;
    }
    data_.pop_front();  // 使用deque的pop_front，O(1)复杂度
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