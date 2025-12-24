# CLAUDE.md

## 项目概述 (WHY)

C++ 算法与数据结构库，用于学习和演示 GitHub Actions CI/CD 最佳实践。

## 技术栈 (WHAT)

- **语言**: C++17
- **构建**: CMake 3.14+
- **测试**: Google Test 1.14.0
- **CI/CD**: GitHub Actions (多平台、多编译器)

## 代码地图

```
src/
├── algorithms/          # 算法库 (排序、搜索、字符串、DP)
├── data_structures/     # 数据结构库 (链表、栈、队列、堆、AVL、跳表、B树)
├── main_app/           # 演示程序
└── cli_tool/           # 命令行工具
tests/                  # 单元测试 (与 src/ 结构对应)
cmake/                  # CMake 模块
.github/workflows/      # CI/CD 工作流
```

## 核心命令 (HOW)

```bash
# 构建
cmake -B build -DCMAKE_BUILD_TYPE=Debug && cmake --build build -j

# 测试
ctest --test-dir build --output-on-failure

# 运行
./build/bin/main_app
./build/bin/cli_tool help
```

## 开发规范

- 头文件放 `include/模块名/`，实现放 `src/`
- 模板类直接在头文件中实现
- 每个新功能必须有对应测试
- 提交前确保 `ctest` 全部通过

## 扩展文档

详细信息请查阅 `agent_docs/` 目录：
- `building.md` - 构建配置和选项
- `testing.md` - 测试编写指南
- `adding_features.md` - 添加新算法/数据结构
- `ci_workflows.md` - CI/CD 工作流说明
