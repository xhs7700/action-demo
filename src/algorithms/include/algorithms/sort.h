#ifndef ALGORITHMS_SORT_H
#define ALGORITHMS_SORT_H

#include <vector>

namespace algorithms {

/**
 * 快速排序算法
 * @param arr 待排序的整数向量
 */
void quickSort(std::vector<int>& arr);

/**
 * 归并排序算法
 * @param arr 待排序的整数向量
 */
void mergeSort(std::vector<int>& arr);

} // namespace algorithms

#endif // ALGORITHMS_SORT_H
