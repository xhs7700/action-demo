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

// ============================================================================
// 泛型测试 - 测试模板化算法支持不同类型
// ============================================================================

// 测试 double 类型 - 快速排序
TEST(GenericSortTest, QuickSortDouble) {
    std::vector<double> arr = {3.14, 2.71, 1.41, 0.577, 2.236};
    std::vector<double> expected = {0.577, 1.41, 2.236, 2.71, 3.14};
    
    algorithms::sort::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试 double 类型 - 归并排序
TEST(GenericSortTest, MergeSortDouble) {
    std::vector<double> arr = {-1.5, 3.7, 0.0, -2.3, 1.1};
    std::vector<double> expected = {-2.3, -1.5, 0.0, 1.1, 3.7};
    
    algorithms::sort::mergeSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试 string 类型 - 插入排序
TEST(GenericSortTest, InsertionSortString) {
    std::vector<std::string> arr = {"banana", "apple", "cherry", "date"};
    std::vector<std::string> expected = {"apple", "banana", "cherry", "date"};
    
    algorithms::sort::insertionSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试 string 类型 - 选择排序
TEST(GenericSortTest, SelectionSortString) {
    std::vector<std::string> arr = {"zebra", "aardvark", "monkey", "elephant"};
    std::vector<std::string> expected = {"aardvark", "elephant", "monkey", "zebra"};
    
    algorithms::sort::selectionSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试 string 类型 - 冒泡排序
TEST(GenericSortTest, BubbleSortString) {
    std::vector<std::string> arr = {"dog", "cat", "bird", "fish"};
    std::vector<std::string> expected = {"bird", "cat", "dog", "fish"};
    
    algorithms::sort::bubbleSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试自定义比较器 - 降序排序（int）
TEST(GenericSortTest, CustomComparatorDescending) {
    std::vector<int> arr = {1, 5, 3, 9, 2};
    std::vector<int> expected = {9, 5, 3, 2, 1};
    
    algorithms::sort::quickSort(arr, std::greater<int>());
    
    EXPECT_EQ(arr, expected);
}

// 测试自定义比较器 - 字符串按长度排序
TEST(GenericSortTest, CustomComparatorStringLength) {
    std::vector<std::string> arr = {"a", "abc", "ab", "abcd"};
    std::vector<std::string> expected = {"a", "ab", "abc", "abcd"};
    
    auto lengthCompare = [](const std::string& a, const std::string& b) {
        return a.length() < b.length();
    };
    
    algorithms::sort::mergeSort(arr, lengthCompare);
    
    EXPECT_EQ(arr, expected);
}

// 测试自定义比较器 - double 降序
TEST(GenericSortTest, CustomComparatorDoubleDescending) {
    std::vector<double> arr = {1.1, 3.3, 2.2, 5.5, 4.4};
    std::vector<double> expected = {5.5, 4.4, 3.3, 2.2, 1.1};
    
    algorithms::sort::insertionSort(arr, std::greater<double>());
    
    EXPECT_EQ(arr, expected);
}

// 测试自定义结构体排序
TEST(GenericSortTest, CustomStructSort) {
    struct Person {
        std::string name;
        int age;
        
        bool operator==(const Person& other) const {
            return name == other.name && age == other.age;
        }
    };
    
    std::vector<Person> arr = {
        {"Alice", 30},
        {"Bob", 25},
        {"Charlie", 35},
        {"David", 20}
    };
    
    std::vector<Person> expected = {
        {"David", 20},
        {"Bob", 25},
        {"Alice", 30},
        {"Charlie", 35}
    };
    
    auto ageCompare = [](const Person& a, const Person& b) {
        return a.age < b.age;
    };
    
    algorithms::sort::quickSort(arr, ageCompare);
    
    EXPECT_EQ(arr, expected);
}

// 测试向后兼容性 - 旧命名空间仍然可用
TEST(BackwardCompatibilityTest, OldNamespaceStillWorks) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    std::vector<int> expected = {1, 2, 5, 8, 9};
    
    // 使用旧的命名空间调用
    algorithms::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试新命名空间
TEST(NewNamespaceTest, SortNamespaceWorks) {
    std::vector<int> arr = {5, 2, 8, 1, 9};
    std::vector<int> expected = {1, 2, 5, 8, 9};
    
    // 使用新的命名空间调用
    algorithms::sort::quickSort(arr);
    
    EXPECT_EQ(arr, expected);
}

// 测试混合使用新旧命名空间
TEST(MixedNamespaceTest, BothNamespacesWork) {
    std::vector<int> arr1 = {5, 2, 8, 1, 9};
    std::vector<int> arr2 = {5, 2, 8, 1, 9};
    std::vector<int> expected = {1, 2, 5, 8, 9};
    
    algorithms::quickSort(arr1);  // 旧命名空间
    algorithms::sort::quickSort(arr2);  // 新命名空间
    
    EXPECT_EQ(arr1, expected);
    EXPECT_EQ(arr2, expected);
    EXPECT_EQ(arr1, arr2);
}