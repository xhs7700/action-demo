#ifndef ALGORITHMS_DP_ALGORITHMS_H
#define ALGORITHMS_DP_ALGORITHMS_H

#include <vector>
#include <string>

namespace algorithms {

/**
 * @brief 使用动态规划解决0-1背包问题
 * 
 * 0-1背包问题：给定n个物品和一个容量为capacity的背包，每个物品有重量和价值，
 * 每个物品只能选择放入或不放入（0-1选择），求在不超过背包容量的前提下，
 * 能够装入背包的物品的最大总价值。
 * 
 * @param weights 物品重量数组，weights[i]表示第i个物品的重量
 * @param values 物品价值数组，values[i]表示第i个物品的价值
 * @param capacity 背包的最大承重容量
 * @return 在容量限制下能获得的最大总价值
 * 
 * @throw std::invalid_argument 如果weights和values数组大小不一致
 * @throw std::invalid_argument 如果capacity为负数
 * @throw std::invalid_argument 如果capacity过大（>100000）
 * 
 * @note 前置条件: weights.size() == values.size()
 * @note 前置条件: capacity >= 0 且 capacity <= 100000
 * @note 时间复杂度: O(n * capacity)，其中n是物品数量
 * @note 空间复杂度: O(n * capacity)
 * 
 * @example
 * std::vector<int> weights = {2, 3, 4, 5};
 * std::vector<int> values = {3, 4, 5, 6};
 * int capacity = 8;
 * int maxValue = algorithms::knapsack01(weights, values, capacity);
 * // maxValue is 10 (选择物品1和3，重量2+4=6，价值3+5=8)
 */
int knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity);

/**
 * @brief 计算两个字符串的最长公共子序列（LCS）的长度
 * 
 * 最长公共子序列是指在两个序列中以相同顺序出现，但不要求连续的最长序列。
 * 例如："ABCDGH"和"AEDFHR"的LCS是"ADH"，长度为3。
 * 
 * @param s1 第一个字符串
 * @param s2 第二个字符串
 * @return 最长公共子序列的长度
 * 
 * @note 时间复杂度: O(m * n)，其中m和n分别是两个字符串的长度
 * @note 空间复杂度: O(m * n)
 * @note 应用场景: 文件对比、DNA序列比对等
 * 
 * @example
 * std::string s1 = "ABCDGH";
 * std::string s2 = "AEDFHR";
 * int length = algorithms::longestCommonSubsequence(s1, s2);
 * // length is 3 (LCS is "ADH")
 */
int longestCommonSubsequence(const std::string& s1, const std::string& s2);

/**
 * @brief 获取两个字符串的最长公共子序列（LCS）本身
 * 
 * 不仅计算LCS的长度，还通过回溯DP表构造出实际的最长公共子序列字符串。
 * 如果存在多个相同长度的LCS，返回其中一个。
 * 
 * @param s1 第一个字符串
 * @param s2 第二个字符串
 * @return 最长公共子序列字符串
 * 
 * @note 时间复杂度: O(m * n)，其中m和n分别是两个字符串的长度
 * @note 空间复杂度: O(m * n)
 * @note 如果有多个LCS，返回字典序最小的一个（取决于实现）
 * 
 * @example
 * std::string s1 = "ABCDGH";
 * std::string s2 = "AEDFHR";
 * std::string lcs = algorithms::getLongestCommonSubsequence(s1, s2);
 * // lcs is "ADH"
 */
std::string getLongestCommonSubsequence(const std::string& s1, const std::string& s2);

} // namespace algorithms

#endif // ALGORITHMS_DP_ALGORITHMS_H