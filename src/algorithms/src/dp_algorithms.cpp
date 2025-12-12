#include "algorithms/dp_algorithms.h"
#include <algorithm>

namespace algorithms {

int knapsack01(const std::vector<int>& weights, const std::vector<int>& values, int capacity) {
    int n = static_cast<int>(weights.size());
    if (n == 0 || capacity <= 0) return 0;

    // dp[i][w] 表示前i个物品，容量为w时的最大价值
    std::vector<std::vector<int>> dp(n + 1, std::vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (weights[i - 1] <= w) {
                dp[i][w] = std::max(dp[i - 1][w],
                                   dp[i - 1][w - weights[i - 1]] + values[i - 1]);
            } else {
                dp[i][w] = dp[i - 1][w];
            }
        }
    }

    return dp[n][capacity];
}

int longestCommonSubsequence(const std::string& s1, const std::string& s2) {
    int m = static_cast<int>(s1.length());
    int n = static_cast<int>(s2.length());

    if (m == 0 || n == 0) return 0;

    // dp[i][j] 表示s1[0..i-1]和s2[0..j-1]的最长公共子序列长度
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    return dp[m][n];
}

std::string getLongestCommonSubsequence(const std::string& s1, const std::string& s2) {
    int m = static_cast<int>(s1.length());
    int n = static_cast<int>(s2.length());

    if (m == 0 || n == 0) return "";

    // dp[i][j] 表示s1[0..i-1]和s2[0..j-1]的最长公共子序列长度
    std::vector<std::vector<int>> dp(m + 1, std::vector<int>(n + 1, 0));

    for (int i = 1; i <= m; i++) {
        for (int j = 1; j <= n; j++) {
            if (s1[i - 1] == s2[j - 1]) {
                dp[i][j] = dp[i - 1][j - 1] + 1;
            } else {
                dp[i][j] = std::max(dp[i - 1][j], dp[i][j - 1]);
            }
        }
    }

    // 重建LCS
    std::string lcs;
    int i = m, j = n;
    while (i > 0 && j > 0) {
        if (s1[i - 1] == s2[j - 1]) {
            lcs.push_back(s1[i - 1]);
            i--;
            j--;
        } else if (dp[i - 1][j] > dp[i][j - 1]) {
            i--;
        } else {
            j--;
        }
    }

    // 反转字符串
    std::reverse(lcs.begin(), lcs.end());
    return lcs;
}

} // namespace algorithms
