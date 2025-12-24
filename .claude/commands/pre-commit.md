提交前检查清单。

执行以下步骤:
1. 构建项目: `cmake --build build -j`
2. 运行所有测试: `ctest --test-dir build --output-on-failure`
3. 检查是否有未处理的 TODO 或 FIXME
4. 运行 `git status` 确认变更范围
5. 如果全部通过，提示可以安全提交
6. 如果有失败，详细说明需要修复的问题
