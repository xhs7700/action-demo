#ifndef DATA_STRUCTURES_DETAIL_CONTAINER_BASE_H
#define DATA_STRUCTURES_DETAIL_CONTAINER_BASE_H

#include <cstddef>

namespace data_structures {
namespace detail {

/**
 * @brief 容器基类，提供通用接口
 * 
 * 为所有数据结构容器提供统一的基础接口，包括大小查询、空状态检查等。
 * 采用非虚函数设计（CRTP可选），避免虚函数开销。
 * 
 * @note 这是一个轻量级基类，不引入虚函数表开销
 */
class ContainerBase {
public:
    /**
     * @brief 默认构造函数
     */
    ContainerBase() noexcept : size_(0) {}
    
    /**
     * @brief 带初始大小的构造函数
     * @param initial_size 初始大小
     */
    explicit ContainerBase(size_t initial_size) noexcept : size_(initial_size) {}
    
    /**
     * @brief 获取容器中元素个数
     * @return 容器中元素的数量
     * @note 时间复杂度: O(1)
     */
    size_t size() const noexcept {
        return size_;
    }
    
    /**
     * @brief 检查容器是否为空
     * @return 容器为空返回true，否则返回false
     * @note 时间复杂度: O(1)
     */
    bool empty() const noexcept {
        return size_ == 0;
    }
    
    /**
     * @brief 析构函数
     */
    ~ContainerBase() = default;

protected:
    size_t size_;  ///< 容器元素个数
    
    /**
     * @brief 增加元素计数
     */
    void incrementSize() noexcept {
        ++size_;
    }
    
    /**
     * @brief 减少元素计数
     */
    void decrementSize() noexcept {
        if (size_ > 0) {
            --size_;
        }
    }
    
    /**
     * @brief 设置元素计数
     * @param new_size 新的大小
     */
    void setSize(size_t new_size) noexcept {
        size_ = new_size;
    }
    
    /**
     * @brief 重置元素计数为0
     */
    void resetSize() noexcept {
        size_ = 0;
    }
};

} // namespace detail
} // namespace data_structures

#endif // DATA_STRUCTURES_DETAIL_CONTAINER_BASE_H
