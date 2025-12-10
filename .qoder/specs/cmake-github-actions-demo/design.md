# CMake GitHub Actions Demo - 设计文档

## 1. 项目概述

### 1.1 项目目标
创建一个使用 CMake 构建系统的 C++ 示例项目，完整展示 GitHub Actions CI/CD 工作流的最佳实践。该项目将作为学习资源，演示如何：
- 使用现代 CMake 组织中等复杂度的 C++ 项目
- 集成单元测试框架（Google Test）
- 配置跨平台的 GitHub Actions 工作流
- 自动化构建、测试和产物管理

### 1.2 项目范围
**包含内容：**
- 2 个独立的 C++ 库模块（algorithms、data_structures）
- 2 个可执行文件（main_app、cli_tool）
- 完整的单元测试套件（使用 Google Test）
- 跨平台 GitHub Actions 工作流（Linux、macOS、Windows）
- CMake 构建配置（主项目 + 子模块）
- 构建产物管理和上传

**不包含内容：**
- 生产级代码优化
- 完整的文档系统（Doxygen）
- 代码覆盖率报告（可作为后续扩展）
- 自动发布流程

### 1.3 技术栈选择

| 技术组件 | 选择 | 理由 |
|---------|------|------|
| **编程语言** | C++17 | 现代特性支持，广泛的编译器兼容性 |
| **构建系统** | CMake 3.14+ | 业界标准，跨平台支持优秀 |
| **测试框架** | Google Test (GTest) | 成熟稳定，功能完善，易于集成 |
| **CI/CD** | GitHub Actions | 原生集成，免费额度充足，配置灵活 |
| **编译器** | GCC/Clang/MSVC | 覆盖主流平台的标准编译器 |

### 1.4 预期学习价值
完成此项目后，开发者将学会：
1. ✅ 使用 CMake 组织多模块 C++ 项目
2. ✅ 集成 Google Test 进行单元测试
3. ✅ 配置跨平台的 GitHub Actions 工作流
4. ✅ 实现自动化构建、测试和产物上传
5. ✅ 使用构建缓存优化 CI 性能
6. ✅ 处理跨平台编译差异

---

## 2. 项目结构设计

### 2.1 完整目录结构

```
cmake-github-actions-demo/
├── .github/
│   └── workflows/
│       └── ci.yml                 # GitHub Actions 主工作流
├── cmake/
│   ├── GoogleTest.cmake           # Google Test 依赖管理
│   └── CompilerWarnings.cmake     # 编译器警告配置
├── src/
│   ├── algorithms/
│   │   ├── CMakeLists.txt         # algorithms 库构建配置
│   │   ├── include/
│   │   │   └── algorithms/
│   │   │       ├── sort.h         # 排序算法接口
│   │   │       └── search.h       # 搜索算法接口
│   │   └── src/
│   │       ├── sort.cpp           # 排序算法实现
│   │       └── search.cpp         # 搜索算法实现
│   ├── data_structures/
│   │   ├── CMakeLists.txt         # data_structures 库构建配置
│   │   ├── include/
│   │   │   └── data_structures/
│   │   │       ├── linked_list.h  # 链表接口
│   │   │       └── stack_queue.h  # 栈和队列接口
│   │   └── src/
│   │       ├── linked_list.cpp    # 链表实现
│   │       └── stack_queue.cpp    # 栈和队列实现
│   ├── main_app/
│   │   ├── CMakeLists.txt         # main_app 可执行文件配置
│   │   └── main.cpp               # 主应用程序入口
│   └── cli_tool/
│       ├── CMakeLists.txt         # cli_tool 可执行文件配置
│       └── cli_main.cpp           # CLI 工具入口
├── tests/
│   ├── CMakeLists.txt             # 测试总配置
│   ├── algorithms/
│   │   ├── test_sort.cpp          # 排序算法测试
│   │   └── test_search.cpp        # 搜索算法测试
│   └── data_structures/
│       ├── test_linked_list.cpp   # 链表测试
│       └── test_stack_queue.cpp   # 栈和队列测试
├── CMakeLists.txt                 # 根 CMake 配置
├── .gitignore                     # Git 忽略文件
└── README.md                      # 项目说明文档
```

### 2.2 源代码组织原则

**库模块设计（algorithms / data_structures）：**
- 采用经典的 `include/` 和 `src/` 分离
- 头文件放在 `include/<库名>/` 子目录，方便 `#include <库名/头文件.h>`
- 实现文件放在 `src/` 目录
- 每个库独立的 `CMakeLists.txt`

**可执行文件设计（main_app / cli_tool）：**
- 每个可执行文件独立目录
- 包含独立的 `CMakeLists.txt`
- 链接所需的库模块

**测试组织：**
- 镜像 `src/` 的结构
- 每个库对应独立的测试目录
- 测试文件命名：`test_<功能名>.cpp`

---

## 3. CMake 配置设计

### 3.1 根 CMakeLists.txt 设计

```cmake
cmake_minimum_required(VERSION 3.14)
project(CMakeGitHubActionsDemo VERSION 1.0.0 LANGUAGES CXX)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录配置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 选项配置
option(BUILD_TESTING "Build the testing tree" ON)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# 导入编译器警告配置
if(ENABLE_WARNINGS)
    include(cmake/CompilerWarnings.cmake)
endif()

# 添加子目录
add_subdirectory(src/algorithms)
add_subdirectory(src/data_structures)
add_subdirectory(src/main_app)
add_subdirectory(src/cli_tool)

# 启用测试
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
```

**设计要点：**
- CMake 最低版本 3.14（支持 FetchContent）
- 统一输出目录，便于产物收集
- 提供构建选项开关
- 清晰的子目录组织

### 3.2 库模块 CMakeLists.txt 设计

**algorithms 库示例：**

```cmake
# src/algorithms/CMakeLists.txt
add_library(algorithms
    src/sort.cpp
    src/search.cpp
)

# 设置包含目录
target_include_directories(algorithms
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 应用编译器警告（如果启用）
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(algorithms)
endif()

# 设置库别名
add_library(Demo::algorithms ALIAS algorithms)
```

**设计要点：**
- 使用 `add_library` 创建库目标
- `target_include_directories` 使用生成器表达式，支持构建和安装
- 创建别名（Alias），便于统一引用
- data_structures 库采用相同模式

### 3.3 可执行文件 CMakeLists.txt 设计

**main_app 示例：**

```cmake
# src/main_app/CMakeLists.txt
add_executable(main_app main.cpp)

target_link_libraries(main_app
    PRIVATE
        Demo::algorithms
        Demo::data_structures
)

# 应用编译器警告
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(main_app)
endif()
```

**cli_tool 示例：**

```cmake
# src/cli_tool/CMakeLists.txt
add_executable(cli_tool cli_main.cpp)

target_link_libraries(cli_tool
    PRIVATE
        Demo::algorithms
        Demo::data_structures
)

if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(cli_tool)
endif()
```

### 3.4 依赖管理策略

**Google Test 集成（cmake/GoogleTest.cmake）：**

```cmake
include(FetchContent)

FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.14.0  # 使用稳定版本
)

# Windows 平台配置
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

# 获取并使用 Google Test
FetchContent_MakeAvailable(googletest)
```

**设计理由：**
- 使用 FetchContent（CMake 3.14+）自动下载依赖
- 无需用户手动安装 Google Test
- 版本锁定，确保可重现构建
- 自动处理 Windows 运行时库问题

### 3.5 编译器警告配置

**cmake/CompilerWarnings.cmake：**

```cmake
function(set_compiler_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4           # 警告级别 4
            /WX           # 警告视为错误
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall         # 所有警告
            -Wextra       # 额外警告
            -Wpedantic    # 严格标准检查
            -Werror       # 警告视为错误
        )
    endif()
endfunction()
```

**设计要点：**
- 跨平台兼容（MSVC vs GCC/Clang）
- 严格的编译警告，确保代码质量
- 函数封装，便于复用

---

## 4. 单元测试设计

### 4.1 测试框架选择：Google Test

**选择理由：**
- ✅ 业界标准，社区支持强大
- ✅ 功能丰富（断言、测试套件、参数化测试等）
- ✅ 良好的 CMake 集成（CTest）
- ✅ 跨平台支持优秀
- ✅ 清晰的测试报告输出

### 4.2 测试 CMakeLists.txt 配置

```cmake
# tests/CMakeLists.txt
include(cmake/GoogleTest.cmake)
include(GoogleTest)

# algorithms 库测试
add_executable(test_algorithms
    algorithms/test_sort.cpp
    algorithms/test_search.cpp
)
target_link_libraries(test_algorithms
    PRIVATE
        Demo::algorithms
        GTest::gtest_main
)
gtest_discover_tests(test_algorithms)

# data_structures 库测试
add_executable(test_data_structures
    data_structures/test_linked_list.cpp
    data_structures/test_stack_queue.cpp
)
target_link_libraries(test_data_structures
    PRIVATE
        Demo::data_structures
        GTest::gtest_main
)
gtest_discover_tests(test_data_structures)
```

**设计要点：**
- 每个库对应独立的测试可执行文件
- 使用 `gtest_discover_tests` 自动发现测试用例
- 链接 `gtest_main`，无需编写 main 函数
- 自动集成到 CTest

### 4.3 测试覆盖范围

**algorithms 库测试：**
| 功能模块 | 测试用例 | 覆盖场景 |
|---------|---------|---------|
| **排序算法** | 快速排序 | 正常数组、空数组、单元素、已排序、逆序 |
| | 归并排序 | 同上 |
| **搜索算法** | 二分查找 | 找到元素、未找到、边界情况 |
| | 线性查找 | 同上 |

**data_structures 库测试：**
| 功能模块 | 测试用例 | 覆盖场景 |
|---------|---------|---------|
| **链表** | 插入操作 | 头插、尾插、中间插入 |
| | 删除操作 | 头删、尾删、中间删除、空链表 |
| | 查找操作 | 找到、未找到 |
| **栈** | 入栈/出栈 | 正常操作、空栈、栈满 |
| **队列** | 入队/出队 | 正常操作、空队列、队列满 |

### 4.4 测试用例示例

**test_sort.cpp 示例：**

```cpp
#include <gtest/gtest.h>
#include <algorithms/sort.h>
#include <vector>

TEST(QuickSortTest, SortsNormalArray) {
    std::vector<int> data = {5, 2, 8, 1, 9};
    std::vector<int> expected = {1, 2, 5, 8, 9};
    
    algorithms::quickSort(data);
    
    EXPECT_EQ(data, expected);
}

TEST(QuickSortTest, HandlesEmptyArray) {
    std::vector<int> data = {};
    algorithms::quickSort(data);
    EXPECT_TRUE(data.empty());
}

TEST(QuickSortTest, HandlesSingleElement) {
    std::vector<int> data = {42};
    algorithms::quickSort(data);
    EXPECT_EQ(data.size(), 1);
    EXPECT_EQ(data[0], 42);
}

TEST(MergeSortTest, SortsReversedArray) {
    std::vector<int> data = {9, 7, 5, 3, 1};
    std::vector<int> expected = {1, 3, 5, 7, 9};
    
    algorithms::mergeSort(data);
    
    EXPECT_EQ(data, expected);
}
```

**test_linked_list.cpp 示例：**

```cpp
#include <gtest/gtest.h>
#include <data_structures/linked_list.h>

TEST(LinkedListTest, InsertAtHead) {
    data_structures::LinkedList<int> list;
    list.insertHead(10);
    list.insertHead(20);
    
    EXPECT_EQ(list.size(), 2);
    EXPECT_EQ(list.front(), 20);
}

TEST(LinkedListTest, DeleteFromEmpty) {
    data_structures::LinkedList<int> list;
    EXPECT_FALSE(list.deleteHead());
    EXPECT_TRUE(list.isEmpty());
}

TEST(LinkedListTest, FindElement) {
    data_structures::LinkedList<int> list;
    list.insertHead(10);
    list.insertHead(20);
    list.insertHead(30);
    
    EXPECT_TRUE(list.find(20));
    EXPECT_FALSE(list.find(99));
}
```

### 4.5 CTest 集成方案

**运行测试：**
```bash
# 构建项目
cmake -B build -S .
cmake --build build

# 运行所有测试
cd build
ctest --output-on-failure

# 运行特定测试
ctest -R test_algorithms -V
```

**CTest 输出示例：**
```
Test project /path/to/build
    Start 1: QuickSortTest.SortsNormalArray
1/8 Test #1: QuickSortTest.SortsNormalArray ......   Passed    0.01 sec
    Start 2: QuickSortTest.HandlesEmptyArray
2/8 Test #2: QuickSortTest.HandlesEmptyArray ........   Passed    0.00 sec
...
100% tests passed, 0 tests failed out of 8
```

---

## 5. GitHub Actions 工作流设计

### 5.1 CI/CD 流程图

```
┌─────────────────────────────────────────────────────────────┐
│                    Push / Pull Request                      │
└───────────────────────┬─────────────────────────────────────┘
                        │
        ┌───────────────┼───────────────┐
        │               │               │
        ▼               ▼               ▼
   ┌─────────┐    ┌─────────┐    ┌──────────┐
   │  Linux  │    │  macOS  │    │ Windows  │
   │ (Ubuntu)│    │         │    │  (MSVC)  │
   └────┬────┘    └────┬────┘    └────┬─────┘
        │              │              │
        ▼              ▼              ▼
   ┌─────────────────────────────────────┐
   │  1. 检出代码 (actions/checkout)      │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  2. 设置编译器和依赖                 │
   │     - Linux: GCC/Clang              │
   │     - macOS: AppleClang             │
   │     - Windows: MSVC                 │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  3. 缓存 CMake 构建文件              │
   │     (actions/cache - 提速 50-70%)   │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  4. 配置 CMake                       │
   │     cmake -B build -S .             │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  5. 构建项目                         │
   │     cmake --build build             │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  6. 运行测试                         │
   │     ctest --output-on-failure       │
   └────────────────┬────────────────────┘
                    ▼
   ┌─────────────────────────────────────┐
   │  7. 上传构建产物                     │
   │     - main_app 可执行文件            │
   │     - cli_tool 可执行文件            │
   │     - 测试报告                       │
   └─────────────────────────────────────┘
```

### 5.2 完整工作流配置

**.github/workflows/ci.yml：**

```yaml
name: CI

on:
  push:
    branches: [ main, develop ]
  pull_request:
    branches: [ main ]

env:
  BUILD_TYPE: Release

jobs:
  build-and-test:
    name: ${{ matrix.os }} - ${{ matrix.compiler }}
    runs-on: ${{ matrix.os }}
    
    strategy:
      fail-fast: false
      matrix:
        include:
          # Linux - GCC
          - os: ubuntu-22.04
            compiler: gcc
            cc: gcc-11
            cxx: g++-11
          
          # Linux - Clang
          - os: ubuntu-22.04
            compiler: clang
            cc: clang-14
            cxx: clang++-14
          
          # macOS
          - os: macos-13
            compiler: clang
            cc: clang
            cxx: clang++
          
          # Windows - MSVC
          - os: windows-2022
            compiler: msvc
            cc: cl
            cxx: cl

    steps:
    - name: 检出代码
      uses: actions/checkout@v4

    - name: 设置编译器环境变量
      if: matrix.os != 'windows-2022'
      run: |
        echo "CC=${{ matrix.cc }}" >> $GITHUB_ENV
        echo "CXX=${{ matrix.cxx }}" >> $GITHUB_ENV

    - name: 安装 CMake (Ubuntu)
      if: runner.os == 'Linux'
      run: |
        sudo apt-get update
        sudo apt-get install -y cmake ninja-build

    - name: 安装 CMake (macOS)
      if: runner.os == 'macOS'
      run: |
        brew install cmake ninja

    - name: 缓存 CMake 构建
      uses: actions/cache@v3
      with:
        path: |
          build/_deps
          build/CMakeCache.txt
          build/CMakeFiles
        key: ${{ runner.os }}-${{ matrix.compiler }}-cmake-${{ hashFiles('**/CMakeLists.txt') }}
        restore-keys: |
          ${{ runner.os }}-${{ matrix.compiler }}-cmake-

    - name: 配置 CMake (Unix)
      if: runner.os != 'Windows'
      run: |
        cmake -B build -S . \
          -DCMAKE_BUILD_TYPE=${{ env.BUILD_TYPE }} \
          -G Ninja

    - name: 配置 CMake (Windows)
      if: runner.os == 'Windows'
      run: |
        cmake -B build -S . `
          -DCMAKE_BUILD_TYPE=${{ env.BUILD_TYPE }}

    - name: 构建项目
      run: cmake --build build --config ${{ env.BUILD_TYPE }}

    - name: 运行测试
      working-directory: build
      run: ctest -C ${{ env.BUILD_TYPE }} --output-on-failure --verbose

    - name: 准备产物 (Unix)
      if: runner.os != 'Windows'
      run: |
        mkdir -p artifacts
        cp build/bin/main_app artifacts/
        cp build/bin/cli_tool artifacts/

    - name: 准备产物 (Windows)
      if: runner.os == 'Windows'
      run: |
        New-Item -ItemType Directory -Force -Path artifacts
        Copy-Item build\bin\${{ env.BUILD_TYPE }}\main_app.exe artifacts\
        Copy-Item build\bin\${{ env.BUILD_TYPE }}\cli_tool.exe artifacts\

    - name: 上传构建产物
      uses: actions/upload-artifact@v4
      with:
        name: build-artifacts-${{ matrix.os }}-${{ matrix.compiler }}
        path: artifacts/
        retention-days: 7
```

### 5.3 构建矩阵配置说明

**矩阵维度：**
| 维度 | 选项 | 说明 |
|------|------|------|
| **操作系统** | ubuntu-22.04, macos-13, windows-2022 | 覆盖主流平台 |
| **编译器** | GCC 11, Clang 14, AppleClang, MSVC | 验证跨编译器兼容性 |
| **构建类型** | Release | 优化构建，接近生产环境 |

**并行执行：**
- 5 个独立任务并行运行
- `fail-fast: false` 确保即使一个失败，其他继续运行
- 总执行时间约 5-10 分钟（取决于缓存）

### 5.4 缓存策略详解

**缓存内容：**
```yaml
path: |
  build/_deps          # FetchContent 下载的依赖（Google Test）
  build/CMakeCache.txt # CMake 配置缓存
  build/CMakeFiles     # CMake 元数据
```

**缓存键策略：**
- **主键：** `{OS}-{编译器}-cmake-{CMakeLists.txt哈希}`
- **回退键：** `{OS}-{编译器}-cmake-`

**性能提升：**
- ✅ 首次构建：~3-5 分钟
- ✅ 缓存命中后：~1-2 分钟
- ✅ 减少 50-70% 构建时间

**缓存失效条件：**
- CMakeLists.txt 文件修改
- 不同操作系统或编译器
- 缓存过期（7 天）

### 5.5 跨平台处理策略

**编译器差异处理：**
```yaml
# Unix 系统：通过环境变量设置
- name: 设置编译器环境变量
  if: matrix.os != 'windows-2022'
  run: |
    echo "CC=${{ matrix.cc }}" >> $GITHUB_ENV
    echo "CXX=${{ matrix.cxx }}" >> $GITHUB_ENV

# Windows：使用默认 MSVC（通过 Visual Studio Generator）
```

**构建系统差异：**
```yaml
# Unix：使用 Ninja（更快）
-G Ninja

# Windows：使用 Visual Studio Generator（默认）
# 无需指定
```

**产物路径差异：**
```bash
# Unix
build/bin/main_app

# Windows
build\bin\Release\main_app.exe
```

### 5.6 可选高级功能（预留扩展）

**代码覆盖率（可后续添加）：**
```yaml
- name: 生成覆盖率报告
  if: matrix.os == 'ubuntu-22.04' && matrix.compiler == 'gcc'
  run: |
    cmake -B build -S . -DCMAKE_BUILD_TYPE=Coverage -DENABLE_COVERAGE=ON
    cmake --build build
    ctest
    lcov --capture --directory . --output-file coverage.info
    
- name: 上传到 Codecov
  uses: codecov/codecov-action@v3
  with:
    files: coverage.info
```

**自动发布（可后续添加）：**
```yaml
release:
  needs: build-and-test
  if: startsWith(github.ref, 'refs/tags/')
  runs-on: ubuntu-latest
  steps:
    - uses: actions/download-artifact@v4
    - name: 创建 Release
      uses: softprops/action-gh-release@v1
      with:
        files: artifacts/**
```

---

## 6. 构建产物规划

### 6.1 产物类型

| 产物类型 | 文件名 | 平台 | 说明 |
|---------|--------|------|------|
| **主程序** | main_app (Unix) / main_app.exe (Windows) | 全平台 | 主应用程序可执行文件 |
| **CLI 工具** | cli_tool (Unix) / cli_tool.exe (Windows) | 全平台 | 命令行工具可执行文件 |
| **静态库** | libalgorithms.a / algorithms.lib | 全平台 | algorithms 库（仅构建，不上传）|
| | libdata_structures.a / data_structures.lib | 全平台 | data_structures 库（仅构建，不上传）|
| **测试可执行文件** | test_algorithms, test_data_structures | 全平台 | 单元测试程序（仅构建，不上传）|

### 6.2 产物命名规范

**格式：** `{程序名}-{平台}-{编译器}`

**示例：**
```
artifacts/
├── linux-gcc/
│   ├── main_app
│   └── cli_tool
├── linux-clang/
│   ├── main_app
│   └── cli_tool
├── macos-clang/
│   ├── main_app
│   └── cli_tool
└── windows-msvc/
    ├── main_app.exe
    └── cli_tool.exe
```

**GitHub Actions artifact 命名：**
- `build-artifacts-ubuntu-22.04-gcc`
- `build-artifacts-ubuntu-22.04-clang`
- `build-artifacts-macos-13-clang`
- `build-artifacts-windows-2022-msvc`

### 6.3 产物保留策略

**GitHub Actions Artifacts：**
- **保留时间：** 7 天（`retention-days: 7`）
- **原因：** 仅用于临时验证，节省存储空间
- **访问：** 通过 Actions 页面下载

**Git Tags Release（可选扩展）：**
- **保留时间：** 永久
- **触发条件：** 推送 Git tag（如 `v1.0.0`）
- **产物打包：** 压缩包形式（.tar.gz / .zip）

### 6.4 产物大小估算

**未优化（Debug）：**
- main_app: ~5-10 MB
- cli_tool: ~5-10 MB
- 测试程序: ~10-15 MB

**优化（Release）：**
- main_app: ~1-2 MB
- cli_tool: ~1-2 MB
- 测试程序: ~2-5 MB

**总产物大小（5 个平台）：**
- 约 20-30 MB（所有平台总和）

---

## 7. 实现细节和最佳实践

### 7.1 代码实现指导

**algorithms 库核心接口：**

```cpp
// include/algorithms/sort.h
#pragma once
#include <vector>

namespace algorithms {

// 快速排序
template <typename T>
void quickSort(std::vector<T>& arr);

// 归并排序
template <typename T>
void mergeSort(std::vector<T>& arr);

} // namespace algorithms
```

**data_structures 库核心接口：**

```cpp
// include/data_structures/linked_list.h
#pragma once
#include <memory>
#include <optional>

namespace data_structures {

template <typename T>
class LinkedList {
public:
    void insertHead(const T& value);
    void insertTail(const T& value);
    bool deleteHead();
    bool deleteTail();
    std::optional<T> front() const;
    bool find(const T& value) const;
    size_t size() const;
    bool isEmpty() const;
    
private:
    struct Node {
        T data;
        std::unique_ptr<Node> next;
    };
    
    std::unique_ptr<Node> head_;
    size_t size_ = 0;
};

} // namespace data_structures
```

### 7.2 错误处理策略

**编译时错误：**
- 使用 `-Werror` 将警告视为错误
- 强制 C++17 标准
- 禁止编译器扩展

**运行时错误：**
- 使用异常处理（标准库异常）
- 边界检查（debug 模式）
- 断言验证（assert）

**测试错误：**
- Google Test 断言失败
- CTest 非零退出码
- GitHub Actions 自动标记失败

### 7.3 性能考虑

**构建性能：**
- ✅ 使用 Ninja（Unix 平台）加速构建
- ✅ 缓存 FetchContent 依赖
- ✅ 并行编译（CMake 自动检测核心数）

**运行时性能：**
- Release 模式启用优化（`-O3` / `/O2`）
- 内联小函数（模板实现）
- 避免不必要的拷贝（move 语义）

### 7.4 跨平台兼容性注意事项

**文件路径：**
- 使用 CMake 路径（正斜杠 `/` 或 CMake 变量）
- 避免硬编码路径分隔符

**编译器特性：**
- 仅使用 C++17 标准特性
- 避免编译器特定扩展
- 测试覆盖所有目标编译器

**行尾符号：**
- 配置 `.gitattributes`（`* text=auto`）
- 自动处理 LF/CRLF 差异

---

## 8. 质量保证

### 8.1 代码质量标准

**编译通过：**
- ✅ 零警告（所有平台）
- ✅ 零错误
- ✅ 符合 C++17 标准

**测试通过：**
- ✅ 所有单元测试通过
- ✅ 测试覆盖核心功能
- ✅ 边界条件测试

**CI 通过：**
- ✅ 所有平台构建成功
- ✅ 所有编译器通过
- ✅ 产物成功上传

### 8.2 文档要求

**代码注释：**
- 公共 API 提供文档注释
- 复杂算法添加实现说明
- 接口合约明确（前置/后置条件）

**README.md 内容：**
- 项目介绍
- 快速开始指南
- 构建指令
- 测试运行方法
- CI 状态徽章
- 目录结构说明

### 8.3 Git 工作流

**分支策略：**
- `main`：稳定版本
- `develop`：开发分支
- `feature/*`：功能分支

**CI 触发条件：**
- `main` 和 `develop` 分支的 push
- 所有针对 `main` 的 Pull Request

---

## 9. 风险评估

### 9.1 潜在风险

| 风险 | 影响 | 缓解策略 |
|------|------|---------|
| **编译器兼容性** | 中 | 构建矩阵覆盖主流编译器，早期发现问题 |
| **依赖下载失败** | 低 | FetchContent 有重试机制，GitHub Actions 网络稳定 |
| **测试不稳定** | 中 | 避免时间依赖测试，确保测试确定性 |
| **产物大小** | 低 | Release 构建优化，仅上传必要文件 |
| **缓存失效** | 低 | 影响构建速度，但不影响正确性 |

### 9.2 依赖风险

**Google Test：**
- 使用固定版本标签（`v1.14.0`）
- 稳定可靠，社区维护活跃

**CMake：**
- 最低版本 3.14（2019 年发布，广泛可用）
- GitHub Actions runner 预装最新版本

**GitHub Actions：**
- 官方维护的 action（checkout, cache, upload-artifact）
- 固定主版本（如 `@v4`），兼容性好

---

## 10. 成功标准

项目成功的标志：

### 10.1 功能完整性
- ✅ 所有库模块正确实现并编译通过
- ✅ 两个可执行文件能正常运行
- ✅ 单元测试覆盖核心功能且全部通过

### 10.2 CI/CD 有效性
- ✅ GitHub Actions 工作流在所有平台通过
- ✅ 构建产物成功上传
- ✅ Pull Request 自动触发 CI 检查

### 10.3 可维护性
- ✅ CMake 配置清晰易懂
- ✅ 代码结构符合最佳实践
- ✅ 文档完整，易于他人理解和使用

### 10.4 教育价值
- ✅ 展示现代 CMake 用法
- ✅ 演示 GitHub Actions 跨平台 CI
- ✅ 提供单元测试集成示例
- ✅ 可作为新项目的模板

---

## 11. 后续扩展方向（可选）

项目完成后，可考虑以下增强：

1. **代码覆盖率报告**
   - 集成 lcov/gcov
   - 上传到 Codecov
   - 添加覆盖率徽章

2. **代码质量工具**
   - Clang-Tidy 静态分析
   - Clang-Format 代码格式化
   - Cppcheck 额外检查

3. **自动发布流程**
   - Tag 触发自动发布
   - 生成 Changelog
   - 跨平台二进制打包

4. **文档生成**
   - Doxygen API 文档
   - GitHub Pages 部署
   - 自动化文档更新

5. **性能基准测试**
   - Google Benchmark 集成
   - 性能回归检测
   - 基准结果可视化

---

## 12. 实施计划

### 12.1 开发阶段划分

**阶段 1：项目脚手架（优先级：高）**
- 创建目录结构
- 配置根 CMakeLists.txt
- 设置 .gitignore 和基本配置

**阶段 2：库实现（优先级：高）**
- 实现 algorithms 库（头文件 + 实现）
- 实现 data_structures 库（头文件 + 实现）
- 配置库的 CMakeLists.txt

**阶段 3：可执行文件（优先级：中）**
- 实现 main_app
- 实现 cli_tool
- 配置可执行文件的 CMakeLists.txt

**阶段 4：单元测试（优先级：高）**
- 配置 Google Test 集成
- 编写 algorithms 库测试
- 编写 data_structures 库测试
- 配置测试 CMakeLists.txt

**阶段 5：GitHub Actions（优先级：高）**
- 编写 ci.yml 工作流
- 配置构建矩阵
- 实现产物上传
- 添加缓存优化

**阶段 6：文档和收尾（优先级：中）**
- 编写 README.md
- 添加 CI 状态徽章
- 最终测试和验证

### 12.2 预估工作量

| 阶段 | 预估时间 | 复杂度 |
|------|---------|--------|
| 阶段 1 | 30 分钟 | 低 |
| 阶段 2 | 2-3 小时 | 中 |
| 阶段 3 | 1 小时 | 低 |
| 阶段 4 | 2-3 小时 | 中 |
| 阶段 5 | 1-2 小时 | 中 |
| 阶段 6 | 1 小时 | 低 |
| **总计** | **7-10 小时** | **中等** |

---

## 13. 附录

### 13.1 参考资源

**CMake：**
- [Modern CMake](https://cliutils.gitlab.io/modern-cmake/)
- [CMake 官方文档](https://cmake.org/documentation/)
- [Effective Modern CMake](https://gist.github.com/mbinna/c61dbb39bca0e4fb7d1f73b0d66a4fd1)

**Google Test：**
- [Google Test Primer](https://google.github.io/googletest/primer.html)
- [Google Test Advanced Guide](https://google.github.io/googletest/advanced.html)

**GitHub Actions：**
- [GitHub Actions 官方文档](https://docs.github.com/en/actions)
- [actions/checkout](https://github.com/actions/checkout)
- [actions/cache](https://github.com/actions/cache)
- [actions/upload-artifact](https://github.com/actions/upload-artifact)

**C++17：**
- [cppreference.com](https://en.cppreference.com/)
- [C++17 特性](https://github.com/AnthonyCalandra/modern-cpp-features#c17)

### 13.2 相关工具版本

| 工具 | 最低版本 | 推荐版本 |
|------|---------|---------|
| CMake | 3.14 | 3.27+ |
| GCC | 7.0 | 11.0+ |
| Clang | 5.0 | 14.0+ |
| MSVC | 2017 | 2022 |
| Google Test | 1.10.0 | 1.14.0 |

---

## 结论

本设计文档提供了一个完整的、可实施的 CMake + GitHub Actions 示例项目方案。该项目：

✅ **技术全面：** 覆盖 CMake、C++17、Google Test、GitHub Actions 核心技术栈  
✅ **跨平台：** 支持 Linux、macOS、Windows 三大平台  
✅ **最佳实践：** 遵循现代 CMake、单元测试、CI/CD 最佳实践  
✅ **教育价值：** 可作为学习资源和项目模板  
✅ **可扩展：** 预留增强空间，支持后续扩展

设计完成后，将通过任务分解文档（tasks.md）指导具体实施。
