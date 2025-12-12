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

// 测试插值查找 - 找到目标值
TEST(InterpolationSearchTest, FindTarget) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    EXPECT_EQ(algorithms::interpolationSearch(arr, 1), 0);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 7), 3);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 13), 6);
}

// 测试插值查找 - 未找到目标值
TEST(InterpolationSearchTest, TargetNotFound) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    EXPECT_EQ(algorithms::interpolationSearch(arr, 0), -1);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 4), -1);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 15), -1);
}

// 测试插值查找 - 空数组
TEST(InterpolationSearchTest, EmptyArray) {
    std::vector<int> arr;
    EXPECT_EQ(algorithms::interpolationSearch(arr, 5), -1);
}

// 测试插值查找 - 单元素数组
TEST(InterpolationSearchTest, SingleElement) {
    std::vector<int> arr = {42};

    EXPECT_EQ(algorithms::interpolationSearch(arr, 42), 0);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 10), -1);
}

// 测试插值查找 - 均匀分布数组
TEST(InterpolationSearchTest, UniformDistribution) {
    std::vector<int> arr = {10, 20, 30, 40, 50, 60, 70, 80, 90, 100};

    EXPECT_EQ(algorithms::interpolationSearch(arr, 10), 0);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 50), 4);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 100), 9);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 25), -1); // 不存在的元素
}

// 测试插值查找 - 所有元素相等
TEST(InterpolationSearchTest, AllElementsEqual) {
    std::vector<int> arr = {5, 5, 5, 5, 5};

    // 查找存在的元素
    int result = algorithms::interpolationSearch(arr, 5);
    EXPECT_GE(result, 0);
    EXPECT_LT(result, 5);
    EXPECT_EQ(arr[result], 5);

    // 查找不存在的元素
    EXPECT_EQ(algorithms::interpolationSearch(arr, 3), -1);
    EXPECT_EQ(algorithms::interpolationSearch(arr, 7), -1);
}

// 测试斐波那契查找 - 找到目标值
TEST(FibonacciSearchTest, FindTarget) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    EXPECT_EQ(algorithms::fibonacciSearch(arr, 1), 0);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 7), 3);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 13), 6);
}

// 测试斐波那契查找 - 未找到目标值
TEST(FibonacciSearchTest, TargetNotFound) {
    std::vector<int> arr = {1, 3, 5, 7, 9, 11, 13};

    EXPECT_EQ(algorithms::fibonacciSearch(arr, 0), -1);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 4), -1);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 15), -1);
}

// 测试斐波那契查找 - 空数组
TEST(FibonacciSearchTest, EmptyArray) {
    std::vector<int> arr;
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 5), -1);
}

// 测试斐波那契查找 - 单元素数组
TEST(FibonacciSearchTest, SingleElement) {
    std::vector<int> arr = {42};

    EXPECT_EQ(algorithms::fibonacciSearch(arr, 42), 0);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 10), -1);
}

// 测试斐波那契查找 - 大数组
TEST(FibonacciSearchTest, LargeArray) {
    std::vector<int> arr(50);
    for (int i = 0; i < 50; i++) {
        arr[i] = i * 2; // 0, 2, 4, 6, ..., 98
    }

    EXPECT_EQ(algorithms::fibonacciSearch(arr, 0), 0);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 50), 25);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 98), 49);
    EXPECT_EQ(algorithms::fibonacciSearch(arr, 1), -1); // 不存在的元素
}

// 测试斐波那契查找 - 边界情况（确保不会越界）
TEST(FibonacciSearchTest, BoundaryCases) {
    // 测试只有一个元素的数组
    std::vector<int> single = {42};
    EXPECT_EQ(algorithms::fibonacciSearch(single, 42), 0);
    EXPECT_EQ(algorithms::fibonacciSearch(single, 0), -1);

    // 测试两个元素的数组
    std::vector<int> two = {10, 20};
    EXPECT_EQ(algorithms::fibonacciSearch(two, 10), 0);
    EXPECT_EQ(algorithms::fibonacciSearch(two, 20), 1);
    EXPECT_EQ(algorithms::fibonacciSearch(two, 15), -1);

    // 测试查找不存在的较大值（可能触发边界检查）
    std::vector<int> small = {1, 2, 3};
    EXPECT_EQ(algorithms::fibonacciSearch(small, 100), -1);
    EXPECT_EQ(algorithms::fibonacciSearch(small, -1), -1);
}
