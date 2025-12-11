#include <gtest/gtest.h>
#include "data_structures/avl_tree.h"
#include <string>

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
