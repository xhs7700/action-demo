# algorithms 库
add_library(algorithms
    src/sort.cpp
    src/search.cpp
    src/string_algorithms.cpp
    src/dp_algorithms.cpp
)

# 设置包含目录
target_include_directories(algorithms
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include>
)

# 应用编译器警告（如果启用）
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(algorithms)
endif()

# 设置库别名
add_library(Demo::algorithms ALIAS algorithms)
