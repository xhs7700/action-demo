#ifndef ALGORITHMS_STRING_ALGORITHMS_H
#define ALGORITHMS_STRING_ALGORITHMS_H

#include <vector>
#include <string>

namespace algorithms {

/**
 * @brief 使用KMP算法在文本中查找所有模式字符串的出现位置
 * 
 * KMP（Knuth-Morris-Pratt）算法是一种高效的字符串匹配算法，
 * 通过预处理模式串构建部分匹配表，避免在匹配失败时回退主串指针，
 * 从而提高查找效率。
 * 
 * @param text 主字符串（待搜索的文本）
 * @param pattern 模式字符串（要查找的子串）
 * @return 包含所有匹配位置起始索引的向量，如果未找到则返回空向量
 * 
 * @note 时间复杂度: O(n + m)，其中 n 是文本长度，m 是模式长度
 * @note 空间复杂度: O(m)（存储前缀表）
 * @note 特点: 不会回退主串指针，适合处理大文本
 * 
 * @example
 * std::string text = "ABABDABACDABABCABAB";
 * std::string pattern = "ABABCABAB";
 * std::vector<int> positions = algorithms::kmpSearch(text, pattern);
 * // positions contains {10}
 * 
 * @example
 * std::string text = "aaaa";
 * std::string pattern = "aa";
 * std::vector<int> positions = algorithms::kmpSearch(text, pattern);
 * // positions contains {0, 1, 2} (overlapping matches)
 */
std::vector<int> kmpSearch(const std::string& text, const std::string& pattern);

/**
 * @brief 计算KMP算法使用的前缀表（部分匹配表）
 * 
 * 前缀表记录了模式串每个位置之前的子串中，最长相等前后缀的长度。
 * 当匹配失败时，使用前缀表确定模式串应该移动到的位置，避免重复比较。
 * 
 * @param pattern 模式字符串
 * @return 前缀表向量，长度等于模式串长度
 * 
 * @note 时间复杂度: O(m)，其中 m 是模式长度
 * @note 空间复杂度: O(m)
 * 
 * @example
 * std::string pattern = "ABABCABAB";
 * std::vector<int> prefix = algorithms::computePrefixTable(pattern);
 * // prefix is {0, 0, 1, 2, 0, 1, 2, 3, 4}
 */
std::vector<int> computePrefixTable(const std::string& pattern);

} // namespace algorithms

#endif // ALGORITHMS_STRING_ALGORITHMS_H