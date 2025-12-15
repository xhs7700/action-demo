#include <gtest/gtest.h>
#include "algorithms/sort.h"
#include <vector>
#include <algorithm>
#include <limits>
#include <random>

// 测试快速排序 - 基本功能
TEST(QuickSortTest, BasicFunctionality) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 空数组
TEST(QuickSortTest, EmptyArray) {
    std::vector<int> arr;
    algorithms::quickSort(arr);
    EXPECT_TRUE(arr.empty());
}

// 测试快速排序 - 单元素数组
TEST(QuickSortTest, SingleElement) {
    std::vector<int> arr = {42};
    algorithms::quickSort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// 测试快速排序 - 已排序数组
TEST(QuickSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 逆序数组
TEST(QuickSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 重复元素
TEST(QuickSortTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 负数
TEST(QuickSortTest, NegativeNumbers) {
    std::vector<int> arr = {-5, 3, -2, 8, -1, 0, 4};
    std::vector<int> expected = {-5, -2, -1, 0, 3, 4, 8};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 全部相同元素
TEST(QuickSortTest, AllSameElements) {
    std::vector<int> arr = {5, 5, 5, 5, 5};
    std::vector<int> expected = {5, 5, 5, 5, 5};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 大规模数据
TEST(QuickSortTest, LargeArray) {
    std::vector<int> arr(1000);
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(1, 10000);
    
    for (int i = 0; i < 1000; i++) {
        arr[i] = dis(gen);
    }
    
    auto expected = arr;
    std::sort(expected.begin(), expected.end());
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试快速排序 - 边界值（INT_MAX, INT_MIN）
TEST(QuickSortTest, BoundaryValues) {
    std::vector<int> arr = {std::numeric_limits<int>::max(), 0, std::numeric_limits<int>::min(), 100, -100};
    std::vector<int> expected = {std::numeric_limits<int>::min(), -100, 0, 100, std::numeric_limits<int>::max()};
    
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 基本功能
TEST(MergeSortTest, BasicFunctionality) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 空数组
TEST(MergeSortTest, EmptyArray) {
    std::vector<int> arr;
    algorithms::mergeSort(arr);
    EXPECT_TRUE(arr.empty());
}

// 测试归并排序 - 单元素数组
TEST(MergeSortTest, SingleElement) {
    std::vector<int> arr = {42};
    algorithms::mergeSort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// 测试归并排序 - 已排序数组
TEST(MergeSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 逆序数组
TEST(MergeSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 重复元素
TEST(MergeSortTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 大数组
TEST(MergeSortTest, LargeArray) {
    std::vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 - i;
    }

    algorithms::mergeSort(arr);

    for (int i = 0; i < 999; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

// 测试归并排序 - 全部相同元素
TEST(MergeSortTest, AllSameElements) {
    std::vector<int> arr = {42, 42, 42, 42, 42};
    std::vector<int> expected = {42, 42, 42, 42, 42};
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试归并排序 - 边界值
TEST(MergeSortTest, BoundaryValues) {
    std::vector<int> arr = {std::numeric_limits<int>::max(), 0, std::numeric_limits<int>::min()};
    std::vector<int> expected = {std::numeric_limits<int>::min(), 0, std::numeric_limits<int>::max()};
    
    algorithms::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试插入排序 - 基本功能
TEST(InsertionSortTest, BasicFunctionality) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};

    algorithms::insertionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试插入排序 - 空数组
TEST(InsertionSortTest, EmptyArray) {
    std::vector<int> arr;
    algorithms::insertionSort(arr);
    EXPECT_TRUE(arr.empty());
}

// 测试插入排序 - 单元素数组
TEST(InsertionSortTest, SingleElement) {
    std::vector<int> arr = {42};
    algorithms::insertionSort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// 测试插入排序 - 已排序数组
TEST(InsertionSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::insertionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试插入排序 - 逆序数组
TEST(InsertionSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::insertionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试插入排序 - 重复元素
TEST(InsertionSortTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    algorithms::insertionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试插入排序 - 大规模数据
TEST(InsertionSortTest, LargeArray) {
    std::vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 - i;
    }

    algorithms::insertionSort(arr);

    for (int i = 0; i < 999; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

// 测试选择排序 - 基本功能
TEST(SelectionSortTest, BasicFunctionality) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};

    algorithms::selectionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试选择排序 - 空数组
TEST(SelectionSortTest, EmptyArray) {
    std::vector<int> arr;
    algorithms::selectionSort(arr);
    EXPECT_TRUE(arr.empty());
}

// 测试选择排序 - 单元素数组
TEST(SelectionSortTest, SingleElement) {
    std::vector<int> arr = {42};
    algorithms::selectionSort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// 测试选择排序 - 逆序数组
TEST(SelectionSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::selectionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试选择排序 - 已排序数组
TEST(SelectionSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::selectionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试选择排序 - 重复元素
TEST(SelectionSortTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    algorithms::selectionSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试选择排序 - 大规模数据
TEST(SelectionSortTest, LargeArray) {
    std::vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 - i;
    }

    algorithms::selectionSort(arr);

    for (int i = 0; i < 999; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}

// 测试冒泡排序 - 基本功能
TEST(BubbleSortTest, BasicFunctionality) {
    std::vector<int> arr = {64, 34, 25, 12, 22, 11, 90};
    std::vector<int> expected = {11, 12, 22, 25, 34, 64, 90};

    algorithms::bubbleSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试冒泡排序 - 空数组
TEST(BubbleSortTest, EmptyArray) {
    std::vector<int> arr;
    algorithms::bubbleSort(arr);
    EXPECT_TRUE(arr.empty());
}

// 测试冒泡排序 - 单元素数组
TEST(BubbleSortTest, SingleElement) {
    std::vector<int> arr = {42};
    algorithms::bubbleSort(arr);
    EXPECT_EQ(arr.size(), 1);
    EXPECT_EQ(arr[0], 42);
}

// 测试冒泡排序 - 重复元素
TEST(BubbleSortTest, DuplicateElements) {
    std::vector<int> arr = {3, 1, 4, 1, 5, 9, 2, 6, 5, 3, 5};
    std::vector<int> expected = arr;
    std::sort(expected.begin(), expected.end());

    algorithms::bubbleSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试冒泡排序 - 已排序数组（提前终止优化）
TEST(BubbleSortTest, AlreadySorted) {
    std::vector<int> arr = {1, 2, 3, 4, 5};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::bubbleSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试冒泡排序 - 逆序数组
TEST(BubbleSortTest, ReverseSorted) {
    std::vector<int> arr = {5, 4, 3, 2, 1};
    std::vector<int> expected = {1, 2, 3, 4, 5};

    algorithms::bubbleSort(arr);

    EXPECT_EQ(arr, expected);
}

// 测试冒泡排序 - 大规模数据
TEST(BubbleSortTest, LargeArray) {
    std::vector<int> arr(1000);
    for (int i = 0; i < 1000; i++) {
        arr[i] = 1000 - i;
    }

    algorithms::bubbleSort(arr);

    for (int i = 0; i < 999; i++) {
        EXPECT_LE(arr[i], arr[i + 1]);
    }
}