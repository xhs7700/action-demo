#include <gtest/gtest.h>
#include "data_structures/skip_list.h"
#include <string>
#include <climits>
#include <algorithm>

// Test Skip List - Basic Operations
TEST(SkipListTest, BasicOperations) {
    data_structures::SkipList<int> skipList;
    
    EXPECT_TRUE(skipList.empty());
    EXPECT_EQ(skipList.size(), 0);
    
    skipList.insert(10);
    EXPECT_FALSE(skipList.empty());
    EXPECT_EQ(skipList.size(), 1);
    EXPECT_TRUE(skipList.search(10));
}

// Test Skip List - Insert and Search
TEST(SkipListTest, InsertAndSearch) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(5);
    skipList.insert(3);
    skipList.insert(7);
    skipList.insert(1);
    skipList.insert(9);
    
    EXPECT_EQ(skipList.size(), 5);
    
    EXPECT_TRUE(skipList.search(5));
    EXPECT_TRUE(skipList.search(3));
    EXPECT_TRUE(skipList.search(7));
    EXPECT_TRUE(skipList.search(1));
    EXPECT_TRUE(skipList.search(9));
    EXPECT_FALSE(skipList.search(10));
    EXPECT_FALSE(skipList.search(0));
}

// Test Skip List - Remove Elements
TEST(SkipListTest, RemoveElements) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(10);
    skipList.insert(5);
    skipList.insert(15);
    skipList.insert(3);
    skipList.insert(7);
    
    EXPECT_EQ(skipList.size(), 5);
    
    EXPECT_TRUE(skipList.remove(3));
    EXPECT_EQ(skipList.size(), 4);
    EXPECT_FALSE(skipList.search(3));
    
    EXPECT_TRUE(skipList.remove(10));
    EXPECT_EQ(skipList.size(), 3);
    EXPECT_FALSE(skipList.search(10));
    
    EXPECT_FALSE(skipList.remove(100)); // Non-existent element
    EXPECT_EQ(skipList.size(), 3);
}

// Test Skip List - Duplicate Handling
TEST(SkipListTest, DuplicateHandling) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(10);
    skipList.insert(10);
    skipList.insert(10);
    
    EXPECT_EQ(skipList.size(), 1); // Duplicates not inserted
    EXPECT_TRUE(skipList.search(10));
}

// Test Skip List - Clear
TEST(SkipListTest, Clear) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(1);
    skipList.insert(2);
    skipList.insert(3);
    
    EXPECT_EQ(skipList.size(), 3);
    
    skipList.clear();
    
    EXPECT_TRUE(skipList.empty());
    EXPECT_EQ(skipList.size(), 0);
    EXPECT_FALSE(skipList.search(1));
}

// Test Skip List - Empty List Operations
TEST(SkipListTest, EmptyListOperations) {
    data_structures::SkipList<int> skipList;
    
    EXPECT_FALSE(skipList.search(10));
    EXPECT_FALSE(skipList.remove(10));
    EXPECT_TRUE(skipList.empty());
}

// Test Skip List - Single Element
TEST(SkipListTest, SingleElement) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(42);
    
    EXPECT_EQ(skipList.size(), 1);
    EXPECT_TRUE(skipList.search(42));
    
    EXPECT_TRUE(skipList.remove(42));
    EXPECT_TRUE(skipList.empty());
    EXPECT_FALSE(skipList.search(42));
}

// Test Skip List - Sequential Insertion
TEST(SkipListTest, SequentialInsertion) {
    data_structures::SkipList<int> skipList;
    
    // Insert in ascending order
    for (int i = 1; i <= 20; i++) {
        skipList.insert(i);
    }
    
    EXPECT_EQ(skipList.size(), 20);
    
    // Verify all elements
    for (int i = 1; i <= 20; i++) {
        EXPECT_TRUE(skipList.search(i));
    }
}

// Test Skip List - Random Insertion
TEST(SkipListTest, RandomInsertion) {
    data_structures::SkipList<int> skipList;
    
    std::vector<int> values = {15, 3, 9, 1, 12, 7, 20, 5, 18, 2};
    
    for (int val : values) {
        skipList.insert(val);
    }
    
    EXPECT_EQ(skipList.size(), values.size());
    
    for (int val : values) {
        EXPECT_TRUE(skipList.search(val));
    }
}

// Test Skip List - Remove All Elements
TEST(SkipListTest, RemoveAllElements) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(1);
    skipList.insert(2);
    skipList.insert(3);
    skipList.insert(4);
    skipList.insert(5);
    
    EXPECT_EQ(skipList.size(), 5);
    
    EXPECT_TRUE(skipList.remove(3));
    EXPECT_TRUE(skipList.remove(1));
    EXPECT_TRUE(skipList.remove(5));
    EXPECT_TRUE(skipList.remove(2));
    EXPECT_TRUE(skipList.remove(4));
    
    EXPECT_TRUE(skipList.empty());
    EXPECT_EQ(skipList.size(), 0);
}

// Test Skip List - String Type
TEST(SkipListTest, StringType) {
    data_structures::SkipList<std::string> skipList;
    
    skipList.insert("dog");
    skipList.insert("cat");
    skipList.insert("bird");
    skipList.insert("zebra");
    skipList.insert("ant");
    
    EXPECT_EQ(skipList.size(), 5);
    
    EXPECT_TRUE(skipList.search("dog"));
    EXPECT_TRUE(skipList.search("ant"));
    EXPECT_FALSE(skipList.search("elephant"));
    
    EXPECT_TRUE(skipList.remove("dog"));
    EXPECT_FALSE(skipList.search("dog"));
    EXPECT_EQ(skipList.size(), 4);
}

// Test Skip List - Large Dataset
TEST(SkipListTest, LargeDataset) {
    data_structures::SkipList<int> skipList;
    
    // Insert 100 elements
    for (int i = 1; i <= 100; i++) {
        skipList.insert(i);
    }
    
    EXPECT_EQ(skipList.size(), 100);
    
    // Verify all elements present
    for (int i = 1; i <= 100; i++) {
        EXPECT_TRUE(skipList.search(i));
    }
    
    // Remove some elements (odd numbers from 1 to 99)
    for (int i = 1; i <= 99; i += 2) {
        EXPECT_TRUE(skipList.remove(i));
    }
    
    EXPECT_EQ(skipList.size(), 50);
    
    // Verify removed elements are gone (odd numbers)
    for (int i = 1; i <= 99; i += 2) {
        EXPECT_FALSE(skipList.search(i));
    }
    
    // Verify remaining elements still present
    for (int i = 2; i <= 100; i += 2) {
        EXPECT_TRUE(skipList.search(i));
    }
}

// Test Skip List - Max Level
TEST(SkipListTest, MaxLevel) {
    data_structures::SkipList<int> skipList;
    
    EXPECT_EQ(skipList.maxLevel(), 0);
    
    // Insert multiple elements to increase level
    for (int i = 1; i <= 50; i++) {
        skipList.insert(i);
    }
    
    // Max level should have increased
    EXPECT_GT(skipList.maxLevel(), 0);
}

// Test Skip List - Search in Empty List
TEST(SkipListTest, SearchInEmptyList) {
    data_structures::SkipList<int> skipList;
    
    EXPECT_FALSE(skipList.search(1));
    EXPECT_FALSE(skipList.search(100));
    EXPECT_FALSE(skipList.search(-50));
}

// Test Skip List - Mixed Operations
TEST(SkipListTest, MixedOperations) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(5);
    skipList.insert(10);
    EXPECT_TRUE(skipList.search(5));
    
    skipList.insert(3);
    skipList.remove(5);
    EXPECT_FALSE(skipList.search(5));
    EXPECT_TRUE(skipList.search(10));
    EXPECT_TRUE(skipList.search(3));
    
    skipList.insert(7);
    skipList.insert(1);
    EXPECT_EQ(skipList.size(), 4);
    
    skipList.clear();
    EXPECT_TRUE(skipList.empty());
}

// ========== 新增：边界测试 ==========

// 测试INT_MAX和INT_MIN值
TEST(SkipListTest, ExtremeValues) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(INT_MAX);
    skipList.insert(INT_MIN);
    skipList.insert(0);
    skipList.insert(-1000);
    skipList.insert(1000);
    
    EXPECT_EQ(skipList.size(), 5);
    
    EXPECT_TRUE(skipList.search(INT_MAX));
    EXPECT_TRUE(skipList.search(INT_MIN));
    EXPECT_TRUE(skipList.search(0));
    EXPECT_TRUE(skipList.search(-1000));
    EXPECT_TRUE(skipList.search(1000));
}

// 测试删除不存在元素
TEST(SkipListTest, RemoveNonExistent) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(1);
    skipList.insert(2);
    skipList.insert(3);
    
    EXPECT_EQ(skipList.size(), 3);
    
    EXPECT_FALSE(skipList.remove(100));
    EXPECT_EQ(skipList.size(), 3);
    
    EXPECT_FALSE(skipList.remove(0));
    EXPECT_EQ(skipList.size(), 3);
}

// 测试重复元素插入和删除
TEST(SkipListTest, DuplicateInsertAndRemove) {
    data_structures::SkipList<int> skipList;
    
    skipList.insert(42);
    skipList.insert(42);
    skipList.insert(42);
    
    EXPECT_EQ(skipList.size(), 1);
    EXPECT_TRUE(skipList.search(42));
    
    EXPECT_TRUE(skipList.remove(42));
    EXPECT_EQ(skipList.size(), 0);
    EXPECT_FALSE(skipList.search(42));
    
    // 再次删除应该失败
    EXPECT_FALSE(skipList.remove(42));
}

// ========== 新增：压力测试 ==========

// 测试大规模插入（1000个元素）
TEST(SkipListTest, LargeScaleInsert) {
    data_structures::SkipList<int> skipList;
    
    // 插入1000个元素
    for (int i = 0; i < 1000; i++) {
        skipList.insert(i);
    }
    
    EXPECT_EQ(skipList.size(), 1000);
    
    // 验证部分元素
    EXPECT_TRUE(skipList.search(0));
    EXPECT_TRUE(skipList.search(500));
    EXPECT_TRUE(skipList.search(999));
    EXPECT_FALSE(skipList.search(1000));
    EXPECT_FALSE(skipList.search(-1));
}

// 测试大规模随机删除
TEST(SkipListTest, LargeScaleRandomRemove) {
    data_structures::SkipList<int> skipList;
    
    // 插入500个元素
    for (int i = 0; i < 500; i++) {
        skipList.insert(i);
    }
    
    EXPECT_EQ(skipList.size(), 500);
    
    // 删除一半（偶数）
    for (int i = 0; i < 500; i += 2) {
        EXPECT_TRUE(skipList.remove(i));
    }
    
    EXPECT_EQ(skipList.size(), 250);
    
    // 验证偶数已删除
    for (int i = 0; i < 500; i += 2) {
        EXPECT_FALSE(skipList.search(i));
    }
    
    // 验证奇数仍存在
    for (int i = 1; i < 500; i += 2) {
        EXPECT_TRUE(skipList.search(i));
    }
}

// 测试删除后跳表仍然正确
TEST(SkipListTest, CorrectnessAfterRemove) {
    data_structures::SkipList<int> skipList;
    
    // 插入100个元素
    for (int i = 1; i <= 100; i++) {
        skipList.insert(i);
    }
    
    // 随机删除一些元素
    std::vector<int> toRemove = {5, 15, 25, 35, 45, 55, 65, 75, 85, 95};
    for (int val : toRemove) {
        EXPECT_TRUE(skipList.remove(val));
    }
    
    EXPECT_EQ(skipList.size(), 90);
    
    // 验证删除的元素不存在
    for (int val : toRemove) {
        EXPECT_FALSE(skipList.search(val));
    }
    
    // 验证其他元素仍存在
    for (int i = 1; i <= 100; i++) {
        bool shouldExist = (std::find(toRemove.begin(), toRemove.end(), i) == toRemove.end());
        EXPECT_EQ(skipList.search(i), shouldExist);
    }
}

// ========== 新增：性能特性测试（可选） ==========

// 测试层数分布合理性（大部分节点层数较低）
TEST(SkipListTest, LevelDistribution) {
    data_structures::SkipList<int> skipList;
    
    // 插入大量元素
    for (int i = 0; i < 200; i++) {
        skipList.insert(i);
    }
    
    EXPECT_EQ(skipList.size(), 200);
    
    // 验证maxLevel合理（应该远小于元素数量）
    // 对于200个元素，理论上maxLevel约为log2(200) ≈ 7-8
    EXPECT_LE(skipList.maxLevel(), 15);
    EXPECT_GT(skipList.maxLevel(), 0);
}

// 测试交替插入删除操作
TEST(SkipListTest, AlternatingInsertRemove) {
    data_structures::SkipList<int> skipList;
    
    for (int i = 0; i < 100; i++) {
        skipList.insert(i);
        skipList.insert(i + 100);
        
        EXPECT_TRUE(skipList.remove(i));
    }
    
    EXPECT_EQ(skipList.size(), 100);
    
    // 验证0-99已被删除
    for (int i = 0; i < 100; i++) {
        EXPECT_FALSE(skipList.search(i));
    }
    
    // 验证100-199仍存在
    for (int i = 100; i < 200; i++) {
        EXPECT_TRUE(skipList.search(i));
    }
}

// 测试连续插入相同元素
TEST(SkipListTest, ConsecutiveDuplicateInserts) {
    data_structures::SkipList<int> skipList;
    
    for (int i = 0; i < 50; i++) {
        skipList.insert(42);
    }
    
    EXPECT_EQ(skipList.size(), 1);
    EXPECT_TRUE(skipList.search(42));
}

// 测试清空后重新使用
TEST(SkipListTest, ReuseAfterClear) {
    data_structures::SkipList<int> skipList;
    
    // 第一轮
    for (int i = 0; i < 50; i++) {
        skipList.insert(i);
    }
    EXPECT_EQ(skipList.size(), 50);
    
    skipList.clear();
    EXPECT_EQ(skipList.size(), 0);
    EXPECT_TRUE(skipList.empty());
    
    // 第二轮
    for (int i = 100; i < 150; i++) {
        skipList.insert(i);
    }
    EXPECT_EQ(skipList.size(), 50);
    
    // 验证第一轮元素不存在
    EXPECT_FALSE(skipList.search(25));
    
    // 验证第二轮元素存在
    EXPECT_TRUE(skipList.search(125));
}