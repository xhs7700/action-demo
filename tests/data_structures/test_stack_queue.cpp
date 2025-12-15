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

// ========== 新增：Stack移动语义测试 ==========

// 测试栈 - 移动语义push
TEST(StackTest, MoveSemanticsTest) {
    data_structures::Stack<std::string> stack;
    
    std::string str1 = "Hello, World!";
    std::string str2 = "Move Test";
    
    // 使用移动语义
    stack.push(std::move(str1));
    stack.push(std::move(str2));
    
    EXPECT_EQ(stack.size(), 2);
    
    auto top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "Move Test");
    
    stack.pop();
    top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), "Hello, World!");
}

// ========== 新增：Stack压力测试 ==========

// 测试栈 - 大量push/pop操作
TEST(StackTest, StressTest) {
    data_structures::Stack<int> stack;
    
    // 1000次push操作
    for (int i = 0; i < 1000; i++) {
        stack.push(i);
    }
    
    EXPECT_EQ(stack.size(), 1000);
    
    // 验证栈顶元素
    auto top = stack.top();
    ASSERT_TRUE(top.has_value());
    EXPECT_EQ(top.value(), 999);
    
    // 1000次pop操作
    for (int i = 999; i >= 0; i--) {
        auto current = stack.top();
        ASSERT_TRUE(current.has_value());
        EXPECT_EQ(current.value(), i);
        EXPECT_TRUE(stack.pop());
    }
    
    EXPECT_TRUE(stack.empty());
    EXPECT_EQ(stack.size(), 0);
}

// 测试栈 - 空栈多次pop
TEST(StackTest, MultiplePopOnEmptyStack) {
    data_structures::Stack<int> stack;
    
    EXPECT_FALSE(stack.pop());
    EXPECT_FALSE(stack.pop());
    EXPECT_FALSE(stack.pop());
    
    EXPECT_TRUE(stack.empty());
    EXPECT_FALSE(stack.top().has_value());
}

// 测试栈 - pop后top应返回nullopt（当栈为空时）
TEST(StackTest, TopAfterPopEmpty) {
    data_structures::Stack<int> stack;
    
    stack.push(42);
    EXPECT_TRUE(stack.pop());
    
    auto top = stack.top();
    EXPECT_FALSE(top.has_value());
    
    EXPECT_TRUE(stack.empty());
}

// ========== 新增：Queue移动语义测试 ==========

// 测试队列 - 移动语义enqueue
TEST(QueueTest, MoveSemanticsTest) {
    data_structures::Queue<std::string> queue;
    
    std::string str1 = "First Element";
    std::string str2 = "Second Element";
    std::string str3 = "Third Element";
    
    // 使用移动语义
    queue.enqueue(std::move(str1));
    queue.enqueue(std::move(str2));
    queue.enqueue(std::move(str3));
    
    EXPECT_EQ(queue.size(), 3);
    
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), "First Element");
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), "Third Element");
}

// ========== 新增：Queue压力测试 ==========

// 测试队列 - 大量enqueue/dequeue操作
TEST(QueueTest, StressTest) {
    data_structures::Queue<int> queue;
    
    // 1000次enqueue操作
    for (int i = 0; i < 1000; i++) {
        queue.enqueue(i);
    }
    
    EXPECT_EQ(queue.size(), 1000);
    
    // 验证front和back
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 0);
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), 999);
    
    // 1000次dequeue操作
    for (int i = 0; i < 1000; i++) {
        auto current = queue.front();
        ASSERT_TRUE(current.has_value());
        EXPECT_EQ(current.value(), i);
        EXPECT_TRUE(queue.dequeue());
    }
    
    EXPECT_TRUE(queue.empty());
    EXPECT_EQ(queue.size(), 0);
}

// 测试队列 - 空队列多次dequeue
TEST(QueueTest, MultipleDequeueOnEmptyQueue) {
    data_structures::Queue<int> queue;
    
    EXPECT_FALSE(queue.dequeue());
    EXPECT_FALSE(queue.dequeue());
    EXPECT_FALSE(queue.dequeue());
    
    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.front().has_value());
    EXPECT_FALSE(queue.back().has_value());
}

// 测试队列 - dequeue后验证队列状态
TEST(QueueTest, VerifyStateAfterDequeue) {
    data_structures::Queue<int> queue;
    
    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    
    EXPECT_TRUE(queue.dequeue());
    EXPECT_EQ(queue.size(), 2);
    
    auto front = queue.front();
    ASSERT_TRUE(front.has_value());
    EXPECT_EQ(front.value(), 20);
    
    auto back = queue.back();
    ASSERT_TRUE(back.has_value());
    EXPECT_EQ(back.value(), 30);
    
    EXPECT_TRUE(queue.dequeue());
    EXPECT_TRUE(queue.dequeue());
    
    EXPECT_TRUE(queue.empty());
    EXPECT_FALSE(queue.front().has_value());
    EXPECT_FALSE(queue.back().has_value());
}

// 测试队列 - 交替enqueue和dequeue操作
TEST(QueueTest, AlternatingOperations) {
    data_structures::Queue<int> queue;
    
    // 交替操作：先添加2个，再移除1个，重复500次
    for (int i = 0; i < 500; i++) {
        queue.enqueue(i);
        queue.enqueue(i + 1000);
        
        EXPECT_TRUE(queue.dequeue());  // 移除一个元素
    }
    
    // 每次循环添加2个移除1个，净增1个，500次后应该有500个元素
    EXPECT_EQ(queue.size(), 500);
    
    // 验证队列不为空
    EXPECT_FALSE(queue.empty());
    
    // 清空队列验证所有元素都能正确dequeue
    size_t count = 0;
    while (!queue.empty()) {
        EXPECT_TRUE(queue.dequeue());
        count++;
    }
    EXPECT_EQ(count, 500);
}