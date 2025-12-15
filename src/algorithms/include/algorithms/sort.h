#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

#include <vector>

namespace algorithms {

/**
 * @brief 使用快速排序算法对整数向量进行原地排序
 * 
 * 快速排序是一种分治算法，通过选择基准值将数组分为两部分，
 * 左侧小于基准值，右侧大于基准值，然后递归排序两部分。
 * 
 * @param arr 待排序的整数向量，排序后原地修改为升序
 * 
 * @note 时间复杂度: 平均 O(n log n)，最坏 O(n²)（当数组已排序或逆序时）
 * @note 空间复杂度: O(log n)（递归调用栈）
 * @note 稳定性: 不稳定
 * @note 原地性: 是
 * 
 * @example
 * std::vector<int> arr = {3, 1, 4, 1, 5};
 * algorithms::quickSort(arr);
 * // arr is now {1, 1, 3, 4, 5}
 */
void quickSort(std::vector<int>& arr);

/**
 * @brief 使用归并排序算法对整数向量进行排序
 * 
 * 归并排序是一种稳定的分治算法，将数组递归分割成两半，
 * 分别排序后再合并成一个有序数组。
 * 
 * @param arr 待排序的整数向量，排序后原地修改为升序
 * 
 * @note 时间复杂度: O(n log n)（所有情况）
 * @note 空间复杂度: O(n)（需要额外空间存储临时数组）
 * @note 稳定性: 稳定
 * @note 原地性: 否
 * 
 * @example
 * std::vector<int> arr = {5, 2, 8, 1, 9};
 * algorithms::mergeSort(arr);
 * // arr is now {1, 2, 5, 8, 9}
 */
void mergeSort(std::vector<int>& arr);

/**
 * @brief 使用插入排序算法对整数向量进行原地排序
 * 
 * 插入排序通过构建有序序列，对于未排序数据，在已排序序列中
 * 从后向前扫描，找到相应位置并插入。
 * 
 * @param arr 待排序的整数向量，排序后原地修改为升序
 * 
 * @note 时间复杂度: 最好 O(n)（已排序），平均/最坏 O(n²)
 * @note 空间复杂度: O(1)
 * @note 稳定性: 稳定
 * @note 原地性: 是
 * @note 适用场景: 小规模数据或基本有序的数据
 * 
 * @example
 * std::vector<int> arr = {5, 2, 4, 6, 1, 3};
 * algorithms::insertionSort(arr);
 * // arr is now {1, 2, 3, 4, 5, 6}
 */
void insertionSort(std::vector<int>& arr);

/**
 * @brief 使用选择排序算法对整数向量进行原地排序
 * 
 * 选择排序每次从未排序部分选择最小元素，放到已排序部分的末尾。
 * 
 * @param arr 待排序的整数向量，排序后原地修改为升序
 * 
 * @note 时间复杂度: O(n²)（所有情况）
 * @note 空间复杂度: O(1)
 * @note 稳定性: 不稳定
 * @note 原地性: 是
 * @note 特点: 交换次数最少（最多n-1次）
 * 
 * @example
 * std::vector<int> arr = {64, 25, 12, 22, 11};
 * algorithms::selectionSort(arr);
 * // arr is now {11, 12, 22, 25, 64}
 */
void selectionSort(std::vector<int>& arr);

/**
 * @brief 使用冒泡排序算法对整数向量进行原地排序
 * 
 * 冒泡排序重复遍历数组，比较相邻元素并交换位置，
 * 使较大元素逐渐"冒泡"到数组末尾。
 * 
 * @param arr 待排序的整数向量，排序后原地修改为升序
 * 
 * @note 时间复杂度: 最好 O(n)（已排序），平均/最坏 O(n²)
 * @note 空间复杂度: O(1)
 * @note 稳定性: 稳定
 * @note 原地性: 是
 * @note 特点: 实现简单但效率较低，主要用于教学
 * 
 * @example
 * std::vector<int> arr = {5, 1, 4, 2, 8};
 * algorithms::bubbleSort(arr);
 * // arr is now {1, 2, 4, 5, 8}
 */
void bubbleSort(std::vector<int>& arr);

} // namespace algorithms

#endif // ALGORITHMS_SORT_H