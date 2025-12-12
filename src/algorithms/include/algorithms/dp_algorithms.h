#ifndef ALGORITHMS_DP_ALGORITHMS_H
#define ALGORITHMS_DP_ALGORITHMS_H

#include <vector>
#include <string>

namespace algorithms {

/**
 * 0-1背包问题 - 动态规划解法
 * @param weights 物品重量数组
 * @param values 物品价值数组
 * @param capacity 背包容量
 * @return 最大价值
 */
int knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity);

/**
 * 最长公共子序列长度
 * @param s1 第一个字符串
 * @param s2 第二个字符串
 * @return 最长公共子序列的长度
 */
int longestCommonSubsequence(const std::string& s1, const std::string& s2);

/**
 * 最长公共子序列（返回子序列本身）
 * @param s1 第一个字符串
 * @param s2 第二个字符串
 * @return 最长公共子序列
 */
std::string getLongestCommonSubsequence(const std::string& s1, const std::string& s2);

} // namespace algorithms

#endif // ALGORITHMS_DP_ALGORITHMS_H
