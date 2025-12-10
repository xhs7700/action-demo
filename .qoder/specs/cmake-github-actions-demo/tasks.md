# CMake GitHub Actions Demo - 任务清单

## 阶段 1：项目脚手架
- [x] 创建完整目录结构（.github/workflows/, cmake/, src/, tests/）
- [x] 创建 .gitignore 文件
- [x] 创建根 CMakeLists.txt 基础配置
- [x] 创建 cmake/CompilerWarnings.cmake

## 阶段 2：库实现
- [x] 实现 algorithms 库（sort.h, search.h, sort.cpp, search.cpp）
- [x] 配置 src/algorithms/CMakeLists.txt
- [x] 实现 data_structures 库（linked_list.h, stack_queue.h, linked_list.cpp, stack_queue.cpp）
- [x] 配置 src/data_structures/CMakeLists.txt

## 阶段 3：可执行文件
- [x] 实现 src/main_app/main.cpp
- [x] 配置 src/main_app/CMakeLists.txt
- [x] 实现 src/cli_tool/cli_main.cpp
- [x] 配置 src/cli_tool/CMakeLists.txt

## 阶段 4：单元测试
- [x] 创建 cmake/GoogleTest.cmake
- [x] 配置 tests/CMakeLists.txt
- [x] 编写 tests/algorithms/test_sort.cpp（至少5个测试用例）
- [x] 编写 tests/algorithms/test_search.cpp
- [x] 编写 tests/data_structures/test_linked_list.cpp
- [x] 编写 tests/data_structures/test_stack_queue.cpp

## 阶段 5：GitHub Actions
- [x] 创建 .github/workflows/ci.yml（完整CI工作流）
- [x] 配置构建矩阵（3平台 × 2配置）
- [x] 实现产物上传
- [x] 添加缓存优化

## 阶段 6：文档和收尾
- [x] 编写 README.md（项目介绍、构建说明、测试方法、CI说明）
- [x] 验证本地构建成功
- [x] 验证所有测试通过
- [x] 验证可执行文件正常运行