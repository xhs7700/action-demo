# BTreeMap 设计文档

## 1. 概述

### 1.1 项目背景
本设计文档用于在 `action-demo` C++ 项目的 `data_structures` 库中添加 BTreeMap（B-Tree Map）数据结构的实现。

### 1.2 设计目标
- 实现一个高性能的有序键值对容器
- 提供 O(log n) 的插入、查找、删除操作
- 支持范围查询和有序遍历
- 遵循项目现有的代码风格和架构标准
- 使用智能指针进行内存管理
- 提供完整的单元测试覆盖

### 1.3 B-Tree 特性
- **阶数（Order）**: 4（每个节点最多 3 个键，最少 1 个键；根节点除外可以少于最小键数）
- **平衡性**: 所有叶子节点在同一层
- **自平衡**: 通过节点分裂和合并维护平衡
- **有序性**: 节点内的键按升序排列

---

## 2. 需求分析

### 2.1 功能性需求

#### 2.1.1 基本操作
- `insert(key, value)`: 插入键值对，键重复时更新值
- `find(key)`: 查找指定键，返回 `std::optional<V>`
- `contains(key)`: 检查键是否存在
- `remove(key)`: 删除指定键值对
- `size()`: 获取键值对数量
- `empty()`: 检查是否为空
- `clear()`: 清空所有键值对

#### 2.1.2 范围查询
- `lower_bound(key)`: 查找第一个不小于指定键的元素
- `upper_bound(key)`: 查找第一个大于指定键的元素

#### 2.1.3 迭代器支持
- `begin()`: 返回指向最小键的迭代器
- `end()`: 返回尾后迭代器
- 支持前向迭代（Forward Iterator）
- 支持 C++11 范围 for 循环

#### 2.1.4 辅助操作
- `at(key)`: 访问指定键的值（不存在时抛出异常）
- `operator[](key)`: 访问指定键的值（不存在时插入默认值）

### 2.2 非功能性需求

#### 2.2.1 性能要求
- 插入/查找/删除: O(log n)
- 范围查询: O(log n + k)，k 为结果数量
- 空间复杂度: O(n)

#### 2.2.2 代码质量
- 使用 C++17 标准
- 使用 `std::unique_ptr` 管理节点内存
- 遵循项目命名规范和代码风格
- 支持移动语义优化性能
- 提供详细的 Doxygen 文档注释

#### 2.2.3 测试覆盖
- 单元测试覆盖率 > 90%
- 包含边界条件测试
- 包含压力测试（大数据量）
- 测试节点分裂和合并逻辑

---

## 3. 接口设计

### 3.1 公共 API

```cpp
namespace data_structures {

template<typename K, typename V>
class BTreeMap {
public:
    // 构造和析构
    BTreeMap();
    ~BTreeMap() = default;
    
    // 基本操作
    void insert(const K& key, const V& value);
    void insert(K&& key, V&& value);
    std::optional<V> find(const K& key) const;
    bool contains(const K& key) const;
    bool remove(const K& key);
    void clear() noexcept;
    
    // 容量相关
    size_t size() const noexcept;
    bool empty() const noexcept;
    
    // 访问操作
    V& at(const K& key);
    const V& at(const K& key) const;
    V& operator[](const K& key);
    
    // 范围查询
    std::optional<std::pair<K, V>> lower_bound(const K& key) const;
    std::optional<std::pair<K, V>> upper_bound(const K& key) const;
    
    // 最小/最大值
    std::optional<std::pair<K, V>> findMin() const;
    std::optional<std::pair<K, V>> findMax() const;
    
    // 迭代器
    class Iterator;
    Iterator begin() const;
    Iterator end() const;
    
private:
    // 内部实现（详见第 4 节）
};

} // namespace data_structures
```

### 3.2 迭代器设计

```cpp
template<typename K, typename V>
class BTreeMap<K, V>::Iterator {
public:
    using iterator_category = std::forward_iterator_tag;
    using value_type = std::pair<K, V>;
    using difference_type = std::ptrdiff_t;
    using pointer = const value_type*;
    using reference = const value_type&;
    
    Iterator();
    reference operator*() const;
    pointer operator->() const;
    Iterator& operator++();
    Iterator operator++(int);
    bool operator==(const Iterator& other) const;
    bool operator!=(const Iterator& other) const;
    
private:
    // 内部状态（节点栈 + 当前位置）
};
```

---

## 4. 内部实现设计

### 4.1 节点结构

```cpp
template<typename K, typename V>
struct BTreeNode {
    static constexpr int ORDER = 4;
    static constexpr int MIN_KEYS = ORDER / 2 - 1;      // 1
    static constexpr int MAX_KEYS = ORDER - 1;          // 3
    static constexpr int MAX_CHILDREN = ORDER;          // 4
    
    bool isLeaf;
    int numKeys;
    std::array<std::pair<K, V>, MAX_KEYS> entries;      // 键值对数组
    std::array<std::unique_ptr<BTreeNode>, MAX_CHILDREN> children; // 子节点指针
    
    BTreeNode(bool leaf = true);
    
    bool isFull() const;
    bool isUnderflow() const;
    int findKeyIndex(const K& key) const;
};
```

### 4.2 核心数据成员

```cpp
template<typename K, typename V>
class BTreeMap {
private:
    std::unique_ptr<BTreeNode<K, V>> root_;
    size_t size_;
};
```

---

## 5. 核心算法设计

### 5.1 插入算法

#### 5.1.1 插入流程
1. **查找插入位置**: 从根节点向下递归查找应插入的叶子节点
2. **处理节点满**: 如果节点已满（3 个键），进行分裂操作
3. **插入键值对**: 在叶子节点中插入键值对，保持有序性
4. **更新父节点**: 如果发生分裂，向上传播中间键

#### 5.1.2 节点分裂（Split）
```
分裂前（节点满，3个键）:
[10, 20, 30]

分裂后:
左节点: [10]
中间键: 20（提升到父节点）
右节点: [30]
```

**分裂步骤**:
1. 创建新的右节点
2. 中间键（索引 1）提升到父节点
3. 左节点保留前半部分键（索引 0）
4. 右节点接收后半部分键（索引 2）
5. 如果是内部节点，同时分配子节点指针

#### 5.1.3 伪代码
```cpp
void insert(K key, V value) {
    if (root is full) {
        创建新根节点
        将旧根设为新根的子节点
        分裂旧根
    }
    insertNonFull(root, key, value);
}

void insertNonFull(node, key, value) {
    if (node is leaf) {
        在叶子节点有序插入键值对
    } else {
        找到应下降的子节点索引 i
        if (children[i] is full) {
            分裂 children[i]
            调整索引 i（可能需要改为 i+1）
        }
        递归调用 insertNonFull(children[i], key, value)
    }
}
```

### 5.2 查找算法

#### 5.2.1 查找流程
1. 从根节点开始
2. 在当前节点的键数组中进行二分查找
3. 如果找到匹配的键，返回对应的值
4. 如果是叶子节点且未找到，返回 `std::nullopt`
5. 如果是内部节点，下降到对应的子节点继续查找

#### 5.2.2 伪代码
```cpp
std::optional<V> find(K key) {
    return findHelper(root, key);
}

std::optional<V> findHelper(node, key) {
    int i = 找到第一个 >= key 的索引
    
    if (i < node->numKeys && node->entries[i].first == key) {
        return node->entries[i].second;
    }
    
    if (node->isLeaf) {
        return std::nullopt;
    }
    
    return findHelper(node->children[i], key);
}
```

### 5.3 删除算法

#### 5.3.1 删除流程
删除操作是 B-Tree 中最复杂的操作，需要处理多种情况以维护 B-Tree 的性质。

#### 5.3.2 删除场景

**场景 1: 键在叶子节点中**
- 直接删除键
- 如果删除后节点键数 < MIN_KEYS，需要重新平衡

**场景 2: 键在内部节点中**
- 找到前驱（左子树的最大值）或后继（右子树的最小值）
- 用前驱/后继替换当前键
- 递归删除前驱/后继

**场景 3: 节点键数不足（Underflow）**

##### 3.1 从兄弟节点借键
```
删除前:
父节点: [20]
左兄弟: [5, 10]  当前节点: [15]  (删除 15 后为空)

删除后（从左兄弟借）:
父节点: [10]
左兄弟: [5]  当前节点: [20]
```

##### 3.2 与兄弟节点合并
```
删除前:
父节点: [20, 40]
左节点: [10]  当前节点: [25]  右节点: [50]
(删除 25)

删除后（与左节点合并）:
父节点: [40]
合并节点: [10, 20]  右节点: [50]
```

#### 5.3.3 伪代码
```cpp
bool remove(K key) {
    bool removed = removeHelper(root, key);
    
    if (root->numKeys == 0 && !root->isLeaf) {
        root = root->children[0];
    }
    
    return removed;
}

bool removeHelper(node, key) {
    int i = findKeyIndex(key);
    
    if (i < node->numKeys && node->entries[i].first == key) {
        if (node->isLeaf) {
            removeFromLeaf(node, i);
        } else {
            removeFromNonLeaf(node, i);
        }
        return true;
    }
    
    if (node->isLeaf) {
        return false;
    }
    
    ensureChildHasEnoughKeys(node, i);
    return removeHelper(node->children[i], key);
}

void ensureChildHasEnoughKeys(node, i) {
    if (node->children[i]->numKeys >= MIN_KEYS + 1) {
        return;
    }
    
    if (i > 0 && node->children[i-1]->numKeys > MIN_KEYS) {
        borrowFromLeftSibling(node, i);
    } else if (i < node->numKeys && node->children[i+1]->numKeys > MIN_KEYS) {
        borrowFromRightSibling(node, i);
    } else {
        if (i > 0) {
            mergeWithLeftSibling(node, i);
        } else {
            mergeWithRightSibling(node, i);
        }
    }
}
```

### 5.4 范围查询算法

#### 5.4.1 lower_bound 实现
```cpp
std::optional<std::pair<K, V>> lower_bound(K key) {
    auto it = begin();
    while (it != end()) {
        if (it->first >= key) {
            return *it;
        }
        ++it;
    }
    return std::nullopt;
}
```

#### 5.4.2 upper_bound 实现
```cpp
std::optional<std::pair<K, V>> upper_bound(K key) {
    auto it = begin();
    while (it != end()) {
        if (it->first > key) {
            return *it;
        }
        ++it;
    }
    return std::nullopt;
}
```

### 5.5 迭代器实现

#### 5.5.1 迭代器状态
```cpp
class Iterator {
private:
    struct StackFrame {
        const BTreeNode<K, V>* node;
        int keyIndex;
    };
    
    std::vector<StackFrame> stack_;
    bool isEnd_;
};
```

#### 5.5.2 begin() 实现
```cpp
Iterator begin() const {
    if (!root_) {
        return Iterator(true);  // end iterator
    }
    
    Iterator it;
    auto node = root_.get();
    
    // 下降到最左的叶子节点
    while (!node->isLeaf) {
        it.stack_.push_back({node, 0});
        node = node->children[0].get();
    }
    
    it.stack_.push_back({node, 0});
    return it;
}
```

#### 5.5.3 operator++() 实现
```cpp
Iterator& operator++() {
    if (stack_.empty()) {
        isEnd_ = true;
        return *this;
    }
    
    auto& frame = stack_.back();
    
    if (!frame.node->isLeaf) {
        // 内部节点：下降到右子树
        auto child = frame.node->children[frame.keyIndex + 1].get();
        frame.keyIndex++;
        
        while (!child->isLeaf) {
            stack_.push_back({child, 0});
            child = child->children[0].get();
        }
        stack_.push_back({child, 0});
    } else {
        // 叶子节点：移动到下一个键
        frame.keyIndex++;
        
        while (!stack_.empty() && 
               stack_.back().keyIndex >= stack_.back().node->numKeys) {
            stack_.pop_back();
        }
        
        if (stack_.empty()) {
            isEnd_ = true;
        }
    }
    
    return *this;
}
```

---

## 6. 时间复杂度分析

| 操作 | 平均时间复杂度 | 最坏时间复杂度 |
|------|----------------|----------------|
| insert | O(log n) | O(log n) |
| find | O(log n) | O(log n) |
| remove | O(log n) | O(log n) |
| lower_bound | O(log n + k) | O(log n + k) |
| upper_bound | O(log n + k) | O(log n + k) |
| begin/end | O(log n) | O(log n) |
| operator++ | O(log n) 摊销 | O(log n) |
| size/empty | O(1) | O(1) |

**说明**:
- **n**: 键值对总数
- **k**: 范围查询结果数量
- **log n 的底**: ORDER（本实现中为 4）

---

## 7. 空间复杂度分析

- **总空间**: O(n)
- **节点开销**: 每个节点最多存储 3 个键值对和 4 个子节点指针
- **最坏情况**: 每个节点只存储 1 个键（除了根节点），空间利用率约 33%
- **平均情况**: 每个节点存储 2 个键，空间利用率约 66%

---

## 8. 测试策略

### 8.1 单元测试用例

#### 8.1.1 基本操作测试
```cpp
TEST(BTreeMapTest, BasicOperations) {
    // 测试空树
    // 测试单个插入
    // 测试查找存在/不存在的键
    // 测试大小和空状态
}
```

#### 8.1.2 插入测试
```cpp
TEST(BTreeMapTest, InsertOperations) {
    // 测试顺序插入
    // 测试逆序插入
    // 测试随机插入
    // 测试重复键插入（更新值）
    // 测试触发节点分裂
}
```

#### 8.1.3 删除测试
```cpp
TEST(BTreeMapTest, RemoveOperations) {
    // 测试删除叶子节点的键
    // 测试删除内部节点的键
    // 测试删除触发借键
    // 测试删除触发合并
    // 测试删除不存在的键
    // 测试删除后树的平衡性
}
```

#### 8.1.4 范围查询测试
```cpp
TEST(BTreeMapTest, RangeQueries) {
    // 测试 lower_bound
    // 测试 upper_bound
    // 测试边界条件（最小/最大值）
}
```

#### 8.1.5 迭代器测试
```cpp
TEST(BTreeMapTest, IteratorOperations) {
    // 测试 begin/end
    // 测试范围 for 循环
    // 测试迭代器递增
    // 测试空树的迭代器
    // 测试迭代顺序（应为升序）
}
```

#### 8.1.6 压力测试
```cpp
TEST(BTreeMapTest, StressTest) {
    // 插入 10,000 个随机键值对
    // 验证所有查找操作正确
    // 删除一半元素
    // 验证剩余元素正确
}
```

#### 8.1.7 边界条件测试
```cpp
TEST(BTreeMapTest, EdgeCases) {
    // 测试空树操作
    // 测试单元素树
    // 测试键类型边界值（INT_MIN, INT_MAX）
    // 测试异常情况（at() 访问不存在的键）
}
```

### 8.2 测试覆盖目标
- 代码覆盖率: > 90%
- 分支覆盖率: > 85%
- 所有公共 API 必须有测试
- 所有内部算法路径必须覆盖

---

## 9. 与现有代码集成

### 9.1 文件组织
```
src/data_structures/
├── include/data_structures/
│   └── btreemap.h              # BTreeMap 头文件（模板实现）
└── src/
    └── btreemap.cpp            # 空实现文件（用于 CMake）

tests/data_structures/
└── test_btreemap.cpp           # 单元测试
```

### 9.2 CMakeLists.txt 修改
```cmake
# src/data_structures/CMakeLists.txt
add_library(data_structures
    src/linked_list.cpp
    src/stack_queue.cpp
    src/heap.cpp
    src/avl_tree.cpp
    src/skip_list.cpp
    src/btreemap.cpp           # 新增
)
```

```cmake
# tests/CMakeLists.txt
add_executable(data_structures_tests
    data_structures/test_linked_list.cpp
    data_structures/test_stack_queue.cpp
    data_structures/test_heap.cpp
    data_structures/test_avl_tree.cpp
    data_structures/test_skip_list.cpp
    data_structures/test_btreemap.cpp  # 新增
)
```

### 9.3 代码风格遵循
- **命名规范**: 
  - 类名: `PascalCase` (BTreeMap)
  - 成员变量: `snake_case_` 结尾带下划线 (root_, size_)
  - 函数名: `camelCase` (insert, findMin)
  
- **文档注释**: 使用 Doxygen 格式
  ```cpp
  /**
   * @brief 插入键值对
   * @param key 要插入的键
   * @param value 要插入的值
   * @note 时间复杂度: O(log n)
   */
  ```

- **内存管理**: 使用 `std::unique_ptr` 管理节点
- **异常安全**: 提供基本异常安全保证
- **移动语义**: 支持键值对的移动构造和移动赋值

---

## 10. 实现优先级

### 第一阶段（核心功能）
1. 节点结构定义
2. 插入操作（包括节点分裂）
3. 查找操作
4. 基本测试

### 第二阶段（完整功能）
5. 删除操作（包括借键和合并）
6. 迭代器实现
7. 范围查询操作
8. 完整测试套件

### 第三阶段（优化和完善）
9. 性能优化
10. 异常处理
11. 文档完善
12. 压力测试

---

## 11. 性能优化建议

### 11.1 短期优化
- 使用 `std::array` 存储键值对和子节点，避免动态分配
- 在节点内使用二分查找定位键
- 支持移动语义减少拷贝

### 11.2 长期优化（可选）
- 实现节点内存池，减少分配开销
- 支持自定义比较器
- 添加批量插入接口
- 实现双向迭代器

---

## 12. 风险和限制

### 12.1 已知限制
- 不支持多线程并发访问（需要外部同步）
- 固定阶数（ORDER = 4），不支持运行时配置
- 迭代器不支持双向遍历（仅支持前向）

### 12.2 潜在风险
- 删除操作实现复杂，容易引入 bug
- 节点分裂和合并的边界条件处理需要仔细测试
- 迭代器状态管理可能导致栈溢出（极端深度的树）

---

## 13. 参考资料

### 13.1 算法参考
- Introduction to Algorithms (CLRS), Chapter 18: B-Trees
- [Wikipedia: B-tree](https://en.wikipedia.org/wiki/B-tree)
- C++ STL `std::map` 源码（基于红黑树，但概念类似）

### 13.2 C++ 实践参考
- C++ Core Guidelines
- Effective Modern C++ by Scott Meyers
- 项目现有代码（AVLTree, LinkedList）

---

## 14. 审批和下一步

### 14.1 设计审批
本设计文档需要经过以下审批：
1. ✅ 技术可行性确认
2. ⏳ 用户确认需求
3. ⏳ 代码审查标准确认

### 14.2 下一步行动
1. **等待用户确认**: 确认设计方案是否满足需求
2. **开始实现**: 按照第一阶段优先级开始编码
3. **持续测试**: 边开发边编写单元测试
4. **代码审查**: 完成后进行代码审查

---

**文档版本**: 1.0  
**创建日期**: 2025-12-15  
**最后更新**: 2025-12-15  
**状态**: 待审批
