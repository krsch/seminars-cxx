cmake_minimum_required(VERSION 3.13)
project(seminar CXX)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
set(RANGES_CXX_STD ${CMAKE_CXX_STANDARD} CACHE STRING "")
set(GSL_CXX_STANDARD ${CMAKE_CXX_STANDARD} CACHE STRING "")
add_subdirectory(external/fmt)
add_subdirectory(external/GSL)
add_subdirectory(external/range-v3)
if(NOT MINGW)
    include(cmake/TBBGet.cmake)
    tbb_get(TBB_ROOT tbb_root CONFIG_DIR TBB_DIR)
    add_subdirectory(external/parallelstl)
endif(NOT MINGW)
set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "")
add_subdirectory(external/benchmark)
add_subdirectory(external/pybind11)

add_executable(example example.cpp)
add_executable(example1 example1.cpp)
add_executable(example3 example3.cpp)
add_executable(example3a example3a.cpp)
add_executable(example4 example4.cpp)
add_executable(example5 example5.cpp)
target_link_libraries(example5 PUBLIC range-v3::range-v3 )
add_executable(example6 example6.cpp)
target_link_libraries(example6 PUBLIC fmt::fmt GSL range-v3::range-v3 )
add_executable(fmt1 ex-fmt.cpp)
target_link_libraries(fmt1 PUBLIC fmt::fmt GSL range-v3::range-v3 )
add_executable(inheritance inheritance.cpp)
# add_executable(words words.cpp)
add_executable(words2 words2.cpp)
if(NOT MINGW)
    add_executable(parallel parallel.cpp)
    target_link_libraries(parallel PUBLIC range-v3::range-v3 pstl::ParallelSTL benchmark)
    find_package(Threads)
    add_executable(parallel2 parallel2.cpp)
    target_link_libraries(parallel2 PUBLIC range-v3::range-v3 pstl::ParallelSTL Threads::Threads)
endif(NOT MINGW)

add_executable(fs fs.cpp)
pybind11_add_module(py_cpp py.cpp)

add_executable(cpp cpp.cpp)