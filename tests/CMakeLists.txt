# 测试总配置
include(${CMAKE_SOURCE_DIR}/cmake/GoogleTest.cmake)

# 包含 Google Test 的测试发现功能
include(GoogleTest)

# 添加测试可执行文件
add_executable(algorithms_tests
    algorithms/test_sort.cpp
    algorithms/test_search.cpp
    algorithms/test_string_algorithms.cpp
    algorithms/test_dp_algorithms.cpp
)

target_link_libraries(algorithms_tests
    PRIVATE
        Demo::algorithms
        gtest_main
)

if(ENABLE_ASAN OR ENABLE_UBSAN)
    enable_sanitizers(algorithms_tests)
endif()

add_executable(data_structures_tests
    data_structures/test_linked_list.cpp
    data_structures/test_stack_queue.cpp
    data_structures/test_heap.cpp
    data_structures/test_avl_tree.cpp
    data_structures/test_skip_list.cpp
    data_structures/test_btreemap.cpp
)

target_link_libraries(data_structures_tests
    PRIVATE
        Demo::data_structures
        gtest_main
)

if(ENABLE_ASAN OR ENABLE_UBSAN)
    enable_sanitizers(data_structures_tests)
endif()

# 发现测试
gtest_discover_tests(algorithms_tests)
gtest_discover_tests(data_structures_tests)