#ifndef DATA_STRUCTURES_EXCEPTIONS_H
#define DATA_STRUCTURES_EXCEPTIONS_H

#include <exception>
#include <string>
#include <sstream>

namespace data_structures {

/**
 * @brief 数据结构异常基类
 * 
 * 所有数据结构相关异常的基类，继承自std::exception。
 * 提供统一的异常消息格式和数据结构名称记录。
 * 
 * @note 这是一个抽象基类，不应直接抛出此异常
 */
class DataStructureException : public std::exception {
public:
    /**
     * @brief 构造数据结构异常
     * @param message 错误消息
     * @param structureName 数据结构名称（可选）
     */
    explicit DataStructureException(const std::string& message, 
                                   const std::string& structureName = "")
        : message_(message), structureName_(structureName) {
        formatMessage();
    }

    /**
     * @brief 获取异常描述信息
     * @return 格式化后的异常消息
     */
    const char* what() const noexcept override {
        return formattedMessage_.c_str();
    }

    /**
     * @brief 获取数据结构名称
     * @return 数据结构名称
     */
    const std::string& getStructureName() const noexcept {
        return structureName_;
    }

    virtual ~DataStructureException() = default;

protected:
    std::string message_;           ///< 原始错误消息
    std::string structureName_;     ///< 数据结构名称
    std::string formattedMessage_;  ///< 格式化后的完整消息

    /**
     * @brief 格式化异常消息
     */
    void formatMessage() {
        std::ostringstream oss;
        if (!structureName_.empty()) {
            oss << "[" << structureName_ << "] ";
        }
        oss << message_;
        formattedMessage_ = oss.str();
    }
};

/**
 * @brief 空容器异常
 * 
 * 当对空容器执行非法操作时抛出此异常。
 * 例如：对空栈调用top()、对空队列调用dequeue()等。
 * 
 * @example
 * Stack<int> stack;
 * try {
 *     stack.topChecked();  // 抛出EmptyContainerException
 * } catch (const EmptyContainerException& e) {
 *     std::cerr << e.what() << std::endl;
 * }
 */
class EmptyContainerException : public DataStructureException {
public:
    /**
     * @brief 构造空容器异常
     * @param containerName 容器类型名称
     * @param operationName 操作名称
     */
    EmptyContainerException(const std::string& containerName, 
                           const std::string& operationName)
        : DataStructureException(
            "Cannot perform operation '" + operationName + 
            "' on empty container", 
            containerName),
          operationName_(operationName) {}

    /**
     * @brief 获取操作名称
     * @return 尝试执行的操作名称
     */
    const std::string& getOperationName() const noexcept {
        return operationName_;
    }

private:
    std::string operationName_;  ///< 操作名称
};

/**
 * @brief 索引越界异常
 * 
 * 当访问的索引超出有效范围时抛出此异常。
 * 
 * @example
 * // 假设有at()方法
 * LinkedList<int> list;
 * list.pushBack(1);
 * try {
 *     list.at(5);  // 抛出OutOfRangeException
 * } catch (const OutOfRangeException& e) {
 *     std::cerr << "Index: " << e.getIndex() << std::endl;
 * }
 */
class OutOfRangeException : public DataStructureException {
public:
    /**
     * @brief 构造索引越界异常
     * @param containerName 容器类型名称
     * @param index 请求的索引
     * @param validSize 容器的有效大小
     */
    OutOfRangeException(const std::string& containerName,
                       size_t index,
                       size_t validSize)
        : DataStructureException(
            "Index " + std::to_string(index) + 
            " out of range [0, " + std::to_string(validSize) + ")",
            containerName),
          index_(index),
          validSize_(validSize) {}

    /**
     * @brief 获取请求的索引
     * @return 越界的索引值
     */
    size_t getIndex() const noexcept {
        return index_;
    }

    /**
     * @brief 获取有效范围
     * @return 容器的有效大小
     */
    size_t getValidSize() const noexcept {
        return validSize_;
    }

private:
    size_t index_;      ///< 请求的索引
    size_t validSize_;  ///< 有效大小
};

/**
 * @brief 非法操作异常
 * 
 * 当执行的操作违反数据结构的约束或前置条件时抛出此异常。
 * 
 * @example
 * // 假设某个操作需要容器处于特定状态
 * if (!isValid()) {
 *     throw InvalidOperationException(
 *         "MyContainer", 
 *         "operation requires valid state",
 *         "Container must be initialized"
 *     );
 * }
 */
class InvalidOperationException : public DataStructureException {
public:
    /**
     * @brief 构造非法操作异常
     * @param containerName 容器类型名称
     * @param operationDesc 操作描述
     * @param constraintDesc 违反的约束描述
     */
    InvalidOperationException(const std::string& containerName,
                             const std::string& operationDesc,
                             const std::string& constraintDesc = "")
        : DataStructureException(
            operationDesc + 
            (constraintDesc.empty() ? "" : " (Constraint: " + constraintDesc + ")"),
            containerName),
          constraintDesc_(constraintDesc) {}

    /**
     * @brief 获取约束描述
     * @return 违反的约束说明
     */
    const std::string& getConstraintDescription() const noexcept {
        return constraintDesc_;
    }

private:
    std::string constraintDesc_;  ///< 约束描述
};

/**
 * @brief 内存分配异常
 * 
 * 当内存分配失败时抛出此异常。
 * 
 * @note 在实践中，现代C++通常依赖std::bad_alloc，
 *       此异常类主要用于提供更多上下文信息
 */
class AllocationException : public DataStructureException {
public:
    /**
     * @brief 构造内存分配异常
     * @param containerName 容器类型名称
     * @param requestedSize 请求分配的大小（字节数或元素数）
     * @param sizeUnit 大小单位描述（如"bytes"或"elements"）
     */
    AllocationException(const std::string& containerName,
                       size_t requestedSize,
                       const std::string& sizeUnit = "bytes")
        : DataStructureException(
            "Failed to allocate " + std::to_string(requestedSize) + 
            " " + sizeUnit,
            containerName),
          requestedSize_(requestedSize) {}

    /**
     * @brief 获取请求的大小
     * @return 请求分配的大小
     */
    size_t getRequestedSize() const noexcept {
        return requestedSize_;
    }

private:
    size_t requestedSize_;  ///< 请求的大小
};

} // namespace data_structures

#endif // DATA_STRUCTURES_EXCEPTIONS_H
