# 编译器警告配置
# 为目标添加适当的编译器警告标志

function(set_compiler_warnings target)
    if(MSVC)
        target_compile_options(${target} PRIVATE
            /W4           # 警告级别4
            /WX-          # 警告不视为错误（可根据需要调整）
        )
    else()
        target_compile_options(${target} PRIVATE
            -Wall         # 所有常见警告
            -Wextra       # 额外警告
            -Wpedantic    # 严格的ISO C++
            # -Werror     # 可选：将警告视为错误
        )
    endif()
endfunction()
