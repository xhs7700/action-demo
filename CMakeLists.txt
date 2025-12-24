cmake_minimum_required(VERSION 3.14)
project(CMakeGitHubActionsDemo VERSION 1.0.0 LANGUAGES CXX)

# 生成 compile_commands.json 供 clangd 使用
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 设置 C++ 标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 输出目录配置
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# 选项配置
option(BUILD_TESTING "Build the testing tree" ON)
option(ENABLE_WARNINGS "Enable compiler warnings" ON)

# 导入编译器警告配置
if(ENABLE_WARNINGS)
    include(cmake/CompilerWarnings.cmake)
endif()

# 添加子目录
add_subdirectory(src/algorithms)
add_subdirectory(src/data_structures)
add_subdirectory(src/main_app)
add_subdirectory(src/cli_tool)

# 启用测试
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(tests)
endif()
