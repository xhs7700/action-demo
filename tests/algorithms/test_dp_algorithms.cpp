#include <gtest/gtest.h>
#include "algorithms/dp_algorithms.h"
#include <vector>
#include <string>

// 测试0-1背包 - 基本功能
TEST(Knapsack01Test, BasicFunctionality) {
    std::vector<int> weights = {1, 2, 3, 4, 5};
    std::vector<int> values = {1, 6, 10, 16, 25};
    int capacity = 7;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 31); // 选择物品5(25), 物品2(6)
}

// 测试0-1背包 - 空数组
TEST(Knapsack01Test, EmptyArrays) {
    std::vector<int> weights;
    std::vector<int> values;
    int capacity = 10;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 0);
}

// 测试0-1背包 - 容量为0
TEST(Knapsack01Test, ZeroCapacity) {
    std::vector<int> weights = {1, 2, 3};
    std::vector<int> values = {10, 20, 30};
    int capacity = 0;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 0);
}

// 测试0-1背包 - 单个物品
TEST(Knapsack01Test, SingleItem) {
    std::vector<int> weights = {5};
    std::vector<int> values = {10};
    int capacity = 5;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 10);
}

// 测试0-1背包 - 单个物品容量不足
TEST(Knapsack01Test, SingleItemInsufficientCapacity) {
    std::vector<int> weights = {5};
    std::vector<int> values = {10};
    int capacity = 3;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 0);
}

// 测试0-1背包 - 经典问题示例
TEST(Knapsack01Test, ClassicExample) {
    std::vector<int> weights = {2, 3, 4, 5};
    std::vector<int> values = {3, 4, 5, 6};
    int capacity = 8;

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 10); // 选择物品2(4)和物品4(6)
}

// 测试最长公共子序列长度 - 基本功能
TEST(LongestCommonSubsequenceTest, BasicFunctionality) {
    std::string s1 = "ABCBDAB";
    std::string s2 = "BDCABA";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 4); // "BCBA" 或 "BDAB" 等
}

// 测试最长公共子序列长度 - 空字符串
TEST(LongestCommonSubsequenceTest, EmptyStrings) {
    std::string s1 = "";
    std::string s2 = "ABC";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 0);
}

// 测试最长公共子序列长度 - 相同字符串
TEST(LongestCommonSubsequenceTest, IdenticalStrings) {
    std::string s1 = "ABC";
    std::string s2 = "ABC";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 3);
}

// 测试最长公共子序列长度 - 无公共字符
TEST(LongestCommonSubsequenceTest, NoCommonCharacters) {
    std::string s1 = "ABC";
    std::string s2 = "DEF";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 0);
}

// 测试最长公共子序列长度 - 一个字符的公共子序列
TEST(LongestCommonSubsequenceTest, SingleCharacter) {
    std::string s1 = "ABCD";
    std::string s2 = "EFGH";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 0);
}

// 测试获取最长公共子序列 - 基本功能
TEST(GetLongestCommonSubsequenceTest, BasicFunctionality) {
    std::string s1 = "ABCBDAB";
    std::string s2 = "BDCABA";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result.length(), 4);
    // 可能的答案: "BCBA", "BDAB", "BCAB", "BDAB"
    bool valid = (result == "BCBA" || result == "BDAB" || result == "BCAB");
    EXPECT_TRUE(valid);
}

// 测试获取最长公共子序列 - 空字符串
TEST(GetLongestCommonSubsequenceTest, EmptyStrings) {
    std::string s1 = "";
    std::string s2 = "ABC";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "");
}

// 测试获取最长公共子序列 - 相同字符串
TEST(GetLongestCommonSubsequenceTest, IdenticalStrings) {
    std::string s1 = "ABC";
    std::string s2 = "ABC";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "ABC");
}

// 测试获取最长公共子序列 - 无公共字符
TEST(GetLongestCommonSubsequenceTest, NoCommonCharacters) {
    std::string s1 = "ABC";
    std::string s2 = "DEF";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "");
}

// 测试获取最长公共子序列 - 经典示例
TEST(GetLongestCommonSubsequenceTest, ClassicExample) {
    std::string s1 = "AGGTAB";
    std::string s2 = "GXTXAYB";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result.length(), 4);
    // 可能的答案: "GTAB"
    EXPECT_EQ(result, "GTAB");
}
