#include <gtest/gtest.h>
#include "data_structures/linked_list.h"
#include "data_structures/stack_queue.h"
#include "data_structures/heap.h"
#include <string>
#include <utility>

using namespace data_structures;

// ============================================================================
// LinkedList 移动语义测试
// ============================================================================

TEST(LinkedListMoveTest, MoveConstructor) {
    LinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    
    // 移动构造
    LinkedList<int> list2(std::move(list1));
    
    // list2 应该包含原来的数据
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front().value(), 1);
    
    // list1 应该为空（有效但未指定状态）
    EXPECT_EQ(list1.size(), 0);
    EXPECT_TRUE(list1.empty());
}

TEST(LinkedListMoveTest, MoveAssignment) {
    LinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    
    LinkedList<int> list2;
    list2.pushBack(10);
    
    // 移动赋值
    list2 = std::move(list1);
    
    // list2 应该包含 list1 的数据
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list2.front().value(), 1);
    
    // list1 应该为空
    EXPECT_EQ(list1.size(), 0);
    EXPECT_TRUE(list1.empty());
}

TEST(LinkedListMoveTest, CopyConstructor) {
    LinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    list1.pushBack(3);
    
    // 拷贝构造
    LinkedList<int> list2(list1);
    
    // 两个链表应该独立且包含相同数据
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 3);
    EXPECT_EQ(list1.front().value(), 1);
    EXPECT_EQ(list2.front().value(), 1);
    
    // 修改一个不应影响另一个
    list2.pushBack(4);
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list2.size(), 4);
}

TEST(LinkedListMoveTest, CopyAssignment) {
    LinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    
    LinkedList<int> list2;
    list2.pushBack(10);
    
    // 拷贝赋值
    list2 = list1;
    
    // 两个链表应该独立
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list2.size(), 2);
    
    list2.pushBack(3);
    EXPECT_EQ(list1.size(), 2);
    EXPECT_EQ(list2.size(), 3);
}

TEST(LinkedListMoveTest, SelfAssignment) {
    LinkedList<int> list;
    list.pushBack(1);
    list.pushBack(2);
    
    // 自赋值测试
    list = list;
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front().value(), 1);
}

TEST(LinkedListMoveTest, SwapFunction) {
    LinkedList<int> list1;
    list1.pushBack(1);
    list1.pushBack(2);
    
    LinkedList<int> list2;
    list2.pushBack(10);
    list2.pushBack(20);
    list2.pushBack(30);
    
    // 交换
    list1.swap(list2);
    
    EXPECT_EQ(list1.size(), 3);
    EXPECT_EQ(list1.front().value(), 10);
    EXPECT_EQ(list2.size(), 2);
    EXPECT_EQ(list2.front().value(), 1);
}

// ============================================================================
// Stack 移动语义测试
// ============================================================================

TEST(StackMoveTest, MoveConstructor) {
    Stack<std::string> stack1;
    stack1.push("hello");
    stack1.push("world");
    
    // 移动构造
    Stack<std::string> stack2(std::move(stack1));
    
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top().value(), "world");
}

TEST(StackMoveTest, MoveAssignment) {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    
    Stack<int> stack2;
    stack2 = std::move(stack1);
    
    EXPECT_EQ(stack2.size(), 2);
    EXPECT_EQ(stack2.top().value(), 2);
}

TEST(StackMoveTest, CopyConstructor) {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    stack1.push(3);
    
    Stack<int> stack2(stack1);
    
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 3);
    
    stack2.pop();
    EXPECT_EQ(stack1.size(), 3);
    EXPECT_EQ(stack2.size(), 2);
}

TEST(StackMoveTest, CopyAssignment) {
    Stack<int> stack1;
    stack1.push(1);
    stack1.push(2);
    
    Stack<int> stack2;
    stack2 = stack1;
    
    EXPECT_EQ(stack1.size(), 2);
    EXPECT_EQ(stack2.size(), 2);
}

// ============================================================================
// Queue 移动语义测试
// ============================================================================

TEST(QueueMoveTest, MoveConstructor) {
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);
    
    Queue<int> queue2(std::move(queue1));
    
    EXPECT_EQ(queue2.size(), 3);
    EXPECT_EQ(queue2.front().value(), 1);
}

TEST(QueueMoveTest, MoveAssignment) {
    Queue<std::string> queue1;
    queue1.enqueue("a");
    queue1.enqueue("b");
    
    Queue<std::string> queue2;
    queue2 = std::move(queue1);
    
    EXPECT_EQ(queue2.size(), 2);
    EXPECT_EQ(queue2.front().value(), "a");
}

TEST(QueueMoveTest, CopyConstructor) {
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    
    Queue<int> queue2(queue1);
    
    EXPECT_EQ(queue1.size(), 2);
    EXPECT_EQ(queue2.size(), 2);
    
    queue2.dequeue();
    EXPECT_EQ(queue1.size(), 2);
    EXPECT_EQ(queue2.size(), 1);
}

TEST(QueueMoveTest, CopyAssignment) {
    Queue<int> queue1;
    queue1.enqueue(1);
    queue1.enqueue(2);
    queue1.enqueue(3);
    
    Queue<int> queue2;
    queue2 = queue1;
    
    EXPECT_EQ(queue1.size(), 3);
    EXPECT_EQ(queue2.size(), 3);
}

// ============================================================================
// Heap 移动语义测试
// ============================================================================

TEST(HeapMoveTest, MoveConstructor) {
    Heap<int> heap1;
    heap1.insert(5);
    heap1.insert(2);
    heap1.insert(8);
    
    Heap<int> heap2(std::move(heap1));
    
    EXPECT_EQ(heap2.size(), 3);
    EXPECT_EQ(heap2.top().value(), 2);  // 最小堆
}

TEST(HeapMoveTest, MoveAssignment) {
    Heap<int> heap1;
    heap1.insert(5);
    heap1.insert(2);
    heap1.insert(8);
    
    Heap<int> heap2;
    heap2 = std::move(heap1);
    
    EXPECT_EQ(heap2.size(), 3);
    EXPECT_EQ(heap2.top().value(), 2);
}

TEST(HeapMoveTest, CopyConstructor) {
    Heap<int> heap1;
    heap1.insert(5);
    heap1.insert(2);
    heap1.insert(8);
    
    Heap<int> heap2(heap1);
    
    EXPECT_EQ(heap1.size(), 3);
    EXPECT_EQ(heap2.size(), 3);
    
    heap2.extractTop();
    EXPECT_EQ(heap1.size(), 3);
    EXPECT_EQ(heap2.size(), 2);
}

TEST(HeapMoveTest, CopyAssignment) {
    Heap<int> heap1;
    heap1.insert(5);
    heap1.insert(2);
    
    Heap<int> heap2;
    heap2 = heap1;
    
    EXPECT_EQ(heap1.size(), 2);
    EXPECT_EQ(heap2.size(), 2);
}

// ============================================================================
// 性能测试 - 验证移动语义的性能优势
// ============================================================================

TEST(MovePerformanceTest, LinkedListMoveVsCopy) {
    // 创建一个大链表
    LinkedList<int> largeList;
    for (int i = 0; i < 10000; i++) {
        largeList.pushBack(i);
    }
    
    // 移动应该很快（O(1)）
    auto start = std::chrono::high_resolution_clock::now();
    LinkedList<int> movedList(std::move(largeList));
    auto end = std::chrono::high_resolution_clock::now();
    auto moveDuration = std::chrono::duration_cast<std::chrono::microseconds>(end - start).count();
    
    // 验证移动成功
    EXPECT_EQ(movedList.size(), 10000);
    EXPECT_EQ(largeList.size(), 0);
    
    // 移动操作应该非常快（通常小于1微秒）
    // 这里不做严格的时间限制，因为性能依赖于硬件
    std::cout << "Move duration: " << moveDuration << " microseconds" << std::endl;
}

TEST(MovePerformanceTest, VectorOfContainers) {
    // 测试容器作为元素时的移动语义
    std::vector<Stack<int>> stacks;
    
    for (int i = 0; i < 100; i++) {
        Stack<int> temp;
        temp.push(i);
        temp.push(i + 1);
        stacks.push_back(std::move(temp));  // 使用移动语义
    }
    
    EXPECT_EQ(stacks.size(), 100);
    EXPECT_EQ(stacks[0].size(), 2);
}
