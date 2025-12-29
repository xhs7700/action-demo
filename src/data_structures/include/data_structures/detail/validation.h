#ifndef DATA_STRUCTURES_DETAIL_VALIDATION_H
#define DATA_STRUCTURES_DETAIL_VALIDATION_H

#include "data_structures/exceptions.h"
#include <cstddef>
#include <string>

namespace data_structures {
namespace detail {

/**
 * @brief 检查容器是否非空
 * 
 * @param is_empty 容器是否为空
 * @param container_name 容器类型名称
 * @param operation_name 操作名称
 * @throws EmptyContainerException 如果容器为空
 * 
 * @example
 * detail::checkNotEmpty(stack.empty(), "Stack<int>", "pop");
 */
inline void checkNotEmpty(bool is_empty, const char* container_name, const char* operation_name) {
    if (is_empty) {
        throw EmptyContainerException(container_name, operation_name);
    }
}

/**
 * @brief 检查索引是否在有效范围内
 * 
 * @param index 要检查的索引
 * @param size 容器的大小
 * @param container_name 容器类型名称
 * @throws OutOfRangeException 如果索引越界
 * 
 * @example
 * detail::checkIndexInRange(5, list.size(), "LinkedList<int>");
 */
inline void checkIndexInRange(size_t index, size_t size, const char* container_name) {
    if (index >= size) {
        throw OutOfRangeException(container_name, index, size);
    }
}

/**
 * @brief 检查指针是否非空
 * 
 * @tparam T 指针类型
 * @param ptr 要检查的指针
 * @param container_name 容器类型名称
 * @param message 错误消息
 * @throws InvalidOperationException 如果指针为空
 * 
 * @example
 * detail::requireNonNull(node, "LinkedList<int>", "Node pointer is null");
 */
template<typename T>
inline void requireNonNull(T* ptr, const char* container_name, const char* message) {
    if (ptr == nullptr) {
        throw InvalidOperationException(container_name, message, "Pointer must not be null");
    }
}

/**
 * @brief 检查条件是否满足
 * 
 * @param condition 要检查的条件
 * @param container_name 容器类型名称
 * @param operation_desc 操作描述
 * @param constraint_desc 约束描述
 * @throws InvalidOperationException 如果条件不满足
 * 
 * @example
 * detail::require(node->left != nullptr, "AVLTree", "Rotate left", "Left child must exist");
 */
inline void require(bool condition, const char* container_name, 
                   const char* operation_desc, const char* constraint_desc = "") {
    if (!condition) {
        throw InvalidOperationException(container_name, operation_desc, constraint_desc);
    }
}

/**
 * @brief 检查大小是否有效（非零）
 * 
 * @param size 要检查的大小
 * @param container_name 容器类型名称
 * @param operation_name 操作名称
 * @throws EmptyContainerException 如果大小为0
 * 
 * @example
 * detail::checkValidSize(heap.size(), "Heap<int>", "extractTop");
 */
inline void checkValidSize(size_t size, const char* container_name, const char* operation_name) {
    checkNotEmpty(size == 0, container_name, operation_name);
}

/**
 * @brief 检查分配大小是否合理
 * 
 * @param requested_size 请求的大小
 * @param max_size 最大允许大小
 * @param container_name 容器类型名称
 * @throws AllocationException 如果请求大小超过最大限制
 * 
 * @example
 * detail::checkAllocationSize(new_capacity, SIZE_MAX / sizeof(T), "Vector<T>");
 */
inline void checkAllocationSize(size_t requested_size, size_t max_size, const char* container_name) {
    if (requested_size > max_size) {
        throw AllocationException(container_name, requested_size, "elements");
    }
}

} // namespace detail
} // namespace data_structures

#endif // DATA_STRUCTURES_DETAIL_VALIDATION_H
