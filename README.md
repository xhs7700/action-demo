# CMake GitHub Actions Demo

[![CI](https://github.com/YOUR_USERNAME/action-demo/workflows/CI/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Code Coverage](https://github.com/YOUR_USERNAME/action-demo/workflows/Code%20Coverage/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![CodeQL](https://github.com/YOUR_USERNAME/action-demo/workflows/CodeQL%20Security%20Scan/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Documentation](https://github.com/YOUR_USERNAME/action-demo/workflows/Documentation/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)
[![Compiler Compatibility](https://github.com/YOUR_USERNAME/action-demo/workflows/Compiler%20Compatibility/badge.svg)](https://github.com/YOUR_USERNAME/action-demo/actions)

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

GitHub Actions 自动化流程包含多个工作流，展示完整的 DevOps 最佳实践：

### 1. 持续集成 (CI)

**文件**: `.github/workflows/ci.yml`

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

### 2. 代码覆盖率 (Code Coverage)

**文件**: `.github/workflows/code-coverage.yml`

- **功能**：
  - 使用 lcov 生成覆盖率报告
  - 上传到 Codecov 平台
  - 在 PR 中自动评论覆盖率百分比
  - 检查覆盖率阈值（80%）
  - 生成 HTML 覆盖率报告

- **触发条件**：push 到主分支、PR

### 3. 安全扫描 (CodeQL)

**文件**: `.github/workflows/codeql.yml`

- **功能**：
  - 使用 GitHub CodeQL 进行静态应用安全测试（SAST）
  - 检测常见安全漏洞（缓冲区溢出、内存泄漏等）
  - 与 GitHub Security 标签集成
  - 生成 SARIF 报告

- **触发条件**：push、PR、每周一定时运行

- **扫描范围**：
  - security-and-quality 查询集
  - C++ 特定安全规则

### 4. 文档生成 (Documentation)

**文件**: `.github/workflows/documentation.yml`

- **功能**：
  - 使用 Doxygen 自动生成 API 文档
  - 生成调用图和类图（使用 Graphviz）
  - 部署到 GitHub Pages
  - 检查未文档化的 API
  - 提供文档质量统计

- **触发条件**：push 到主分支、手动触发

- **访问文档**：部署后可通过 GitHub Pages URL 访问

### 5. 自动发布 (Release)

**文件**: `.github/workflows/release.yml`

- **功能**：
  - 自动创建 GitHub Release
  - 构建多平台发布产物：
    - Linux (tar.gz)
    - macOS (tar.gz)
    - Windows (zip)
  - 生成 SHA256 校验和
  - 从 Git 提交历史自动生成发布说明
  - 按类型分组变更（功能、修复、文档等）

- **触发条件**：推送版本标签（v*.*.*）或手动触发

- **使用方法**：
  ```bash
  git tag -a v1.0.0 -m "Release version 1.0.0"
  git push origin v1.0.0
  ```

### 6. 编译器兼容性测试 (Compiler Compatibility)

**文件**: `.github/workflows/compiler-compatibility.yml`

- **功能**：
  - 测试多个编译器版本和 C++ 标准组合
  - 确保广泛的编译器兼容性
  - 使用 Docker 容器保证环境一致性

- **测试矩阵**：
  - **GCC**: 9, 10, 11, 12, 13
  - **Clang**: 12, 13, 14, 15, 16
  - **MSVC**: 2019, 2022
  - **C++ 标准**: C++17, C++20

- **触发条件**：push、PR、每周日定时运行

### 工作流总结

| 工作流 | 目的 | 运行频率 | 平台 |
|--------|------|----------|------|
| CI | 构建和测试 | 每次 push/PR | Linux, macOS, Windows |
| Code Coverage | 代码质量指标 | 每次 push/PR | Linux |
| CodeQL | 安全扫描 | push/PR/每周 | Linux |
| Documentation | API 文档 | push 到主分支 | Linux |
| Release | 发布管理 | 版本标签 | Linux, macOS, Windows |
| Compiler Compatibility | 编译器测试 | push/PR/每周 | Linux, Windows |

### 配置要求

某些工作流需要额外的配置：

1. **Codecov** (可选)：
   - 在 [codecov.io](https://codecov.io) 注册并获取 token
   - 在仓库设置中添加 `CODECOV_TOKEN` secret

2. **GitHub Pages**：
   - 在仓库设置中启用 GitHub Pages
   - 设置源为 "GitHub Actions"

3. **Release**：
   - 确保仓库有 `GITHUB_TOKEN` 权限（默认已启用）

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