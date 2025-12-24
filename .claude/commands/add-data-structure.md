帮助添加新的数据结构到 data_structures 库。

参数: $ARGUMENTS (数据结构名称和简要描述)

执行以下步骤:
1. 先阅读 `agent_docs/adding_features.md` 了解开发规范
2. 在 `src/data_structures/include/data_structures/` 创建头文件
3. 如果不是模板类，在 `src/data_structures/src/` 创建实现文件
4. 更新 `src/data_structures/CMakeLists.txt`
5. 在 `tests/data_structures/` 创建测试文件
6. 更新 `tests/CMakeLists.txt`
7. 构建并运行测试验证
