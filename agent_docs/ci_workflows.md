# CI/CD 工作流说明

## 工作流概览

| 文件 | 目的 | 触发条件 |
|------|------|----------|
| `ci.yml` | 构建和测试 | push, PR |
| `code-coverage.yml` | 代码覆盖率 | push, PR |
| `codeql.yml` | 安全扫描 | push, PR, 每周 |
| `compiler-compatibility.yml` | 编译器兼容性 | push, PR, 每周 |
| `release.yml` | 自动发布 | 版本标签 |

## CI 工作流 (ci.yml)

构建矩阵:
- 平台: Ubuntu, macOS, Windows
- 配置: Debug, Release

## 代码覆盖率 (code-coverage.yml)

- 使用 lcov 生成报告
- 上传到 Codecov
- 阈值: 80%

## 发布工作流 (release.yml)

触发方式:
```bash
git tag -a v1.0.0 -m "Release version 1.0.0"
git push origin v1.0.0
```

产物:
- Linux: tar.gz
- macOS: tar.gz
- Windows: zip
- SHA256 校验和

## 编译器兼容性矩阵

- GCC: 9, 10, 11, 12, 13
- Clang: 12, 13, 14, 15, 16
- MSVC: 2019, 2022
- C++ 标准: C++17, C++20

## 本地模拟 CI

```bash
# 模拟 CI 构建
cmake -B build -DCMAKE_BUILD_TYPE=Release
cmake --build build -j
ctest --test-dir build --output-on-failure
```
