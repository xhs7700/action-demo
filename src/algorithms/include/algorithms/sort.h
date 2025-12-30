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

// 小数组阈值：当子数组大小 <= 此值时切换到插入排序
constexpr int INSERTION_SORT_THRESHOLD = 16;

/**
 * @brief 三数取中选择枢轴
 * 
 * 从首、中、尾三个位置选择中位数作为枢轴，避免在已排序数据上退化为 O(n²)。
 * 
 * @return 中位数的索引
 */
template<typename T, typename Compare>
int medianOfThree(std::vector<T>& arr, int low, int high, Compare comp) {
    int mid = low + (high - low) / 2;
    
    // 对 arr[low], arr[mid], arr[high] 排序
    if (comp(arr[mid], arr[low])) {
        std::swap(arr[low], arr[mid]);
    }
    if (comp(arr[high], arr[low])) {
        std::swap(arr[low], arr[high]);
    }
    if (comp(arr[high], arr[mid])) {
        std::swap(arr[mid], arr[high]);
    }
    
    // 将中位数移到 high-1 位置
    std::swap(arr[mid], arr[high - 1]);
    return high - 1;
}

/**
 * @brief 快速排序的分区辅助函数（优化版：使用三数取中）
 */
template<typename T, typename Compare>
int partition(std::vector<T>& arr, int low, int high, Compare comp) {
    // 对于小数组，直接使用最后一个元素作为枢轴
    if (high - low < 3) {
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
    
    // 三数取中选择枢轴
    int pivotIndex = medianOfThree(arr, low, high, comp);
    T pivot = arr[pivotIndex];
    int i = low - 1;
    
    for (int j = low; j < pivotIndex; j++) {
        if (comp(arr[j], pivot)) {
            i++;
            std::swap(arr[i], arr[j]);
        }
    }
    std::swap(arr[i + 1], arr[pivotIndex]);
    return i + 1;
}

/**
 * @brief 快速排序递归辅助函数（优化版：尾递归 + 混合插入排序）
 * 
 * - 小数组切换到插入排序
 * - 尾递归优化：先递归小分区，大分区使用迭代
 */
template<typename T, typename Compare>
void quickSortHelper(std::vector<T>& arr, int low, int high, Compare comp) {
    while (low < high) {
        // 小数组优化：切换到插入排序
        if (high - low + 1 <= INSERTION_SORT_THRESHOLD) {
            // 对 [low, high] 区间进行插入排序
            for (int i = low + 1; i <= high; i++) {
                T key = std::move(arr[i]);
                int j = i - 1;
                while (j >= low && comp(key, arr[j])) {
                    arr[j + 1] = std::move(arr[j]);
                    j--;
                }
                arr[j + 1] = std::move(key);
            }
            return;
        }
        
        // 分区
        int pi = partition(arr, low, high, comp);
        
        // 尾递归优化：递归较小的分区，迭代较大的分区
        if (pi - low < high - pi) {
            // 左分区较小
            quickSortHelper(arr, low, pi - 1, comp);
            low = pi + 1;  // 继续迭代右分区
        } else {
            // 右分区较小
            quickSortHelper(arr, pi + 1, high, comp);
            high = pi - 1;  // 继续迭代左分区
        }
    }
}

/**
 * @brief 使用快速排序算法对向量进行原地排序（优化版）
 * 
 * 快速排序是一种分治算法，通过选择基准值将数组分为两部分，
 * 左侧小于基准值，右侧大于基准值，然后递归排序两部分。
 * 
 * 优化特性：
 * - 三数取中法选择枢轴，避免在已排序数据上退化为 O(n²)
 * - 小数组（≤16 元素）切换到插入排序，减少递归开销
 * - 尾递归优化，保证栈深度 O(log n)
 * 
 * @tparam T 元素类型，必须支持拷贝/移动和比较操作
 * @tparam Compare 比较器类型，默认为 std::less<T>（升序）
 * @param arr 待排序的向量，排序后原地修改
 * @param comp 比较器对象，默认为升序
 * 
 * @note 时间复杂度: 平均 O(n log n)，最坏 O(n log n)（三数取中优化后）
 * @note 空间复杂度: O(log n)（递归调用栈，尾递归优化后）
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
 * @brief 归并排序的合并辅助函数（优化版：使用共享缓冲区）
 * 
 * @param buffer 预分配的临时缓冲区，大小至少为 arr.size()
 */
template<typename T, typename Compare>
void mergeWithBuffer(std::vector<T>& arr, int left, int mid, int right, 
                     std::vector<T>& buffer, Compare comp) {
    int i = left;
    int j = mid + 1;
    int k = left;
    
    // 合并到缓冲区
    while (i <= mid && j <= right) {
        if (comp(arr[i], arr[j]) || !comp(arr[j], arr[i])) {
            buffer[k++] = std::move(arr[i++]);
        } else {
            buffer[k++] = std::move(arr[j++]);
        }
    }
    
    // 复制剩余元素
    while (i <= mid) {
        buffer[k++] = std::move(arr[i++]);
    }
    while (j <= right) {
        buffer[k++] = std::move(arr[j++]);
    }
    
    // 从缓冲区复制回原数组
    for (int idx = left; idx <= right; idx++) {
        arr[idx] = std::move(buffer[idx]);
    }
}

/**
 * @brief 归并排序递归辅助函数（使用共享缓冲区）
 */
template<typename T, typename Compare>
void mergeSortWithBuffer(std::vector<T>& arr, int left, int right, 
                         std::vector<T>& buffer, Compare comp) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSortWithBuffer(arr, left, mid, buffer, comp);
        mergeSortWithBuffer(arr, mid + 1, right, buffer, comp);
        mergeWithBuffer(arr, left, mid, right, buffer, comp);
    }
}

/**
 * @brief 使用归并排序算法对向量进行排序（优化版：单次缓冲区分配）
 * 
 * 归并排序是一种稳定的分治算法，将数组递归分割成两半，
 * 分别排序后再合并成一个有序数组。
 * 
 * 优化特性：
 * - 在顶层一次性分配临时缓冲区，避免递归过程中重复分配
 * - 减少内存分配次数从 O(n log n) 到 O(1)
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
    if (arr.size() <= 1) {
        return;
    }
    
    // 一次性分配缓冲区，递归过程中重用
    std::vector<T> buffer(arr.size());
    mergeSortWithBuffer(arr, 0, static_cast<int>(arr.size()) - 1, buffer, comp);
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