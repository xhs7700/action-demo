#ifndef ALGORITHMS_STRING_ALGORITHMS_H
#define ALGORITHMS_STRING_ALGORITHMS_H

#include <vector>
#include <string>

namespace algorithms {

/**
 * KMP字符串匹配算法
 * @param text 主字符串
 * @param pattern 模式字符串
 * @return 匹配位置的向量，如果未找到则为空
 */
std::vector<int> kmpSearch(const std::string& text, const std::string& pattern);

/**
 * 计算KMP算法的前缀表（部分匹配表）
 * @param pattern 模式字符串
 * @return 前缀表
 */
std::vector<int> computePrefixTable(const std::string& pattern);

} // namespace algorithms

#endif // ALGORITHMS_STRING_ALGORITHMS_H
