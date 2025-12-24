帮助添加新的算法到 algorithms 库。

参数: $ARGUMENTS (算法名称和简要描述)

执行以下步骤:
1. 先阅读 `agent_docs/adding_features.md` 了解开发规范
2. 在 `src/algorithms/include/algorithms/` 创建头文件
3. 在 `src/algorithms/src/` 创建实现文件
4. 更新 `src/algorithms/CMakeLists.txt`
5. 在 `tests/algorithms/` 创建测试文件
6. 更新 `tests/CMakeLists.txt`
7. 构建并运行测试验证
