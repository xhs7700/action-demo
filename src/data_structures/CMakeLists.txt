# data_structures 库
add_library(data_structures
    src/linked_list.cpp
    src/stack_queue.cpp
    src/heap.cpp
    src/avl_tree.cpp
    src/skip_list.cpp
    src/btreemap.cpp
)

# 设置包含目录
target_include_directories(data_structures
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 应用编译器警告（如果启用）
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(data_structures)
endif()

# 设置库别名
add_library(Demo::data_structures ALIAS data_structures)
