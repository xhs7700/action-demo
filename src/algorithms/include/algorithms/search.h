#ifndef ALGORITHMS_SEARCH_H
#define ALGORITHMS_SEARCH_H

#include <vector>

namespace algorithms {

/**
 * 二分查找算法（要求数组已排序）
 * @param arr 已排序的整数向量
 * @param target 目标值
 * @return 目标值的索引，未找到返回-1
 */
int binarySearch(const std::vector<int>& arr, int target);

/**
 * 线性查找算法
 * @param arr 整数向量
 * @param target 目标值
 * @return 目标值的索引，未找到返回-1
 */
int linearSearch(const std::vector<int>& arr, int target);

/**
 * 插值查找算法（要求数组已排序且元素均匀分布）
 * @param arr 已排序的整数向量
 * @param target 目标值
 * @return 目标值的索引，未找到返回-1
 */
int interpolationSearch(const std::vector<int>& arr, int target);

/**
 * 斐波那契查找算法（要求数组已排序）
 * @param arr 已排序的整数向量
 * @param target 目标值
 * @return 目标值的索引，未找到返回-1
 */
int fibonacciSearch(const std::vector<int>& arr, int target);

} // namespace algorithms

#endif // ALGORITHMS_SEARCH_H
