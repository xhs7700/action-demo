#include <gtest/gtest.h>
#include "data_structures/avl_tree.h"
#include <string>
#include <climits>
#include <cmath>

// Test AVL Tree - Basic Operations
TEST(AVLTreeTest, BasicOperations) {
    data_structures::AVLTree<int> tree;
    
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
    
    tree.insert(10);
    EXPECT_FALSE(tree.empty());
    EXPECT_EQ(tree.size(), 1);
    EXPECT_TRUE(tree.search(10));
}

// Test AVL Tree - Insert and Search
TEST(AVLTreeTest, InsertAndSearch) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    
    EXPECT_EQ(tree.size(), 5);
    
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(3));
    EXPECT_TRUE(tree.search(7));
    EXPECT_TRUE(tree.search(1));
    EXPECT_TRUE(tree.search(9));
    EXPECT_FALSE(tree.search(10));
    EXPECT_FALSE(tree.search(0));
}

// Test AVL Tree - Remove Elements
TEST(AVLTreeTest, RemoveElements) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(3);
    tree.insert(7);
    
    EXPECT_EQ(tree.size(), 5);
    
    EXPECT_TRUE(tree.remove(3));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_FALSE(tree.search(3));
    
    EXPECT_TRUE(tree.remove(10));
    EXPECT_EQ(tree.size(), 3);
    EXPECT_FALSE(tree.search(10));
    
    EXPECT_FALSE(tree.remove(100)); // Non-existent element
    EXPECT_EQ(tree.size(), 3);
}

// Test AVL Tree - Find Min and Max
TEST(AVLTreeTest, FindMinMax) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(20);
    tree.insert(1);
    tree.insert(30);
    
    auto minVal = tree.findMin();
    ASSERT_TRUE(minVal.has_value());
    EXPECT_EQ(minVal.value(), 1);
    
    auto maxVal = tree.findMax();
    ASSERT_TRUE(maxVal.has_value());
    EXPECT_EQ(maxVal.value(), 30);
}

// Test AVL Tree - In-order Traversal
TEST(AVLTreeTest, InorderTraversal) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(5);
    tree.insert(3);
    tree.insert(7);
    tree.insert(1);
    tree.insert(9);
    tree.insert(4);
    tree.insert(6);
    
    auto result = tree.inorderTraversal();
    
    EXPECT_EQ(result.size(), 7);
    // Should be in sorted order
    std::vector<int> expected = {1, 3, 4, 5, 6, 7, 9};
    EXPECT_EQ(result, expected);
}

// Test AVL Tree - Left-Left Rotation
TEST(AVLTreeTest, LeftLeftRotation) {
    data_structures::AVLTree<int> tree;
    
    // Insert in descending order to trigger LL rotation
    tree.insert(30);
    tree.insert(20);
    tree.insert(10);
    
    EXPECT_EQ(tree.size(), 3);
    
    // Tree should be balanced
    EXPECT_EQ(tree.height(), 2);
    
    // Verify all elements present
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(30));
    
    // Verify sorted order
    auto result = tree.inorderTraversal();
    std::vector<int> expected = {10, 20, 30};
    EXPECT_EQ(result, expected);
}

// Test AVL Tree - Right-Right Rotation
TEST(AVLTreeTest, RightRightRotation) {
    data_structures::AVLTree<int> tree;
    
    // Insert in ascending order to trigger RR rotation
    tree.insert(10);
    tree.insert(20);
    tree.insert(30);
    
    EXPECT_EQ(tree.size(), 3);
    
    // Tree should be balanced
    EXPECT_EQ(tree.height(), 2);
    
    // Verify all elements present
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(30));
}

// Test AVL Tree - Left-Right Rotation
TEST(AVLTreeTest, LeftRightRotation) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(30);
    tree.insert(10);
    tree.insert(20); // Triggers LR rotation
    
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(tree.height(), 2);
    
    // Verify all elements present
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(30));
}

// Test AVL Tree - Right-Left Rotation
TEST(AVLTreeTest, RightLeftRotation) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(30);
    tree.insert(20); // Triggers RL rotation
    
    EXPECT_EQ(tree.size(), 3);
    EXPECT_EQ(tree.height(), 2);
    
    // Verify all elements present
    EXPECT_TRUE(tree.search(10));
    EXPECT_TRUE(tree.search(20));
    EXPECT_TRUE(tree.search(30));
}

// Test AVL Tree - Height Validation
TEST(AVLTreeTest, HeightValidation) {
    data_structures::AVLTree<int> tree;
    
    EXPECT_EQ(tree.height(), 0);
    
    tree.insert(10);
    EXPECT_EQ(tree.height(), 1);
    
    tree.insert(5);
    tree.insert(15);
    EXPECT_EQ(tree.height(), 2);
    
    tree.insert(3);
    tree.insert(7);
    tree.insert(12);
    tree.insert(17);
    EXPECT_EQ(tree.height(), 3);
}

// Test AVL Tree - Clear
TEST(AVLTreeTest, Clear) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(1);
    tree.insert(2);
    tree.insert(3);
    
    EXPECT_EQ(tree.size(), 3);
    
    tree.clear();
    
    EXPECT_TRUE(tree.empty());
    EXPECT_EQ(tree.size(), 0);
    EXPECT_EQ(tree.height(), 0);
    EXPECT_FALSE(tree.search(1));
}

// Test AVL Tree - Empty Tree Operations
TEST(AVLTreeTest, EmptyTreeOperations) {
    data_structures::AVLTree<int> tree;
    
    EXPECT_FALSE(tree.findMin().has_value());
    EXPECT_FALSE(tree.findMax().has_value());
    EXPECT_FALSE(tree.search(10));
    EXPECT_FALSE(tree.remove(10));
    
    auto result = tree.inorderTraversal();
    EXPECT_TRUE(result.empty());
}

// Test AVL Tree - Duplicate Prevention
TEST(AVLTreeTest, DuplicatePrevention) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(10);
    tree.insert(10);
    
    EXPECT_EQ(tree.size(), 1); // Only one instance should exist
    EXPECT_TRUE(tree.search(10));
}

// Test AVL Tree - String Type
TEST(AVLTreeTest, StringType) {
    data_structures::AVLTree<std::string> tree;
    
    tree.insert("dog");
    tree.insert("cat");
    tree.insert("bird");
    tree.insert("zebra");
    tree.insert("ant");
    
    EXPECT_EQ(tree.size(), 5);
    
    EXPECT_TRUE(tree.search("dog"));
    EXPECT_TRUE(tree.search("ant"));
    EXPECT_FALSE(tree.search("elephant"));
    
    auto result = tree.inorderTraversal();
    std::vector<std::string> expected = {"ant", "bird", "cat", "dog", "zebra"};
    EXPECT_EQ(result, expected);
}

// Test AVL Tree - Large Dataset Balance
TEST(AVLTreeTest, LargeDatasetBalance) {
    data_structures::AVLTree<int> tree;
    
    // Insert 100 elements
    for (int i = 1; i <= 100; i++) {
        tree.insert(i);
    }
    
    EXPECT_EQ(tree.size(), 100);
    
    // Height should be logarithmic (approximately log2(100) ≈ 7)
    // AVL tree guarantees height <= 1.44 * log2(n)
    EXPECT_LE(tree.height(), 10);
    
    // Verify all elements present
    for (int i = 1; i <= 100; i++) {
        EXPECT_TRUE(tree.search(i));
    }
    
    // Verify sorted order
    auto result = tree.inorderTraversal();
    EXPECT_EQ(result.size(), 100);
    for (size_t i = 1; i < result.size(); i++) {
        EXPECT_LT(result[i-1], result[i]);
    }
}

// Test AVL Tree - Remove and Rebalance
TEST(AVLTreeTest, RemoveAndRebalance) {
    data_structures::AVLTree<int> tree;
    
    // Build a tree
    for (int i = 1; i <= 15; i++) {
        tree.insert(i);
    }
    
    EXPECT_EQ(tree.size(), 15);
    int initialHeight = tree.height();
    
    // Remove several elements
    tree.remove(1);
    tree.remove(2);
    tree.remove(3);
    
    EXPECT_EQ(tree.size(), 12);
    
    // Tree should still be balanced
    EXPECT_LE(tree.height(), initialHeight);
    
    // Verify remaining elements
    for (int i = 4; i <= 15; i++) {
        EXPECT_TRUE(tree.search(i));
    }
}

// ========== 新增：size计数正确性测试 ==========

// 测试插入后size正确
TEST(AVLTreeTest, SizeAfterInsert) {
    data_structures::AVLTree<int> tree;
    
    EXPECT_EQ(tree.size(), 0);
    
    for (int i = 1; i <= 50; i++) {
        tree.insert(i);
        EXPECT_EQ(tree.size(), static_cast<size_t>(i));
    }
}

// 测试删除后size正确（包括双子节点情况）
TEST(AVLTreeTest, SizeAfterRemove) {
    data_structures::AVLTree<int> tree;
    
    // 构建一个较大的树
    for (int i = 1; i <= 20; i++) {
        tree.insert(i);
    }
    
    EXPECT_EQ(tree.size(), 20);
    
    // 删除叶子节点
    tree.remove(1);
    EXPECT_EQ(tree.size(), 19);
    
    // 删除单子节点
    tree.remove(2);
    EXPECT_EQ(tree.size(), 18);
    
    // 删除双子节点（通常是较复杂的情况）
    tree.remove(10);  // 10通常会有两个子节点
    EXPECT_EQ(tree.size(), 17);
    
    // 验证所有操作后size正确
    EXPECT_FALSE(tree.search(1));
    EXPECT_FALSE(tree.search(2));
    EXPECT_FALSE(tree.search(10));
}

// 测试删除不存在元素后size不变
TEST(AVLTreeTest, SizeUnchangedForNonExistentElement) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(5);
    tree.insert(10);
    tree.insert(15);
    
    EXPECT_EQ(tree.size(), 3);
    
    EXPECT_FALSE(tree.remove(100));
    EXPECT_EQ(tree.size(), 3);
    
    EXPECT_FALSE(tree.remove(0));
    EXPECT_EQ(tree.size(), 3);
}

// 测试大量插入删除后size正确
TEST(AVLTreeTest, SizeAfterMixedOperations) {
    data_structures::AVLTree<int> tree;
    
    // 插入100个元素
    for (int i = 0; i < 100; i++) {
        tree.insert(i);
    }
    EXPECT_EQ(tree.size(), 100);
    
    // 删除50个元素
    for (int i = 0; i < 50; i++) {
        EXPECT_TRUE(tree.remove(i));
    }
    EXPECT_EQ(tree.size(), 50);
    
    // 再插入25个新元素
    for (int i = 100; i < 125; i++) {
        tree.insert(i);
    }
    EXPECT_EQ(tree.size(), 75);
}

// ========== 新增：移动语义测试 ==========

// 测试insert移动语义
TEST(AVLTreeTest, InsertMoveSemantics) {
    data_structures::AVLTree<std::string> tree;
    
    std::string str1 = "alpha";
    std::string str2 = "beta";
    std::string str3 = "gamma";
    
    tree.insert(std::move(str1));
    tree.insert(std::move(str2));
    tree.insert(std::move(str3));
    
    EXPECT_EQ(tree.size(), 3);
    EXPECT_TRUE(tree.search("alpha"));
    EXPECT_TRUE(tree.search("beta"));
    EXPECT_TRUE(tree.search("gamma"));
}

// ========== 新增：平衡性验证测试 ==========

// 测试插入递增序列后树保持平衡
TEST(AVLTreeTest, BalanceAfterAscendingInsert) {
    data_structures::AVLTree<int> tree;
    
    // 插入递增序列
    for (int i = 1; i <= 100; i++) {
        tree.insert(i);
    }
    
    EXPECT_EQ(tree.size(), 100);
    
    // 验证高度满足AVL树性质 h <= 1.44 * log2(n+2)
    // log2(102) ≈ 6.67, 1.44 * 6.67 ≈ 9.6
    EXPECT_LE(tree.height(), 10);
}

// 测试插入递减序列后树保持平衡
TEST(AVLTreeTest, BalanceAfterDescendingInsert) {
    data_structures::AVLTree<int> tree;
    
    // 插入递减序列
    for (int i = 100; i >= 1; i--) {
        tree.insert(i);
    }
    
    EXPECT_EQ(tree.size(), 100);
    
    // 验证高度
    EXPECT_LE(tree.height(), 10);
}

// 测试删除操作后树保持平衡
TEST(AVLTreeTest, BalanceAfterRemove) {
    data_structures::AVLTree<int> tree;
    
    // 插入元素
    for (int i = 1; i <= 50; i++) {
        tree.insert(i);
    }
    
    int heightBefore = tree.height();
    
    // 删除一些元素
    for (int i = 1; i <= 20; i++) {
        tree.remove(i);
    }
    
    EXPECT_EQ(tree.size(), 30);
    
    // 删除后高度应该合理
    // log2(32) ≈ 5, 1.44 * 5 ≈ 7.2
    EXPECT_LE(tree.height(), 8);
}

// 测试验证树高度满足AVL性质（理论上界）
TEST(AVLTreeTest, VerifyAVLHeightBound) {
    data_structures::AVLTree<int> tree;
    
    std::vector<int> sizes = {10, 50, 100, 200};
    
    for (int size : sizes) {
        tree.clear();
        
        for (int i = 0; i < size; i++) {
            tree.insert(i);
        }
        
        EXPECT_EQ(tree.size(), static_cast<size_t>(size));
        
        // AVL树高度上界: h <= 1.44 * log2(n+2)
        double maxHeight = 1.44 * std::log2(size + 2);
        EXPECT_LE(tree.height(), static_cast<int>(std::ceil(maxHeight)) + 1);
    }
}

// ========== 新增：边界测试 ==========

// 测试删除根节点（单子节点）
TEST(AVLTreeTest, RemoveRootWithOneChild) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    
    EXPECT_TRUE(tree.remove(10));
    EXPECT_EQ(tree.size(), 1);
    EXPECT_FALSE(tree.search(10));
    EXPECT_TRUE(tree.search(5));
}

// 测试删除根节点（双子节点）
TEST(AVLTreeTest, RemoveRootWithTwoChildren) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(10);
    tree.insert(5);
    tree.insert(15);
    tree.insert(12);
    tree.insert(20);
    
    EXPECT_TRUE(tree.remove(10));
    EXPECT_EQ(tree.size(), 4);
    EXPECT_FALSE(tree.search(10));
    EXPECT_TRUE(tree.search(5));
    EXPECT_TRUE(tree.search(15));
}

// 测试空树search
TEST(AVLTreeTest, SearchInEmptyTree) {
    data_structures::AVLTree<int> tree;
    
    EXPECT_FALSE(tree.search(0));
    EXPECT_FALSE(tree.search(42));
    EXPECT_FALSE(tree.search(-100));
}

// 测试重复元素插入（应被忽略）
TEST(AVLTreeTest, DuplicateInsertIgnored) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(5);
    EXPECT_EQ(tree.size(), 1);
    
    tree.insert(5);
    EXPECT_EQ(tree.size(), 1);  // size不应增加
    
    tree.insert(5);
    tree.insert(5);
    EXPECT_EQ(tree.size(), 1);
    
    EXPECT_TRUE(tree.search(5));
}

// 测试极值元素
TEST(AVLTreeTest, ExtremeValues) {
    data_structures::AVLTree<int> tree;
    
    tree.insert(INT_MAX);
    tree.insert(INT_MIN);
    tree.insert(0);
    
    EXPECT_EQ(tree.size(), 3);
    
    auto minVal = tree.findMin();
    ASSERT_TRUE(minVal.has_value());
    EXPECT_EQ(minVal.value(), INT_MIN);
    
    auto maxVal = tree.findMax();
    ASSERT_TRUE(maxVal.has_value());
    EXPECT_EQ(maxVal.value(), INT_MAX);
}