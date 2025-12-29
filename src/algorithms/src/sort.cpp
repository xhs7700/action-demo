#include "algorithms/sort.h"
#include <string>

// 此文件用于显式实例化常用类型的排序算法，以减少编译时间

namespace algorithms {
namespace sort {

// 为int类型的显式实例化
template void quickSort<int>(std::vector<int>&, std::less<int>);
template void mergeSort<int>(std::vector<int>&, std::less<int>);
template void insertionSort<int>(std::vector<int>&, std::less<int>);
template void selectionSort<int>(std::vector<int>&, std::less<int>);
template void bubbleSort<int>(std::vector<int>&, std::less<int>);

// 为double类型的显式实例化
template void quickSort<double>(std::vector<double>&, std::less<double>);
template void mergeSort<double>(std::vector<double>&, std::less<double>);
template void insertionSort<double>(std::vector<double>&, std::less<double>);
template void selectionSort<double>(std::vector<double>&, std::less<double>);
template void bubbleSort<double>(std::vector<double>&, std::less<double>);

// 为std::string类型的显式实例化
template void quickSort<std::string>(std::vector<std::string>&, std::less<std::string>);
template void mergeSort<std::string>(std::vector<std::string>&, std::less<std::string>);
template void insertionSort<std::string>(std::vector<std::string>&, std::less<std::string>);
template void selectionSort<std::string>(std::vector<std::string>&, std::less<std::string>);
template void bubbleSort<std::string>(std::vector<std::string>&, std::less<std::string>);

} // namespace sort
} // namespace algorithms
