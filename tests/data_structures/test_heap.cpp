#include <gtest/gtest.h>
#include "data_structures/heap.h"
#include <string>

// Test Heap - Basic Min-Heap Operations
TEST(HeapTest, BasicMinHeapOperations) {
    data_structures::Heap<int> minHeap;
    
    EXPECT_TRUE(minHeap.empty());
    EXPECT_EQ(minHeap.size(), 0);
    
    minHeap.insert(10);
    EXPECT_FALSE(minHeap.empty());
    EXPECT_EQ(minHeap.size(), 1);
    
    auto top = minHeap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 10);
}

// Test Heap - Min-Heap Property
TEST(HeapTest, MinHeapProperty) {
    data_structures::Heap<int> minHeap;
    
    minHeap.insert(5);
    minHeap.insert(3);
    minHeap.insert(7);
    minHeap.insert(1);
    minHeap.insert(9);
    
    EXPECT_EQ(minHeap.size(), 5);
    
    auto top = minHeap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 1); // Minimum element should be at top
}

// Test Heap - Max-Heap Operations
TEST(HeapTest, MaxHeapOperations) {
    data_structures::Heap<int, std::greater<int>> maxHeap;
    
    maxHeap.insert(5);
    maxHeap.insert(3);
    maxHeap.insert(7);
    maxHeap.insert(1);
    maxHeap.insert(9);
    
    EXPECT_EQ(maxHeap.size(), 5);
    
    auto top = maxHeap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 9); // Maximum element should be at top
}

// Test Heap - Extract Top (Min-Heap)
TEST(HeapTest, ExtractTopMinHeap) {
    data_structures::Heap<int> minHeap;
    
    minHeap.insert(10);
    minHeap.insert(5);
    minHeap.insert(20);
    minHeap.insert(1);
    
    auto extracted = minHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 1);
    EXPECT_EQ(minHeap.size(), 3);
    
    extracted = minHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 5);
    EXPECT_EQ(minHeap.size(), 2);
    
    extracted = minHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 10);
    
    extracted = minHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 20);
    
    EXPECT_TRUE(minHeap.empty());
}

// Test Heap - Extract Top (Max-Heap)
TEST(HeapTest, ExtractTopMaxHeap) {
    data_structures::Heap<int, std::greater<int>> maxHeap;
    
    maxHeap.insert(10);
    maxHeap.insert(5);
    maxHeap.insert(20);
    maxHeap.insert(1);
    
    auto extracted = maxHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 20);
    
    extracted = maxHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 10);
    
    extracted = maxHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 5);
    
    extracted = maxHeap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 1);
    
    EXPECT_TRUE(maxHeap.empty());
}

// Test Heap - Build from Collection
TEST(HeapTest, BuildHeapFromCollection) {
    std::vector<int> values = {9, 5, 7, 1, 3, 8, 2};
    data_structures::Heap<int> minHeap(values);
    
    EXPECT_EQ(minHeap.size(), 7);
    
    auto top = minHeap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 1);
    
    // Extract all and verify they come out in sorted order
    std::vector<int> extracted;
    while (!minHeap.empty()) {
        auto val = minHeap.extractTop();
        ASSERT_TRUE(val.has_value());
        extracted.push_back(val.value());
    }
    
    EXPECT_EQ(extracted.size(), 7);
    for (size_t i = 1; i < extracted.size(); i++) {
        EXPECT_LE(extracted[i-1], extracted[i]);
    }
}

// Test Heap - Empty Heap Operations
TEST(HeapTest, EmptyHeapOperations) {
    data_structures::Heap<int> heap;
    
    EXPECT_FALSE(heap.top().has_value());
    EXPECT_FALSE(heap.extractTop().has_value());
    EXPECT_TRUE(heap.empty());
}

// Test Heap - Clear
TEST(HeapTest, Clear) {
    data_structures::Heap<int> heap;
    
    heap.insert(1);
    heap.insert(2);
    heap.insert(3);
    
    EXPECT_EQ(heap.size(), 3);
    
    heap.clear();
    
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
    EXPECT_FALSE(heap.top().has_value());
}

// Test Heap - Single Element
TEST(HeapTest, SingleElement) {
    data_structures::Heap<int> heap;
    
    heap.insert(42);
    
    EXPECT_EQ(heap.size(), 1);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 42);
    
    auto extracted = heap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 42);
    
    EXPECT_TRUE(heap.empty());
}

// Test Heap - Duplicate Values
TEST(HeapTest, DuplicateValues) {
    data_structures::Heap<int> heap;
    
    heap.insert(5);
    heap.insert(5);
    heap.insert(5);
    heap.insert(3);
    heap.insert(3);
    
    EXPECT_EQ(heap.size(), 5);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 3);
    
    heap.extractTop();
    top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 3);
}

// Test Heap - String Type
TEST(HeapTest, StringType) {
    data_structures::Heap<std::string> heap;
    
    heap.insert("dog");
    heap.insert("cat");
    heap.insert("bird");
    heap.insert("zebra");
    heap.insert("ant");
    
    EXPECT_EQ(heap.size(), 5);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "ant");
    
    std::vector<std::string> extracted;
    while (!heap.empty()) {
        auto val = heap.extractTop();
        ASSERT_TRUE(val.has_value());
        extracted.push_back(val.value());
    }
    
    // Should be in alphabetical order
    EXPECT_EQ(extracted[0], "ant");
    EXPECT_EQ(extracted[1], "bird");
    EXPECT_EQ(extracted[2], "cat");
    EXPECT_EQ(extracted[3], "dog");
    EXPECT_EQ(extracted[4], "zebra");
}

// Test Heap - Large Dataset
TEST(HeapTest, LargeDataset) {
    data_structures::Heap<int> heap;
    
    // Insert 100 elements
    for (int i = 100; i > 0; i--) {
        heap.insert(i);
    }
    
    EXPECT_EQ(heap.size(), 100);
    
    // Top should be 1
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 1);
    
    // Extract all and verify order
    int prev = 0;
    while (!heap.empty()) {
        auto val = heap.extractTop();
        ASSERT_TRUE(val.has_value());
        EXPECT_GT(val.value(), prev);
        prev = val.value();
    }
}
