#include <gtest/gtest.h>
#include "data_structures/heap.h"
#include <string>
#include <climits>

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

// ========== 新增：移动语义测试 ==========

// 测试insert移动语义
TEST(HeapTest, InsertMoveSemantics) {
    data_structures::Heap<std::string> heap;
    
    std::string str1 = "apple";
    std::string str2 = "banana";
    std::string str3 = "cherry";
    
    heap.insert(std::move(str1));
    heap.insert(std::move(str2));
    heap.insert(std::move(str3));
    
    EXPECT_EQ(heap.size(), 3);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "apple");
}

// ========== 新增：堆性质验证测试 ==========

// 辅助函数：验证MinHeap性质（父节点 <= 子节点）
template<typename T>
bool verifyMinHeapProperty(const std::vector<T>& heap_data) {
    for (size_t i = 0; i < heap_data.size(); i++) {
        size_t left = 2 * i + 1;
        size_t right = 2 * i + 2;
        
        if (left < heap_data.size() && heap_data[i] > heap_data[left]) {
            return false;
        }
        if (right < heap_data.size() && heap_data[i] > heap_data[right]) {
            return false;
        }
    }
    return true;
}

// 测试MinHeap性质验证
TEST(HeapTest, VerifyMinHeapProperty) {
    data_structures::Heap<int> minHeap;
    
    std::vector<int> values = {15, 10, 20, 8, 12, 25, 30, 3, 9};
    for (int val : values) {
        minHeap.insert(val);
    }
    
    // 通过extractTop验证堆性质（每次提取的都应该是当前最小值）
    int prev = INT_MIN;
    while (!minHeap.empty()) {
        auto current = minHeap.extractTop();
        ASSERT_TRUE(current.has_value());
        EXPECT_GE(current.value(), prev);
        prev = current.value();
    }
}

// 测试MaxHeap性质验证
TEST(HeapTest, VerifyMaxHeapProperty) {
    data_structures::Heap<int, std::greater<int>> maxHeap;
    
    std::vector<int> values = {15, 10, 20, 8, 12, 25, 30, 3, 9};
    for (int val : values) {
        maxHeap.insert(val);
    }
    
    // 每次提取的都应该是当前最大值
    int prev = INT_MAX;
    while (!maxHeap.empty()) {
        auto current = maxHeap.extractTop();
        ASSERT_TRUE(current.has_value());
        EXPECT_LE(current.value(), prev);
        prev = current.value();
    }
}

// 测试插入后堆性质保持
TEST(HeapTest, HeapPropertyAfterInsert) {
    data_structures::Heap<int> heap;
    
    heap.insert(50);
    heap.insert(30);
    heap.insert(70);
    heap.insert(10);
    heap.insert(40);
    heap.insert(60);
    heap.insert(80);
    
    // 验证top始终是最小值
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 10);
    
    heap.insert(5);  // 插入更小的值
    top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 5);
}

// 测试extract后堆性质保持
TEST(HeapTest, HeapPropertyAfterExtract) {
    data_structures::Heap<int> heap;
    
    std::vector<int> values = {20, 15, 30, 10, 18, 25, 35};
    for (int val : values) {
        heap.insert(val);
    }
    
    // Extract最小值后，新的top仍应该是剩余元素中的最小值
    heap.extractTop();  // 移除10
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 15);
    
    heap.extractTop();  // 移除15
    top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 18);
}

// ========== 新增：buildHeap正确性测试 ==========

// 测试buildHeap后堆性质正确
TEST(HeapTest, BuildHeapCorrectness) {
    std::vector<int> values = {9, 5, 7, 1, 3, 8, 2, 6, 4};
    data_structures::Heap<int> heap(values);
    
    EXPECT_EQ(heap.size(), values.size());
    
    // 验证top是最小值
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 1);
    
    // 提取所有元素，验证有序性
    std::vector<int> sorted;
    while (!heap.empty()) {
        auto val = heap.extractTop();
        ASSERT_TRUE(val.has_value());
        sorted.push_back(val.value());
    }
    
    // 验证是升序
    for (size_t i = 1; i < sorted.size(); i++) {
        EXPECT_LE(sorted[i-1], sorted[i]);
    }
}

// 测试大规模数据buildHeap
TEST(HeapTest, LargeScaleBuildHeap) {
    std::vector<int> values(1000);
    for (int i = 0; i < 1000; i++) {
        values[i] = 1000 - i;  // 逆序
    }
    
    data_structures::Heap<int> heap(values);
    
    EXPECT_EQ(heap.size(), 1000);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 1);
    
    // 验证前10个提取的元素
    for (int i = 1; i <= 10; i++) {
        auto val = heap.extractTop();
        ASSERT_TRUE(val.has_value());
        EXPECT_EQ(val.value(), i);
    }
}

// ========== 新增：边界测试 ==========

// 测试空堆extract
TEST(HeapTest, EmptyHeapExtract) {
    data_structures::Heap<int> heap;
    
    auto result = heap.extractTop();
    EXPECT_FALSE(result.has_value());
    
    EXPECT_TRUE(heap.empty());
    EXPECT_EQ(heap.size(), 0);
}

// 测试单元素堆所有操作
TEST(HeapTest, SingleElementHeapAllOperations) {
    data_structures::Heap<int> heap;
    
    heap.insert(100);
    
    EXPECT_EQ(heap.size(), 1);
    EXPECT_FALSE(heap.empty());
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 100);
    
    auto extracted = heap.extractTop();
    ASSERT_TRUE(extracted.has_value());
    EXPECT_EQ(extracted.value(), 100);
    
    EXPECT_TRUE(heap.empty());
    EXPECT_FALSE(heap.top().has_value());
}

// 测试重复元素堆
TEST(HeapTest, AllDuplicateElements) {
    data_structures::Heap<int> heap;
    
    for (int i = 0; i < 10; i++) {
        heap.insert(42);
    }
    
    EXPECT_EQ(heap.size(), 10);
    
    // 所有元素都应该是42
    for (int i = 0; i < 10; i++) {
        auto val = heap.extractTop();
        ASSERT_TRUE(val.has_value());
        EXPECT_EQ(val.value(), 42);
    }
    
    EXPECT_TRUE(heap.empty());
}

// 测试极值元素
TEST(HeapTest, ExtremeValues) {
    data_structures::Heap<int> heap;
    
    heap.insert(INT_MAX);
    heap.insert(INT_MIN);
    heap.insert(0);
    heap.insert(-1000);
    heap.insert(1000);
    
    EXPECT_EQ(heap.size(), 5);
    
    auto top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), INT_MIN);
    
    heap.extractTop();
    top = heap.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), -1000);
}