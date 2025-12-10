#include <gtest/gtest.h>
#include "data_structures/stack_queue.h"
#include <string>

// ========== Stack Tests ==========

// 测试栈 - 基本操作
TEST(StackTest, BasicOperations) {
    data_structures::Stack<int> stack;
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
    
    stack.push(10);
    EXPECT_FALSE(stack.empty());
    EXPECT_EQ(stack.size(), 1);
}

// 测试栈 - push 和 top
TEST(StackTest, PushAndTop) {
    data_structures::Stack<int> stack;
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    auto top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 3); // 最后压入的值
    
    EXPECT_EQ(stack.size(), 3);
}

// 测试栈 - pop
TEST(StackTest, Pop) {
    data_structures::Stack<int> stack;
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    EXPECT_TRUE(stack.pop());
    auto top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 2);
    
    EXPECT_TRUE(stack.pop());
    EXPECT_TRUE(stack.pop());
    EXPECT_TRUE(stack.empty());
    
    EXPECT_FALSE(stack.pop()); // 空栈，返回false
}

// 测试栈 - 空栈操作
TEST(StackTest, EmptyStackOperations) {
    data_structures::Stack<int> stack;
    
    EXPECT_FALSE(stack.top().has_value());
    EXPECT_FALSE(stack.pop());
}

// 测试栈 - clear
TEST(StackTest, Clear) {
    data_structures::Stack<int> stack;
    
    stack.push(1);
    stack.push(2);
    stack.push(3);
    
    EXPECT_EQ(stack.size(), 3);
    
    stack.clear();
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

// 测试栈 - 字符串类型
TEST(StackTest, StringType) {
    data_structures::Stack<std::string> stack;
    
    stack.push("hello");
    stack.push("world");
    
    auto top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "world");
    
    stack.pop();
    top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "hello");
}

// 测试栈 - LIFO（后进先出）验证
TEST(StackTest, LIFOBehavior) {
    data_structures::Stack<int> stack;
    
    for (int i = 1; i <= 5; i++) {
        stack.push(i);
    }
    
    for (int i = 5; i >= 1; i--) {
        auto top = stack.top();
        ASSERT_TRUE(top.has_value());
        EXPECT_EQ(top.value(), i);
        stack.pop();
    }
    
    EXPECT_TRUE(stack.empty());
}

// ========== Queue Tests ==========

// 测试队列 - 基本操作
TEST(QueueTest, BasicOperations) {
    data_structures::Queue<int> queue;
    
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
    
    queue.enqueue(10);
    EXPECT_FALSE(queue.empty());
    EXPECT_EQ(queue.size(), 1);
}

// 测试队列 - enqueue 和 front/back
TEST(QueueTest, EnqueueAndFrontBack) {
    data_structures::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 1); // 第一个入队的值
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), 3); // 最后入队的值
    
    EXPECT_EQ(queue.size(), 3);
}

// 测试队列 - dequeue
TEST(QueueTest, Dequeue) {
    data_structures::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    EXPECT_TRUE(queue.dequeue());
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 2);
    
    EXPECT_TRUE(queue.dequeue());
    EXPECT_TRUE(queue.dequeue());
    EXPECT_TRUE(queue.empty());
    
    EXPECT_FALSE(queue.dequeue()); // 空队列，返回false
}

// 测试队列 - 空队列操作
TEST(QueueTest, EmptyQueueOperations) {
    data_structures::Queue<int> queue;
    
    EXPECT_FALSE(queue.front().has_value());
    EXPECT_FALSE(queue.back().has_value());
    EXPECT_FALSE(queue.dequeue());
}

// 测试队列 - clear
TEST(QueueTest, Clear) {
    data_structures::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.enqueue(3);
    
    EXPECT_EQ(queue.size(), 3);
    
    queue.clear();
    
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

// 测试队列 - 字符串类型
TEST(QueueTest, StringType) {
    data_structures::Queue<std::string> queue;
    
    queue.enqueue("hello");
    queue.enqueue("world");
    
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "hello");
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), "world");
}

// 测试队列 - FIFO（先进先出）验证
TEST(QueueTest, FIFOBehavior) {
    data_structures::Queue<int> queue;
    
    for (int i = 1; i <= 5; i++) {
        queue.enqueue(i);
    }
    
    for (int i = 1; i <= 5; i++) {
        auto front = queue.front();
        ASSERT_TRUE(front.has_value());
        EXPECT_EQ(front.value(), i);
        queue.dequeue();
    }
    
    EXPECT_TRUE(queue.empty());
}

// 测试队列 - 混合操作
TEST(QueueTest, MixedOperations) {
    data_structures::Queue<int> queue;
    
    queue.enqueue(1);
    queue.enqueue(2);
    queue.dequeue();
    queue.enqueue(3);
    queue.enqueue(4);
    
    EXPECT_EQ(queue.size(), 3);
    
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 2);
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), 4);
}
