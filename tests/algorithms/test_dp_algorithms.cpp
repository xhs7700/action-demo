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

// ========== 新增：knapsack01异常测试 ==========

// 测试0-1背包 - weights和values大小不一致
TEST(Knapsack01Test, MismatchedArraySizes) {
    std::vector<int> weights = {1, 2, 3};
    std::vector<int> values = {10, 20};  // 少一个元素
    int capacity = 5;

    EXPECT_THROW(algorithms::knapsack01(weights, values, capacity), std::invalid_argument);
}

// 测试0-1背包 - 负数容量
TEST(Knapsack01Test, NegativeCapacity) {
    std::vector<int> weights = {1, 2, 3};
    std::vector<int> values = {10, 20, 30};
    int capacity = -5;

    EXPECT_THROW(algorithms::knapsack01(weights, values, capacity), std::invalid_argument);
}

// 测试0-1背包 - 容量过大
TEST(Knapsack01Test, ExcessiveCapacity) {
    std::vector<int> weights = {1, 2};
    std::vector<int> values = {10, 20};
    int capacity = 100001;  // 超过100000

    EXPECT_THROW(algorithms::knapsack01(weights, values, capacity), std::invalid_argument);
}

// ========== 新增：knapsack01边界测试 ==========

// 测试0-1背包 - 所有物品都太重
TEST(Knapsack01Test, AllItemsTooHeavy) {
    std::vector<int> weights = {10, 20, 30};
    std::vector<int> values = {100, 200, 300};
    int capacity = 5;  // 比最轻的物品还小

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 0);  // 一个物品都放不进去
}

// 测试0-1背包 - 所有物品都能放入
TEST(Knapsack01Test, AllItemsFit) {
    std::vector<int> weights = {1, 2, 3};
    std::vector<int> values = {10, 20, 30};
    int capacity = 100;  // 容量非常大

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 60);  // 所有物品价值之和
}

// 测试0-1背包 - 恰好等于容量
TEST(Knapsack01Test, ExactCapacity) {
    std::vector<int> weights = {2, 3, 5};
    std::vector<int> values = {10, 15, 25};
    int capacity = 5;  // 恰好能放下最重的物品

    int result = algorithms::knapsack01(weights, values, capacity);
    EXPECT_EQ(result, 25);  // 选择重量为5的物品
}

// ========== 新增：longestCommonSubsequence边界测试 ==========

// 测试LCS - 两个都是空字符串
TEST(LongestCommonSubsequenceTest, BothEmptyStrings) {
    std::string s1 = "";
    std::string s2 = "";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 0);
}

// 测试LCS - 单字符相同
TEST(LongestCommonSubsequenceTest, SingleCharacterMatch) {
    std::string s1 = "A";
    std::string s2 = "A";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 1);
}

// 测试LCS - 单字符不同
TEST(LongestCommonSubsequenceTest, SingleCharacterNoMatch) {
    std::string s1 = "A";
    std::string s2 = "B";

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 0);
}

// 测试LCS - 一个是另一个的子序列
TEST(LongestCommonSubsequenceTest, OneIsSubsequence) {
    std::string s1 = "ABC";
    std::string s2 = "AEBFCG";  // s1是s2的子序列

    int result = algorithms::longestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, 3);
}

// 测试getLCS - 两个都是空字符串
TEST(GetLongestCommonSubsequenceTest, BothEmptyStrings) {
    std::string s1 = "";
    std::string s2 = "";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "");
}

// 测试getLCS - 单字符相同
TEST(GetLongestCommonSubsequenceTest, SingleCharacterMatch) {
    std::string s1 = "X";
    std::string s2 = "X";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "X");
}

// 测试getLCS - 单字符不同
TEST(GetLongestCommonSubsequenceTest, SingleCharacterNoMatch) {
    std::string s1 = "X";
    std::string s2 = "Y";

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "");
}

// 测试getLCS - 一个是另一个的子序列
TEST(GetLongestCommonSubsequenceTest, OneIsSubsequence) {
    std::string s1 = "ACE";
    std::string s2 = "ABCDE";  // s1是s2的子序列

    std::string result = algorithms::getLongestCommonSubsequence(s1, s2);
    EXPECT_EQ(result, "ACE");
}