cmake_minimum_required(VERSION 3.16)
project(hw1_sort LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include_directories(src)

add_executable(hw1_tests tests/correctness.cpp)

if(MSVC)
    target_compile_options(hw1_tests PRIVATE
        $<$<CONFIG:Debug>:/fsanitize=address>
    )
else()
    target_compile_options(hw1_tests PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
        $<$<CONFIG:Debug>:-fno-omit-frame-pointer>
    )
    target_link_options(hw1_tests PRIVATE
        $<$<CONFIG:Debug>:-fsanitize=address>
    )
endif()

add_executable(hw1_bench bench/benchmark.cpp)

if(MSVC)
    target_compile_options(hw1_bench PRIVATE
        $<$<CONFIG:Release>:/O2>
    )
else()
    target_compile_options(hw1_bench PRIVATE
        $<$<CONFIG:Release>:-O2>
    )
endif()
