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

// ========== 新增：tail指针正确性测试 ==========

// 测试tail指针 - pushBack后tail指向正确节点
TEST(LinkedListTest, TailPointerAfterPushBack) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    // 通过遍历验证tail指向最后一个节点
    EXPECT_TRUE(list.find(1));
    EXPECT_EQ(list.size(), 1);
    
    list.pushBack(2);
    list.pushBack(3);
    EXPECT_EQ(list.size(), 3);
    
    // 验证链表中所有元素都存在
    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(2));
    EXPECT_TRUE(list.find(3));
}

// 测试tail指针 - pushFront不改变tail（非空链表）
TEST(LinkedListTest, TailPointerAfterPushFront) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);  // tail指向1
    list.pushBack(2);  // tail指向2
    
    list.pushFront(0);  // 在头部插入，tail应该仍指向2
    
    EXPECT_EQ(list.size(), 3);
    EXPECT_TRUE(list.find(0));
    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(2));
}

// 测试tail指针 - popFront后tail正确更新（链表变空时）
TEST(LinkedListTest, TailPointerAfterPopFrontToEmpty) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(42);
    EXPECT_EQ(list.size(), 1);
    
    list.popFront();
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
    
    // 链表为空后再次pushBack应该正常工作
    list.pushBack(100);
    EXPECT_EQ(list.size(), 1);
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 100);
}

// 测试tail指针 - 混合操作后tail始终指向最后一个节点
TEST(LinkedListTest, TailPointerMixedOperations) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    list.pushBack(2);
    list.pushFront(0);
    list.pushBack(3);
    
    EXPECT_EQ(list.size(), 4);
    
    // 验证所有元素
    EXPECT_TRUE(list.find(0));
    EXPECT_TRUE(list.find(1));
    EXPECT_TRUE(list.find(2));
    EXPECT_TRUE(list.find(3));
    
    // popFront不影响tail
    list.popFront();
    list.popFront();
    EXPECT_EQ(list.size(), 2);
    EXPECT_TRUE(list.find(2));
    EXPECT_TRUE(list.find(3));
}

// ========== 新增：移动语义测试 ==========

// 测试pushFront移动语义
TEST(LinkedListTest, PushFrontMoveSemantics) {
    data_structures::LinkedList<std::string> list;
    
    std::string str1 = "First";
    std::string str2 = "Second";
    
    list.pushFront(std::move(str1));
    list.pushFront(std::move(str2));
    
    EXPECT_EQ(list.size(), 2);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "Second");
    
    list.popFront();
    front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "First");
}

// 测试pushBack移动语义
TEST(LinkedListTest, PushBackMoveSemantics) {
    data_structures::LinkedList<std::string> list;
    
    std::string str1 = "Hello";
    std::string str2 = "World";
    std::string str3 = "Test";
    
    list.pushBack(std::move(str1));
    list.pushBack(std::move(str2));
    list.pushBack(std::move(str3));
    
    EXPECT_EQ(list.size(), 3);
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "Hello");
    
    EXPECT_TRUE(list.find("World"));
    EXPECT_TRUE(list.find("Test"));
}

// ========== 新增：压力测试 ==========

// 测试大量插入删除操作
TEST(LinkedListTest, StressTest) {
    data_structures::LinkedList<int> list;
    
    // 1000次pushBack
    for (int i = 0; i < 1000; i++) {
        list.pushBack(i);
    }
    
    EXPECT_EQ(list.size(), 1000);
    
    // 验证头尾元素
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 0);
    
    // 验证部分元素存在
    EXPECT_TRUE(list.find(500));
    EXPECT_TRUE(list.find(999));
    
    // 500次popFront
    for (int i = 0; i < 500; i++) {
        EXPECT_TRUE(list.popFront());
    }
    
    EXPECT_EQ(list.size(), 500);
    
    // 验证前500个已被删除
    EXPECT_FALSE(list.find(0));
    EXPECT_FALSE(list.find(499));
    
    // 验证后500个仍存在
    EXPECT_TRUE(list.find(500));
    EXPECT_TRUE(list.find(999));
}

// 测试交替pushFront/pushBack操作
TEST(LinkedListTest, AlternatingPushOperations) {
    data_structures::LinkedList<int> list;
    
    for (int i = 0; i < 500; i++) {
        list.pushFront(i);      // 在前面插入
        list.pushBack(i + 1000); // 在后面插入
    }
    
    EXPECT_EQ(list.size(), 1000);
    
    // 验证部分元素
    EXPECT_TRUE(list.find(0));
    EXPECT_TRUE(list.find(499));
    EXPECT_TRUE(list.find(1000));
    EXPECT_TRUE(list.find(1499));
}

// ========== 新增：边界测试 ==========

// 测试空链表的find操作
TEST(LinkedListTest, FindOnEmptyList) {
    data_structures::LinkedList<int> list;
    
    EXPECT_FALSE(list.find(0));
    EXPECT_FALSE(list.find(42));
    EXPECT_FALSE(list.find(-1));
}

// 测试删除不存在的元素（通过popFront清空后再pop）
TEST(LinkedListTest, PopFromEmptyList) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(1);
    EXPECT_TRUE(list.popFront());
    
    // 链表已空
    EXPECT_FALSE(list.popFront());
    EXPECT_FALSE(list.popFront());
    
    EXPECT_EQ(list.size(), 0);
    EXPECT_TRUE(list.empty());
}

// 测试单元素链表的各种操作
TEST(LinkedListTest, SingleElementOperations) {
    data_structures::LinkedList<int> list;
    
    list.pushBack(42);
    
    EXPECT_EQ(list.size(), 1);
    EXPECT_FALSE(list.empty());
    
    auto front = list.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 42);
    
    EXPECT_TRUE(list.find(42));
    EXPECT_FALSE(list.find(0));
    
    EXPECT_TRUE(list.popFront());
    EXPECT_TRUE(list.empty());
    EXPECT_EQ(list.size(), 0);
}