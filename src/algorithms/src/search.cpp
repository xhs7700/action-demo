#include "algorithms/search.h"

namespace algorithms {

int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0;
    int right = static_cast<int>(arr.size()) - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2;
        
        if (arr[mid] == target) {
            return mid;
        } else if (arr[mid] < target) {
            left = mid + 1;
        } else {
            right = mid - 1;
        }
    }
    
    return -1; // 未找到
}

int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); i++) {
        if (arr[i] == target) {
            return static_cast<int>(i);
        }
    }
    return -1; // 未找到
}

int interpolationSearch(const std::vector<int>& arr, int target) {
    int n = static_cast<int>(arr.size());
    if (n == 0) return -1;

    int low = 0;
    int high = n - 1;

    while (low <= high && target >= arr[low] && target <= arr[high]) {
        if (low == high) {
            if (arr[low] == target) return low;
            return -1;
        }

        // 计算插值位置（使用long long避免溢出）
        int denominator = arr[high] - arr[low];
        if (denominator == 0) {
            // 当所有元素相等时，回退到线性查找
            for (int i = low; i <= high; i++) {
                if (arr[i] == target) {
                    return i;
                }
            }
            return -1;
        }
        
        // 使用long long进行中间计算，避免整数溢出
        long long numerator = static_cast<long long>(target - arr[low]) * (high - low);
        int pos = low + static_cast<int>(numerator / denominator);
        
        // 确保pos在有效范围内
        if (pos < low) pos = low;
        if (pos > high) pos = high;

        if (arr[pos] == target) {
            return pos;
        } else if (arr[pos] < target) {
            low = pos + 1;
        } else {
            high = pos - 1;
        }
    }
    return -1; // 未找到
}

int fibonacciSearch(const std::vector<int>& arr, int target) {
    int n = static_cast<int>(arr.size());
    if (n == 0) return -1;

    // 初始化斐波那契数
    int fib2 = 0; // (m-2)th Fibonacci number
    int fib1 = 1; // (m-1)th Fibonacci number
    int fib = fib2 + fib1; // mth Fibonacci number

    // fib 存储最小的斐波那契数大于或等于n
    while (fib < n) {
        fib2 = fib1;
        fib1 = fib;
        fib = fib2 + fib1;
    }

    int offset = -1;

    while (fib > 1) {
        // 检查有效范围
        int i = std::min(offset + fib2, n - 1);

        if (arr[i] < target) {
            fib = fib1;
            fib1 = fib2;
            fib2 = fib - fib1;
            offset = i;
        } else if (arr[i] > target) {
            fib = fib2;
            fib1 = fib1 - fib2;
            fib2 = fib - fib1;
        } else {
            return i;
        }
    }

    // 比较最后元素
    if (fib1 && offset + 1 < n && arr[offset + 1] == target) {
        return offset + 1;
    }

    return -1; // 未找到
}

} // namespace algorithms