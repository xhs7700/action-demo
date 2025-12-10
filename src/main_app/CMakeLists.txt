# main_app 可执行文件
add_executable(main_app
    main.cpp
)

# 链接库
target_link_libraries(main_app
    PRIVATE
        Demo::algorithms
        Demo::data_structures
)

# 应用编译器警告（如果启用）
if(ENABLE_WARNINGS AND COMMAND set_compiler_warnings)
    set_compiler_warnings(main_app)
endif()
