# CMake GitHub Actions Demo

[![CI](https://github.com/YOUR_USERNAME/action-demo/workflows/CI/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)

一个使用 CMake 构建系统的 C++ 示例项目，完整展示 GitHub Actions CI/CD 工作流的最佳实践。

## 项目概述

本项目包含：
- **2 个 C++ 库模块**：`algorithms`（排序、搜索、字符串和动态规划算法）和 `data_structures`（基础和高级数据结构）
- **2 个可执行文件**：`main_app`（演示程序）和 `cli_tool`（命令行工具）
- **完整的单元测试套件**：使用 Google Test 框架
- **跨平台 CI/CD**：支持 Linux、macOS 和 Windows

## 技术栈

- **C++17** 标准
- **CMake 3.14+** 构建系统
- **Google Test 1.14.0** 测试框架
- **GitHub Actions** 持续集成

## 项目结构

```
action-demo/
├── .github/workflows/
│   └── ci.yml                    # GitHub Actions 工作流
├── cmake/
│   ├── CompilerWarnings.cmake    # 编译器警告配置
│   └── GoogleTest.cmake          # Google Test 集成
├── src/
│   ├── algorithms/               # 算法库
│   │   ├── include/algorithms/
│   │   │   ├── sort.h           # 排序算法接口
│   │   │   ├── search.h         # 搜索算法接口
│   │   │   ├── string_algorithms.h # 字符串算法接口
│   │   │   └── dp_algorithms.h  # 动态规划算法接口
│   │   └── src/
│   │       ├── sort.cpp         # 排序算法实现
│   │       ├── search.cpp       # 搜索算法实现
│   │       ├── string_algorithms.cpp # 字符串算法实现
│   │       └── dp_algorithms.cpp # 动态规划算法实现
│   ├── data_structures/         # 数据结构库
│   │   ├── include/data_structures/
│   │   │   ├── linked_list.h    # 链表
│   │   │   ├── stack_queue.h    # 栈和队列
│   │   │   ├── heap.h           # 二叉堆
│   │   │   ├── avl_tree.h       # AVL 平衡树
│   │   │   └── skip_list.h      # 跳表
│   │   └── src/
│   │       ├── linked_list.cpp
│   │       └── stack_queue.cpp
│   ├── main_app/                # 主应用程序
│   │   └── main.cpp
│   └── cli_tool/                # 命令行工具
│       └── cli_main.cpp
├── tests/                       # 单元测试
│   ├── algorithms/
│   │   ├── test_sort.cpp
│   │   ├── test_search.cpp
│   │   ├── test_string_algorithms.cpp
│   │   └── test_dp_algorithms.cpp
│   └── data_structures/
│       ├── test_linked_list.cpp
│       ├── test_stack_queue.cpp
│       ├── test_heap.cpp
│       ├── test_avl_tree.cpp
│       └── test_skip_list.cpp
└── CMakeLists.txt               # 根 CMake 配置
```

## 快速开始

### 前置要求

- CMake 3.14 或更高版本
- C++17 兼容的编译器（GCC 7+, Clang 5+, MSVC 2017+）

### 构建项目

```bash
# 配置构建
cmake -B build -DCMAKE_BUILD_TYPE=Release

# 编译
cmake --build build --config Release

# 运行测试
ctest --test-dir build --config Release --output-on-failure
```

### 运行应用程序

```bash
# 运行主应用程序（演示所有功能）
./build/bin/main_app

# 或在 Windows 上
.\build\Release\bin\main_app.exe

# 运行命令行工具
./build/bin/cli_tool help
./build/bin/cli_tool sort 5 2 8 1 9
./build/bin/cli_tool search 5 1 2 5 8 9
```

## 功能特性

### algorithms 库

- **排序算法**
  - 快速排序 (Quick Sort) - O(n log n) 分治算法
  - 归并排序 (Merge Sort) - O(n log n) 稳定排序
  - 插入排序 (Insertion Sort) - O(n²) 稳定排序，适用于小型数组
  - 选择排序 (Selection Sort) - O(n²) 不稳定排序
  - 冒泡排序 (Bubble Sort) - O(n²) 稳定排序，包含优化

- **搜索算法**
  - 二分查找 (Binary Search) - O(log n)，用于已排序数组
  - 线性查找 (Linear Search) - O(n)，用于任意数组
  - 插值查找 (Interpolation Search) - O(log log n)，适用于均匀分布数据
  - 斐波那契查找 (Fibonacci Search) - O(log n)，使用斐波那契数列

- **字符串算法**
  - KMP字符串匹配 (KMP Search) - O(m+n) 高效字符串搜索
  - 前缀表计算 (Prefix Table) - KMP算法的核心组件

- **动态规划算法**
  - 0-1背包问题 (0-1 Knapsack) - 经典组合优化问题
  - 最长公共子序列 (LCS) - 序列比较和编辑距离

### data_structures 库

#### 基础数据结构

- **链表 (LinkedList)**
  - 支持头部/尾部插入
  - 支持删除和查找操作
  - 使用智能指针管理内存

- **栈 (Stack)**
  - 后进先出 (LIFO) 数据结构
  - 支持 push、pop、top 操作

- **队列 (Queue)**
  - 先进先出 (FIFO) 数据结构
  - 支持 enqueue、dequeue、front、back 操作

#### 高级数据结构

- **二叉堆 (Binary Heap)**
  - 支持最小堆和最大堆配置
  - O(log n) 插入和提取操作
  - O(n) 批量建堆
  - 支持堆排序应用

- **AVL 树 (AVL Tree)**
  - 自平衡二叉搜索树
  - 保证 O(log n) 的搜索、插入和删除
  - 自动旋转平衡（LL、RR、LR、RL）
  - 中序遍历支持

- **跳表 (Skip List)**
  - 概率性数据结构
  - 平均 O(log n) 的搜索、插入和删除
  - 比平衡树实现更简单
  - 多层链表结构

## 测试

项目包含全面的单元测试，覆盖所有核心功能：

```bash
# 运行所有测试
ctest --test-dir build --output-on-failure

# 运行特定测试
./build/bin/algorithms_tests
./build/bin/data_structures_tests
```

测试统计：
- **algorithms 库**：77 测试用例（包含排序、搜索、字符串和动态规划算法）
- **data_structures 库**：40+ 测试用例（包含基础和高级数据结构）

## CI/CD 工作流

GitHub Actions 自动化流程：

- **构建矩阵**：
  - 平台：Ubuntu、macOS、Windows
  - 配置：Debug、Release
  - 总共 6 种组合

- **工作流步骤**：
  1. 检出代码
  2. 配置构建环境
  3. 配置 CMake
  4. 编译项目
  5. 运行测试
  6. 上传构建产物

- **优化**：
  - 使用缓存加速构建
  - 并行编译（-j 4）

## 开发指南

### 添加新的算法

1. 在 `src/algorithms/include/algorithms/` 中添加头文件
2. 在 `src/algorithms/src/` 中实现算法
3. 更新 `src/algorithms/CMakeLists.txt`
4. 在 `tests/algorithms/` 中添加测试

### 添加新的数据结构

1. 在 `src/data_structures/include/data_structures/` 中添加头文件
2. 在 `src/data_structures/src/` 中实现（如果不是模板）
3. 更新 `src/data_structures/CMakeLists.txt`
4. 在 `tests/data_structures/` 中添加测试

## CMake 选项

- `BUILD_TESTING`（默认：ON）：是否构建测试
- `ENABLE_WARNINGS`（默认：ON）：是否启用编译器警告

```bash
# 禁用测试构建
cmake -B build -DBUILD_TESTING=OFF

# 禁用编译器警告
cmake -B build -DENABLE_WARNINGS=OFF
```

## 许可证

本项目仅用于教育和演示目的。

## 贡献

欢迎提交 Issue 和 Pull Request！

## 参考资源

- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [Google Test Documentation](https://google.github.io/googletest/)
- [GitHub Actions Documentation](https://docs.github.com/en/actions)
- [C++17 Features](https://en.cppreference.com/w/cpp/17)