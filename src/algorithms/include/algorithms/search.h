#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H

#include <vector>

namespace algorithms {

/**
 * @brief 使用二分查找算法在已排序数组中查找目标值
 * 
 * 二分查找通过将查找区间不断对半分割，每次比较中间元素，
 * 根据比较结果决定在左半部分或右半部分继续查找。
 * 
 * @param arr 已排序的整数向量（升序）
 * @param target 要查找的目标值
 * @return 目标值在数组中的索引，未找到返回-1
 * 
 * @note 前置条件: 数组必须已按升序排序
 * @note 时间复杂度: O(log n)
 * @note 空间复杂度: O(1)
 * 
 * @example
 * std::vector<int> arr = {1, 3, 5, 7, 9};
 * int index = algorithms::binarySearch(arr, 5);
 * // index is 2
 */
int binarySearch(const std::vector<int>& arr, int target);

/**
 * @brief 使用线性查找算法在数组中查找目标值
 * 
 * 线性查找从数组第一个元素开始，逐个比较直到找到目标值或遍历完整个数组。
 * 该算法不要求数组有序，适用于所有情况。
 * 
 * @param arr 整数向量（无序或有序均可）
 * @param target 要查找的目标值
 * @return 目标值在数组中的索引（首次出现位置），未找到返回-1
 * 
 * @note 时间复杂度: O(n)
 * @note 空间复杂度: O(1)
 * @note 适用场景: 小规模数据或无序数组
 * 
 * @example
 * std::vector<int> arr = {4, 2, 7, 1, 5};
 * int index = algorithms::linearSearch(arr, 7);
 * // index is 2
 */
int linearSearch(const std::vector<int>& arr, int target);

/**
 * @brief 使用插值查找算法在已排序且均匀分布的数组中查找目标值
 * 
 * 插值查找是二分查找的改进版本，根据目标值在最小值和最大值之间的相对位置
 * 来估算目标值可能所在的位置，而不是简单地取中间位置。
 * 
 * @param arr 已排序且元素较为均匀分布的整数向量（升序）
 * @param target 要查找的目标值
 * @return 目标值在数组中的索引，未找到返回-1
 * 
 * @note 前置条件: 数组必须已按升序排序，且元素分布较为均匀
 * @note 时间复杂度: 平均 O(log log n)，最坏 O(n)（元素分布不均匀时）
 * @note 空间复杂度: O(1)
 * @note 适用场景: 数据量大且分布均匀的有序数组
 * 
 * @example
 * std::vector<int> arr = {10, 20, 30, 40, 50};
 * int index = algorithms::interpolationSearch(arr, 30);
 * // index is 2
 */
int interpolationSearch(const std::vector<int>& arr, int target);

/**
 * @brief 使用斐波那契查找算法在已排序数组中查找目标值
 * 
 * 斐波那契查找利用斐波那契数列来分割查找区间，
 * 每次将数组分为两个不相等的部分，适合顺序读取的存储介质。
 * 
 * @param arr 已排序的整数向量（升序）
 * @param target 要查找的目标值
 * @return 目标值在数组中的索引，未找到返回-1
 * 
 * @note 前置条件: 数组必须已按升序排序
 * @note 时间复杂度: O(log n)
 * @note 空间复杂度: O(1)
 * @note 特点: 只使用加法和减法运算，避免除法
 * 
 * @example
 * std::vector<int> arr = {1, 2, 3, 5, 8, 13, 21};
 * int index = algorithms::fibonacciSearch(arr, 8);
 * // index is 4
 */
int fibonacciSearch(const std::vector<int>& arr, int target);

} // namespace algorithms

#endif // ALGORITHMS_SEARCH_H