# 构建指南

## 基本构建

```bash
# Debug 构建 (推荐开发时使用)
cmake -B build -DCMAKE_BUILD_TYPE=Debug
cmake --build build -j

# Release 构建
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
```

## CMake 选项

| 选项 | 默认值 | 说明 |
|------|--------|------|
| `BUILD_TESTING` | ON | 构建测试 |
| `ENABLE_WARNINGS` | ON | 启用编译器警告 |

```bash
# 禁用测试
cmake -B build -DBUILD_TESTING=OFF

# 禁用警告
cmake -B build -DENABLE_WARNINGS=OFF
```

## 输出路径

- 可执行文件: `build/bin/`
- 库文件: `build/lib/`

## 编译器要求

- GCC 7+ / Clang 5+ / MSVC 2017+
- 必须支持 C++17

## 代码覆盖率构建

```bash
cmake -B build -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_FLAGS="--coverage"
cmake --build build
ctest --test-dir build
lcov --capture --directory build --output-file coverage.info
```

## 清理构建

```bash
rm -rf build
```
