#include <gtest/gtest.h>
#include "algorithms/string_algorithms.h"
#include <vector>
#include <string>

// 测试KMP搜索 - 找到单个匹配
TEST(KMPSearchTest, SingleMatch) {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "ABABCABAB";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 10);
}

// 测试KMP搜索 - 找到多个匹配
TEST(KMPSearchTest, MultipleMatches) {
    std::string text = "AAAAA";
    std::string pattern = "AA";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 1);
    EXPECT_EQ(result[2], 2);
    EXPECT_EQ(result[3], 3);
}

// 测试KMP搜索 - 未找到匹配
TEST(KMPSearchTest, NoMatch) {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "XYZ";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_TRUE(result.empty());
}

// 测试KMP搜索 - 空模式串
TEST(KMPSearchTest, EmptyPattern) {
    std::string text = "ABABDABACDABABCABAB";
    std::string pattern = "";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_TRUE(result.empty());
}

// 测试KMP搜索 - 空文本
TEST(KMPSearchTest, EmptyText) {
    std::string text = "";
    std::string pattern = "ABAB";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_TRUE(result.empty());
}

// 测试KMP搜索 - 模式串比文本长
TEST(KMPSearchTest, PatternLongerThanText) {
    std::string text = "AB";
    std::string pattern = "ABAB";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_TRUE(result.empty());
}

// 测试KMP搜索 - 模式串等于文本
TEST(KMPSearchTest, PatternEqualsText) {
    std::string text = "ABAB";
    std::string pattern = "ABAB";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

// 测试KMP搜索 - 重叠匹配
TEST(KMPSearchTest, OverlappingMatches) {
    std::string text = "AAA";
    std::string pattern = "AAA";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_EQ(result.size(), 1);
    EXPECT_EQ(result[0], 0);
}

// 测试KMP搜索 - 边界匹配
TEST(KMPSearchTest, BoundaryMatches) {
    std::string text = "ABCABCD";
    std::string pattern = "ABC";

    std::vector<int> result = algorithms::kmpSearch(text, pattern);

    EXPECT_EQ(result.size(), 2);
    EXPECT_EQ(result[0], 0);
    EXPECT_EQ(result[1], 3);
}

// 测试前缀表计算
TEST(ComputePrefixTableTest, BasicPrefixTable) {
    std::string pattern = "ABABACA";

    std::vector<int> result = algorithms::computePrefixTable(pattern);

    EXPECT_EQ(result.size(), 7);
    EXPECT_EQ(result[0], 0); // A
    EXPECT_EQ(result[1], 0); // B
    EXPECT_EQ(result[2], 1); // A
    EXPECT_EQ(result[3], 2); // B
    EXPECT_EQ(result[4], 3); // A
    EXPECT_EQ(result[5], 0); // C
    EXPECT_EQ(result[6], 1); // A
}

// 测试前缀表计算 - 全重复字符
TEST(ComputePrefixTableTest, RepeatingPattern) {
    std::string pattern = "AAAA";

    std::vector<int> result = algorithms::computePrefixTable(pattern);

    EXPECT_EQ(result.size(), 4);
    EXPECT_EQ(result[0], 0); // A
    EXPECT_EQ(result[1], 1); // A
    EXPECT_EQ(result[2], 2); // A
    EXPECT_EQ(result[3], 3); // A
}

// 测试前缀表计算 - 无重复字符
TEST(ComputePrefixTableTest, NoRepeatingPattern) {
    std::string pattern = "ABCDE";

    std::vector<int> result = algorithms::computePrefixTable(pattern);

    EXPECT_EQ(result.size(), 5);
    for (int val : result) {
        EXPECT_EQ(val, 0);
    }
}
