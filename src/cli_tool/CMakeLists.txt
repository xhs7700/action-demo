# cli_tool 可执行文件
add_executable(cli_tool
    cli_main.cpp
)

# 链接库
target_link_libraries(cli_tool
    PRIVATE
        Demo::algorithms
)

# 应用编译器警告（如果启用）
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(cli_tool)
endif()
