#ifndef DATA_STRUCTURES_HEAP_H
#define DATA_STRUCTURES_HEAP_H

#include <vector>
#include <optional>
#include <functional>
#include <stdexcept>

namespace data_structures {

/**
 * Binary Heap (Min-Heap or Max-Heap)
 * Template-based implementation with configurable comparison
 */
template<typename T, typename Compare = std::less<T>>
class Heap {
public:
    // Constructor
    Heap() : size_(0) {}
    
    // Constructor with custom comparator
    explicit Heap(Compare comp) : comparator_(comp), size_(0) {}
    
    // Build heap from collection
    explicit Heap(const std::vector<T>& values);
    Heap(const std::vector<T>& values, Compare comp);
    
    // Insert element
    void insert(const T& value);
    
    // Extract top element
    std::optional<T> extractTop();
    
    // Peek top element without removal
    std::optional<T> top() const;
    
    // Get size
    size_t size() const { return size_; }
    
    // Check if empty
    bool empty() const { return size_ == 0; }
    
    // Clear heap
    void clear();
    
private:
    std::vector<T> data_;
    Compare comparator_;
    size_t size_;
    
    // Helper methods
    void heapifyUp(size_t index);
    void heapifyDown(size_t index);
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
void Heap<T, Compare>::clear() {
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
