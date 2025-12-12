#include "algorithms/string_algorithms.h"

namespace algorithms {

std::vector<int> computePrefixTable(const std::string& pattern) {
    int m = static_cast<int>(pattern.length());
    std::vector<int> prefixTable(m, 0);

    int len = 0; // length of the previous longest prefix suffix
    int i = 1;

    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            prefixTable[i] = len;
            i++;
        } else {
            if (len != 0) {
                len = prefixTable[len - 1];
            } else {
                prefixTable[i] = 0;
                i++;
            }
        }
    }

    return prefixTable;
}

std::vector<int> kmpSearch(const std::string& text, const std::string& pattern) {
    std::vector<int> result;
    int n = static_cast<int>(text.length());
    int m = static_cast<int>(pattern.length());

    if (m == 0) return result;

    std::vector<int> prefixTable = computePrefixTable(pattern);

    int i = 0; // index for text
    int j = 0; // index for pattern

    while (i < n) {
        if (pattern[j] == text[i]) {
            j++;
            i++;
        }

        if (j == m) {
            result.push_back(i - j);
            j = prefixTable[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = prefixTable[j - 1];
            } else {
                i++;
            }
        }
    }

    return result;
}

} // namespace algorithms
