#ifndef DATA_STRUCTURES_SKIP_LIST_H
#define DATA_STRUCTURES_SKIP_LIST_H

#include <memory>
#include <optional>
#include <vector>
#include <random>
#include <cmath>

namespace data_structures {

/**
 * Skip List Node
 */
template<typename T>
struct SkipNode {
    T data;
    std::vector<std::shared_ptr<SkipNode<T>>> forward;
    
    SkipNode(const T& value, int level) 
        : data(value), forward(level + 1, nullptr) {}
};

/**
 * Skip List - Probabilistic data structure
 */
template<typename T>
class SkipList {
public:
    static constexpr int MAX_LEVEL = 16;
    static constexpr float PROBABILITY = 0.5f;
    
    SkipList();
    
    // Insert element
    void insert(const T& value);
    
    // Remove element
    bool remove(const T& value);
    
    // Search for element
    bool search(const T& value) const;
    
    // Get size
    size_t size() const { return size_; }
    
    // Check if empty
    bool empty() const { return size_ == 0; }
    
    // Clear list
    void clear();
    
    // Get current maximum level
    int maxLevel() const { return currentMaxLevel_; }
    
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
    // Create header node with maximum possible level
    header_ = std::make_shared<SkipNode<T>>(T(), MAX_LEVEL);
    
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
        while (current->forward[i] && current->forward[i]->data < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Check if element already exists
    if (current && current->data == value) {
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
        while (current->forward[i] && current->forward[i]->data < value) {
            current = current->forward[i];
        }
        update[i] = current;
    }
    
    current = current->forward[0];
    
    // Check if element exists
    if (!current || current->data != value) {
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
        while (current->forward[i] && current->forward[i]->data < value) {
            current = current->forward[i];
        }
    }
    
    // Move to next node at level 0
    current = current->forward[0];
    
    // Check if we found the value
    return current && current->data == value;
}

template<typename T>
void SkipList<T>::clear() {
    // Clear all forward pointers from header
    for (int i = 0; i <= MAX_LEVEL; i++) {
        header_->forward[i] = nullptr;
    }
    
    currentMaxLevel_ = 0;
    size_ = 0;
}

} // namespace data_structures

#endif // DATA_STRUCTURES_SKIP_LIST_H
