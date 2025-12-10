#include <gtest/gtest.h>
#include "algorithms/search.h"
#include <vector>

// 测试二分查找 - 找到目标值
TEST(BinarySearchTest, FindTarget) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    
    EXPECT_EQ(algorithms::binarySearch(arr, 1), 0);
    EXPECT_EQ(algorithms::binarySearch(arr, 7), 3);
    EXPECT_EQ(algorithms::binarySearch(arr, 13), 6);
}

// 测试二分查找 - 未找到目标值
TEST(BinarySearchTest, TargetNotFound) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};
    
    EXPECT_EQ(algorithms::binarySearch(arr, 0), -1);
    EXPECT_EQ(algorithms::binarySearch(arr, 4), -1);
    EXPECT_EQ(algorithms::binarySearch(arr, 15), -1);
}

// 测试二分查找 - 空数组
TEST(BinarySearchTest, EmptyArray) {
    std::vector<int> arr;
    EXPECT_EQ(algorithms::binarySearch(arr, 5), -1);
}

// 测试二分查找 - 单元素数组
TEST(BinarySearchTest, SingleElement) {
    std::vector<int> arr = {42};
    
    EXPECT_EQ(algorithms::binarySearch(arr, 42), 0);
    EXPECT_EQ(algorithms::binarySearch(arr, 10), -1);
}

// 测试二分查找 - 重复元素
TEST(BinarySearchTest, DuplicateElements) {
    std::vector<int> arr = {1, 2, 2, 2, 3, 4, 5};
    
    int result = algorithms::binarySearch(arr, 2);
    EXPECT_GE(result, 1);
    EXPECT_LE(result, 3);
    EXPECT_EQ(arr[result], 2);
}

// 测试线性查找 - 找到目标值
TEST(LinearSearchTest, FindTarget) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    EXPECT_EQ(algorithms::linearSearch(arr, 64), 0);
    EXPECT_EQ(algorithms::linearSearch(arr, 12), 3);
    EXPECT_EQ(algorithms::linearSearch(arr, 90), 6);
}

// 测试线性查找 - 未找到目标值
TEST(LinearSearchTest, TargetNotFound) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    
    EXPECT_EQ(algorithms::linearSearch(arr, 100), -1);
    EXPECT_EQ(algorithms::linearSearch(arr, 0), -1);
}

// 测试线性查找 - 空数组
TEST(LinearSearchTest, EmptyArray) {
    std::vector<int> arr;
    EXPECT_EQ(algorithms::linearSearch(arr, 5), -1);
}

// 测试线性查找 - 单元素数组
TEST(LinearSearchTest, SingleElement) {
    std::vector<int> arr = {42};
    
    EXPECT_EQ(algorithms::linearSearch(arr, 42), 0);
    EXPECT_EQ(algorithms::linearSearch(arr, 10), -1);
}

// 测试线性查找 - 重复元素（返回第一个）
TEST(LinearSearchTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2};
    
    EXPECT_EQ(algorithms::linearSearch(arr, 1), 1); // 第一个出现的位置
}

// 测试线性查找 - 负数
TEST(LinearSearchTest, NegativeNumbers) {
    std::vector<int> arr = {-5, 3, -2, 8, -1, 0, 4};
    
    EXPECT_EQ(algorithms::linearSearch(arr, -5), 0);
    EXPECT_EQ(algorithms::linearSearch(arr, -2), 2);
    EXPECT_EQ(algorithms::linearSearch(arr, 0), 5);
}

// 测试线性查找 - 未排序数组
TEST(LinearSearchTest, UnsortedArray) {
    std::vector<int> arr = {9, 2, 5, 1, 7, 3, 8};
    
    EXPECT_EQ(algorithms::linearSearch(arr, 5), 2);
    EXPECT_EQ(algorithms::linearSearch(arr, 1), 3);
    EXPECT_EQ(algorithms::linearSearch(arr, 8), 6);
}
