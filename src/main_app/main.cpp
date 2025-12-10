#include <iostream>
#include <vector>
#include "algorithms/sort.h"
#include "algorithms/search.h"
#include "data_structures/linked_list.h"
#include "data_structures/stack_queue.h"

void demonstrateAlgorithms() {
    std::cout << "=== 算法演示 ===" << std::endl;
    
    // 演示排序算法
    std::vector<int> data = {64, 34, 25, 12, 22, 11, 90};
    std::cout << "\n原始数据: ";
    for (int val : data) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 快速排序
    auto quickSortData = data;
    algorithms::quickSort(quickSortData);
    std::cout << "快速排序结果: ";
    for (int val : quickSortData) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 归并排序
    auto mergeSortData = data;
    algorithms::mergeSort(mergeSortData);
    std::cout << "归并排序结果: ";
    for (int val : mergeSortData) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
    
    // 演示搜索算法
    int target = 22;
    int index = algorithms::binarySearch(quickSortData, target);
    std::cout << "\n二分查找 " << target << ": ";
    if (index != -1) {
        std::cout << "找到，索引 = " << index << std::endl;
    } else {
        std::cout << "未找到" << std::endl;
    }
    
    index = algorithms::linearSearch(data, target);
    std::cout << "线性查找 " << target << ": ";
    if (index != -1) {
        std::cout << "找到，索引 = " << index << std::endl;
    } else {
        std::cout << "未找到" << std::endl;
    }
}

void demonstrateDataStructures() {
    std::cout << "\n=== 数据结构演示 ===" << std::endl;
    
    // 演示链表
    std::cout << "\n链表操作:" << std::endl;
    data_structures::LinkedList<int> list;
    list.pushBack(10);
    list.pushBack(20);
    list.pushFront(5);
    std::cout << "链表大小: " << list.size() << std::endl;
    
    auto frontVal = list.front();
    if (frontVal.has_value()) {
        std::cout << "链表头部元素: " << frontVal.value() << std::endl;
    }
    
    std::cout << "查找元素 20: " << (list.find(20) ? "找到" : "未找到") << std::endl;
    std::cout << "查找元素 99: " << (list.find(99) ? "找到" : "未找到") << std::endl;
    
    // 演示栈
    std::cout << "\n栈操作:" << std::endl;
    data_structures::Stack<int> stack;
    stack.push(1);
    stack.push(2);
    stack.push(3);
    std::cout << "栈大小: " << stack.size() << std::endl;
    
    auto topVal = stack.top();
    if (topVal.has_value()) {
        std::cout << "栈顶元素: " << topVal.value() << std::endl;
    }
    
    stack.pop();
    topVal = stack.top();
    if (topVal.has_value()) {
        std::cout << "弹出后栈顶元素: " << topVal.value() << std::endl;
    }
    
    // 演示队列
    std::cout << "\n队列操作:" << std::endl;
    data_structures::Queue<int> queue;
    queue.enqueue(100);
    queue.enqueue(200);
    queue.enqueue(300);
    std::cout << "队列大小: " << queue.size() << std::endl;
    
    auto frontQueueVal = queue.front();
    if (frontQueueVal.has_value()) {
        std::cout << "队首元素: " << frontQueueVal.value() << std::endl;
    }
    
    auto backQueueVal = queue.back();
    if (backQueueVal.has_value()) {
        std::cout << "队尾元素: " << backQueueVal.value() << std::endl;
    }
    
    queue.dequeue();
    frontQueueVal = queue.front();
    if (frontQueueVal.has_value()) {
        std::cout << "出队后队首元素: " << frontQueueVal.value() << std::endl;
    }
}

int main() {
    std::cout << "CMake GitHub Actions Demo - 主应用程序" << std::endl;
    std::cout << "==========================================" << std::endl;
    
    demonstrateAlgorithms();
    demonstrateDataStructures();
    
    std::cout << "\n程序执行完成！" << std::endl;
    return 0;
}
