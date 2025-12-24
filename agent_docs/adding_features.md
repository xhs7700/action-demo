# 添加新功能指南

## 添加新算法

1. **创建头文件**: `src/algorithms/include/algorithms/new_algo.h`
   - 声明函数接口
   - 包含必要的文档注释

2. **创建实现**: `src/algorithms/src/new_algo.cpp`
   - 实现算法逻辑
   - 包含头文件: `#include "algorithms/new_algo.h"`

3. **更新 CMakeLists.txt**: `src/algorithms/CMakeLists.txt`
   ```cmake
   add_library(algorithms
       src/sort.cpp
       src/new_algo.cpp  # 添加这行
   )
   ```

4. **添加测试**: `tests/algorithms/test_new_algo.cpp`

5. **更新测试 CMakeLists.txt**: `tests/CMakeLists.txt`

## 添加新数据结构

同上，但路径为 `src/data_structures/`

### 模板类特殊处理

模板类应直接在头文件中实现，不需要 .cpp 文件：
- 参考: `avl_tree.h`, `skip_list.h`, `btreemap.h`

## 代码风格

- 命名空间: `algorithms::` 或 `data_structures::`
- 函数命名: `snake_case`
- 类命名: `PascalCase`
- 使用智能指针管理内存
- 避免裸 `new/delete`

## 验证清单

- [ ] 代码编译无警告
- [ ] 所有测试通过
- [ ] 新功能有测试覆盖
- [ ] 头文件有必要的 include guards
