#include <gtest/gtest.h>
#include "data_structures/linked_list.h"
#include <string>

// 测试链表 - 基本插入和查询
TEST(LinkedListTest, BasicOperations) {
    data_structures::LinkedList<int> list;
    
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    
    list.pushBack(10);
    EXPECT_FALSE(list.empty());
    EXPECT_EQ(list.size(), 1);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 10);
}

// 测试链表 - pushFront
TEST(LinkedListTest, PushFront) {
    data_structures::LinkedList<int> list;
    
    list.pushFront(1);
    list.pushFront(2);
    list.pushFront(3);
    
    EXPECT_EQ(list.size(), 3);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 3); // 最后压入的是3
}

// 测试链表 - pushBack
TEST(LinkedListTest, PushBack) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    EXPECT_EQ(list.size(), 3);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 1); // 第一个压入的是1
}

// 测试链表 - popFront
TEST(LinkedListTest, PopFront) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    EXPECT_TRUE(list.popFront());
    EXPECT_EQ(list.size(), 2);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 2);
    
    EXPECT_TRUE(list.popFront());
    EXPECT_TRUE(list.popFront());
    EXPECT_TRUE(list.empty());
    
    EXPECT_FALSE(list.popFront()); // 空链表，应该返回false
}

// 测试链表 - find
TEST(LinkedListTest, Find) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(10);
    list.pushBack(20);
    list.pushBack(30);
    
    EXPECT_TRUE(list.find(10));
    EXPECT_TRUE(list.find(20));
    EXPECT_TRUE(list.find(30));
    EXPECT_FALSE(list.find(40));
    EXPECT_FALSE(list.find(0));
}

// 测试链表 - clear
TEST(LinkedListTest, Clear) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    list.pushBack(2);
    list.pushBack(3);
    
    EXPECT_EQ(list.size(), 3);
    
    list.clear();
    
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
    EXPECT_FALSE(list.front().has_value());
}

// 测试链表 - 空链表操作
TEST(LinkedListTest, EmptyListOperations) {
    data_structures::LinkedList<int> list;
    
    EXPECT_FALSE(list.front().has_value());
    EXPECT_FALSE(list.popFront());
    EXPECT_FALSE(list.find(10));
}

// 测试链表 - 字符串类型
TEST(LinkedListTest, StringType) {
    data_structures::LinkedList<std::string> list;
    
    list.pushBack("hello");
    list.pushBack("world");
    list.pushFront("foo");
    
    EXPECT_EQ(list.size(), 3);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "foo");
    
    EXPECT_TRUE(list.find("hello"));
    EXPECT_TRUE(list.find("world"));
    EXPECT_FALSE(list.find("bar"));
}

// 测试链表 - 混合操作
TEST(LinkedListTest, MixedOperations) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    list.pushFront(2);
    list.pushBack(3);
    list.pushFront(4);
    
    EXPECT_EQ(list.size(), 4);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 4);
    
    list.popFront();
    front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 2);
    
    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(3));
}
