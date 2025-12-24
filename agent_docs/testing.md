# 测试指南

## 运行测试

```bash
# 运行所有测试
ctest --test-dir build --output-on-failure

# 运行特定测试可执行文件
./build/bin/algorithms_tests
./build/bin/data_structures_tests

# 运行特定测试用例 (Google Test 过滤器)
./build/bin/algorithms_tests --gtest_filter="*Sort*"
./build/bin/data_structures_tests --gtest_filter="AVLTreeTest.*"
```

## 测试目录结构

```
tests/
├── algorithms/
│   ├── test_sort.cpp
│   ├── test_search.cpp
│   ├── test_string_algorithms.cpp
│   └── test_dp_algorithms.cpp
└── data_structures/
    ├── test_linked_list.cpp
    ├── test_stack_queue.cpp
    ├── test_heap.cpp
    ├── test_avl_tree.cpp
    ├── test_skip_list.cpp
    └── test_btreemap.cpp
```

## 编写新测试

1. 在对应模块目录下创建 `test_xxx.cpp`
2. 使用 Google Test 框架:

```cpp
#include <gtest/gtest.h>
#include "module/header.h"

TEST(TestSuiteName, TestName) {
    // Arrange
    // Act
    // Assert
    EXPECT_EQ(expected, actual);
}
```

3. 在 `tests/CMakeLists.txt` 中添加源文件

## 测试命名规范

- 测试套件名: `模块名Test` (如 `AVLTreeTest`)
- 测试用例名: 描述测试内容 (如 `InsertMaintainsBalance`)
