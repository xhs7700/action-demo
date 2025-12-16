#include <gtest/gtest.h>
#include "data_structures/btreemap.h"
#include <string>
#include <climits>

// ==================== 基本操作测试 ====================

TEST(BTreeMapTest, BasicOperations) {
    data_structures::BTreeMap<int, std::string> map;
    
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0);
    
    map.insert(10, "ten");
    EXPECT_FALSE(map.empty());
    EXPECT_EQ(map.size(), 1);
    EXPECT_TRUE(map.contains(10));
    
    auto value = map.find(10);
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), "ten");
}

TEST(BTreeMapTest, EmptyMapOperations) {
    data_structures::BTreeMap<int, int> map;
    
    EXPECT_FALSE(map.contains(10));
    EXPECT_FALSE(map.find(10).has_value());
    EXPECT_FALSE(map.remove(10));
    EXPECT_FALSE(map.findMin().has_value());
    EXPECT_FALSE(map.findMax().has_value());
}

// ==================== 插入测试 ====================

TEST(BTreeMapTest, InsertMultipleElements) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(5, "five");
    map.insert(10, "ten");
    map.insert(15, "fifteen");
    map.insert(20, "twenty");
    
    EXPECT_EQ(map.size(), 4);
    EXPECT_TRUE(map.contains(5));
    EXPECT_TRUE(map.contains(10));
    EXPECT_TRUE(map.contains(15));
    EXPECT_TRUE(map.contains(20));
}

TEST(BTreeMapTest, InsertDuplicateKey) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(10, "ten");
    EXPECT_EQ(map.size(), 1);
    
    // 插入重复键应该更新值
    map.insert(10, "TEN");
    EXPECT_EQ(map.size(), 1);
    
    auto value = map.find(10);
    ASSERT_TRUE(value.has_value());
    EXPECT_EQ(value.value(), "TEN");
}

TEST(BTreeMapTest, InsertTriggersSplit) {
    data_structures::BTreeMap<int, int> map;
    
    // 插入足够多的元素以触发节点分裂
    for (int i = 1; i <= 10; i++) {
        map.insert(i, i * 10);
    }
    
    EXPECT_EQ(map.size(), 10);
    
    // 验证所有元素都能找到
    for (int i = 1; i <= 10; i++) {
        auto value = map.find(i);
        ASSERT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), i * 10);
    }
}

TEST(BTreeMapTest, InsertAscendingOrder) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 1; i <= 50; i++) {
        map.insert(i, i);
    }
    
    EXPECT_EQ(map.size(), 50);
    
    for (int i = 1; i <= 50; i++) {
        EXPECT_TRUE(map.contains(i));
    }
}

TEST(BTreeMapTest, InsertDescendingOrder) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 50; i >= 1; i--) {
        map.insert(i, i);
    }
    
    EXPECT_EQ(map.size(), 50);
    
    for (int i = 1; i <= 50; i++) {
        EXPECT_TRUE(map.contains(i));
    }
}

TEST(BTreeMapTest, InsertMoveSemantics) {
    data_structures::BTreeMap<std::string, std::string> map;
    
    std::string key1 = "key1";
    std::string val1 = "value1";
    std::string key2 = "key2";
    std::string val2 = "value2";
    
    map.insert(std::move(key1), std::move(val1));
    map.insert(std::move(key2), std::move(val2));
    
    EXPECT_EQ(map.size(), 2);
    EXPECT_TRUE(map.contains("key1"));
    EXPECT_TRUE(map.contains("key2"));
}

// ==================== 查找测试 ====================

TEST(BTreeMapTest, FindExistingKeys) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(5, "five");
    map.insert(10, "ten");
    map.insert(15, "fifteen");
    
    auto val5 = map.find(5);
    ASSERT_TRUE(val5.has_value());
    EXPECT_EQ(val5.value(), "five");
    
    auto val10 = map.find(10);
    ASSERT_TRUE(val10.has_value());
    EXPECT_EQ(val10.value(), "ten");
    
    auto val15 = map.find(15);
    ASSERT_TRUE(val15.has_value());
    EXPECT_EQ(val15.value(), "fifteen");
}

TEST(BTreeMapTest, FindNonExistingKeys) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(10, "ten");
    
    EXPECT_FALSE(map.find(5).has_value());
    EXPECT_FALSE(map.find(15).has_value());
    EXPECT_FALSE(map.find(100).has_value());
}

TEST(BTreeMapTest, ContainsTest) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 0; i < 20; i += 2) {
        map.insert(i, i);
    }
    
    for (int i = 0; i < 20; i++) {
        if (i % 2 == 0) {
            EXPECT_TRUE(map.contains(i));
        } else {
            EXPECT_FALSE(map.contains(i));
        }
    }
}

// ==================== 删除测试 ====================

TEST(BTreeMapTest, RemoveSingleElement) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(10, "ten");
    EXPECT_EQ(map.size(), 1);
    
    EXPECT_TRUE(map.remove(10));
    EXPECT_EQ(map.size(), 0);
    EXPECT_FALSE(map.contains(10));
}

TEST(BTreeMapTest, RemoveNonExistingElement) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(10, 10);
    EXPECT_EQ(map.size(), 1);
    
    EXPECT_FALSE(map.remove(5));
    EXPECT_EQ(map.size(), 1);
}

TEST(BTreeMapTest, RemoveMultipleElements) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 1; i <= 20; i++) {
        map.insert(i, i);
    }
    
    EXPECT_EQ(map.size(), 20);
    
    // 删除一半元素
    for (int i = 1; i <= 10; i++) {
        EXPECT_TRUE(map.remove(i));
    }
    
    EXPECT_EQ(map.size(), 10);
    
    // 验证删除的元素不存在
    for (int i = 1; i <= 10; i++) {
        EXPECT_FALSE(map.contains(i));
    }
    
    // 验证剩余元素存在
    for (int i = 11; i <= 20; i++) {
        EXPECT_TRUE(map.contains(i));
    }
}

TEST(BTreeMapTest, RemoveTriggersRebalance) {
    data_structures::BTreeMap<int, int> map;
    
    // 插入足够多的元素
    for (int i = 1; i <= 30; i++) {
        map.insert(i, i);
    }
    
    // 删除大部分元素
    for (int i = 1; i <= 25; i++) {
        EXPECT_TRUE(map.remove(i));
    }
    
    EXPECT_EQ(map.size(), 5);
    
    // 验证剩余元素
    for (int i = 26; i <= 30; i++) {
        EXPECT_TRUE(map.contains(i));
    }
}

// ==================== 清空测试 ====================

TEST(BTreeMapTest, ClearEmptyMap) {
    data_structures::BTreeMap<int, int> map;
    
    map.clear();
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0);
}

TEST(BTreeMapTest, ClearNonEmptyMap) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 1; i <= 10; i++) {
        map.insert(i, i);
    }
    
    EXPECT_EQ(map.size(), 10);
    
    map.clear();
    
    EXPECT_TRUE(map.empty());
    EXPECT_EQ(map.size(), 0);
    
    for (int i = 1; i <= 10; i++) {
        EXPECT_FALSE(map.contains(i));
    }
}

// ==================== 最小/最大值测试 ====================

TEST(BTreeMapTest, FindMinMax) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(10, "ten");
    map.insert(5, "five");
    map.insert(20, "twenty");
    map.insert(1, "one");
    map.insert(30, "thirty");
    
    auto minPair = map.findMin();
    ASSERT_TRUE(minPair.has_value());
    EXPECT_EQ(minPair.value().first, 1);
    EXPECT_EQ(minPair.value().second, "one");
    
    auto maxPair = map.findMax();
    ASSERT_TRUE(maxPair.has_value());
    EXPECT_EQ(maxPair.value().first, 30);
    EXPECT_EQ(maxPair.value().second, "thirty");
}

TEST(BTreeMapTest, FindMinMaxAfterRemove) {
    data_structures::BTreeMap<int, int> map;
    
    for (int i = 1; i <= 10; i++) {
        map.insert(i, i);
    }
    
    map.remove(1);
    map.remove(10);
    
    auto minPair = map.findMin();
    ASSERT_TRUE(minPair.has_value());
    EXPECT_EQ(minPair.value().first, 2);
    
    auto maxPair = map.findMax();
    ASSERT_TRUE(maxPair.has_value());
    EXPECT_EQ(maxPair.value().first, 9);
}

// ==================== 访问操作测试 ====================

TEST(BTreeMapTest, AtOperator) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(10, "ten");
    map.insert(20, "twenty");
    
    EXPECT_EQ(map.at(10), "ten");
    EXPECT_EQ(map.at(20), "twenty");
    
    // 修改值
    map.at(10) = "TEN";
    EXPECT_EQ(map.at(10), "TEN");
}

TEST(BTreeMapTest, AtOperatorThrowsException) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(10, 10);
    
    EXPECT_THROW(map.at(5), std::out_of_range);
    EXPECT_THROW(map.at(15), std::out_of_range);
}

TEST(BTreeMapTest, SubscriptOperator) {
    data_structures::BTreeMap<int, std::string> map;
    
    // 访问不存在的键应插入默认值
    map[10] = "ten";
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map[10], "ten");
    
    // 访问存在的键
    map[10] = "TEN";
    EXPECT_EQ(map.size(), 1);
    EXPECT_EQ(map[10], "TEN");
}

// ==================== 范围查询测试 ====================

TEST(BTreeMapTest, LowerBound) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(10, 10);
    map.insert(20, 20);
    map.insert(30, 30);
    map.insert(40, 40);
    
    auto result1 = map.lower_bound(10);
    ASSERT_TRUE(result1.has_value());
    EXPECT_EQ(result1.value().first, 10);
    
    auto result2 = map.lower_bound(15);
    ASSERT_TRUE(result2.has_value());
    EXPECT_EQ(result2.value().first, 20);
    
    auto result3 = map.lower_bound(40);
    ASSERT_TRUE(result3.has_value());
    EXPECT_EQ(result3.value().first, 40);
    
    auto result4 = map.lower_bound(50);
    EXPECT_FALSE(result4.has_value());
}

TEST(BTreeMapTest, UpperBound) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(10, 10);
    map.insert(20, 20);
    map.insert(30, 30);
    map.insert(40, 40);
    
    auto result1 = map.upper_bound(10);
    ASSERT_TRUE(result1.has_value());
    EXPECT_EQ(result1.value().first, 20);
    
    auto result2 = map.upper_bound(15);
    ASSERT_TRUE(result2.has_value());
    EXPECT_EQ(result2.value().first, 20);
    
    auto result3 = map.upper_bound(40);
    EXPECT_FALSE(result3.has_value());
}

// ==================== 迭代器测试 ====================

TEST(BTreeMapTest, IteratorBasic) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(5, 50);
    map.insert(3, 30);
    map.insert(7, 70);
    map.insert(1, 10);
    map.insert(9, 90);
    
    std::vector<int> keys;
    for (auto it = map.begin(); it != map.end(); ++it) {
        keys.push_back((*it).first);
    }
    
    // 迭代器应该按升序遍历
    std::vector<int> expected = {1, 3, 5, 7, 9};
    EXPECT_EQ(keys, expected);
}

TEST(BTreeMapTest, IteratorEmptyMap) {
    data_structures::BTreeMap<int, int> map;
    
    auto it = map.begin();
    EXPECT_EQ(it, map.end());
}

TEST(BTreeMapTest, RangeForLoop) {
    data_structures::BTreeMap<int, std::string> map;
    
    map.insert(1, "one");
    map.insert(2, "two");
    map.insert(3, "three");
    
    std::vector<int> keys;
    std::vector<std::string> values;
    
    for (const auto& pair : map) {
        keys.push_back(pair.first);
        values.push_back(pair.second);
    }
    
    EXPECT_EQ(keys, std::vector<int>({1, 2, 3}));
    EXPECT_EQ(values, std::vector<std::string>({"one", "two", "three"}));
}

TEST(BTreeMapTest, IteratorOrder) {
    data_structures::BTreeMap<int, int> map;
    
    // 插入随机顺序的元素
    std::vector<int> insertOrder = {15, 3, 8, 22, 1, 19, 5, 12, 7, 20};
    for (int key : insertOrder) {
        map.insert(key, key);
    }
    
    // 迭代应该返回有序序列
    std::vector<int> keys;
    for (const auto& pair : map) {
        keys.push_back(pair.first);
    }
    
    std::vector<int> expected = insertOrder;
    std::sort(expected.begin(), expected.end());
    EXPECT_EQ(keys, expected);
}

// ==================== 压力测试 ====================

TEST(BTreeMapTest, StressTestLargeDataset) {
    data_structures::BTreeMap<int, int> map;
    
    // 插入1000个元素
    for (int i = 0; i < 1000; i++) {
        map.insert(i, i * 2);
    }
    
    EXPECT_EQ(map.size(), 1000);
    
    // 验证所有元素
    for (int i = 0; i < 1000; i++) {
        auto value = map.find(i);
        ASSERT_TRUE(value.has_value());
        EXPECT_EQ(value.value(), i * 2);
    }
    
    // 删除一半元素
    for (int i = 0; i < 500; i++) {
        EXPECT_TRUE(map.remove(i));
    }
    
    EXPECT_EQ(map.size(), 500);
    
    // 验证剩余元素
    for (int i = 500; i < 1000; i++) {
        EXPECT_TRUE(map.contains(i));
    }
}

TEST(BTreeMapTest, StressTestRandomOperations) {
    data_structures::BTreeMap<int, int> map;
    
    // 随机插入
    std::vector<int> keys;
    for (int i = 0; i < 100; i++) {
        int key = i * 3 + 1;
        map.insert(key, key);
        keys.push_back(key);
    }
    
    EXPECT_EQ(map.size(), 100);
    
    // 验证所有键
    for (int key : keys) {
        EXPECT_TRUE(map.contains(key));
    }
    
    // 删除部分键
    for (size_t i = 0; i < keys.size() / 2; i++) {
        EXPECT_TRUE(map.remove(keys[i]));
    }
    
    EXPECT_EQ(map.size(), 50);
}

// ==================== 边界条件测试 ====================

TEST(BTreeMapTest, ExtremeValues) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(INT_MAX, 1);
    map.insert(INT_MIN, 2);
    map.insert(0, 3);
    
    EXPECT_EQ(map.size(), 3);
    
    auto minPair = map.findMin();
    ASSERT_TRUE(minPair.has_value());
    EXPECT_EQ(minPair.value().first, INT_MIN);
    
    auto maxPair = map.findMax();
    ASSERT_TRUE(maxPair.has_value());
    EXPECT_EQ(maxPair.value().first, INT_MAX);
}

TEST(BTreeMapTest, StringKeys) {
    data_structures::BTreeMap<std::string, int> map;
    
    map.insert("apple", 1);
    map.insert("banana", 2);
    map.insert("cherry", 3);
    map.insert("date", 4);
    
    EXPECT_EQ(map.size(), 4);
    
    auto minPair = map.findMin();
    ASSERT_TRUE(minPair.has_value());
    EXPECT_EQ(minPair.value().first, "apple");
    
    auto maxPair = map.findMax();
    ASSERT_TRUE(maxPair.has_value());
    EXPECT_EQ(maxPair.value().first, "date");
}

TEST(BTreeMapTest, SingleElementOperations) {
    data_structures::BTreeMap<int, int> map;
    
    map.insert(42, 100);
    EXPECT_EQ(map.size(), 1);
    
    auto minPair = map.findMin();
    auto maxPair = map.findMax();
    
    ASSERT_TRUE(minPair.has_value());
    ASSERT_TRUE(maxPair.has_value());
    EXPECT_EQ(minPair.value().first, 42);
    EXPECT_EQ(maxPair.value().first, 42);
    
    auto it = map.begin();
    EXPECT_NE(it, map.end());
    EXPECT_EQ((*it).first, 42);
    ++it;
    EXPECT_EQ(it, map.end());
    
    map.remove(42);
    EXPECT_TRUE(map.empty());
}
