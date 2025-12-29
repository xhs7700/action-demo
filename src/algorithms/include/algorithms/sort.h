#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

#include <vector>
#include <functional>
#include <algorithm>

namespace algorithms {
namespace sort {

// ============================================================================
// 快速排序 (Quick Sort)
// ============================================================================

/**
 * @brief 快速排序的分区辅助函数
 */
template<typename T, typename Compare>
int partition(std::vector<T>& arr, int low, int high, Compare comp) {
    T pivot = arr[high];
    int i = low - 1;
    
    for (int j = low; j < high; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[high]);
    return i + 1;
}

/**
 * @brief 快速排序递归辅助函数
 */
template<typename T, typename Compare>
void quickSortHelper(std::vector<T>& arr, int low, int high, Compare comp) {
    if (low < high) {
        int pi = partition(arr, low, high, comp);
        quickSortHelper(arr, low, pi - 1, comp);
        quickSortHelper(arr, pi + 1, high, comp);
    }
}

/**
 * @brief 使用快速排序算法对向量进行原地排序
 * 
 * 快速排序是一种分治算法，通过选择基准值将数组分为两部分，
 * 左侧小于基准值，右侧大于基准值，然后递归排序两部分。
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: 平均 O(n log n)，最坏 O(n²)（当数组已排序或逆序时）
 * @note 空间复杂度: O(log n)（递归调用栈）
 * @note 稳定性: 不稳定
 * @note 原地性: 是
 * 
 * @example
 * // 整数数组升序排序
 * std::vector<int> arr = {3, 1, 4, 1, 5};
 * algorithms::sort::quickSort(arr);
 * // arr is now {1, 1, 3, 4, 5}
 * 
 * @example
 * // 字符串数组降序排序
 * std::vector<std::string> arr = {"apple", "orange", "banana"};
 * algorithms::sort::quickSort(arr, std::greater<std::string>());
 * // arr is now {"orange", "banana", "apple"}
 */
template<typename T, typename Compare = std::less<T>>
void quickSort(std::vector<T>& arr, Compare comp = Compare{}) {
    if (!arr.empty()) {
        quickSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

// ============================================================================
// 归并排序 (Merge Sort)
// ============================================================================

/**
 * @brief 归并排序的合并辅助函数
 */
template<typename T, typename Compare>
void merge(std::vector<T>& arr, int left, int mid, int right, Compare comp) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    std::vector<T> leftArr(n1);
    std::vector<T> rightArr(n2);
    
    for (int i = 0; i < n1; i++)
        leftArr[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        rightArr[j] = arr[mid + 1 + j];
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (comp(leftArr[i], rightArr[j]) || !comp(rightArr[j], leftArr[i])) {
            arr[k] = std::move(leftArr[i]);
            i++;
        } else {
            arr[k] = std::move(rightArr[j]);
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = std::move(leftArr[i]);
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = std::move(rightArr[j]);
        j++;
        k++;
    }
}

/**
 * @brief 归并排序递归辅助函数
 */
template<typename T, typename Compare>
void mergeSortHelper(std::vector<T>& arr, int left, int right, Compare comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortHelper(arr, left, mid, comp);
        mergeSortHelper(arr, mid + 1, right, comp);
        merge(arr, left, mid, right, comp);
    }
}

/**
 * @brief 使用归并排序算法对向量进行排序
 * 
 * 归并排序是一种稳定的分治算法，将数组递归分割成两半，
 * 分别排序后再合并成一个有序数组。
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: O(n log n)（所有情况）
 * @note 空间复杂度: O(n)（需要额外空间存储临时数组）
 * @note 稳定性: 稳定
 * @note 原地性: 否
 */
template<typename T, typename Compare = std::less<T>>
void mergeSort(std::vector<T>& arr, Compare comp = Compare{}) {
    if (!arr.empty()) {
        mergeSortHelper(arr, 0, static_cast<int>(arr.size()) - 1, comp);
    }
}

// ============================================================================
// 插入排序 (Insertion Sort)
// ============================================================================

/**
 * @brief 使用插入排序算法对向量进行原地排序
 * 
 * 插入排序通过构建有序序列，对于未排序数据，在已排序序列中
 * 从后向前扫描，找到相应位置并插入。
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: 最好 O(n)（已排序），平均/最坏 O(n²)
 * @note 空间复杂度: O(1)
 * @note 稳定性: 稳定
 * @note 原地性: 是
 * @note 适用场景: 小规模数据或基本有序的数据
 */
template<typename T, typename Compare = std::less<T>>
void insertionSort(std::vector<T>& arr, Compare comp = Compare{}) {
    int n = static_cast<int>(arr.size());
    for (int i = 1; i < n; i++) {
        T key = std::move(arr[i]);
        int j = i - 1;

        // 将大于key的元素向右移动
        while (j >= 0 && comp(key, arr[j])) {
            arr[j + 1] = std::move(arr[j]);
            j--;
        }
        arr[j + 1] = std::move(key);
    }
}

// ============================================================================
// 选择排序 (Selection Sort)
// ============================================================================

/**
 * @brief 使用选择排序算法对向量进行原地排序
 * 
 * 选择排序每次从未排序部分选择最小元素，放到已排序部分的末尾。
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: O(n²)（所有情况）
 * @note 空间复杂度: O(1)
 * @note 稳定性: 不稳定
 * @note 原地性: 是
 * @note 特点: 交换次数最少（最多n-1次）
 */
template<typename T, typename Compare = std::less<T>>
void selectionSort(std::vector<T>& arr, Compare comp = Compare{}) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        // 找到剩余未排序元素中的最小元素
        int minIndex = i;
        for (int j = i + 1; j < n; j++) {
            if (comp(arr[j], arr[minIndex])) {
                minIndex = j;
            }
        }
        // 交换找到的最小元素与第一个元素
        if (minIndex != i) {
            std::swap(arr[i], arr[minIndex]);
        }
    }
}

// ============================================================================
// 冒泡排序 (Bubble Sort)
// ============================================================================

/**
 * @brief 使用冒泡排序算法对向量进行原地排序
 * 
 * 冒泡排序重复遍历数组，比较相邻元素并交换位置，
 * 使较大元素逐渐“冒泡”到数组末尾。
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: 最好 O(n)（已排序），平均/最坏 O(n²)
 * @note 空间复杂度: O(1)
 * @note 稳定性: 稳定
 * @note 原地性: 是
 * @note 特点: 实现简单但效率较低，主要用于教学
 */
template<typename T, typename Compare = std::less<T>>
void bubbleSort(std::vector<T>& arr, Compare comp = Compare{}) {
    int n = static_cast<int>(arr.size());
    for (int i = 0; i < n - 1; i++) {
        bool swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (comp(arr[j + 1], arr[j])) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        // 如果在一轮中没有发生交换，说明数组已经有序
        if (!swapped) {
            break;
        }
    }
}

} // namespace sort

// 向后兼容层：将新命名空间中的符号导入旧命名空间
using sort::quickSort;
using sort::mergeSort;
using sort::insertionSort;
using sort::selectionSort;
using sort::bubbleSort;

} // namespace algorithms

#endif // ALGORITHMS_SORT_H